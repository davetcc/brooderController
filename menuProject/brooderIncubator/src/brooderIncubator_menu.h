/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>
#include <LiquidCrystalIO.h>
#include <IoAbstraction.h>
#include <EepromAbstraction.h>
#include "tcMenuLiquidCrystal.h"

// variables we declare that you may need to access
extern const PROGMEM ConnectorLocalInfo applicationInfo;
extern LiquidCrystal lcd;
extern LiquidCrystalRenderer renderer;

// Any externals needed by IO expanders, EEPROMs etc


// Global Menu Item exports
extern ActionMenuItem menuSettingsSaveSettings;
extern BooleanMenuItem menuSettingsEnableBuzzer;
extern EnumMenuItem menuSettingsMode;
extern AnalogMenuItem menuSettingsAccuracy;
extern AnalogMenuItem menuSettingsReqdTemp;
extern BackMenuItem menuBackSettings;
extern SubMenuItem menuSettings;
extern BooleanMenuItem menuBuzzer;
extern BooleanMenuItem menuHeatLamp;
extern AnalogMenuItem menuTemp;

// Provide a wrapper to get hold of the root menu item and export setupMenu
inline MenuItem& rootMenuItem() { return menuTemp; }
void setupMenu();

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION onSaveSettings(int id);

#endif // MENU_GENERATED_CODE_H
