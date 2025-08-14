/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_DIAGRAM_C_INCLUDED
#define ZS_DIAGRAM_C_INCLUDED

#include "ZS_Diagram.h"

void ZSDIA_Colors(void) {
    ZT_FLAG lPalette = ZTK_GetPaletteSystem();
    gDia.color.background = ZTM_ColorConvert(gUsr.color.background, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.trigger = ZTM_ColorConvert(gUsr.color.trigger, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.cursor.data = ZTM_ColorConvert(gUsr.color.cursor.data, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.cursor.first = ZTM_ColorConvert(gUsr.color.cursor.first, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.cursor.second = ZTM_ColorConvert(gUsr.color.cursor.second, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.grid.major = ZTM_ColorConvert(gUsr.color.grid.major, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.grid.minor = ZTM_ColorConvert(gUsr.color.grid.minor, ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[0] = ZTM_ColorConvert(gUsr.color.plot[0], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[1] = ZTM_ColorConvert(gUsr.color.plot[1], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[2] = ZTM_ColorConvert(gUsr.color.plot[2], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[3] = ZTM_ColorConvert(gUsr.color.plot[3], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[4] = ZTM_ColorConvert(gUsr.color.plot[4], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[5] = ZTM_ColorConvert(gUsr.color.plot[5], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[6] = ZTM_ColorConvert(gUsr.color.plot[6], ZTM_PALETTE_RGBA, lPalette);
    gDia.color.plot[7] = ZTM_ColorConvert(gUsr.color.plot[7], ZTM_PALETTE_RGBA, lPalette);
}

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
void ZSDIA_FlipV(ZT_BOOL iEnabled) {
    if (gDia.diagram != NULL) {
        if (iEnabled) {gDia.diagram->flag |= ZDX_DIAGRAM_FLAG_FLIP_V;} else {gDia.diagram->flag &= ~ZDX_DIAGRAM_FLAG_FLIP_V;}
    }
}
void ZSDIA_Init(void) {
    ZSDIA_Defaults();
    ZSDIA_Colors();
    gDia.diagram = ZDX_DiagramNew(0x0);
    gDia.diagram->data.offset = &gDia.offset.data;
    gDia.diagram->grid.major = &gDia.grid.major;
    gDia.diagram->grid.minor = &gDia.grid.minor;
    gDia.diagram->color.plot = gDia.color.plot;
    gDia.diagram->color.background = &gDia.color.background;
    gDia.diagram->color.trigger = &gDia.color.trigger;
    gDia.diagram->color.cursor.data = &gDia.color.cursor.data;
    gDia.diagram->color.cursor.first = &gDia.color.cursor.first;
    gDia.diagram->color.cursor.second = &gDia.color.cursor.second;
    gDia.diagram->color.grid.major = &gDia.color.grid.major;
    gDia.diagram->color.grid.minor = &gDia.color.grid.minor;
    ZSDIA_FlipV((ZTK_GetRendererType() & ZTK_RENDERER_FLIP_V) ? ZT_TRUE : ZT_FALSE);
}
void ZSDIA_Exit(void) {
    if (gDia.plot != NULL) {ZTM_SurfaceFree(gDia.plot);}
    ZDX_DiagramFree(gDia.diagram);
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
