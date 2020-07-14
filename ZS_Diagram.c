/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_DIAGRAM_C_INCLUDED
#define ZS_DIAGRAM_C_INCLUDED

#include "ZS_Diagram.h"

void ZSDIA_Defaults(void) {
    gDia.grid.major.xU = 10;
    gDia.grid.major.yU = 5;
    gDia.grid.minor.xU = 10;
    gDia.grid.minor.yU = 10;
    gDia.offset.data.xU = 0;
    gDia.offset.data.yU = 0;
    gDia.offset.grid.xU = 0;
    gDia.offset.grid.yU = 0;
    gDia.offset.cursor.horizontal.xU = 0;
    gDia.offset.cursor.horizontal.yU = 0;
    gDia.offset.cursor.vertical.xU = 0;
    gDia.offset.cursor.vertical.yU = 0;
    gDia.color.background = ZDX_DIAGRAM_COLOR_BACKGROUND;
    gDia.color.trigger = ZDX_DIAGRAM_COLOR_TRIGGER;
    gDia.color.cursor.data = ZDX_DIAGRAM_COLOR_CURSOR_DATA;
    gDia.color.cursor.first = ZDX_DIAGRAM_COLOR_CURSOR_FIRST;
    gDia.color.cursor.second = ZDX_DIAGRAM_COLOR_CURSOR_SECOND;
    gDia.color.grid.major = ZDX_DIAGRAM_COLOR_GRID_MAJOR;
    gDia.color.grid.minor = ZDX_DIAGRAM_COLOR_GRID_MINOR;
    gDia.color.plot[0] = 0xffffff00;
    gDia.color.plot[1] = 0xff0080ff;
    gDia.color.plot[2] = 0xffff0000;
    gDia.color.plot[3] = 0xff00ff00;
    gDia.color.plot[4] = 0xffff8000;
    gDia.color.plot[5] = 0xffffffff;
    gDia.color.plot[6] = 0xff004000;
    gDia.color.plot[7] = 0xff400080;
}
void ZSDIA_Reset(void) {
    gDia.offset.data.xU = 0;
    gDia.offset.data.yU = 0;
    gDia.offset.grid.xU = gApp.rect.plot.w >> 1;
    gDia.offset.grid.yU = 0;
    gDia.offset.cursor.horizontal.xU = gApp.rect.plot.w >> 2;
    gDia.offset.cursor.horizontal.yU = 3 * (gApp.rect.plot.w >> 2);
    gDia.offset.cursor.vertical.xU = (gDev.data != NULL) ? ((1 << gDev.data->resolution) >> 2) : 0;
    gDia.offset.cursor.vertical.yU = (gDev.data != NULL) ? (3 * ((1 << gDev.data->resolution) >> 2)) : 0;
    if (gDev.data != NULL) {gDev.data->cursor = 0;}
}
void ZSDIA_Grid(void) {
    if (gDev.hardware != NULL && gDev.data != NULL) {
        ZT_INDEX lSpeed = ZDX_GetSpeed(gDev.hardware);
        ZT_INDEX lDiv = 1;
        while ((lSpeed + 1) / (1000 * lDiv)) {lDiv *= 10;}
        if (lSpeed) {gDia.grid.major.xU = (gDev.data->block.yU * lDiv / lSpeed);}
    } else {
        ZSDIA_Defaults();
    }
}
void ZSDIA_Init(void) {
    ZSDIA_Defaults();
    if (gDia.diagram == NULL) {
        if ((gDia.diagram = ZDX_DiagramNew(0x0))!= NULL) {
            gDia.diagram->data.offset = &(gDia.offset.data);
            gDia.diagram->grid.major = &(gDia.grid.major);
            gDia.diagram->grid.minor = &(gDia.grid.minor);
            gDia.diagram->color.plot = gDia.color.plot;
            gDia.diagram->color.background = &(gDia.color.background);
            gDia.diagram->color.trigger = &(gDia.color.trigger);
            gDia.diagram->color.cursor.data = &(gDia.color.cursor.data);
            gDia.diagram->color.cursor.first = &(gDia.color.cursor.first);
            gDia.diagram->color.cursor.second = &(gDia.color.cursor.second);
            gDia.diagram->color.grid.major = &(gDia.color.grid.major);
            gDia.diagram->color.grid.minor = &(gDia.color.grid.minor);
        }
    }
}
void ZSDIA_Exit(void) {
    if (gDia.diagram != NULL) {
        ZDX_DiagramFree(gDia.diagram);
        gDia.diagram = NULL;
    }
}
void ZSDIA_Move(ZT_I iIncrement) {
    ZT_U lIncrement;
    if (iIncrement < 0) {
        lIncrement = -iIncrement;
        if (!(gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE)) {
            gDia.offset.data.xU += lIncrement;
            gDia.offset.data.xU %= gDev.data->block.yU;
        } else if (ZUI_GetDataValue(gGUI.hud.selector) == ZSCOPE_HUD_TRIGGER) {
            gDia.offset.grid.xU = (gDia.offset.grid.xU < lIncrement) ? (gDia.plot->block.xU - lIncrement + gDia.offset.grid.xU) : (gDia.offset.grid.xU - lIncrement);
        }
    } else {
        lIncrement = iIncrement;
        if (!(gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE)) {
            gDia.offset.data.xU = (gDia.offset.data.xU < lIncrement) ? (gDev.data->block.yU - lIncrement + gDia.offset.data.xU) : (gDia.offset.data.xU - lIncrement);
        } else if (ZUI_GetDataValue(gGUI.hud.selector) == ZSCOPE_HUD_TRIGGER) {
            gDia.offset.grid.xU += lIncrement;
            gDia.offset.grid.xU %= gDia.plot->block.xU;
        }
    }
}

#endif //ZS_DIAGRAM_C_INCLUDED
