/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_C_INCLUDED
#define ZS_C_INCLUDED

#include "ZS.h"

int main(void) {
	ZS_Init();
    while (ZTK_Main());
    ZS_Exit();
    return 0;
}
void ZS_Main(void) {
    if (ZTK_TimeoutReset(&(gApp.fps.timestamp), 1000)) {
        gApp.fps.stat = gApp.fps.counter;
        gApp.fps.counter = 0;
        gDev.stat.trigger = gDev.counter.trigger;
        gDev.counter.trigger = 0;
    }
    ZSDEV_Read();
    ZS_Event();
    ZS_Draw();
}
void ZS_Printer(void) {
    ZT_RECT lRect;
    ZTK_PrintBufferLoad("fps: %3u", gApp.fps.stat);
    ZTK_PrintBufferGetSize(&lRect);
    ZTK_PrintPosX(gApp.pos.fps.x - lRect.w / 2);
    ZTK_PrintPosY(gApp.pos.fps.y);
    ZTK_PrintPos(&gApp.pos.fps);
    ZTK_PrintBuffer();
    if (gDev.hardware != NULL && !gApp.menu) {
        ZT_TIME lTime = ZTK_GetTicks();
        ZT_INDEX lChannel = gDev.hardware->task.number;
        ZT_INDEX lChannelOK = gDev.hardware->task.counter.sample / lChannel;
        ZT_INDEX lChannelTotal = gDev.hardware->task.counter.total / (2 * lChannel);
        ZT_INDEX lChannelNG = lChannelTotal - lChannelOK;
        ZT_INDEX lChannelTime = (lTime - gDev.timestamp.connect);
        ZT_DBL lChannelFreq = (lChannelTime > 1000) ? (lChannelTotal * 1000.0 / (ZT_DBL)lChannelTime) : 0.0;
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
        ZT_FLAG lUnit = ZUI_GetDataValue(gGUI.hud.measure.unit);
        ZT_DBL lResolution = ((1 << gDev.data->resolution) - 1);
        ZT_DBL lRange = 5.0;
        if (gUsr.hud == ZSCOPE_HUD_MEASURE) {
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
        } else if (gUsr.hud == ZSCOPE_HUD_TRIGGER) {
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
        } else if (gUsr.hud == ZSCOPE_HUD_CURSOR) {
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
                    ZT_DBL lTime = (1000.0 / (gDev.hardware->task.speed / 100.0)) * lDelta;
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
    gApp.fps.counter++;
}
void ZSUSR_DiskLoad(void) {
    ZKY* lConfig = ZKY_New();
    if (ZKY_FileRead(lConfig, ZSCOPE_CFG_DELIMIT, ZSCOPE_CFG_ASSIGN, ZSCOPE_CFG_PATH)) {
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_SET_RENDER, &gUsr.renderer);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_SET_LANG, &gUsr.lang);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_DEV_PORT, &gUsr.device.address);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_DEV_RATE, &gUsr.device.speed);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_DEV_CHANNEL, &gUsr.device.channel);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_MES_UNIT, &gUsr.measure.unit);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_GRID_0, &gUsr.color.grid.major);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_GRID_1, &gUsr.color.grid.minor);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_0, &gUsr.color.cursor.data);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_1, &gUsr.color.cursor.first);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_2, &gUsr.color.cursor.second);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_BACKGROUND, &gUsr.color.background);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_TRIGGER, &gUsr.color.trigger);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_0, &gUsr.color.plot[0]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_1, &gUsr.color.plot[1]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_2, &gUsr.color.plot[2]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_3, &gUsr.color.plot[3]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_4, &gUsr.color.plot[4]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_5, &gUsr.color.plot[5]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_6, &gUsr.color.plot[6]);
        ZKY_ReadHex(lConfig, ZSCOPE_CFG_CLR_PLOT_7, &gUsr.color.plot[7]);
    }
    ZKY_Free(lConfig);
}
void ZSUSR_Save(void) {
    gUsr.renderer = 0x1 << ZUI_GetDataValue(gGUI.menu.settings.renderer);
    gUsr.lang = ZUI_GetDataValue(gGUI.menu.settings.language);
    gUsr.device.address = ZUI_GetDataValue(gGUI.menu.device.address);
    gUsr.device.speed = ZUI_GetDataValue(gGUI.menu.device.speed);
    gUsr.device.channel = ZUI_GetDataValue(gGUI.menu.device.channel);
    gUsr.measure.unit = ZUI_GetDataValue(gGUI.hud.measure.unit);
    ZT_FLAG lPalette = ZTK_GetPaletteSystem();
    gUsr.color.grid.major = ZTM_ColorConvert(gDia.color.grid.major, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.grid.minor = ZTM_ColorConvert(gDia.color.grid.minor, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.cursor.data = ZTM_ColorConvert(gDia.color.cursor.data, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.cursor.first = ZTM_ColorConvert(gDia.color.cursor.first, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.cursor.second = ZTM_ColorConvert(gDia.color.cursor.second, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.background = ZTM_ColorConvert(gDia.color.background, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.trigger = ZTM_ColorConvert(gDia.color.trigger, lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[0] = ZTM_ColorConvert(gDia.color.plot[0], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[1] = ZTM_ColorConvert(gDia.color.plot[1], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[2] = ZTM_ColorConvert(gDia.color.plot[2], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[3] = ZTM_ColorConvert(gDia.color.plot[3], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[4] = ZTM_ColorConvert(gDia.color.plot[4], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[5] = ZTM_ColorConvert(gDia.color.plot[5], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[6] = ZTM_ColorConvert(gDia.color.plot[6], lPalette, ZTM_PALETTE_RGBA);
    gUsr.color.plot[7] = ZTM_ColorConvert(gDia.color.plot[7], lPalette, ZTM_PALETTE_RGBA);
}
void ZSUSR_DiskSave(void) {
    ZSUSR_Save();
    ZKY* lConfig = ZKY_New();
    ZKY_SetHex(lConfig, ZSCOPE_CFG_SET_RENDER, gUsr.renderer);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_SET_LANG, gUsr.lang);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_DEV_PORT, gUsr.device.address);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_DEV_RATE, gUsr.device.speed);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_DEV_CHANNEL, gUsr.device.channel);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_MES_UNIT, gUsr.measure.unit);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_GRID_0, gUsr.color.grid.major);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_GRID_1, gUsr.color.grid.minor);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_0, gUsr.color.cursor.data);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_1, gUsr.color.cursor.first);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_CURSOR_2, gUsr.color.cursor.second);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_BACKGROUND, gUsr.color.background);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_TRIGGER, gUsr.color.trigger);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_0, gUsr.color.plot[0]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_1, gUsr.color.plot[1]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_2, gUsr.color.plot[2]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_3, gUsr.color.plot[3]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_4, gUsr.color.plot[4]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_5, gUsr.color.plot[5]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_6, gUsr.color.plot[6]);
    ZKY_SetHex(lConfig, ZSCOPE_CFG_CLR_PLOT_7, gUsr.color.plot[7]);
    ZKY_FileWrite(lConfig, ZSCOPE_CFG_DELIMIT, ZSCOPE_CFG_ASSIGN, ZSCOPE_CFG_PATH);
    ZKY_Free(lConfig);
}
void ZSUSR_Init(void) {
    gUsr.flag = ZSCOPE_USER_FLAG_NONE;
    gUsr.hud = ZSCOPE_HUD_DIAGRAM;
    gUsr.lang = ZSCOPE_DEFAULT_TEXT_LANG;
    gUsr.renderer = ZSCOPE_DEFAULT_RENDERER;
    gUsr.device.address = ZSCOPE_DEFAULT_ADDRESS;
    gUsr.device.speed = ZSCOPE_DEFAULT_SPEED;
    gUsr.device.channel = ZSCOPE_DEFAULT_CONFIG;
    gUsr.color.background = ZDX_DIAGRAM_COLOR_BACKGROUND;
    gUsr.color.trigger = ZDX_DIAGRAM_COLOR_TRIGGER;
    gUsr.color.cursor.data = ZDX_DIAGRAM_COLOR_CURSOR_DATA;
    gUsr.color.cursor.first = ZDX_DIAGRAM_COLOR_CURSOR_FIRST;
    gUsr.color.cursor.second = ZDX_DIAGRAM_COLOR_CURSOR_SECOND;
    gUsr.color.grid.major = ZDX_DIAGRAM_COLOR_GRID_MAJOR;
    gUsr.color.grid.minor = ZDX_DIAGRAM_COLOR_GRID_MINOR;
    gUsr.color.plot[0] = ZDX_DIAGRAM_COLOR_PLOT_1;
    gUsr.color.plot[1] = ZDX_DIAGRAM_COLOR_PLOT_2;
    gUsr.color.plot[2] = ZDX_DIAGRAM_COLOR_PLOT_3;
    gUsr.color.plot[3] = ZDX_DIAGRAM_COLOR_PLOT_4;
    gUsr.color.plot[4] = ZDX_DIAGRAM_COLOR_PLOT_5;
    gUsr.color.plot[5] = ZDX_DIAGRAM_COLOR_PLOT_6;
    gUsr.color.plot[6] = ZDX_DIAGRAM_COLOR_PLOT_7;
    gUsr.color.plot[7] = ZDX_DIAGRAM_COLOR_PLOT_8;
    ZSUSR_DiskLoad();
}
void ZS_Init(void) {
    ZTX_Init(ZTX_PNG);
    ZTM8_Zero(&gApp, sizeof(gApp));
    ZTM8_Zero(&gGUI, sizeof(gGUI));
    ZTM8_Zero(&gUsr, sizeof(gUsr));
    ZTM8_Zero(&gDia, sizeof(gDia));
    ZTM8_Zero(&gDev, sizeof(gDev));
    ZTM_Rect(&gApp.rect.window, ZTL_ScreenWidth() / 4, ZTL_ScreenHeight() / 4, ZTL_ScreenWidth() / 2, ZTL_ScreenHeight() / 2);
    ZTM_RectZero(&gApp.rect.plot);
    gApp.flag = ZSCOPE_FLAG_NONE;
    gApp.menu = ZSCOPE_DEFAULT_MENU;
    gApp.font.window = NULL;
    gApp.font.title = NULL;
    gApp.font.desc = NULL;
    gDia.plot = NULL;
    ZSUSR_Init();
    ZS_TextLoad(gUsr.lang);
    ZTK_New(&ZS_Main, gText[ZSTX_WINDOW], &(gApp.rect.window), NULL);
    ZTK_Renderer(gUsr.renderer);
    ZSDIA_Init();
    ZSGUI_Init();
    ZS_Size();
    ZSGUI_Menu();
    ZTK_Open();
}
void ZS_Renderer(void) {
    ZSUSR_Save();
    ZS_TextLoad(gUsr.lang);
    ZTK_Renderer(gUsr.renderer);
    ZSDIA_Colors();
    ZSDIA_FlipV(gUsr.renderer & ZTK_RENDERER_FLIP_V ? ZT_TRUE : ZT_FALSE);
    ZSGUI_Exit();
    ZSGUI_Init();
    ZSGUI_Size();
    ZSGUI_Menu();
}
void ZS_Exit(void) {
    ZSUSR_DiskSave();
    ZSDEV_Free();
    ZSDIA_Exit();
    ZSGUI_Exit();
    ZTK_Free();
}
void ZSUSR_HUD(void) {
    gUsr.hud = ZUI_GetDataValue(gGUI.hud.selector);
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
        case ZSCOPE_MENU_TOGGLE: if (gApp.menu) {if (gDev.hardware != NULL) {gApp.menu = ZSCOPE_MENU_NONE;}} else {gApp.menu = ZSCOPE_MENU_DEVICE;} break;
        case ZSCOPE_MENU_NONE: if (gDev.hardware != NULL) {gApp.menu = ZSCOPE_MENU_NONE;} break;
        default: gApp.menu = iSelection; break;
    }
    ZSGUI_Menu();
}
void ZS_Connect(void) {
    ZT_CHAR* lAddress = ZTL_SerialAddress(ZUI_GetDataValue(gGUI.menu.device.address));
    ZT_FLAG lChannels = ZUI_GetDataValue(gGUI.menu.device.channel);
    ZT_INDEX lSpeed = ZUI_GetDataValue(gGUI.menu.device.speed);
    ZSDEV_Connect(lAddress, lSpeed, lChannels);
    ZTM8_Free(lAddress);
    ZSDIA_Grid();
    ZSDIA_Reset();
    if (gDev.hardware != NULL) {
        ZUI_DataMaximum(gGUI.hud.trigger.channel, gDev.hardware->task.number - 1);
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
            lFullscreen.x = 4 * ZTL_ScreenWidth();
            lFullscreen.y = 4 * ZTL_ScreenHeight();
            gDia.plot = ZTM_SurfaceNew(&lFullscreen, NULL);
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
        switch (gUsr.hud) {
            case ZSCOPE_HUD_TRIGGER: ZSDEV_TriggerLevel(lIncrement); break;
            case ZSCOPE_HUD_CURSOR: ZSUSR_CursorLevel(lIncrement); break;
            default: break;
        }
    }
}
void ZSUSR_Channels(void) {
    ZT_FLAG lConfig = ZTM_BitCount(ZUI_GetDataValue(gGUI.menu.device.channel));
    ZT_INDEX lMax;
    switch (lConfig) {
        default: lMax = 9999999; break;
        case 2: lMax = 4000000; break;
        case 3: lMax = 2500000; break;
        case 4: lMax = 2000000; break;
        case 5: lMax = 1500000; break;
        case 6: lMax = 1250000; break;
        case 7: lMax = 1000000; break;
        case 8: lMax = 750000; break;
    }
    ZUI_DataMaximum(gGUI.menu.device.speed, lMax);
}
void ZS_SaveMeta(const ZT_CHAR* iReference) {
    ZT_CHAR* lPath = ZTC8_Merge(iReference, (const ZT_CHAR*)".meta");
    ZT_FLAG lSpeed = ZUI_GetDataValue(gGUI.menu.device.speed);
    ZT_FLAG lConfig = ZUI_GetDataValue(gGUI.menu.device.channel);
    ZT_CHAR* lSpeedText = ZTC8_MergeFree(ZTC8_Unsigned(lSpeed / 100), ZTC8_MergeFreeB((const ZT_CHAR*)".", ZTC8_Unsigned(lSpeed % 100)));
    ZT_CHAR* lConfigText = ZTM8_New(sizeof(ZT_CHAR) * ZTM_BitCount(lConfig) * 3);
    ZT_INDEX lCursor = -1;
    for (ZT_INDEX i = 0; i < 8; ++i) {if ((0x1 << i) & lConfig) {lConfigText[++lCursor] = ZTM_CHAR_a; lConfigText[++lCursor] = ZTM_CHAR_0 + i; lConfigText[++lCursor] = ZTM_CHAR_COMMA;}}
    lConfigText[lCursor] = ZTM_CHAR_NT;
    ZKY* lMeta = ZKY_New();
    ZKY_Set(lMeta, (const ZT_CHAR*)"Rate", lSpeedText);
    ZKY_Set(lMeta, (const ZT_CHAR*)"Channels", lConfigText);
    ZKY_FileWrite(lMeta, ZSCOPE_CFG_DELIMIT, ZSCOPE_CFG_ASSIGN, lPath);
    ZTM8_Free(lConfigText);
    ZTM8_Free(lSpeedText);
    ZTM8_Free(lPath);
    ZKY_Free(lMeta);
}
void ZSDIA_SaveBMP(void) {
    ZT_CHAR* lPath = ZTC8_PathFileISO(NULL, (const ZT_CHAR*)"bmp", ZTM_Time());
    ZS_SaveMeta(lPath);
    ZTM_SurfaceSaveToBitmapFile(gDia.plot, lPath, ZTK_GetPaletteSystem());
    ZTM8_Free(lPath);
}
void ZSDIA_SavePNG(void) {
    ZT_CHAR* lPath = ZTC8_PathFileISO(NULL, (const ZT_CHAR*)"png", ZTM_Time());
    ZS_SaveMeta(lPath);
    ZTX_SurfaceSaveToPNGFile(gDia.plot, lPath, ZTK_GetPaletteSystem());
    ZTM8_Free(lPath);
}
void ZS_Event(void) {
    ZT_EVENT* lEvent;
    while (ZTK_PollMessages(&lEvent)) {
        //printf("%x %x %u %u %u %u\n", lEvent->id.device, lEvent->id.event, lEvent->data.d0, lEvent->data.d1, lEvent->data.d2, lEvent->data.d3);
        ZT_EVENT* lEventGUI;
        ZT_BOOL lCaptureGUI = ZT_FALSE;
        while (ZUI_HostPoll(lEvent, &lEventGUI)) {
            //printf("%x %x %u %u %u %u\n", lEventGUI->id.device, lEventGUI->id.event, lEventGUI->data.d0, lEventGUI->data.d1, lEventGUI->data.d2, lEventGUI->data.d3);
            lCaptureGUI = ZT_TRUE;
            if (lEventGUI->id.E == ZTK_EID_GUI_RELEASE) {
                switch (lEventGUI->id.S) {
                    case ZSCOPE_ID_MENU_HEAD_DEVICE: ZSUSR_Menu(ZSCOPE_MENU_DEVICE); break;
                    case ZSCOPE_ID_MENU_HEAD_HELP: ZSUSR_Menu(ZSCOPE_MENU_HELP); break;
                    case ZSCOPE_ID_MENU_HEAD_CREDITS: ZSUSR_Menu(ZSCOPE_MENU_CREDITS);  break;
                    case ZSCOPE_ID_MENU_HEAD_SETTINGS: ZSUSR_Menu(ZSCOPE_MENU_SETTINGS);  break;
                    case ZSCOPE_ID_MENU_HEAD_EXIT: ZTK_Quit(); break;
                    case ZSCOPE_ID_MENU_DEVICE_CHANNEL: ZSUSR_Channels(); break;
                    case ZSCOPE_ID_MENU_DEVICE_CONNECT: ZS_Connect(); break;
                    case ZSCOPE_ID_MENU_DEVICE_DISCONNECT: ZS_Disconnect(); break;
                    case ZSCOPE_ID_MENU_SETTINGS_LANGUAGE: ZS_Renderer(); break;
                    case ZSCOPE_ID_MENU_SETTINGS_RENDERER: ZS_Renderer(); break;
                    case ZSCOPE_ID_HUD_MENU: ZSUSR_Menu(ZSCOPE_MENU_TOGGLE); break;
                    case ZSCOPE_ID_HUD_CAPTURE: ZSDEV_Capture(-1); break;
                    case ZSCOPE_ID_HUD_RECORD: ZSDEV_Record(-1); break;
                    case ZSCOPE_ID_HUD_SELECTOR: ZSUSR_HUD(); break;
                    case ZSCOPE_ID_HUD_DIAGRAM_RESET: ZSDIA_Reset(); break;
                    case ZSCOPE_ID_HUD_DIAGRAM_BITMAP: ZSDIA_SaveBMP(); break;
                    case ZSCOPE_ID_HUD_DIAGRAM_PNG: ZSDIA_SavePNG(); break;
                    case ZSCOPE_ID_HUD_TRIGGER_MODE: ZSUSR_TriggerMode(); break;
                    case ZSCOPE_ID_HUD_TRIGGER_FLANK: ZSUSR_TriggerType(); break;
                    case ZSCOPE_ID_HUD_TRIGGER_CHANNEL: break;
                    default: break;
                }
            }
        }
        if (!(lCaptureGUI || gApp.menu)) {
            switch (lEvent->id.H) {
                case ZTK_HID_MOUSE:
                    switch (lEvent->id.E) {
                        case ZTK_EID_MOUSE_BUTTON_L_DOWN: gUsr.flag |= ZSCOPE_USER_FLAG_MOVE; break;
                        case ZTK_EID_MOUSE_BUTTON_L_UP: gUsr.flag &= ~ZSCOPE_USER_FLAG_MOVE; break;
                        case ZTK_EID_MOUSE_MOVE: if (gUsr.flag & ZSCOPE_USER_FLAG_MOVE) {ZSDIA_Move((ZT_I)lEvent->data.d0 - (ZT_I)lEvent->data.d2);} break;
                        case ZTK_EID_MOUSE_WHEEL_UP: ZSUSR_Level(ZT_FALSE); break;
                        case ZTK_EID_MOUSE_WHEEL_DOWN: ZSUSR_Level(ZT_TRUE); break;
                        default: break;
                    }
                    break;
                case ZTK_HID_KEY:
                    if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                        switch (lEvent->id.S) {
                            case ZTK_SID_KEY_SPACE: case ZTK_SID_KEY_PAUSE: ZSDEV_Capture(-1); break;
                            case ZTK_SID_KEY_SHIFT: gUsr.flag &= ~ZSCOPE_USER_FLAG_SHIFT; break;
                            default: break;
                        }
                    } else if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_DOWN) {
                        switch (lEvent->id.S) {
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
        switch (lEvent->id.H) {
            case ZTK_HID_KEY:
                if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                    switch (lEvent->id.S) {
                        case ZTK_SID_KEY_ESC: ZSUSR_Menu(ZSCOPE_MENU_TOGGLE); break;
                        case ZTK_SID_KEY_S: ZSDIA_SaveBMP(); break;
                        case ZTK_SID_KEY_D: ZSDIA_SavePNG(); break;
                        default: break;
                    }
                }
                break;
            case ZTK_HID_WINDOW:
                switch (lEvent->id.E) {
                    case ZTK_EID_WINDOW_RESIZE: ZS_Size(); break;
                    default: break;
                }
                break;
            default:
                break;
        }
    }
}

#endif // ZS_C_INCLUDED
