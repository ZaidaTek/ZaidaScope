/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/

// V210309

#define ZDX_MAX_CH 8
#define ZDX_PACKET_BUFF 16

#define ZDX_MODE_FAST 0x0
#define ZDX_MODE_MIX 0x1
#define ZDX_MODE_CTRL 0x2

#define ZDX_PACKET_EXPECT_FAST 9
#define ZDX_PACKET_EXPECT_MIX 12
#define ZDX_PACKET_EXPECT_CTRL 3

#define ZDX_DEFAULT_CHCONFIG 0xff
#define ZDX_DEFAULT_SAMPDLY 1000
#define ZDX_DEFAULT_CFGMODE 0x0


unsigned char gZDX_Mode = ZDX_DEFAULT_CFGMODE;
unsigned char gZDX_Packets[ZDX_PACKET_BUFF] = {0};

unsigned char gAI_ChConfig = ZDX_DEFAULT_CHCONFIG;
unsigned char gAI_ChNum = 0;
unsigned char gAI_ChPin[ZDX_MAX_CH] = {0};
unsigned char gAI_ChIndex = 0;
unsigned char gAI_HiByte = 0;
unsigned char gAI_LoByte = 0;
unsigned char gAI_AcquireSample = 0;
unsigned int gAI_TimerValue = 0;
unsigned long gAI_SampleDelay = ZDX_DEFAULT_SAMPDLY;

unsigned char gDO_ChConfig = 0x0;
unsigned char gDO_ChInit = 0x0;
unsigned char gDO_ChState = 0x0;

