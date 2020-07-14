/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_TEXT_C_INCLUDED
#define ZS_TEXT_C_INCLUDED

#include "ZS_Text.h"

void ZSTXT_Load(ZSCOPE_TEXT* iHive, ZT_FLAG iLang) {
	if (iHive != NULL) {
		switch (iLang) {
            case ZSCOPE_TEXT_LANG_EN:
                iHive->window.title = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_WINDOW_TITLE " - " ZSCOPE_VERSION);
                iHive->menu.title = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_TITLE);
                iHive->menu.head.device = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_HEAD_DEVICE);
                iHive->menu.head.help = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_HEAD_HELP);
                iHive->menu.head.credits = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_HEAD_CREDITS);
                iHive->menu.head.exit = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_HEAD_EXIT);
                iHive->menu.device.connect = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_DEVICE_CONNECT);
                iHive->menu.device.disconnect = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_DEVICE_DISCONNECT);
                iHive->menu.device.label.address.title = (const ZT_CHAR*)"COM Port";
                iHive->menu.device.label.speed.title = (const ZT_CHAR*)"Rate";
                iHive->menu.device.label.speed.right = (const ZT_CHAR*)"Hz";
                iHive->menu.device.label.channel.title = (const ZT_CHAR*)"Channels";
                iHive->menu.device.label.channel.left = (const ZT_CHAR*)"A7";
                iHive->menu.device.label.channel.right = (const ZT_CHAR*)"A0";
                iHive->menu.help.desc = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_HELP_DESC);
                iHive->menu.credits.desc = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_MENU_CREDITS_DESC);
                iHive->hud.menu = (const ZT_CHAR*)(ZSCOPE_TEXT_EN_HUD_MENU);
                iHive->hud.capture.resume = (const ZT_CHAR*)"Resume";
                iHive->hud.capture.running = (const ZT_CHAR*)"Running";
                iHive->hud.selector.diagram = (const ZT_CHAR*)"Diagram";
                iHive->hud.selector.trigger = (const ZT_CHAR*)"Trigger";
                iHive->hud.selector.measure = (const ZT_CHAR*)"Measure";
                iHive->hud.selector.cursor = (const ZT_CHAR*)"Cursor";
                iHive->hud.selector.setting = (const ZT_CHAR*)"Setting";
                iHive->hud.diagram.type.scan = (const ZT_CHAR*)"Type: Scan";
                iHive->hud.diagram.type.fixed = (const ZT_CHAR*)"Type: Fixed";
                iHive->hud.diagram.reset = (const ZT_CHAR*)"Reset";
                iHive->hud.trigger.mode.none = (const ZT_CHAR*)"Mode: None";
                iHive->hud.trigger.mode.cont = (const ZT_CHAR*)"Mode: Continuous";
                iHive->hud.trigger.mode.single = (const ZT_CHAR*)"Mode: Single";
                iHive->hud.trigger.type.rising = (const ZT_CHAR*)"Flank: Rising";
                iHive->hud.trigger.type.falling = (const ZT_CHAR*)"Flank: Falling";
                iHive->hud.trigger.channel.ch1 = (const ZT_CHAR*)"Channel: 1";
                iHive->hud.trigger.channel.ch2 = (const ZT_CHAR*)"Channel: 2";
                iHive->hud.trigger.channel.ch3 = (const ZT_CHAR*)"Channel: 3";
                iHive->hud.trigger.channel.ch4 = (const ZT_CHAR*)"Channel: 4";
                iHive->hud.trigger.channel.ch5 = (const ZT_CHAR*)"Channel: 5";
                iHive->hud.trigger.channel.ch6 = (const ZT_CHAR*)"Channel: 6";
                iHive->hud.trigger.channel.ch7 = (const ZT_CHAR*)"Channel: 7";
                iHive->hud.trigger.channel.ch8 = (const ZT_CHAR*)"Channel: 8";
                iHive->hud.trigger.label.holdoff.title = (const ZT_CHAR*)"Holdoff";
                iHive->hud.trigger.label.holdoff.right = (const ZT_CHAR*)"ms";
                iHive->hud.measure.unit.raw = (const ZT_CHAR*)"Unit: Raw";
                iHive->hud.measure.unit.volt = (const ZT_CHAR*)"Unit: Physical";
                iHive->hud.cursor.type.none = (const ZT_CHAR*)"Type: Off";
                iHive->hud.cursor.type.time = (const ZT_CHAR*)"Type: Time";
                iHive->hud.cursor.type.volt = (const ZT_CHAR*)"Type: Voltage";
                iHive->hud.cursor.target.first = (const ZT_CHAR*)"Target: 1";
                iHive->hud.cursor.target.second = (const ZT_CHAR*)"Target: 2";
                break;
            default:
                break;
        }
    }
}

#endif //ZS_TEXT_C_INCLUDED
