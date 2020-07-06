/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZSCOPE_C_INCLUDED
#define ZSCOPE_C_INCLUDED

#include "ZScope.h"

int main(void) {
	ZS_Init();
    while (ZTK_Main(&ZS_Main));
    ZS_Exit();
    return 0;
}
void ZS_Main(void) {
    if (ZTK_Timeout(&(gApp.timestamp.fps), gApp.timeout.fps)) {
        ZTK_TimeoutReset(&(gApp.timestamp.fps), gApp.timeout.fps);
        gApp.stat.fps = gApp.counter.fps;
        gApp.counter.fps = 0;
        gDev.stat.trigger = gDev.counter.trigger;
        gDev.counter.trigger = 0;
    }
    if (ZTK_Timeout(&(gApp.timestamp.capture), gApp.timeout.capture)) {
        ZTK_TimeoutReset(&(gApp.timestamp.capture), gApp.timeout.capture);
        ZSDEV_Read();
    }
    while (ZTK_PollMessages(&(gApp.event.window))) {ZS_Event();}
    if (ZTK_Timeout(&(gApp.timestamp.draw), gApp.timeout.draw)) {
        ZTK_TimeoutReset(&(gApp.timestamp.draw), gApp.timeout.draw);
        ZS_Draw();
    }
}
void ZS_Printer(void) {
    ZT_RECT lRect;
    ZTK_PrintBufferLoad("fps: %3u", gApp.stat.fps);
    ZTK_PrintBufferGetSize(&lRect);
    ZTK_PrintPosX(gApp.pos.fps.x - lRect.w / 2);
    ZTK_PrintPosY(gApp.pos.fps.y);
    ZTK_PrintPos(&(gApp.pos.fps));
    ZTK_PrintBuffer();
    if (gDev.hardware != NULL && !gUsr.menu) {
        ZT_TIME lTime = ZTK_GetTicks();
        ZT_INDEX lChannel = gDev.hardware->channel->number;
        ZT_INDEX lChannelOK = gDev.hardware->channel->counter.sample / lChannel;
        ZT_INDEX lChannelTotal = gDev.hardware->channel->counter.total / (2 * lChannel);
        ZT_INDEX lChannelNG = lChannelTotal - lChannelOK;
        ZT_INDEX lChannelTime = (lTime - gDev.timestamp.connect);
        ZT_DBL lChannelFreq = (lChannelTime > gApp.timeout.fps) ? (lChannelTotal * 1000.0 / (ZT_DBL)lChannelTime) : 0.0;
        ZT_DBL lChannelQuality = 100.0 * lChannelOK / (ZT_DBL)lChannelTotal;
        ZTK_PrintBufferLoad("f: %.2f Hz", lChannelFreq);
        ZTK_PrintBufferGetSize(&lRect);
        ZTK_PrintPosX(gApp.pos.daq.x - lRect.w / 2);
        ZTK_PrintPosY(gApp.pos.daq.y);
        ZTK_PrintBuffer();
        ZTK_PrintBufferLoad("t: %.0fs, RX: %3.2f%%, NG: %u", (lChannelTime / 1000.0), lChannelQuality, lChannelNG);
        ZTK_PrintBufferGetSize(&lRect);
        ZTK_PrintPosX(gApp.pos.xfer.x - lRect.w / 2);
        ZTK_PrintPosY(gApp.pos.xfer.y);
        ZTK_PrintBuffer();
        ZT_INDEX lSelection = ZUI_GetDataValue(gGUI.hud.selector);
        ZT_FLAG lUnit = ZUI_GetDataValue(gGUI.hud.measure.unit);
        ZT_DBL lResolution = ((1 << gDev.data->resolution) - 1);
        ZT_DBL lRange = 5.0;
        if (lSelection == ZSCOPE_HUD_MEASURE) {
            ZT_U* lValue = ZDX_DataGetLastLine(gDev.data);
            for (ZT_INDEX i = 0; i < lChannel; i++) {
                if (lUnit) {
                    ZTK_PrintBufferLoad("ch%u: %.3f V", i + 1, lValue[i] * lRange / lResolution);
                } else {
                    ZTK_PrintBufferLoad("ch%u: %u", i + 1, lValue[i]);
                }
                ZTK_PrintBufferGetSize(&lRect);
                ZTK_PrintPosX(gApp.pos.measure[i].x - lRect.w / 2);
                ZTK_PrintPosY(gApp.pos.measure[i].y - lRect.h / 2);
                ZTK_PrintBuffer();
            }
        } else if (lSelection == ZSCOPE_HUD_TRIGGER) {
            if (ZUI_GetDataValue(gGUI.hud.trigger.mode)) {
                if (lUnit) {
                    ZT_DBL lLevel = lRange * gDev.trigger->level.yU / lResolution;
                    ZTK_PrintBufferLoad("y: %.3f V", lLevel);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[4].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[4].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                } else {
                    ZTK_PrintBufferLoad("y: %u", gDev.trigger->level.yU);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[4].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[4].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                }
                ZTK_PrintBufferLoad("f: %u Hz", gDev.stat.trigger);
                ZTK_PrintBufferGetSize(&lRect);
                ZTK_PrintPosX(gApp.pos.measure[5].x - lRect.w / 2);
                ZTK_PrintPosY(gApp.pos.measure[5].y - lRect.h / 2);
                ZTK_PrintBuffer();
            }
        } else if (lSelection == ZSCOPE_HUD_CURSOR) {
            ZT_INDEX lType = ZUI_GetDataValue(gGUI.hud.cursor.type);
            if (lType == 2) {
                ZT_I lDelta = gDia.offset.cursor.vertical.y - gDia.offset.cursor.vertical.x;
                if (lUnit) {
                    ZT_DBL lVolts = lRange * lDelta / lResolution;
                    ZTK_PrintBufferLoad("Delta: %.3f V", lVolts);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[3].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[3].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                } else {
                    ZTK_PrintBufferLoad("Delta: %d", lDelta);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[3].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[3].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                }
            } else if (lType == 1) {
                ZT_I lDelta = gDia.offset.cursor.horizontal.y - gDia.offset.cursor.horizontal.x;
                if (lUnit) {
                    ZT_DBL lTime = (1000.0 / (gDev.hardware->channel->speed / 100.0)) * lDelta;
                    ZTK_PrintBufferLoad("Delta: %.2f ms", lTime);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[3].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[3].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                } else {
                    ZTK_PrintBufferLoad("Delta: %d", lDelta);
                    ZTK_PrintBufferGetSize(&lRect);
                    ZTK_PrintPosX(gApp.pos.measure[3].x - lRect.w / 2);
                    ZTK_PrintPosY(gApp.pos.measure[3].y - lRect.h / 2);
                    ZTK_PrintBuffer();
                }
            }
        }
    }
}
void ZS_Draw(void) {
    ZTK_DrawClear();
    if (gDia.diagram != NULL && gDia.plot != NULL) {
        if (ZUI_GetDataValue(gGUI.hud.trigger.mode) && !ZUI_GetDataValue(gGUI.hud.diagram.type)) {gDia.diagram->data.trigger = &(gDev.trigger->level);} else {gDia.diagram->data.trigger = NULL;}
        if (ZUI_GetDataValue(gGUI.hud.cursor.type) == 2) {
            gDia.diagram->data.cursor.horizontal = NULL;
            gDia.diagram->data.cursor.vertical = &(gDia.offset.cursor.vertical);
        } else if (ZUI_GetDataValue(gGUI.hud.cursor.type) == 1) {
            gDia.diagram->data.cursor.horizontal = &(gDia.offset.cursor.horizontal);
            gDia.diagram->data.cursor.vertical = NULL;
        } else {
            gDia.diagram->data.cursor.horizontal = NULL;
            gDia.diagram->data.cursor.vertical = NULL;
        }
        ZDX_DiagramRender(gDia.diagram, gDev.data, gDia.plot);
        ZTK_DrawSurface(gDia.plot, &(gApp.rect.plot));
    }
    ZUI_HostDraw();
    ZS_Printer();
    ZTK_DrawPresent();
    gApp.counter.fps++;
}
void ZS_Init(void) {
    ZTM8_Zero(&gApp, sizeof(gApp));
    ZTM8_Zero(&gGUI, sizeof(gGUI));
    ZTM8_Zero(&gTxt, sizeof(gTxt));
    ZTM8_Zero(&gUsr, sizeof(gUsr));
    ZTM8_Zero(&gDia, sizeof(gDia));
    ZTM8_Zero(&gDev, sizeof(gDev));
    ZTM_Rect(&(gApp.rect.window), ZTK_HostGetScreenWidth() / 4, ZTK_HostGetScreenHeight() / 4, ZTK_HostGetScreenWidth() / 2, ZTK_HostGetScreenHeight() / 2);
    ZTM_RectZero(&(gApp.rect.plot));
    gApp.flag = ZSCOPE_FLAG_NONE;
    gApp.timestamp.fps = 0;
    gApp.timestamp.draw = 0;
    gApp.timestamp.capture = 0;
    gApp.timeout.fps = 999;
    gApp.timeout.draw = 3;
    gApp.timeout.capture = 1;
    gApp.counter.fps = 0;
    gApp.stat.fps = 0;
    gApp.event.window = NULL;
    gApp.event.gui = NULL;
    gApp.font.window = NULL;
    gApp.font.title = NULL;
    gApp.font.desc = NULL;
    gApp.printer = NULL;
    gDia.plot = NULL;
    ZSTXT_Load(&(gTxt), gUsr.lang);
    ZTK_New(gTxt.window.title, &(gApp.rect.window), NULL);
    ZTK_IdleForbid(ZT_FALSE);
    ZTK_IdleAuto(ZT_TRUE);
    ZTK_Heartbeat(1);
    ZSUSR_Init();
    ZSDIA_Init();
    ZSGUI_Init();
    ZS_Size();
    ZSGUI_Menu();
    ZTK_Open();
}
void ZS_Exit(void) {
    ZSDEV_Free();
    ZSDIA_Exit();
    ZSGUI_Exit();
    ZTK_Free();
}
void ZSUSR_Init(void) {
    gUsr.flag = ZSCOPE_USER_FLAG_NONE;
    gUsr.lang = ZSCOPE_DEFAULT_TEXT_LANG;
    gUsr.menu = ZSCOPE_DEFAULT_MENU;
}
void ZSUSR_HUD(void) {
    ZSGUI_Menu();
}
void ZSUSR_TriggerType(void) {
    ZSDEV_TriggerFlank(ZUI_GetDataValue(gGUI.hud.trigger.type) ? ZDX_TRIGGER_TYPE_FALLING : ZDX_TRIGGER_TYPE_RISING);
}
void ZSUSR_TriggerMode(void) {
    gDev.flag &= ~ZSCOPE_DEVICE_FLAG_HALT;
    ZUI_DataValue(gGUI.hud.diagram.type, 0);
}
void ZSUSR_Menu(ZT_INDEX iSelection) {
    switch (iSelection) {
        case ZSCOPE_MENU_TOGGLE: if (gUsr.menu) {if (gDev.hardware != NULL) {gUsr.menu = ZSCOPE_MENU_NONE;}} else {gUsr.menu = ZSCOPE_MENU_DEVICE;} break;
        case ZSCOPE_MENU_NONE: if (gDev.hardware != NULL) {gUsr.menu = ZSCOPE_MENU_NONE;} break;
        default: gUsr.menu = iSelection; break;
    }
    ZSGUI_Menu();
}
void ZS_Connect(void) {
    ZT_INDEX lAddressID = ZUI_GetDataValue(gGUI.menu.device.address);
    ZT_CHAR lAddress[11] = "\\\\.\\COM000";
    if (lAddressID < 10) {
        lAddress[7] = lAddressID + ZTM_CHAR_0;
        lAddress[8] = ZTM_CHAR_NT;
    } else if (lAddressID < 100) {
        lAddress[7] = (lAddressID / 10) + ZTM_CHAR_0;
        lAddress[8] = (lAddressID % 10) + ZTM_CHAR_0;
        lAddress[9] = ZTM_CHAR_NT;
    } else if (lAddressID < 0x100) {
        lAddress[7] = (lAddressID / 100) + ZTM_CHAR_0;
        lAddress[8] = ((lAddressID / 10) % 10) + ZTM_CHAR_0;
        lAddress[9] = (lAddressID % 10) + ZTM_CHAR_0;
        lAddress[10] = ZTM_CHAR_NT;
    } else {
        lAddress[7] = ZTM_CHAR_NT;
    }
    ZT_FLAG lChannels = ZUI_GetDataValue(gGUI.menu.device.channel);
    ZT_INDEX lSpeed = ZUI_GetDataValue(gGUI.menu.device.speed);
    ZSDEV_Connect(lAddress, lSpeed, lChannels);
    ZSDIA_Grid();
    ZSDIA_Reset();
    if (gDev.hardware != NULL) {
        ZUI_DataMaximum(gGUI.hud.trigger.channel, gDev.hardware->channel->number - 1);
        ZSUSR_TriggerMode();
        ZSUSR_TriggerType();
        ZSUSR_Menu(ZSCOPE_MENU_NONE);
    }
}
void ZS_Disconnect(void) {
    ZSDEV_Disconnect();
}
void ZS_Size(void) {
    ZTK_GetRect(&(gApp.rect.window));
    if (gApp.rect.window.w && gApp.rect.window.h) {
        ZSGUI_Size();
        // PLOT
        ZT_I lPlotHeight = gApp.rect.window.h - 3 * gApp.dim.button.hud.y - ZUI_GetBorderSize(gGUI.hud.box.top) - ZUI_GetBorderSize(gGUI.hud.box.bottom);
        ZT_I lPlotY = gApp.dim.button.hud.y + ZUI_GetBorderSize(gGUI.hud.box.top);
        ZTM_Rect(&(gApp.rect.plot), 0, lPlotY, gApp.rect.window.w, (lPlotHeight < 0) ? 0 : lPlotHeight);
        if (gDia.plot == NULL) {
            ZT_POINT lFullscreen;
            lFullscreen.x = 4 * ZTK_HostGetScreenWidth();
            lFullscreen.y = 4 * ZTK_HostGetScreenHeight();
            gDia.plot = ZTM_SurfaceNewFill(&lFullscreen, 0x0);
        }
        gDia.plot->block.x = gApp.rect.plot.w;
        gDia.plot->block.y = gApp.rect.plot.h;
        if (gDia.plot->block.xU) {gDia.offset.grid.xU %= gDia.plot->block.xU;}
    }
}
void ZSUSR_CursorLevel(ZT_I iIncrement) {
    ZT_INDEX lType = ZUI_GetDataValue(gGUI.hud.cursor.type);
    if (lType == 2) {
        if (gDev.data != NULL) {
            ZT_INDEX lMax = (1 << gDev.data->resolution);
            ZT_U* lTarget = (ZUI_GetDataValue(gGUI.hud.cursor.target)) ? &(gDia.offset.cursor.vertical.yU) : &(gDia.offset.cursor.vertical.xU);
            ZT_INDEX lIncrement;
            if (iIncrement < 0) {
                lIncrement = -iIncrement;
                *lTarget = (*lTarget < lIncrement) ? (lMax - lIncrement + *lTarget) : (*lTarget - lIncrement);
            } else {
                lIncrement = iIncrement;
                *lTarget += lIncrement;
                *lTarget %= lMax;
            }
        }
    } else if (lType == 1) {
        if (gDia.plot != NULL) {
            if (gDia.plot->block.xU) {
                ZT_INDEX lMax = gDia.plot->block.xU;
                ZT_U* lTarget = (ZUI_GetDataValue(gGUI.hud.cursor.target)) ? &(gDia.offset.cursor.horizontal.yU) : &(gDia.offset.cursor.horizontal.xU);
                ZT_INDEX lIncrement;
                if (iIncrement < 0) {
                    lIncrement = -iIncrement;
                    *lTarget = (*lTarget < lIncrement) ? (lMax - lIncrement + *lTarget) : (*lTarget - lIncrement);
                } else {
                    lIncrement = iIncrement;
                    *lTarget += lIncrement;
                    *lTarget %= lMax;
                }
            }
        }
    }
}
void ZSUSR_Level(ZT_BOOL iReverse) {
    if (ZTK_Repeat(ZSCOPE_REPEAT)) {
        ZT_I lIncrement = (gUsr.flag & ZSCOPE_USER_FLAG_SHIFT) ? 1 : 10;
        if (iReverse) {lIncrement = -lIncrement;}
        ZT_INDEX lSelection = ZUI_GetDataValue(gGUI.hud.selector);
        switch (lSelection) {
            case ZSCOPE_HUD_TRIGGER: ZSDEV_TriggerLevel(lIncrement); break;
            case ZSCOPE_HUD_CURSOR: ZSUSR_CursorLevel(lIncrement); break;
            default: break;
        }
    }
}
void ZSUSR_Channels(void) {
    ZT_FLAG lConfig = ZTM_BitCount(ZUI_GetDataValue(gGUI.menu.device.channel));
    ZT_INDEX lMax = 9999999;
    switch (lConfig) {
        case 2: lMax = 4000000; break;
        case 3: lMax = 2500000; break;
        case 4: lMax = 2000000; break;
        case 5: lMax = 1500000; break;
        case 6: lMax = 1250000; break;
        case 7: lMax = 1000000; break;
        case 8: lMax = 750000; break;
        default: break;
    }
    ZUI_DataMaximum(gGUI.menu.device.speed, lMax);
}
void ZS_EventGUI(void) {
    //printf("%x %x %u %u %u %u\n", gApp.event.gui->id.device, gApp.event.gui->id.event, gApp.event.gui->data.d0, gApp.event.gui->data.d1, gApp.event.gui->data.d2, gApp.event.gui->data.d3);
    if (gApp.event.gui->id.E == ZTK_EID_GUI_RELEASE) {
        switch (gApp.event.gui->id.S) {
            case ZSCOPE_ID_MENU_HEAD_DEVICE: ZSUSR_Menu(ZSCOPE_MENU_DEVICE); break;
            case ZSCOPE_ID_MENU_HEAD_HELP: ZSUSR_Menu(ZSCOPE_MENU_HELP); break;
            case ZSCOPE_ID_MENU_HEAD_CREDITS: ZSUSR_Menu(ZSCOPE_MENU_CREDITS);  break;
            case ZSCOPE_ID_MENU_HEAD_EXIT: ZTK_Quit(); break;
            case ZSCOPE_ID_MENU_DEVICE_CHANNEL: ZSUSR_Channels(); break;
            case ZSCOPE_ID_MENU_DEVICE_CONNECT: ZS_Connect(); break;
            case ZSCOPE_ID_MENU_DEVICE_DISCONNECT: ZS_Disconnect(); break;
            case ZSCOPE_ID_HUD_MENU: ZSUSR_Menu(ZSCOPE_MENU_TOGGLE); break;
            case ZSCOPE_ID_HUD_CAPTURE: ZSDEV_Capture(-1); break;
            case ZSCOPE_ID_HUD_SELECTOR: ZSUSR_HUD(); break;
            case ZSCOPE_ID_HUD_DIAGRAM_RESET: ZSDIA_Reset(); break;
            case ZSCOPE_ID_HUD_TRIGGER_MODE: ZSUSR_TriggerMode(); break;
            case ZSCOPE_ID_HUD_TRIGGER_FLANK: ZSUSR_TriggerType(); break;
            case ZSCOPE_ID_HUD_TRIGGER_CHANNEL: break;
            default: break;
        }
    }
}
void ZS_Event(void) {
    //printf("%x %x %u %u %u %u\n", gApp.event.window->id.device, gApp.event.window->id.event, gApp.event.window->data.d0, gApp.event.window->data.d1, gApp.event.window->data.d2, gApp.event.window->data.d3);
    ZT_BOOL lGUI_Event = ZT_FALSE;
    while (ZUI_HostPoll(gApp.event.window, &(gApp.event.gui))) {ZS_EventGUI(); lGUI_Event = ZT_TRUE;}
    if (!(lGUI_Event || gUsr.menu)) {
        switch (gApp.event.window->id.H) {
            case ZTK_HID_MOUSE:
                switch (gApp.event.window->id.E) {
                    case ZTK_EID_MOUSE_BUTTON_L_DOWN: gUsr.flag |= ZSCOPE_USER_FLAG_MOVE; break;
                    case ZTK_EID_MOUSE_BUTTON_L_UP: gUsr.flag &= ~ZSCOPE_USER_FLAG_MOVE; break;
                    case ZTK_EID_MOUSE_MOVE: if (gUsr.flag & ZSCOPE_USER_FLAG_MOVE) {ZSDIA_Move((ZT_I)gApp.event.window->data.d0 - (ZT_I)gApp.event.window->data.d2);} break;
                    case ZTK_EID_MOUSE_WHEEL_UP: ZSUSR_Level(ZT_FALSE); break;
                    case ZTK_EID_MOUSE_WHEEL_DOWN: ZSUSR_Level(ZT_TRUE); break;
                    default: break;
                }
                break;
            case ZTK_HID_KEY:
                if (gApp.event.window->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                    switch (gApp.event.window->id.S) {
                        case ZTK_SID_KEY_SPACE: case ZTK_SID_KEY_PAUSE: ZSDEV_Capture(-1); break;
                        case ZTK_SID_KEY_SHIFT: gUsr.flag &= ~ZSCOPE_USER_FLAG_SHIFT; break;
                        case ZTK_SID_KEY_L: break;
                        case ZTK_SID_KEY_K: break;
                        default: break;
                    }
                } else if (gApp.event.window->id.E == ZTK_EID_KEYBOARD_KEY_DOWN) {
                    switch (gApp.event.window->id.S) {
                        case ZTK_SID_KEY_SHIFT: gUsr.flag |= ZSCOPE_USER_FLAG_SHIFT; break;
                        case ZTK_SID_KEY_UP: ZSUSR_Level(ZT_FALSE); break;
                        case ZTK_SID_KEY_DOWN: ZSUSR_Level(ZT_TRUE); break;
                        case ZTK_SID_KEY_LEFT: break;
                        case ZTK_SID_KEY_RIGHT: break;
                        default: break;
                    }
                }
                break;
            default:
                break;
        }
    }
    switch (gApp.event.window->id.H) {
        case ZTK_HID_KEY:
            if (gApp.event.window->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                switch (gApp.event.window->id.S) {
                    case ZTK_SID_KEY_ESC: ZSUSR_Menu(ZSCOPE_MENU_TOGGLE); break;
                    default: break;
                }
            }
            break;
        case ZTK_HID_WINDOW:
            switch (gApp.event.window->id.E) {
                case ZTK_EID_WINDOW_RESIZE: ZS_Size(); break;
                default: break;
            }
            break;
        default:
            break;
    }
}

#endif // ZSCOPE_C_INCLUDED
