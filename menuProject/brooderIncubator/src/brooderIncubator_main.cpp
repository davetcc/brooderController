#include "brooderIncubator_menu.h"
#include "DallasTemperature.h"

#define FAN_PIN 13
#define PWR_OFF_DETECT 5
#define HEATER_PIN 4
#define SPEAKER_PIN 6
#define TEMP_DETECT_PIN 3

OneWire roomTempWire(TEMP_DETECT_PIN);
DallasTemperature roomTemp(&roomTempWire);
bool tempRequested = false;

volatile bool saveNow = true;
unsigned long saveMillis = 0;

void saveNotification() {
    saveNow = true;
}

enum EnFanMode: uint8_t {
    FAN_AUTO, FAN_MANUAL, FAN_OFF
};

void setup() {
    pinMode(PWR_OFF_DETECT, INPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    digitalWrite(FAN_PIN, 0);
    digitalWrite(HEATER_PIN, 0);
    digitalWrite(SPEAKER_PIN, 0);

    setupMenu();

    roomTemp.begin();
    roomTemp.setWaitForConversion(false);
    taskManager.scheduleFixedRate(1000, []() {
        if(tempRequested) {
            float degc = roomTemp.getTempCByIndex(0);
            if(degc > 0.0F) {
                tempRequested = false;

                auto allowableError = menuSettingsAccuracy.getAsFloatingPointValue();
                auto tempUser = menuSettingsReqdTemp.getAsFloatingPointValue();
                bool lampNeeded = degc < (tempUser - allowableError);
                menuHeatLamp.setBoolean(lampNeeded);
                digitalWrite(HEATER_PIN, lampNeeded);
                menuTemp.setFromFloatingPointValue(degc);

                bool fanRequired = degc > (tempUser + allowableError);
                auto fanMode = (EnFanMode)menuSettingsFanMode.getCurrentValue();
                bool fanOn = fanMode == FAN_MANUAL || (fanMode == FAN_AUTO && fanRequired);
                menuFan.setBoolean(fanOn);
                digitalWrite(FAN_PIN, fanOn);

                auto unacceptableError = allowableError + 1.5F;
                bool buzzerRequired = degc > (tempUser + unacceptableError) || degc < (tempUser - unacceptableError);
                menuBuzzer.setBoolean(buzzerRequired);
                analogWrite(SPEAKER_PIN, buzzerRequired ? 128 : 0);

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

    attachInterrupt(PWR_OFF_DETECT, saveNotification, CHANGE);
}

void loop() {
    taskManager.runLoop();
    if(saveNow && (millis() - saveMillis) < 30000U) {
        saveNow = false;
        saveMillis = millis();
        menuMgr.save(0xfade);
    }
}
