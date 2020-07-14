/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS_DIAGRAM_H_INCLUDED
#define ZS_DIAGRAM_H_INCLUDED

#include "ZS.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZSDIA_Init(void);
void ZSDIA_Exit(void);
void ZSDIA_Reset(void);
void ZSDIA_Grid(void);
void ZSDIA_Move(ZT_I iIncrement);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZS_DIAGRAM_H_INCLUDED


