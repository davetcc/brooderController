/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "brooderIncubator_menu.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Incubator", "6212819e-acb2-43cc-9982-5574ea4f17c9" };

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystalRenderer renderer(lcd, 16, 2);

// Global Menu Item declarations
const PROGMEM BooleanMenuInfo minfoBuzzer = { "Buzzer", 3, 0xffff, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuBuzzer(&minfoBuzzer, false, NULL);
const PROGMEM BooleanMenuInfo minfoHeatLamp = { "Heat Lamp", 7, 0xffff, 1, NO_CALLBACK, NAMING_TRUE_FALSE };
BooleanMenuItem menuHeatLamp(&minfoHeatLamp, false, &menuBuzzer);
const char enumStrSettingsAutoFan_0[] PROGMEM = "Hourly";
const char enumStrSettingsAutoFan_1[] PROGMEM = "30 mins";
const char enumStrSettingsAutoFan_2[] PROGMEM = "15 mins";
const char enumStrSettingsAutoFan_3[] PROGMEM = "Never";
const char* const enumStrSettingsAutoFan[] PROGMEM  = { enumStrSettingsAutoFan_0, enumStrSettingsAutoFan_1, enumStrSettingsAutoFan_2, enumStrSettingsAutoFan_3 };
const PROGMEM EnumMenuInfo minfoSettingsAutoFan = { "Auto Fan", 10, 0xffff, 3, NO_CALLBACK, enumStrSettingsAutoFan };
EnumMenuItem menuSettingsAutoFan(&minfoSettingsAutoFan, 0, NULL);
const PROGMEM AnalogMenuInfo minfoSettingsMaxTemp = { "Max Temp", 9, 0xffff, 255, NO_CALLBACK, 0, 1, "oC" };
AnalogMenuItem menuSettingsMaxTemp(&minfoSettingsMaxTemp, 0, &menuSettingsAutoFan);
const char enumStrSettingsMode_0[] PROGMEM = "Brooder";
const char enumStrSettingsMode_1[] PROGMEM = "Incubator";
const char* const enumStrSettingsMode[] PROGMEM  = { enumStrSettingsMode_0, enumStrSettingsMode_1 };
const PROGMEM EnumMenuInfo minfoSettingsMode = { "Mode", 8, 0xffff, 1, NO_CALLBACK, enumStrSettingsMode };
EnumMenuItem menuSettingsMode(&minfoSettingsMode, 0, &menuSettingsMaxTemp);
const PROGMEM AnalogMenuInfo minfoSettingsAccuracy = { "Accuracy", 6, 4, 95, NO_CALLBACK, 90, 1, "%" };
AnalogMenuItem menuSettingsAccuracy(&minfoSettingsAccuracy, 0, &menuSettingsMode);
const PROGMEM AnalogMenuInfo minfoSettingsReqdTemp = { "Reqd Temp", 5, 2, 255, NO_CALLBACK, 0, 1, "oC" };
AnalogMenuItem menuSettingsReqdTemp(&minfoSettingsReqdTemp, 0, &menuSettingsAccuracy);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoSettings = { "Settings", 4, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuSettingsReqdTemp);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, &menuHeatLamp);
const PROGMEM BooleanMenuInfo minfoFan = { "Fan", 2, 0xffff, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuFan(&minfoFan, false, &menuSettings);
const PROGMEM AnalogMenuInfo minfoTemp = { "Temp", 1, 0xffff, 255, NO_CALLBACK, 0, 1, "oC" };
AnalogMenuItem menuTemp(&minfoTemp, 0, &menuFan);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).

    // Now add any readonly, non-remote and visible flags.
    menuHeatLamp.setReadOnly(true);

    // Code generated by plugins.
    lcd.begin(16, 2);
    renderer.setUpdatesPerSecond(4);
    lcd.configureBacklightPin(10);
    lcd.backlight();
    switches.init(internalDigitalIo(), SWITCHES_POLL_EVERYTHING, true);
    menuMgr.initForEncoder(&renderer, &menuTemp, 2, A3, A2);
}
