/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_H_INCLUDED
#define ZS_H_INCLUDED

#include <ZTK.h>
#include <ZUI.h>
#include <ZDX.h>
#include <ZTX.h>

#include "ZS__Defines.h"
#include "ZS__Types.h"

#include "ZS_Text.h"
#include "ZS_GUI.h"
#include "ZS_Device.h"
#include "ZS_Diagram.h"

const ZT_CHAR* gText[ZSTX_TOTAL];

ZSCOPE_APP gApp;
ZSCOPE_GUI gGUI;
ZSCOPE_USER gUsr;

ZSCOPE_DIAGRAM gDia;
ZSCOPE_DEVICE gDev;

int main(void);
void ZS_Main(void);
void ZS_Draw(void);
void ZS_Init(void);
void ZS_Exit(void);
void ZS_Size(void);
void ZSUSR_Init(void);
void ZSUSR_Load(void);
void ZSUSR_Save(void);
void ZSUSR_Menu(ZT_INDEX iSelection);
void ZS_EventGUI(void);
void ZS_Event(void);
void ZS_TextLoad(ZT_FLAG iLang);
void ZS_SaveMeta(const ZT_CHAR* iReference);

#endif // ZS_H_INCLUDED
