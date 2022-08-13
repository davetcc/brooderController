#include "brooderIncubator_menu.h"
#include "DallasTemperature.h"

#define PWR_OFF_DETECT 3
#define HEATER_PIN 13
#define SPEAKER_PIN 6
#define TEMP_DETECT_PIN 5
#define SAVE_THRESHOLD 60000

OneWire roomTempWire(TEMP_DETECT_PIN);
DallasTemperature roomTemp(&roomTempWire);
bool tempRequested = false;
int currentSpeakerValue = 0;


class SaveEvent : public BaseEvent {
private:
    unsigned long lastSaveMillis = 0;
public:
    void exec() override {
        auto millisNow = millis();
        if((millisNow - lastSaveMillis) > SAVE_THRESHOLD) {
            menuMgr.save(0xfade);
        }
    }

    uint32_t timeOfNextCheck() override {
        return secondsToMillis(1UL);
    }
} saveEvent;

void saveInterruptTriggered() {
    saveEvent.markTriggeredAndNotify();
}

void setup() {
    pinMode(PWR_OFF_DETECT, INPUT);
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, 0);
    digitalWrite(SPEAKER_PIN, 0);

    setupMenu();

    roomTemp.begin();
    roomTemp.setWaitForConversion(false);
    taskManager.scheduleFixedRate(1000, []() {
        if(tempRequested) {
            float deg = roomTemp.getTempCByIndex(0);
            if(deg > 0.0F) {
                tempRequested = false;

                auto allowableError = menuSettingsAccuracy.getAsFloatingPointValue();
                auto tempUser = menuSettingsReqdTemp.getAsFloatingPointValue();
                bool lampNeeded = deg < (tempUser - allowableError);
                menuHeatLamp.setBoolean(lampNeeded);
                digitalWrite(HEATER_PIN, lampNeeded);
                menuTemp.setFromFloatingPointValue(deg);

                auto unacceptableError = allowableError + 1.5F;
                bool buzzerRequired = deg > (tempUser + unacceptableError) || deg < (tempUser - unacceptableError);
                menuBuzzer.setBoolean(buzzerRequired);
                if(buzzerRequired && menuSettingsEnableBuzzer.getBoolean()) {
                    analogWrite(SPEAKER_PIN, currentSpeakerValue == 128 ? 85 : currentSpeakerValue == 85 ? 0 : 128);
                } else {
                    analogWrite(SPEAKER_PIN, 0);
                }

                return;
            }
        }
        roomTemp.requestTemperatures();
        tempRequested = true;

    });
    
    menuMgr.load(0xfade, []() {
        menuSettingsAccuracy.setCurrentValue(3);
        menuSettingsReqdTemp.setCurrentValue(62);
    });

    attachInterrupt(PWR_OFF_DETECT, saveInterruptTriggered, CHANGE);

    taskManager.registerEvent(&saveEvent);
}

void loop() {
    taskManager.runLoop();
}

const char pgmSavedText[] = "Settings saved";

void CALLBACK_FUNCTION onSaveSettings(int /*id*/) {
    menuMgr.save(0xfade);
    auto dlg = renderer.getDialog();
    if(dlg->isInUse()) return;
    dlg->setButtons(BTNTYPE_CLOSE, BTNTYPE_NONE);
    dlg->show(pgmSavedText, false);
}
