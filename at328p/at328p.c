/*** Copyright (C) 2019-2025 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/

// v250815 (functionally equivalent to v210603, different formatting)

#include <avr/io.h>

#define ZDX_MAX_CH 8
#define ZDX_PACKET_BUFF 16

#define ZDX_MODE_ADC 0x0
#define ZDX_MODE_MIX 0x1
#define ZDX_MODE_DIO 0x2
#define ZDX_MODE_PWM 0x3

#define ZDX_PACKETS_ADC 9
#define ZDX_PACKETS_MIX 12
#define ZDX_PACKETS_DIO 2
#define ZDX_PACKETS_PWM 6

unsigned char gADC_Config;
unsigned long gADC_Timer;
unsigned char gDIO_Config;
unsigned char gPWM_Config;
unsigned int gPWM_Depth;
unsigned int gPWM_Timer;

void ZDX_ADC_Timer(void) {
	unsigned int lTimer;
	unsigned char lPrescale;
	if (gADC_Timer < 0x10000UL) {
		lPrescale = 0x1;
		lTimer = gADC_Timer;
	} else if (gADC_Timer < 0x80000UL) {
		lPrescale = 0x2;
		lTimer = gADC_Timer >> 3;
	} else if (gADC_Timer < 0x400000UL) {
		lPrescale = 0x3;
		lTimer = gADC_Timer >> 6;
	} else if (gADC_Timer < 0x1000000UL) {
		lPrescale = 0x4;
		lTimer = gADC_Timer >> 8;
	} else {
		lPrescale = 0x5;
		lTimer = gADC_Timer >> 10;
	}
	OCR1A = lTimer;
	TCCR1A = 0x0;
	TCCR1B = 0x8 | lPrescale;
}
void ZDX_ADC_Clock(unsigned char iChannels) {
	unsigned long lPrescale = 16UL * 0x2UL * (unsigned long)iChannels;
	unsigned char i = 0;
	while ((gADC_Timer > lPrescale) && (i < 7)) {
		++i;
		lPrescale <<= 1;
	}
	ADCSRB = 0x0;
	ADCSRA = 0x80 | i;
}
void ZDX_ADC_Init(void) {
	UCSR0B = 0x8;
	DIDR0 = 0x3f;
	DIDR1 = 0x3;
	ADMUX |= 0x40;
}
void ZDX_ADC_Main(void) {
	#define mZDX_ADC_Main_INCREMENT() lTransmit = lRead; if (++lRead == lChannels) {lRead = 0;} ADMUX &= 0xf0; ADMUX |= lPort[lRead]
	unsigned char lPort[ZDX_MAX_CH];
	unsigned char lChannels = 0;
	unsigned char lTransmit;
	unsigned char lRead = 0;
	for (unsigned char i = 0; i < ZDX_MAX_CH; i++) {if (gADC_Config & (1 << i)) {lPort[lChannels++] = i;}}
	ZDX_ADC_Init();
	ZDX_ADC_Clock(lChannels);
	ZDX_ADC_Timer();
	mZDX_ADC_Main_INCREMENT();
	while(0x1) {
		unsigned char lAcquire = lChannels;
		do {
			if (!(ADCSRA & 0x40)) {
				unsigned char lSampleL = ADCL;
				unsigned char lSampleH = ADCH;
				ADCSRA |= 0x40;
				while (!(UCSR0A & 0x20));
				UDR0 = 0x80 | (lTransmit << 3) | (lSampleH << 1) | (lSampleL >> 7);
				while (!(UCSR0A & 0x20));
				UDR0 = lSampleL & 0x7f;
				mZDX_ADC_Main_INCREMENT();
				--lAcquire;
			}
		} while (lAcquire);
		while (!(TIFR1 & 0x2));
		TIFR1 |= 0x2;
	}
	#undef mZDX_ADC_Main_INCREMENT
}
void ZDX_DIO_Write(unsigned char iState) {
	iState &= gDIO_Config;
	unsigned char lPortB = iState & 0x3;
	unsigned char lPortD = iState & 0xfc;
	PORTB &= lPortB;
	PORTD &= lPortD;
	PORTB |= lPortB;
	PORTD |= lPortD;
}
void ZDX_DIO_Init(void) {
	DDRB = gDIO_Config & 0x3;
	DDRD = gDIO_Config & 0xfc;
}
void ZDX_DIO_Main(void) {
	ZDX_DIO_Init();
	while(0x1) {if (UCSR0A & 0x80) {ZDX_DIO_Write(UDR0);}}
}
void ZDX_MIX_Main(void) {
	while(0x1) {__asm__("nop\n\t");}
}
void ZDX_PWM_Init(void) {
	DDRB = gPWM_Config & 0x3;
	DDRD = gPWM_Config & 0xfc;
	OCR1A = gPWM_Timer; // shouldn't this be one less?
	TCCR1A = 0x0;
	TCCR1B = 0x9;
}
#define mZDX_PWM_MAIN(TYPE) \
	unsigned char lCache = 0x0;\
	TYPE lMax = gPWM_Depth;\
	TYPE lPhase = lMax;\
	TYPE lDuty[8] = {0x0};\
	ZDX_PWM_Init();\
	while (0x1) {\
		if (TIFR1 & 0x2) {\
			TIFR1 |= 0x2;\
			++lPhase;\
			lPhase &= lMax;\
			unsigned char lOut;\
			for (unsigned char i = 8; i;) {lOut <<= 1; lOut |= (lDuty[--i] >= lPhase);}\
			lOut &= gPWM_Config;\
			PORTB = lOut & 0x3;\
			PORTD = lOut & 0xfc;\
		}\
		if (UCSR0A & 0x80) {\
			unsigned char lBuffer = UDR0;\
			if (lCache) {\
				if (!(lBuffer & 0x80)) {lDuty[(lCache >> 3) & 0x7] = ((TYPE)(lCache & 0x7) << 7) | (TYPE)lBuffer;}\
				lCache = 0x0;\
			} else if (lBuffer & 0x80) {\
				lCache = lBuffer;\
			}\
		}\
	}
void ZDX_PWM8_Main(void) {mZDX_PWM_MAIN(unsigned char);}
void ZDX_PWM16_Main(void) {mZDX_PWM_MAIN(unsigned int);}
#undef mZDX_PWM_MAIN
void ZDX_PWM_Main(void) {
	if (gPWM_Depth > 0xff) {
		ZDX_PWM16_Main();
	} else {
		ZDX_PWM8_Main();
	}
}
void ZDX_Init(void) {
	UBRR0L = 0x0;
	UBRR0H = 0x0;
	UCSR0A = 0x2;
	UCSR0B = 0x18;
	UCSR0C = 0x6;
}
unsigned char ZDX_Mode(void) {
	unsigned char lBuffer[ZDX_PACKET_BUFF];
	unsigned char lReceived = 0;
	unsigned char lWait = 0x1;
	unsigned char lMode = 0xff;
	while (lWait) {
		if (UCSR0A & 0x80) {
			lBuffer[lReceived++] = UDR0;
			if (lReceived == 1) {lMode = lBuffer[0];}
			switch (lMode) {
				case ZDX_MODE_ADC:
					if (lReceived == ZDX_PACKETS_ADC) {
						gADC_Timer  = (unsigned long)lBuffer[1] << 24;
						gADC_Timer |= (unsigned long)lBuffer[2] << 16;
						gADC_Timer |= (unsigned long)lBuffer[3] << 8;
						gADC_Timer |= (unsigned long)lBuffer[4];
						gADC_Config = lBuffer[8];
						lWait = 0x0;
					}
					break;
				case ZDX_MODE_MIX:
					if (lReceived == ZDX_PACKETS_MIX) {
						lWait = 0x0;
					}
					break;
				case ZDX_MODE_DIO:
					if (lReceived == ZDX_PACKETS_DIO) {
						gDIO_Config = lBuffer[1];
						lWait = 0x0;
					}
					break;
				case ZDX_MODE_PWM:
					if (lReceived == ZDX_PACKETS_PWM) {
						gPWM_Config = lBuffer[1];
						gPWM_Timer  = (unsigned int)lBuffer[2] << 8;
						gPWM_Timer |= (unsigned int)lBuffer[3];
						gPWM_Depth  = (unsigned int)lBuffer[4] << 8;
						gPWM_Depth |= (unsigned int)lBuffer[5];
						lWait = 0x0;
					}
					break;
				default:
					lWait = 0x0;
					break;
			}
		} else {
			__asm__("nop\n\t");
		}
	}
	return lMode;
}
int main() {
	ZDX_Init();
	switch (ZDX_Mode()) {
		case ZDX_MODE_ADC: ZDX_ADC_Main(); break;
		case ZDX_MODE_MIX: ZDX_MIX_Main(); break;
		case ZDX_MODE_DIO: ZDX_DIO_Main(); break;
		case ZDX_MODE_PWM: ZDX_PWM_Main(); break;
		default: break;
	}
	return 0x0;
}