void gZDX_Init(void) {
	UBRR0L = 0x0;
	UBRR0H = 0x0;
	UCSR0A = 0x2;
	UCSR0B = 0x18;
	UCSR0C = 0x6;
}
void gZDX_AwaitConfig(void) {
	unsigned char lReceived = 0;
	unsigned char lWait = 0x1;
	while (lWait) {
		if (UCSR0A & 0x80) {
			gZDX_Packets[lReceived] = UDR0;
			if (++lReceived == 1) {gZDX_Mode = gZDX_Packets[0];}
			switch (gZDX_Mode) {
				case ZDX_MODE_FAST:
					if (lReceived == ZDX_PACKET_EXPECT_FAST) {
						gAI_SampleDelay = (long)gZDX_Packets[1] << 24;
						gAI_SampleDelay |= (long)gZDX_Packets[2] << 16;
						gAI_SampleDelay |= (long)gZDX_Packets[3] << 8;
						gAI_SampleDelay |= gZDX_Packets[4];
						gAI_ChConfig = gZDX_Packets[8];
						gAI_AcquireSample = 0x1;
						lWait = 0x0;
					}
					break;
				case ZDX_MODE_MIX:
					if (lReceived == ZDX_PACKET_EXPECT_MIX) {
						lWait = 0x0;
					}
					break;
				case ZDX_MODE_CTRL:
					if (lReceived == ZDX_PACKET_EXPECT_CTRL) {
						gDO_ChConfig = gZDX_Packets[1];
						gDO_ChInit = gZDX_Packets[2];
						gDO_ChState = gDO_ChInit;
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
}
void gZDX_SetAITimer(void) {
	TCCR1A = 0x0;
	if (gAI_SampleDelay < 0x10000) {
		TCCR1B = 0x1;
		gAI_TimerValue = gAI_SampleDelay;
		gAI_TimerValue -= 0xD;
	} else if (gAI_SampleDelay < 0x80000) {
		TCCR1B = 0x2;
		gAI_TimerValue = gAI_SampleDelay >> 3;
		gAI_TimerValue -= 0x1;
	} else if (gAI_SampleDelay < 0x400000) {
		TCCR1B = 0x3;
		gAI_TimerValue = gAI_SampleDelay >> 6;
	} else if (gAI_SampleDelay < 0x1000000) {
		TCCR1B = 0x4;
		gAI_TimerValue = gAI_SampleDelay >> 8;
	} else {
		TCCR1B = 0x5;
		gAI_TimerValue = gAI_SampleDelay >> 10;
	}
	TCNT1 = 0;
}
void gZDX_SetADCClock(void) {
	unsigned long lPrescale = 0x2;
	unsigned char i = 0;
	while (gAI_SampleDelay > (14 * lPrescale * gAI_ChNum) && i < 7) {
		++i;
		lPrescale <<= 1;
	}
	ADCSRB = 0x0;
	ADCSRA = (0x80 | i);
}
void gZDX_SetupDO(void) {
	DDRD &= 0x3;
	DDRD |= ((gDO_ChConfig & 0x3f) << 2);
	DDRB &= 0xfc;
	DDRB |= ((gDO_ChConfig & 0xc0) >> 6);
}

void gZDX_WriteDO(void) {
	unsigned char prototypeD = ((gDO_ChState & 0x3f) << 2);
	unsigned char currentD = PORTD & 0xfc;
	unsigned char toggleD = prototypeD ^ currentD;
	for (unsigned char i = 2; i < 8; i++) {
		unsigned char bitIndex = (1 << i);
		if (toggleD & bitIndex) {
			if (prototypeD & bitIndex) {
				PORTD |= bitIndex;
			} else {
				PORTD &= ~bitIndex;
			}
		}
	}
	unsigned char prototypeB = ((gDO_ChState & 0xc0) >> 6);
	unsigned char currentB = PORTB & 0x3;
	unsigned char toggleB = prototypeB ^ currentB;
	for (unsigned char i = 0; i < 2; i++) {
		unsigned char bitIndex = (1 << i);
		if (toggleB & bitIndex) {
			if (prototypeB & bitIndex) {
				PORTB |= bitIndex;
			} else {
				PORTB &= ~bitIndex;
			}
		}
	}
}

void gZDX_Main_Fast(void) {
	while(0x1) {
		while(gAI_AcquireSample) {
			if (ADCSRA & 0x40) {
				if ((ADMUX & 0xf) == gAI_ChPin[gAI_ChIndex]) {
					gAI_ChIndex = (gAI_ChIndex ? gAI_ChIndex : gAI_ChNum) - 1;
					gZDX_Packets[0] = 0x80 | (gAI_ChIndex << 3);
					gZDX_Packets[0] |= (gAI_HiByte << 1) | (gAI_LoByte >> 7);
					while (!(UCSR0A & 0x20));
					UDR0 = gZDX_Packets[0];
					while (!(UCSR0A & 0x20));
					UDR0 = (gAI_LoByte & 0x7f);
					--gAI_AcquireSample;
				}
			} else {
				gAI_LoByte = ADCL;
				gAI_HiByte = ADCH;
				gAI_ChIndex = (gAI_ChNum - gAI_AcquireSample) & 0x7;
				ADMUX = 0x40 | gAI_ChPin[gAI_ChIndex];
				ADCSRA |= 0x40;
			}
		}
		while (!(TIFR1 & 0x1));
		TIFR1 |= 0x1;
		TCNT1 -= gAI_TimerValue;
		gAI_AcquireSample = gAI_ChNum;
	}
}

void gZDX_Main_Mix(void) {
	while(0x1) {
		__asm__("nop\n\t");  
	}
}

void gZDX_Main_Ctrl(void) {
	while(0x1) {
		if (UCSR0A & 0x80) {gDO_ChState = UDR0;}
		gZDX_WriteDO();
	}
}


int main() {
	gZDX_Init();
	gZDX_AwaitConfig();
	switch (gZDX_Mode) {
		case ZDX_MODE_MIX:
			gZDX_Main_Mix();
			break;
		case ZDX_MODE_CTRL:
			gZDX_SetupDO();
			gZDX_Main_Ctrl();
			break;
		default:
		case ZDX_MODE_FAST:
			UCSR0B = 0x8;
			for (unsigned char i = 0; i < ZDX_MAX_CH; i++) {
				if (gAI_ChConfig & (1 << i)) {
				  gAI_ChPin[gAI_ChNum] = (i & 0x7);
				  ++gAI_ChNum;
				}
			}
			DIDR0 = 0xff;
			DIDR1 = 0x3;
			gZDX_SetADCClock();
			gZDX_SetAITimer();
			gAI_AcquireSample = gAI_ChNum;
			gZDX_Main_Fast();
			break;
	}
	return 0;
}
