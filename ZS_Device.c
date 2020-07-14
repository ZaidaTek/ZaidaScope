/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_DEVICE_C_INCLUDED
#define ZS_DEVICE_C_INCLUDED

#include "ZS_Device.h"

void ZSDEV_Capture(ZT_FLAG iState) {
    switch (iState) {
        default:
        case ZT_TRUE: gDev.flag |= ZSCOPE_DEVICE_FLAG_CAPTURE; break;
        case ZT_FALSE: gDev.flag &= ~ZSCOPE_DEVICE_FLAG_CAPTURE; break;
        case -1: gDev.flag ^= ZSCOPE_DEVICE_FLAG_CAPTURE; break;
    }
    gDev.flag &= ~ZSCOPE_DEVICE_FLAG_HALT;
    ZUI_DataValue(gGUI.hud.capture, (gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE ? 0x1 : 0x0));
    ZUI_Update(gGUI.hud.capture);
}
void ZSDEV_Read(void) {
    if (gDev.hardware != NULL) {
        if ((gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE)) {
            if (ZDX_Read(gDev.hardware, gDev.data)) {
                if (ZUI_GetDataValue(gGUI.hud.diagram.type) != 0) {
                    ZT_INDEX lPlotWidth = (gDia.plot->block.xU ? gDia.plot->block.xU : 1) - 1;
                    gDia.offset.data.xU = gDev.data->cursor < lPlotWidth ? (gDev.data->block.yU - lPlotWidth + gDev.data->cursor) : (gDev.data->cursor - lPlotWidth);
                } else {
                    ZT_FLAG lTriggerMode = ZUI_GetDataValue(gGUI.hud.trigger.mode);
                    if (lTriggerMode) {
                        ZT_INDEX lTriggerChannel = ZUI_GetDataValue(gGUI.hud.trigger.channel);
                        ZT_TIME lTriggerHoldoff = ZUI_GetDataValue(gGUI.hud.trigger.holdoff);
                        ZT_INDEX lCount;
                        if ((lTriggerMode == ZSCOPE_USER_TRIGGER_MODE_CONT) && !((ZTK_HostGetTicks() - gDev.timestamp.trigger) < lTriggerHoldoff)) {
                            if ((lCount = ZDX_TriggerCheck(gDev.trigger, gDev.data, lTriggerChannel))) {
                                gDev.timestamp.trigger = ZTK_HostGetTicks();
                                if (lTriggerHoldoff) {gDev.counter.trigger++;} else {gDev.counter.trigger += lCount;}
                                gDia.offset.data.xU = (gDev.trigger->level.xU < gDia.offset.grid.xU) ? (gDev.data->block.yU - gDia.offset.grid.xU + gDev.trigger->level.xU) : (gDev.trigger->level.xU - gDia.offset.grid.xU);
                            }
                        } else if ((lTriggerMode == ZSCOPE_USER_TRIGGER_MODE_SINGLE) && !(gDev.flag & ZSCOPE_DEVICE_FLAG_HALT)) {
                            if ((lCount = ZDX_TriggerCheck(gDev.trigger, gDev.data, lTriggerChannel))) {
                                gDev.timestamp.trigger = ZTK_HostGetTicks();
                                gDev.counter.trigger += lCount;
                                gDev.flag |= ZSCOPE_DEVICE_FLAG_HALT;
                                gDia.offset.data.xU = (gDev.trigger->level.xU < gDia.offset.grid.xU) ? (gDev.data->block.yU - gDia.offset.grid.xU + gDev.trigger->level.xU) : (gDev.trigger->level.xU - gDia.offset.grid.xU);
                            }
                        }

                    }
                    ZT_INDEX lDelta;
                    if (lTriggerMode == ZSCOPE_USER_TRIGGER_MODE_SINGLE && gDev.flag & ZSCOPE_DEVICE_FLAG_HALT) {
                        gDev.trigger->cursor = gDev.data->cursor;
                        lDelta = (gDev.trigger->level.xU > gDev.data->cursor) ? (gDev.data->block.yU - gDev.trigger->level.xU + gDev.data->cursor) : (gDev.data->cursor - gDev.trigger->level.xU);
                        if (lDelta > gDev.data->block.yU / 4) {ZSDEV_Capture(ZT_FALSE);}
                    } else {
                        if (gDia.plot->block.xU) {
                            while ((lDelta = (gDia.offset.data.xU > gDev.data->cursor) ? (gDev.data->block.yU - gDia.offset.data.xU + gDev.data->cursor) : (gDev.data->cursor - gDia.offset.data.xU)) > gDia.plot->block.xU) {
                                gDia.offset.data.xU += gDia.plot->block.xU;
                                gDia.offset.data.xU %= gDev.data->block.yU;
                            }
                        }
                    }
                }
            }
        } else {
            ZDX_Read(gDev.hardware, NULL);
        }
    }
}
void ZSDEV_FreeTrigger(void) {
    gDia.diagram->data.trigger = NULL;
    if (gDev.trigger != NULL) {ZDX_TriggerFree(gDev.trigger); gDev.trigger = NULL;}
}
void ZSDEV_FreeData(void) {
    if (gDev.data != NULL) {ZDX_DataFree(gDev.data); gDev.data = NULL;}
}
void ZSDEV_FreeHardware(void) {
    if (gDev.hardware != NULL) {ZDX_Free(gDev.hardware); gDev.hardware = NULL;}
}
void ZSDEV_Disconnect(void) {
    ZSDEV_FreeHardware();
}
void ZSDEV_Free(void) {
    ZSDEV_FreeHardware();
    ZSDEV_FreeTrigger();
    ZSDEV_FreeData();
}
void ZSDEV_LoadGUI(void) {
    if (gDev.hardware != NULL) {
        ZUI_DataValue(gGUI.menu.device.channel, ZDX_GetChannels(gDev.hardware));
        ZUI_DataValue(gGUI.menu.device.speed, ZDX_GetSpeed(gDev.hardware));
        const ZT_CHAR* lAddress;
        if ((lAddress = gDev.hardware->address) != NULL) {
            ZT_INDEX lAddressID = 0;
            ZT_INDEX lLength = ZTC8_GetLength(lAddress);
            if (lLength < 9) {
                lAddressID += lAddress[7] - ZTM_CHAR_0;
            } else if (lLength < 10) {
                lAddressID += (lAddress[7] - ZTM_CHAR_0) * 10;
                lAddressID += lAddress[8] - ZTM_CHAR_0;
            } else if (lLength < 11) {
                lAddressID += (lAddress[7] - ZTM_CHAR_0) * 100;
                lAddressID += (lAddress[8] - ZTM_CHAR_0) * 10;
                lAddressID += lAddress[9] - ZTM_CHAR_0;
            }
            ZUI_DataValue(gGUI.menu.device.address, lAddressID);
        }
    }
}
void ZSDEV_Connect(const ZT_CHAR* iAddress, ZT_INDEX iSpeed, ZT_FLAG iChannels) {
    ZSDEV_Free();
    if ((gDev.hardware = ZDX_New(iAddress, ZDX_DEVICE_TYPE_AT328P)) != NULL) {
        ZDX_Assign(gDev.hardware, ZDX_CHANNEL_TYPE_ANALOG_IN, iChannels, iSpeed);
        gDev.hardware->flag |= ZDX_DEVICE_FLAG_UNBUFFERED;
        if ((gDev.data = ZDX_DataNew(gDev.hardware, iSpeed / 10)) != NULL) {
            if ((gDev.trigger = ZDX_TriggerNew()) != NULL) {
                gDev.trigger->type = ZDX_TRIGGER_TYPE_FALLING;
                gDev.trigger->level.xU = -1;
                gDev.trigger->level.yU = (1 << gDev.data->resolution) >> 1;
                ZDX_Connect(gDev.hardware);
                if (gDev.hardware->interface != NULL) {
                    if (gDev.hardware->interface->runtime != NULL) {
                        gDev.timestamp.connect = ZTK_HostGetTicks();
                        ZSDEV_Capture(ZT_TRUE);
                        return;
                    }
                }
                ZSDEV_FreeTrigger();
            }
            ZSDEV_FreeData();
        }
        ZSDEV_FreeHardware();
    }
}
void ZSDEV_TriggerLevel(ZT_I iIncrement) {
    if (gDia.diagram->data.trigger != NULL) {
        if (gDev.trigger != NULL && gDev.data != NULL) {
            ZT_U lIncrement;
            if (iIncrement < 0) {
                lIncrement = -iIncrement;
                gDev.trigger->level.yU = (gDev.trigger->level.yU < lIncrement) ? ((1 << gDev.data->resolution) - lIncrement + gDev.trigger->level.yU) : (gDev.trigger->level.yU - lIncrement);
            } else {
                lIncrement = iIncrement;
                gDev.trigger->level.yU += lIncrement;
                gDev.trigger->level.yU %= (1 << gDev.data->resolution);
            }
        }
    }
}
void ZSDEV_TriggerFlank(ZT_FLAG iType) {
    if (gDev.trigger != NULL) {
        gDev.trigger->type = iType;
    }
}

#endif //ZS_DEVICE_C_INCLUDED

