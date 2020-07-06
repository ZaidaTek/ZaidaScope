/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZSCOPE_TEXT_H_INCLUDED
#define ZSCOPE_TEXT_H_INCLUDED

#include "ZScope.h"

#define ZSCOPE_TEXT_LANG_EN 0x0
#define ZSCOPE_TEXT_LANG_DE 0x1
#define ZSCOPE_DEFAULT_TEXT_LANG ZSCOPE_TEXT_LANG_EN

#define ZSCOPE_VERSION "v20200706"

#define ZSCOPE_TEXT_EN_WINDOW_TITLE "ZScope"

#define ZSCOPE_TEXT_EN_MENU_TITLE "ZScope"
#define ZSCOPE_TEXT_EN_MENU_HEAD_DEVICE "Devices"
#define ZSCOPE_TEXT_EN_MENU_HEAD_SETTING "Settings"
#define ZSCOPE_TEXT_EN_MENU_HEAD_HELP "Help"
#define ZSCOPE_TEXT_EN_MENU_HEAD_CREDITS "About"
#define ZSCOPE_TEXT_EN_MENU_HEAD_EXIT "Exit"
#define ZSCOPE_TEXT_EN_MENU_DEVICE_CONNECT "Connect"
#define ZSCOPE_TEXT_EN_MENU_DEVICE_DISCONNECT "Disconnect"
#define ZSCOPE_TEXT_EN_MENU_HELP_DESC "Use MWHEEL or UP/DOWN\nwhile in trigger or cursor\nmenu to adjust levels.\nHold SHIFT for fine adustement.\n\nPress and hold LMOUSE\nto scroll capture while paused or\ntrigger position while in trigger menu."
#define ZSCOPE_TEXT_EN_MENU_CREDITS_DESC "ZScope:\nZaidaTek\nAndreas Riebesehl\n\nlibZDK:\nZaidaTek\nAndreas Riebesehl\n\nLicense:\nCreative Commons BY-ND 4.0"

#define ZSCOPE_TEXT_EN_HUD_MENU "Menu"
#define ZSCOPE_TEXT_EN_HUD_SPEED_PAUSE "Run/Pause"
#define ZSCOPE_TEXT_EN_HUD_SPEED_FASTER ">>"
#define ZSCOPE_TEXT_EN_HUD_SPEED_SLOWER "<<"
#define ZSCOPE_TEXT_EN_HUD_GAME_SPAWN "Spawn"
#define ZSCOPE_TEXT_EN_HUD_GAME_WIPE "Wipe"
#define ZSCOPE_TEXT_EN_HUD_GAME_SAVE "Save"
#define ZSCOPE_TEXT_EN_HUD_TRIGGER_FLANK "Flank"
#define ZSCOPE_TEXT_EN_HUD_TRIGGER_CHUP "+"
#define ZSCOPE_TEXT_EN_HUD_TRIGGER_CHDN "-"
#define ZSCOPE_TEXT_EN_HUD_TRIGGER_MODE "Trigger"

#define ZSCOPE_TEXT_EN_PRINTER_TRIGGER_NONE "off"
#define ZSCOPE_TEXT_EN_PRINTER_TRIGGER_CONT "cont"
#define ZSCOPE_TEXT_EN_PRINTER_TRIGGER_SINGLE "single"
#define ZSCOPE_TEXT_EN_PRINTER_TRIGGER_RISING "rising"
#define ZSCOPE_TEXT_EN_PRINTER_TRIGGER_FALLING "falling"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZSTXT_Load(ZSCOPE_TEXT* iHive, ZT_FLAG iLang);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZSCOPE_TEXT_H_INCLUDED
