/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZSCOPE_GUI_C_INCLUDED
#define ZSCOPE_GUI_C_INCLUDED

#include "ZScope_GUI.h"
void ZSGUI_InitMenu(void) {
    gGUI.menu.box = ZUI_BoxNew(ZSCOPE_ID_MENU_BOX, NULL, 0x101010bf, 0xffffffff);
    gGUI.menu.title = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.title, gApp.font.title);
    gGUI.menu.head.device = ZUI_ButtonNew(ZSCOPE_ID_MENU_HEAD_DEVICE, NULL, gTxt.menu.head.device);
    gGUI.menu.head.help = ZUI_ButtonNew(ZSCOPE_ID_MENU_HEAD_HELP, NULL, gTxt.menu.head.help);
    gGUI.menu.head.credits = ZUI_ButtonNew(ZSCOPE_ID_MENU_HEAD_CREDITS, NULL, gTxt.menu.head.credits);
    gGUI.menu.head.exit = ZUI_ButtonNew(ZSCOPE_ID_MENU_HEAD_EXIT, NULL, gTxt.menu.head.exit);
    gGUI.menu.device.address = ZUI_IncrementNewDigital(ZSCOPE_ID_MENU_DEVICE_ADDRESS, NULL, 0, 255, ZSCOPE_DEFAULT_ADDRESS);
    gGUI.menu.device.speed = ZUI_IncrementNewPrecision(ZSCOPE_ID_MENU_DEVICE_SPEED, NULL, 100000, 9999999, ZSCOPE_DEFAULT_SPEED, 2);
    gGUI.menu.device.channel = ZUI_SwitchNewArray(ZSCOPE_ID_MENU_DEVICE_CHANNEL, NULL, (const ZT_CHAR*)"O", (const ZT_CHAR*)"I", 8);
    ZUI_DataValue(gGUI.menu.device.channel, ZSCOPE_DEFAULT_CONFIG);
    gGUI.menu.device.connect = ZUI_ButtonNew(ZSCOPE_ID_MENU_DEVICE_CONNECT, NULL, gTxt.menu.device.connect);
    gGUI.menu.device.disconnect = ZUI_ButtonNew(ZSCOPE_ID_MENU_DEVICE_DISCONNECT, NULL, gTxt.menu.device.disconnect);
    gGUI.menu.device.label.address.title = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.address.title, gApp.font.desc);
    gGUI.menu.device.label.speed.title = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.speed.title, gApp.font.desc);
    gGUI.menu.device.label.speed.right = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.speed.right, gApp.font.desc);
    gGUI.menu.device.label.channel.title = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.channel.title, gApp.font.desc);
    gGUI.menu.device.label.channel.left = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.channel.left, gApp.font.desc);
    gGUI.menu.device.label.channel.right = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.device.label.channel.right, gApp.font.desc);
    gGUI.menu.help.desc = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.help.desc, gApp.font.desc);
    gGUI.menu.credits.desc = ZUI_LabelNewFromFont(0, NULL, gTxt.menu.credits.desc, gApp.font.desc);
}
void ZSGUI_InitHUD(void) {
    gGUI.hud.box.top = ZUI_BoxNew(ZSCOPE_ID_HUD_BOX_TOP, NULL, 0x101010bf, 0xffffffff);
    gGUI.hud.box.bottom = ZUI_BoxNew(ZSCOPE_ID_HUD_BOX_BOTTOM, NULL, 0x101010bf, 0xffffffff);
    gGUI.hud.menu = ZUI_ButtonNew(ZSCOPE_ID_HUD_MENU, NULL, gTxt.hud.menu);
    gGUI.hud.capture = ZUI_SwitchNew(ZSCOPE_ID_HUD_CAPTURE, NULL, gTxt.hud.capture.resume, gTxt.hud.capture.running);
    gGUI.hud.selector = ZUI_CycleNew(ZSCOPE_ID_HUD_SELECTOR, NULL, &(gTxt.hud.selector.diagram), 5);
    gGUI.hud.diagram.type = ZUI_CycleNew(ZSCOPE_ID_HUD_DIAGRAM_TYPE, NULL, &(gTxt.hud.diagram.type.scan), 2);
    gGUI.hud.diagram.reset = ZUI_ButtonNew(ZSCOPE_ID_HUD_DIAGRAM_RESET, NULL, gTxt.hud.diagram.reset);
    gGUI.hud.trigger.type = ZUI_CycleNew(ZSCOPE_ID_HUD_TRIGGER_FLANK, NULL, &(gTxt.hud.trigger.type.rising), 2);
    gGUI.hud.trigger.channel = ZUI_CycleNew(ZSCOPE_ID_HUD_TRIGGER_CHANNEL, NULL, &(gTxt.hud.trigger.channel.ch1), 8);
    gGUI.hud.trigger.mode = ZUI_CycleNew(ZSCOPE_ID_HUD_TRIGGER_MODE, NULL, &(gTxt.hud.trigger.mode.none), 3);
    gGUI.hud.trigger.holdoff = ZUI_IncrementNewDigital(ZSCOPE_ID_HUD_TRIGGER_HOLDOFF, NULL, 0, 9999, 0);
    gGUI.hud.trigger.label.holdoff.title = ZUI_LabelNewFromFont(0, NULL, gTxt.hud.trigger.label.holdoff.title, gApp.font.desc);
    gGUI.hud.trigger.label.holdoff.right = ZUI_LabelNewFromFont(0, NULL, gTxt.hud.trigger.label.holdoff.right, gApp.font.desc);
    gGUI.hud.measure.unit = ZUI_CycleNew(ZSCOPE_ID_HUD_MEASURE_UNIT, NULL, &(gTxt.hud.measure.unit.raw), 2);
    gGUI.hud.cursor.type = ZUI_CycleNew(ZSCOPE_ID_HUD_CURSOR_TYPE, NULL, &(gTxt.hud.cursor.type.none), 3);
    gGUI.hud.cursor.target = ZUI_CycleNew(ZSCOPE_ID_HUD_CURSOR_TARGET, NULL, &(gTxt.hud.cursor.target.first), 2);
}
void ZSGUI_Init(void) {
    gApp.font.window = ZTK_FontNew(NULL, (ZT_CHAR*)ZSCOPE_FONT_WINDOW, ZTK_DEFAULT_WINDOW_TEXT_SIZE, ZTM_FONT_STYLE_NORMAL, ZTK_DEFAULT_WINDOW_TEXT_COLOR);
    gApp.font.title = ZTK_FontNew(NULL, (ZT_CHAR*)ZSCOPE_FONT_TITLE, ZTK_DEFAULT_WINDOW_TEXT_SIZE, ZTM_FONT_STYLE_NORMAL | ZTM_FONT_STYLE_ALIGN_CENTER, ZTK_DEFAULT_WINDOW_TEXT_COLOR);
    gApp.font.desc = ZTK_FontNew(NULL, (ZT_CHAR*)ZSCOPE_FONT_TITLE, ZTK_DEFAULT_WINDOW_TEXT_SIZE, ZTM_FONT_STYLE_NORMAL | ZTM_FONT_STYLE_ALIGN_CENTER, ZTK_DEFAULT_WINDOW_TEXT_COLOR);
    ZTK_FontSet(gApp.font.window);
    ZTK_PrinterInit(gApp.font.window);
    ZUI_HostNew();
    ZSGUI_InitMenu();
    ZSGUI_InitHUD();
}
void ZSGUI_SizeMenu(void) {
    ZT_RECT lBox;
    ZT_POINT lButtonSize;
    lButtonSize.x = gApp.rect.window.w * ZSCOPE_WIDTH_MENU / 4;
    lButtonSize.y = gApp.rect.window.h * ZSCOPE_HEIGHT_MENU / 10;
    ZT_I lBoxBorder = (ZT_I)ZUI_GetBorderSize(gGUI.menu.box);
    lBox.w = 4 * lButtonSize.x + 2 * lBoxBorder;
    lBox.h = 10 * lButtonSize.y + 2 * lBoxBorder;
    lBox.x = (gApp.rect.window.w - lBox.w) / 2;
    lBox.y = (gApp.rect.window.h - lBox.h) / 2;
    // MENU SIZE
	ZUI_Rect(gGUI.menu.box, &lBox);
	ZUI_Size(gGUI.menu.title, NULL);
	ZUI_Size(gGUI.menu.head.device, &lButtonSize);
	ZUI_Size(gGUI.menu.head.help, &lButtonSize);
	ZUI_Size(gGUI.menu.head.credits, &lButtonSize);
	ZUI_Size(gGUI.menu.head.exit, &lButtonSize);
	ZUI_Size(gGUI.menu.device.address, NULL);
	ZUI_Size(gGUI.menu.device.speed, NULL);
	ZUI_Size(gGUI.menu.device.channel, &(gApp.dim.button.hudHalf));
	ZUI_Size(gGUI.menu.device.connect, &(gApp.dim.button.hudHalf));
	ZUI_Size(gGUI.menu.device.disconnect, &(gApp.dim.button.hudHalf));
	ZUI_Size(gGUI.menu.device.label.address.title, NULL);
	ZUI_Size(gGUI.menu.device.label.speed.title, NULL);
	ZUI_Size(gGUI.menu.device.label.speed.right, NULL);
	ZUI_Size(gGUI.menu.device.label.channel.title, NULL);
	ZUI_Size(gGUI.menu.device.label.channel.left, NULL);
	ZUI_Size(gGUI.menu.device.label.channel.right, NULL);
	ZUI_Size(gGUI.menu.help.desc, NULL);
	ZUI_Size(gGUI.menu.credits.desc, NULL);
	// MENU POS
	ZUI_PosCenterRelative(gGUI.menu.title, 0.5, (1.0 - ZSCOPE_HEIGHT_MENU) / 4);
	ZUI_PosFromInteger(gGUI.menu.head.device, lBox.x + lBoxBorder, lBox.y + lBox.h - lButtonSize.y - lBoxBorder);
	ZUI_PosFromInteger(gGUI.menu.head.help, lBox.x + lBoxBorder + lButtonSize.x, lBox.y + lBox.h - lButtonSize.y - lBoxBorder);
	ZUI_PosFromInteger(gGUI.menu.head.credits, lBox.x + lBoxBorder + 2 * lButtonSize.x, lBox.y + lBox.h - lButtonSize.y - lBoxBorder);
	ZUI_PosFromInteger(gGUI.menu.head.exit, lBox.x + lBoxBorder + 3 * lButtonSize.x, lBox.y + lBox.h - lButtonSize.y - lBoxBorder);
	ZUI_PosCenterFromInteger(gGUI.menu.device.address, lBox.x + 7 * lBox.w / 14, lBox.y + 3 * lBox.h / 10);
	ZUI_PosCenterFromInteger(gGUI.menu.device.channel, lBox.x + 2 * lBox.w / 7, lBox.y + 6 * lBox.h / 10);
	ZUI_PosCenterFromInteger(gGUI.menu.device.speed, lBox.x + 5 * lBox.w / 7, lBox.y + 6 * lBox.h / 10);
	ZUI_PosCenterFromInteger(gGUI.menu.device.connect, lBox.x + 2 * lBox.w / 7, lBox.y + 8 * lBox.h / 10);
	ZUI_PosCenterFromInteger(gGUI.menu.device.disconnect, lBox.x + 5 * lBox.w / 7, lBox.y + 8 * lBox.h / 10);
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.address.title, ZUI_GetXCenter(gGUI.menu.device.address), ZUI_GetY(gGUI.menu.device.address) - gApp.dim.font);
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.speed.title, ZUI_GetXCenter(gGUI.menu.device.speed), ZUI_GetY(gGUI.menu.device.speed) - gApp.dim.font);
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.speed.right, ZUI_GetXRight(gGUI.menu.device.speed) + gApp.dim.font, ZUI_GetYCenter(gGUI.menu.device.speed));
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.channel.title, ZUI_GetXCenter(gGUI.menu.device.channel), ZUI_GetY(gGUI.menu.device.channel) - gApp.dim.font);
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.channel.left, ZUI_GetX(gGUI.menu.device.channel) - gApp.dim.font, ZUI_GetYCenter(gGUI.menu.device.channel));
	ZUI_PosCenterFromInteger(gGUI.menu.device.label.channel.right, ZUI_GetXRight(gGUI.menu.device.channel) + gApp.dim.font, ZUI_GetYCenter(gGUI.menu.device.channel));
	ZUI_PosCenterFromInteger(gGUI.menu.help.desc, lBox.x + lBox.w / 2, lBox.y + (lBox.h - lButtonSize.y) / 2);
	ZUI_PosCenterFromInteger(gGUI.menu.credits.desc, lBox.x + lBox.w / 2, lBox.y + (lBox.h - lButtonSize.y) / 2);
}
void ZSGUI_SizeHUD(void) {
    ZT_I lWidth = gApp.rect.window.w;
    ZT_I lHeight = gApp.rect.window.h;
    // HUD SIZE
	ZUI_SizeFromInteger(gGUI.hud.box.top, lWidth + 2 * ZUI_GetBorderSize(gGUI.hud.box.top), gApp.dim.button.hud.y + 2 * ZUI_GetBorderSize(gGUI.hud.box.top));
	ZUI_SizeFromInteger(gGUI.hud.box.bottom, lWidth + 2 * ZUI_GetBorderSize(gGUI.hud.box.bottom), 2 * gApp.dim.button.hud.y + 2 * ZUI_GetBorderSize(gGUI.hud.box.bottom));
	ZUI_Size(gGUI.hud.menu, (const ZT_POINT*)&(gApp.dim.button.hudHalf));
	ZUI_Size(gGUI.hud.capture, (const ZT_POINT*)&(gApp.dim.button.hudHalf));
	ZUI_SizeFromInteger(gGUI.hud.selector, gApp.dim.button.hud.x, 2 * gApp.dim.button.hud.y);
	ZUI_Size(gGUI.hud.diagram.type, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.diagram.reset, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.trigger.mode, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.trigger.type, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.trigger.channel, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.trigger.label.holdoff.title, NULL);
	ZUI_Size(gGUI.hud.trigger.label.holdoff.right, NULL);
	ZUI_SizeFromInteger(gGUI.hud.trigger.holdoff, gApp.dim.button.hud.x / 4, 2 * gApp.dim.button.hud.y);
	ZUI_SizeFromInteger(gGUI.hud.measure.unit, gApp.dim.button.hud.x, 2 * gApp.dim.button.hud.y);
	ZUI_Size(gGUI.hud.cursor.type, (const ZT_POINT*)&(gApp.dim.button.hud));
	ZUI_Size(gGUI.hud.cursor.target, (const ZT_POINT*)&(gApp.dim.button.hud));
    // HUD POS
    ZUI_PosFromInteger(gGUI.hud.box.top, -ZUI_GetBorderSize(gGUI.hud.box.top), -ZUI_GetBorderSize(gGUI.hud.box.top));
    ZUI_PosFromInteger(gGUI.hud.box.bottom, -ZUI_GetBorderSize(gGUI.hud.box.bottom), lHeight - 2 * gApp.dim.button.hud.y - ZUI_GetBorderSize(gGUI.hud.box.bottom));
    ZUI_PosFromInteger(gGUI.hud.menu, lWidth - gApp.dim.button.hudHalf.x, 0);
    ZUI_PosFromInteger(gGUI.hud.capture, lWidth - 2 * gApp.dim.button.hudHalf.x, 0);
    ZUI_X(gGUI.hud.selector, 0);
    ZUI_X(gGUI.hud.diagram.type, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.diagram.reset, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.trigger.mode, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.trigger.type, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.trigger.channel, 2 * gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.trigger.holdoff, 7 * gApp.dim.button.hud.x / 2);
    ZUI_XCenter(gGUI.hud.trigger.label.holdoff.title, ZUI_GetX(gGUI.hud.trigger.holdoff) - 2 * gApp.dim.font);
    ZUI_XCenter(gGUI.hud.trigger.label.holdoff.right, ZUI_GetXRight(gGUI.hud.trigger.holdoff) + gApp.dim.font);
    ZUI_X(gGUI.hud.measure.unit, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.cursor.type, gApp.dim.button.hud.x);
    ZUI_X(gGUI.hud.cursor.target, gApp.dim.button.hud.x);
    ZUI_Y(gGUI.hud.selector, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.diagram.type, lHeight - gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.diagram.reset, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.trigger.mode, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.trigger.type, lHeight - gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.trigger.channel, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.trigger.holdoff, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_YCenter(gGUI.hud.trigger.label.holdoff.title, ZUI_GetYCenter(gGUI.hud.trigger.holdoff));
    ZUI_YCenter(gGUI.hud.trigger.label.holdoff.right, ZUI_GetYCenter(gGUI.hud.trigger.holdoff));
    ZUI_Y(gGUI.hud.measure.unit, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.cursor.type, lHeight - 2 * gApp.dim.button.hud.y);
    ZUI_Y(gGUI.hud.cursor.target, lHeight - gApp.dim.button.hud.y);
}
void ZSGUI_Size(void){
    ZT_I lWidth = gApp.rect.window.w;
    ZT_I lHeight = gApp.rect.window.h;
    // CALC SIZES
    if ((gApp.dim.font = lHeight * ZSCOPE_HEIGHT_FONT) > ZSCOPE_HEIGHT_MAX_FONT) {gApp.dim.font = ZSCOPE_HEIGHT_MAX_FONT;}
    if ((gApp.dim.fontTitle = lHeight * ZSCOPE_HEIGHT_FONT_BIG) > ZSCOPE_HEIGHT_MAX_FONT_BIG) {gApp.dim.fontTitle = ZSCOPE_HEIGHT_MAX_FONT_BIG;}
    ZTM_Point(&(gApp.dim.button.hud), lWidth * ZSCOPE_WIDTH_BUTTON, lHeight * ZSCOPE_HEIGHT_BUTTON);
    if (gApp.dim.button.hud.y > ZSCOPE_HEIGHT_MAX_BUTTON) {gApp.dim.button.hud.y = ZSCOPE_HEIGHT_MAX_BUTTON;}
    ZTM_Point(&(gApp.dim.button.hudHalf), lWidth * ZSCOPE_WIDTH_BUTTON / 2, gApp.dim.button.hud.y);
    // FONTS
    ZT_I lYPrinter = (gApp.dim.button.hud.y - gApp.dim.font) / 2; // TOP
    ZTM_Point(&(gApp.pos.fps), lWidth * 0.025, lYPrinter);
    ZTM_Point(&(gApp.pos.daq), lWidth * 0.2, lYPrinter);
    ZTM_Point(&(gApp.pos.trigger), lWidth * 0.4, lYPrinter);
    ZTM_Point(&(gApp.pos.xfer), lWidth * 0.6, lYPrinter);
    lYPrinter = lHeight - gApp.dim.button.hud.y * 1.5; // BOTTOM TOP
    ZTM_Point(&(gApp.pos.measure[0]), gApp.dim.button.hud.x * 2.0 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[1]), gApp.dim.button.hud.x * 2.5 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[2]), gApp.dim.button.hud.x * 3.0 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[3]), gApp.dim.button.hud.x * 3.5 + gApp.dim.button.hud.x / 4, lYPrinter);
    lYPrinter = lHeight - gApp.dim.button.hud.y * 0.5; // BOTTOM BOTTOM
    ZTM_Point(&(gApp.pos.measure[4]), gApp.dim.button.hud.x * 2.0 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[5]), gApp.dim.button.hud.x * 2.5 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[6]), gApp.dim.button.hud.x * 3.0 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTM_Point(&(gApp.pos.measure[7]), gApp.dim.button.hud.x * 3.5 + gApp.dim.button.hud.x / 4, lYPrinter);
    ZTK_FontSize(gApp.font.window, gApp.dim.font);
    ZTK_FontSize(gApp.font.title, gApp.dim.fontTitle);
    ZTK_FontSize(gApp.font.desc, gApp.dim.font);
	ZSGUI_SizeMenu();
	ZSGUI_SizeHUD();
}
void ZSGUI_MenuValues(void) {
    ZSDEV_LoadGUI();
}
void ZSGUI_Menu(void) {
    if (gUsr.menu) {
        ZSGUI_MenuValues();
        for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud) / sizeof(ZUI_ELEMENT*)); i++) {
            ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)&(gGUI.hud) + i);
            ZUI_Bury(lElement);
        }
        ZUI_Restore(gGUI.hud.menu);
        ZUI_Restore(gGUI.menu.box);
        ZUI_Restore(gGUI.menu.title);
        for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.head) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.menu.head) + i));}
        switch (gUsr.menu) {
            case ZSCOPE_MENU_DEVICE:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.device) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.menu.device) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.help) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.help) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.credits) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.credits) + i));}
                break;
            case ZSCOPE_MENU_HELP:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.device) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.device) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.help) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.menu.help) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.credits) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.credits) + i));}
                break;
            case ZSCOPE_MENU_CREDITS:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.device) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.device) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.help) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.menu.help) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu.credits) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.menu.credits) + i));}
                break;
            default:
                break;
        }
    } else {
        for (ZT_INDEX i = 0; i < (sizeof(gGUI.menu) / sizeof(ZUI_ELEMENT*)); i++) {
            ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)&(gGUI.menu) + i);
            ZUI_Bury(lElement);
        }
        ZUI_Restore(gGUI.hud.selector);
        ZUI_Restore(gGUI.hud.menu);
        ZUI_Restore(gGUI.hud.capture);
        switch (ZUI_GetDataValue(gGUI.hud.selector)) {
            case ZSCOPE_HUD_DIAGRAM:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.diagram) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.hud.diagram) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.trigger) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.trigger) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.measure) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.measure) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.cursor) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.cursor) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.setting) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.setting) + i));}
                break;
            case ZSCOPE_HUD_TRIGGER:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.diagram) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.diagram) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.trigger) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.hud.trigger) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.measure) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.measure) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.cursor) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.cursor) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.setting) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.setting) + i));}
                break;
            case ZSCOPE_HUD_MEASURE:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.diagram) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.diagram) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.trigger) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.trigger) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.measure) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.hud.measure) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.cursor) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.cursor) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.setting) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.setting) + i));}
                break;
            case ZSCOPE_HUD_CURSOR:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.diagram) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.diagram) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.trigger) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.trigger) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.measure) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.measure) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.cursor) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.hud.cursor) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.setting) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.setting) + i));}
                break;
            case ZSCOPE_HUD_SETTING:
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.diagram) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.diagram) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.trigger) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.trigger) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.measure) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.measure) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.cursor) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Bury(*((ZUI_ELEMENT**)&(gGUI.hud.cursor) + i));}
                for (ZT_INDEX i = 0; i < (sizeof(gGUI.hud.setting) / sizeof(ZUI_ELEMENT*)); i++) {ZUI_Restore(*((ZUI_ELEMENT**)&(gGUI.hud.setting) + i));}
                break;
            default:
                break;
        }
    }
}
void ZSGUI_Exit(void) {
    if (gDia.plot != NULL) {ZTM_SurfaceFree(gDia.plot);}
    ZUI_HostFree();
    ZTK_PrinterQuit();
    ZTK_FontFree(gApp.font.window);
    ZTK_FontFree(gApp.font.title);
    ZTK_FontFree(gApp.font.desc);
}
#endif // ZSCOPE_GUI_C_INCLUDED
