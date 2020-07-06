/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZSCOPE_H_INCLUDED
#define ZSCOPE_H_INCLUDED

#include <ZTK.h>
#include <ZDX.h>

// temporary
#define ZSCOPE_DEFAULT_ADDRESS 3
#define ZSCOPE_DEFAULT_CONFIG 0x1
#define ZSCOPE_DEFAULT_SPEED 100000

#include "ZScope__Defines.h"
#include "ZScope__Types.h"

#include "ZScope_Text.h"
#include "ZScope_GUI.h"
#include "ZScope_Device.h"
#include "ZScope_Diagram.h"

ZSCOPE_APP gApp;
ZSCOPE_GUI gGUI;
ZSCOPE_TEXT gTxt;
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
void ZSUSR_Menu(ZT_INDEX iSelection);
void ZS_EventGUI(void);
void ZS_Event(void);

#endif // ZSCOPE_H_INCLUDED
