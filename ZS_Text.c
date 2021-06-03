/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_TEXT_C_INCLUDED
#define ZS_TEXT_C_INCLUDED

#include "ZS.h"

void ZS_TextLoad(ZT_FLAG iLang) {
    switch (iLang) {
        default:
        case ZSCOPE_TEXT_LANG_EN:
gText[ZSTX_VERSION] = (const ZT_CHAR*)"v210603";
gText[ZSTX_TITLE] = (const ZT_CHAR*)"ZaidaScope";
gText[ZSTX_WINDOW] = (const ZT_CHAR*)"ZaidaScope - v210603";
gText[ZSTX_MN_DEVICE] = (const ZT_CHAR*)"Devices";
gText[ZSTX_MN_HELP] = (const ZT_CHAR*)"Help";
gText[ZSTX_MN_CREDITS] = (const ZT_CHAR*)"Credits";
gText[ZSTX_MN_SETTINGS] = (const ZT_CHAR*)"Settings";
gText[ZSTX_MN_EXIT] = (const ZT_CHAR*)"Exit";
gText[ZSTX_MN_CONNECT] = (const ZT_CHAR*)"Connect";
gText[ZSTX_MN_DISCONNECT] = (const ZT_CHAR*)"Disconnect";
gText[ZSTX_MN_LBL_ADDRESS] = (const ZT_CHAR*)"COM Port";
gText[ZSTX_MN_LBL_SPEED] = (const ZT_CHAR*)"Rate";
gText[ZSTX_MN_LBL_SPEED_R] = (const ZT_CHAR*)"Hz";
gText[ZSTX_MN_LBL_CHANNEL] = (const ZT_CHAR*)"Channels";
gText[ZSTX_MN_LBL_CHANNEL_L] = (const ZT_CHAR*)"A7";
gText[ZSTX_MN_LBL_CHANNEL_R] = (const ZT_CHAR*)"A0";
gText[ZSTX_MN_HELP_DESC] = (const ZT_CHAR*)"Use MWHEEL or UP/DOWN\nwhile in trigger or cursor\nmenu to adjust levels.\nHold SHIFT for fine adustement.\n\nPress and hold LMOUSE\nto scroll capture while paused or\ntrigger position while in trigger menu.";
gText[ZSTX_MN_CREDITS_DESC] = (const ZT_CHAR*)"ZaidaScope:\nZaidaTek\nAndreas Riebesehl\n\nlibZDK:\nZaidaTek\nAndreas Riebesehl\n\nLicense:\nCreative Commons BY-ND 4.0";
gText[ZSTX_MN_SET_RENDER_SYS] = (const ZT_CHAR*)"Renderer: System";
gText[ZSTX_MN_SET_RENDER_GL] = (const ZT_CHAR*)"Renderer: OpenGL";
gText[ZSTX_MN_SET_LANG_EN] = (const ZT_CHAR*)"Language: English";
gText[ZSTX_MN_SET_LANG_DE] = (const ZT_CHAR*)"Sprache: Deutsch";
gText[ZSTX_MN_SET_FPS_MAX] = (const ZT_CHAR*)"FPS-Limit: Uncapped";
gText[ZSTX_MN_SET_FPS_1000] = (const ZT_CHAR*)"FPS-Limit: 1000";
gText[ZSTX_MN_SET_FPS_500] = (const ZT_CHAR*)"FPS-Limit: 500";
gText[ZSTX_MN_SET_FPS_250] = (const ZT_CHAR*)"FPS-Limit: 250";
gText[ZSTX_MN_SET_FPS_200] = (const ZT_CHAR*)"FPS-Limit: 200";
gText[ZSTX_MN_SET_FPS_125] = (const ZT_CHAR*)"FPS-Limit: 125";
gText[ZSTX_MN_SET_FPS_100] = (const ZT_CHAR*)"FPS-Limit: 100";
gText[ZSTX_MN_SET_FPS_50] = (const ZT_CHAR*)"FPS-Limit: 50";
gText[ZSTX_MN_SET_FPS_40] = (const ZT_CHAR*)"FPS-Limit: 40";
gText[ZSTX_MN_SET_FPS_25] = (const ZT_CHAR*)"FPS-Limit: 25";
gText[ZSTX_HD_MENU] = (const ZT_CHAR*)"Menu";
gText[ZSTX_HD_CAPTURE_OFF] = (const ZT_CHAR*)"Resume";
gText[ZSTX_HD_CAPTURE_ON] = (const ZT_CHAR*)"Running";
gText[ZSTX_HD_RECORD_OFF] = (const ZT_CHAR*)"Record";
gText[ZSTX_HD_RECORD_ON] = (const ZT_CHAR*)"Recording";
gText[ZSTX_HD_SELECT_DIA] = (const ZT_CHAR*)"Diagram";
gText[ZSTX_HD_SELECT_TRI] = (const ZT_CHAR*)"Trigger";
gText[ZSTX_HD_SELECT_MES] = (const ZT_CHAR*)"Measure";
gText[ZSTX_HD_SELECT_CUR] = (const ZT_CHAR*)"Cursor";
gText[ZSTX_HD_DIA_TYPE_SCAN] = (const ZT_CHAR*)"Type: Scan";
gText[ZSTX_HD_DIA_TYPE_FIXED] = (const ZT_CHAR*)"Type: Fixed";
gText[ZSTX_HD_DIA_RESET] = (const ZT_CHAR*)"Reset";
gText[ZSTX_HD_DIA_BMP] = (const ZT_CHAR*)"Export BMP";
gText[ZSTX_HD_DIA_PNG] = (const ZT_CHAR*)"Export PNG";
gText[ZSTX_HD_TRI_MODE_NONE] = (const ZT_CHAR*)"Mode: None";
gText[ZSTX_HD_TRI_MODE_CONT] = (const ZT_CHAR*)"Mode: Continuous";
gText[ZSTX_HD_TRI_MODE_SINGLE] = (const ZT_CHAR*)"Mode: Single";
gText[ZSTX_HD_TRI_TYPE_RISING] = (const ZT_CHAR*)"Flank: Rising";
gText[ZSTX_HD_TRI_TYPE_FALLING] = (const ZT_CHAR*)"Flank: Falling";
gText[ZSTX_HD_TRI_CH_1] = (const ZT_CHAR*)"Channel: 1";
gText[ZSTX_HD_TRI_CH_2] = (const ZT_CHAR*)"Channel: 2";
gText[ZSTX_HD_TRI_CH_3] = (const ZT_CHAR*)"Channel: 3";
gText[ZSTX_HD_TRI_CH_4] = (const ZT_CHAR*)"Channel: 4";
gText[ZSTX_HD_TRI_CH_5] = (const ZT_CHAR*)"Channel: 5";
gText[ZSTX_HD_TRI_CH_6] = (const ZT_CHAR*)"Channel: 6";
gText[ZSTX_HD_TRI_CH_7] = (const ZT_CHAR*)"Channel: 7";
gText[ZSTX_HD_TRI_CH_8] = (const ZT_CHAR*)"Channel: 8";
gText[ZSTX_HD_TRI_LBL_HOLDOFF] = (const ZT_CHAR*)"Holdoff";
gText[ZSTX_HD_TRI_LBL_HOLDOFF_R] = (const ZT_CHAR*)"ms";
gText[ZSTX_HD_MES_UNIT_RAW] = (const ZT_CHAR*)"Unit: Raw";
gText[ZSTX_HD_MES_UNIT_PHY] = (const ZT_CHAR*)"Unit: Physical";
gText[ZSTX_HD_CUR_TYPE_NONE] = (const ZT_CHAR*)"Type: Off";
gText[ZSTX_HD_CUR_TYPE_TIME] = (const ZT_CHAR*)"Type: Time";
gText[ZSTX_HD_CUR_TYPE_VOLT] = (const ZT_CHAR*)"Type: Voltage";
gText[ZSTX_HD_CUR_TARGET_1] = (const ZT_CHAR*)"Target: 1";
gText[ZSTX_HD_CUR_TARGET_2] = (const ZT_CHAR*)"Target: 2";
return;
        case ZSCOPE_TEXT_LANG_DE:
gText[ZSTX_VERSION] = (const ZT_CHAR*)"v210603";
gText[ZSTX_TITLE] = (const ZT_CHAR*)"ZaidaScope";
gText[ZSTX_WINDOW] = (const ZT_CHAR*)"ZaidaScope - v210603";
gText[ZSTX_MN_DEVICE] = (const ZT_CHAR*)"Geräte";
gText[ZSTX_MN_HELP] = (const ZT_CHAR*)"Hilfe";
gText[ZSTX_MN_CREDITS] = (const ZT_CHAR*)"Autor";
gText[ZSTX_MN_SETTINGS] = (const ZT_CHAR*)"Einstellungen";
gText[ZSTX_MN_EXIT] = (const ZT_CHAR*)"Beenden";
gText[ZSTX_MN_CONNECT] = (const ZT_CHAR*)"Verbinden";
gText[ZSTX_MN_DISCONNECT] = (const ZT_CHAR*)"Trennen";
gText[ZSTX_MN_LBL_ADDRESS] = (const ZT_CHAR*)"COM Port";
gText[ZSTX_MN_LBL_SPEED] = (const ZT_CHAR*)"Rate";
gText[ZSTX_MN_LBL_SPEED_R] = (const ZT_CHAR*)"Hz";
gText[ZSTX_MN_LBL_CHANNEL] = (const ZT_CHAR*)"Kanäle";
gText[ZSTX_MN_LBL_CHANNEL_L] = (const ZT_CHAR*)"A7";
gText[ZSTX_MN_LBL_CHANNEL_R] = (const ZT_CHAR*)"A0";
gText[ZSTX_MN_HELP_DESC] = (const ZT_CHAR*)"HILFETEXT";
gText[ZSTX_MN_CREDITS_DESC] = (const ZT_CHAR*)"ZaidaScope:\nZaidaTek\nAndreas Riebesehl\n\nlibZDK:\nZaidaTek\nAndreas Riebesehl\n\nLizenz:\nCreative Commons BY-ND 4.0";
gText[ZSTX_MN_SET_RENDER_SYS] = (const ZT_CHAR*)"Grafik: System";
gText[ZSTX_MN_SET_RENDER_GL] = (const ZT_CHAR*)"Grafik: OpenGL";
gText[ZSTX_MN_SET_LANG_EN] = (const ZT_CHAR*)"Language: English";
gText[ZSTX_MN_SET_LANG_DE] = (const ZT_CHAR*)"Sprache: Deutsch";
gText[ZSTX_MN_SET_FPS_MAX] = (const ZT_CHAR*)"FPS-Limit: Unbegrenzt";
gText[ZSTX_MN_SET_FPS_1000] = (const ZT_CHAR*)"FPS-Limit: 1000";
gText[ZSTX_MN_SET_FPS_500] = (const ZT_CHAR*)"FPS-Limit: 500";
gText[ZSTX_MN_SET_FPS_250] = (const ZT_CHAR*)"FPS-Limit: 250";
gText[ZSTX_MN_SET_FPS_200] = (const ZT_CHAR*)"FPS-Limit: 200";
gText[ZSTX_MN_SET_FPS_125] = (const ZT_CHAR*)"FPS-Limit: 125";
gText[ZSTX_MN_SET_FPS_100] = (const ZT_CHAR*)"FPS-Limit: 100";
gText[ZSTX_MN_SET_FPS_50] = (const ZT_CHAR*)"FPS-Limit: 50";
gText[ZSTX_MN_SET_FPS_40] = (const ZT_CHAR*)"FPS-Limit: 40";
gText[ZSTX_MN_SET_FPS_25] = (const ZT_CHAR*)"FPS-Limit: 25";
gText[ZSTX_HD_MENU] = (const ZT_CHAR*)"Menü";
gText[ZSTX_HD_CAPTURE_OFF] = (const ZT_CHAR*)"Fortsetzen";
gText[ZSTX_HD_CAPTURE_ON] = (const ZT_CHAR*)"Aufnahme";
gText[ZSTX_HD_RECORD_OFF] = (const ZT_CHAR*)"Aufzeichnen";
gText[ZSTX_HD_RECORD_ON] = (const ZT_CHAR*)"Aufzeichnung";
gText[ZSTX_HD_SELECT_DIA] = (const ZT_CHAR*)"Diagramm";
gText[ZSTX_HD_SELECT_TRI] = (const ZT_CHAR*)"Trigger";
gText[ZSTX_HD_SELECT_MES] = (const ZT_CHAR*)"Messen";
gText[ZSTX_HD_SELECT_CUR] = (const ZT_CHAR*)"Cursor";
gText[ZSTX_HD_DIA_TYPE_SCAN] = (const ZT_CHAR*)"Typ: Scan";
gText[ZSTX_HD_DIA_TYPE_FIXED] = (const ZT_CHAR*)"Typ: Fixiert";
gText[ZSTX_HD_DIA_RESET] = (const ZT_CHAR*)"Wiederherstellen";
gText[ZSTX_HD_DIA_BMP] = (const ZT_CHAR*)"BMP exportieren";
gText[ZSTX_HD_DIA_PNG] = (const ZT_CHAR*)"PNG exportieren";
gText[ZSTX_HD_TRI_MODE_NONE] = (const ZT_CHAR*)"Modus: Aus";
gText[ZSTX_HD_TRI_MODE_CONT] = (const ZT_CHAR*)"Modus: Kontinuierlich";
gText[ZSTX_HD_TRI_MODE_SINGLE] = (const ZT_CHAR*)"Modus: Einzeln";
gText[ZSTX_HD_TRI_TYPE_RISING] = (const ZT_CHAR*)"Flanke: Steigend";
gText[ZSTX_HD_TRI_TYPE_FALLING] = (const ZT_CHAR*)"Flanke: Fallend";
gText[ZSTX_HD_TRI_CH_1] = (const ZT_CHAR*)"Kanal: 1";
gText[ZSTX_HD_TRI_CH_2] = (const ZT_CHAR*)"Kanal: 2";
gText[ZSTX_HD_TRI_CH_3] = (const ZT_CHAR*)"Kanal: 3";
gText[ZSTX_HD_TRI_CH_4] = (const ZT_CHAR*)"Kanal: 4";
gText[ZSTX_HD_TRI_CH_5] = (const ZT_CHAR*)"Kanal: 5";
gText[ZSTX_HD_TRI_CH_6] = (const ZT_CHAR*)"Kanal: 6";
gText[ZSTX_HD_TRI_CH_7] = (const ZT_CHAR*)"Kanal: 7";
gText[ZSTX_HD_TRI_CH_8] = (const ZT_CHAR*)"Kanal: 8";
gText[ZSTX_HD_TRI_LBL_HOLDOFF] = (const ZT_CHAR*)"Holdoff";
gText[ZSTX_HD_TRI_LBL_HOLDOFF_R] = (const ZT_CHAR*)"ms";
gText[ZSTX_HD_MES_UNIT_RAW] = (const ZT_CHAR*)"Einheit: Roh";
gText[ZSTX_HD_MES_UNIT_PHY] = (const ZT_CHAR*)"Einheit: Physisch";
gText[ZSTX_HD_CUR_TYPE_NONE] = (const ZT_CHAR*)"Typ: Aus";
gText[ZSTX_HD_CUR_TYPE_TIME] = (const ZT_CHAR*)"Typ: Zeitlich";
gText[ZSTX_HD_CUR_TYPE_VOLT] = (const ZT_CHAR*)"Typ: Spannung";
gText[ZSTX_HD_CUR_TARGET_1] = (const ZT_CHAR*)"Cursor: 1";
gText[ZSTX_HD_CUR_TARGET_2] = (const ZT_CHAR*)"Cursor: 2";
return;
    }
}

#endif //ZS_TEXT_C_INCLUDED
