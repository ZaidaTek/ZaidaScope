/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_DEVICE_C_INCLUDED
#define ZS_DEVICE_C_INCLUDED

#include "ZS_Device.h"

void ZSDEV_WriteData(void) {
    if (gDev.data != NULL) {
        ZT_INDEX lLength = gDev.data->block.yU;
        ZT_INDEX lDelta = (gDev.data->cursor < gDev.counter.record) ? (lLength - gDev.counter.record + gDev.data->cursor) : (gDev.data->cursor - gDev.counter.record);
        if (lDelta) {
            ZT_INDEX lChannels = gDev.data->block.xU;
            ZT_INDEX lChannelLast = lChannels - 1;
            ZWV_Empty();
            for (ZT_INDEX y = 0; y < lDelta; ++y) {
                ZT_U* lSample = &(gDev.data->data[gDev.counter.record * lChannels]);
                for (ZT_INDEX x = 0; x < lChannels; ++x) {ZWV_AddUnsigned(lSample[x]); if (x < lChannelLast) {ZWV_Add(",");} else {ZWV_Add("\n");}}
                ++gDev.counter.record;
                gDev.counter.record %= lLength;
            }
            ZIO_PipedAppend(gDev.path.record, gDev.recorder->data.byte, gDev.recorder->data.length);
        }
        gDev.timestamp.record = ZTL_Tick();
    }
}
void ZSDEV_Record(ZT_FLAG iState) {
    if (gDev.data != NULL) {
        ZT_FLAG lState = (gDev.flag & ZSCOPE_DEVICE_FLAG_RECORD) ? ZT_TRUE : ZT_FALSE;
        if (lState ^ ((iState == (ZT_FLAG)-1) ? (lState ? ZT_FALSE : ZT_TRUE) : iState)) {
            if (lState) {
                ZSDEV_WriteData();
                gDev.flag &= ~ZSCOPE_DEVICE_FLAG_RECORD;
            } else {
                gDev.timestamp.record = ZTL_Tick();
                gDev.counter.record = gDev.data->cursor;
                if (gDev.path.record != NULL) {ZTM8_Free(gDev.path.record);}
                ZS_SaveMeta(gDev.path.record = ZTC8_PathFileISO(NULL, (const ZT_CHAR*)"csv", ZTM_Time()));
                gDev.flag |= ZSCOPE_DEVICE_FLAG_RECORD;
            }
        }
    } else {
        gDev.flag &= ~ZSCOPE_DEVICE_FLAG_RECORD;
    }
    ZUI_DataValue(gGUI.hud.record, (gDev.flag & ZSCOPE_DEVICE_FLAG_RECORD ? 0x1 : 0x0));
}
void ZSDEV_Capture(ZT_FLAG iState) {
    switch (iState) {
        default:
        case ZT_TRUE: gDev.flag |= ZSCOPE_DEVICE_FLAG_CAPTURE; break;
        case ZT_FALSE: gDev.flag &= ~ZSCOPE_DEVICE_FLAG_CAPTURE; break;
        case -1: gDev.flag ^= ZSCOPE_DEVICE_FLAG_CAPTURE; break;
    }
    gDev.flag &= ~ZSCOPE_DEVICE_FLAG_HALT;
    ZUI_DataValue(gGUI.hud.capture, (gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE ? 0x1 : 0x0));
    if (!(gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE)) {ZSDEV_Record(ZT_FALSE);}
}
void ZSDEV_Read(void) {
    if (gDev.hardware != NULL) {
        if (gDev.flag & ZSCOPE_DEVICE_FLAG_CAPTURE) {
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
                        ZT_TIME lNow = ZTL_Tick();
                        if ((lTriggerMode == ZSCOPE_USER_TRIGGER_MODE_CONT) && !((lNow - gDev.timestamp.trigger) < lTriggerHoldoff)) {
                            if ((lCount = ZDX_TriggerCheck(gDev.trigger, gDev.data, lTriggerChannel))) {
                                gDev.timestamp.trigger = lNow;
                                if (lTriggerHoldoff) {gDev.counter.trigger++;} else {gDev.counter.trigger += lCount;}
                                gDia.offset.data.xU = (gDev.trigger->level.xU < gDia.offset.grid.xU) ? (gDev.data->block.yU - gDia.offset.grid.xU + gDev.trigger->level.xU) : (gDev.trigger->level.xU - gDia.offset.grid.xU);
                            }
                        } else if ((lTriggerMode == ZSCOPE_USER_TRIGGER_MODE_SINGLE) && !(gDev.flag & ZSCOPE_DEVICE_FLAG_HALT)) {
                            if ((lCount = ZDX_TriggerCheck(gDev.trigger, gDev.data, lTriggerChannel))) {
                                gDev.timestamp.trigger = lNow;
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
                    } else if (gDia.plot->block.xU) {
                        while ((lDelta = (gDia.offset.data.xU > gDev.data->cursor) ? (gDev.data->block.yU - gDia.offset.data.xU + gDev.data->cursor) : (gDev.data->cursor - gDia.offset.data.xU)) > gDia.plot->block.xU) {
                            gDia.offset.data.xU += gDia.plot->block.xU;
                            gDia.offset.data.xU %= gDev.data->block.yU;
                        }
                    }
                }
            }
            if (gDev.flag & ZSCOPE_DEVICE_FLAG_RECORD && ZTK_Timeout(gDev.timestamp.record, 1000)) {ZSDEV_WriteData();}
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
void ZSDEV_FreeRecorder(void) {
    if (gDev.recorder != NULL) {
        ZTM_DoNull(ZWV_Free, gDev.recorder);
        ZTM_DoNull(ZTM8_Free, gDev.path.record);
    }
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
    ZSDEV_FreeRecorder();
    ZSDEV_FreeData();
}
void ZSDEV_LoadGUI(void) {
    if (gDev.hardware != NULL) {
        ZUI_DataValue(gGUI.menu.device.channel, ZDX_GetChannels(gDev.hardware));
        ZUI_DataValue(gGUI.menu.device.speed, ZDX_GetSpeed(gDev.hardware));
        const ZT_CHAR* lAddress;
        if ((lAddress = gDev.hardware->address) != NULL) {
            ZUI_DataValue(gGUI.menu.device.address, ZTL_SerialPort(lAddress));
        }
    }
}
void ZSDEV_Connect(const ZT_CHAR* iAddress, ZT_INDEX iSpeed, ZT_FLAG iChannels) {
    ZSDEV_Free();
    if ((gDev.hardware = ZDX_New(iAddress, ZDX_DEVICE_TYPE_AT328P)) != NULL) {
        ZDX_Assign(gDev.hardware, ZDX_CHANNEL_TYPE_ANALOG_IN, iChannels, iSpeed);
        gDev.hardware->flag |= ZDX_DEVICE_FLAG_UNBUFFERED;
        if ((gDev.data = ZDX_DataNew(gDev.hardware, iSpeed / 10)) != NULL) {
            if ((gDev.recorder = ZWV_New(6 * gDev.data->block.xU * gDev.data->block.yU)) != NULL) {
                ZWV_Set(gDev.recorder);
                if ((gDev.trigger = ZDX_TriggerNew()) != NULL) {
                    gDev.trigger->type = ZDX_TRIGGER_TYPE_FALLING;
                    gDev.trigger->level.xU = -1;
                    gDev.trigger->level.yU = (0x1 << gDev.data->resolution) >> 1;
                    ZDX_Connect(gDev.hardware);
                    if (gDev.hardware->interface.runtime != NULL) {
                        gDev.timestamp.connect = ZTL_Tick();
                        ZSDEV_Capture(ZT_TRUE);
                        ZSDEV_Record(ZT_FALSE);
                        return;
                    }
                    ZSDEV_FreeTrigger();
                }
                ZSDEV_FreeRecorder();
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

