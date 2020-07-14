/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZS__TYPES_H_INCLUDED
#define ZS__TYPES_H_INCLUDED

#include "ZS.h"

typedef struct {
    ZDX_DEVICE* hardware;
    ZDX_DATA* data;
    ZDX_TRIGGER* trigger;
    ZT_FLAG flag;
    struct {
        ZT_TIME connect;
        ZT_TIME trigger;
    } timestamp;
    struct {
        ZT_INDEX trigger;
    } counter;
    struct {
        ZT_INDEX trigger;
    } stat;
} ZSCOPE_DEVICE;

typedef struct {
    ZT_SURFACE* plot;
    ZDX_DIAGRAM* diagram;
    struct {
        ZT_UPOINT data;
        ZT_UPOINT grid;
        struct {
            ZT_UPOINT horizontal;
            ZT_UPOINT vertical;
        } cursor;
    } offset;
    struct {
        ZT_POINT major;
        ZT_POINT minor;
    } grid;
    struct {
        struct {
            ZT_COLOR major;
            ZT_COLOR minor;
        } grid;
        struct {
            ZT_COLOR data;
            ZT_COLOR first;
            ZT_COLOR second;
        } cursor;
        ZT_COLOR background;
        ZT_COLOR trigger;
        ZT_COLOR plot[8];
    } color;
} ZSCOPE_DIAGRAM;

typedef struct {
    ZT_FLAG flag;
    ZT_FLAG lang;
    ZT_FLAG menu;
} ZSCOPE_USER;

typedef struct {
	struct {
		const ZT_CHAR* title;
		struct {
			const ZT_CHAR* device;
			const ZT_CHAR* help;
			const ZT_CHAR* credits;
			const ZT_CHAR* exit;
		} head;
		struct {
			const ZT_CHAR* connect;
			const ZT_CHAR* disconnect;
			struct {
			    struct {
			        const ZT_CHAR* title;
			    } address;
			    struct {
			        const ZT_CHAR* title;
			        const ZT_CHAR* right;
			    } speed;
			    struct {
			        const ZT_CHAR* title;
			        const ZT_CHAR* left;
			        const ZT_CHAR* right;
			    } channel;
			} label;
		} device;
		struct {
			const ZT_CHAR* desc;
		} help;
		struct {
			const ZT_CHAR* desc;
		} credits;
	} menu;
	struct {
		const ZT_CHAR* menu;
		struct {
            const ZT_CHAR* resume;
            const ZT_CHAR* running;
		} capture;
		struct {
			const ZT_CHAR* diagram;
			const ZT_CHAR* trigger;
			const ZT_CHAR* measure;
			const ZT_CHAR* cursor;
			const ZT_CHAR* setting;
		} selector;
		struct {
		    struct {
		        const ZT_CHAR* scan;
		        const ZT_CHAR* fixed;
		    } type;
            const ZT_CHAR* reset;
		} diagram;
		struct {
		    struct {
		        const ZT_CHAR* none;
		        const ZT_CHAR* cont;
		        const ZT_CHAR* single;
		    } mode;
		    struct {
		        const ZT_CHAR* rising;
		        const ZT_CHAR* falling;
		    } type;
		    struct {
		        const ZT_CHAR* ch1;
		        const ZT_CHAR* ch2;
		        const ZT_CHAR* ch3;
		        const ZT_CHAR* ch4;
		        const ZT_CHAR* ch5;
		        const ZT_CHAR* ch6;
		        const ZT_CHAR* ch7;
		        const ZT_CHAR* ch8;
		    } channel;
		    struct {
		        struct {
		            const ZT_CHAR* title;
		            const ZT_CHAR* right;
		        } holdoff;
		    } label;
		} trigger;
		struct {
		    struct {
		        const ZT_CHAR* raw;
		        const ZT_CHAR* volt;
		    } unit;
		} measure;
		struct {
		    struct {
		        const ZT_CHAR* none;
		        const ZT_CHAR* time;
		        const ZT_CHAR* volt;
		    } type;
		    struct {
		        const ZT_CHAR* first;
		        const ZT_CHAR* second;
		    } target;
		} cursor;
	} hud;
	struct {
		const ZT_CHAR* title;
	} window;
} ZSCOPE_TEXT;

typedef struct {
	struct {
		ZUI_BOX* box;
        ZUI_LABEL* title;
		struct {
			ZUI_BUTTON* device;
			ZUI_BUTTON* help;
			ZUI_BUTTON* credits;
			ZUI_BUTTON* exit;
		} head;
		struct {
            ZUI_INCREMENT* address;
            ZUI_INCREMENT* speed;
            ZUI_SWITCH* channel;
			ZUI_BUTTON* connect;
			ZUI_BUTTON* disconnect;
			struct {
			    struct {
                    ZUI_LABEL* title;
			    } address;
			    struct {
                    ZUI_LABEL* title;
                    ZUI_LABEL* right;
			    } speed;
			    struct {
                    ZUI_LABEL* title;
                    ZUI_LABEL* left;
                    ZUI_LABEL* right;
			    } channel;
			} label;
		} device;
		struct {
			ZUI_LABEL* desc;
		} help;
		struct {
			ZUI_LABEL* desc;
		} credits;
	} menu;
	struct {
		ZUI_BUTTON* menu;
        ZUI_SWITCH* capture;
        ZUI_CYCLE* selector;
		struct {
			ZUI_BOX* top;
			ZUI_BOX* bottom;
		} box;
		struct {
			ZUI_CYCLE* type;
            ZUI_BUTTON* reset;
		} diagram;
		struct {
			ZUI_CYCLE* mode;
			ZUI_CYCLE* type;
			ZUI_CYCLE* channel;
			ZUI_INCREMENT* holdoff;
			struct {
			    struct {
                    ZUI_LABEL* title;
                    ZUI_LABEL* right;
			    } holdoff;
			} label;
		} trigger;
		struct {
			ZUI_CYCLE* unit;
		} measure;
		struct {
			ZUI_CYCLE* type;
			ZUI_CYCLE* target;
		} cursor;
		struct {
			ZUI_BUTTON* spawn;
			ZUI_BUTTON* wipe;
			ZUI_BUTTON* save;
		} setting;
	} hud;
} ZSCOPE_GUI;

typedef struct {
    struct {
        ZT_EVENT* window;
        ZT_EVENT* gui;
    } event;
    ZT_PRINTER* printer;
    struct {
        ZT_FONT* window;
        ZT_FONT* title;
        ZT_FONT* desc;
    } font;
    struct {
        ZT_INDEX fps;
    } counter;
    struct {
        ZT_INDEX fps;
    } stat;
    struct {
        ZT_TIME fps;
        ZT_TIME draw;
        ZT_TIME capture;
    } timestamp;
    struct {
        ZT_TIME fps;
        ZT_TIME draw;
        ZT_TIME capture;
    } timeout;
    ZT_FLAG flag;
    struct {
        struct {
            ZT_POINT hud;
            ZT_POINT hudHalf;
         } button;
        ZT_I font;
        ZT_I fontTitle;
    } dim;
    struct {
        ZT_POINT fps;
        ZT_POINT daq;
        ZT_POINT trigger;
        ZT_POINT xfer;
        ZT_POINT measure[8];
    } pos;
    struct {
        ZT_RECT window;
        ZT_RECT plot;
    } rect;
} ZSCOPE_APP;

#endif // ZS__TYPES_H_INCLUDED
