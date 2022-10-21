/* 
 * File:   T6963.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. április 28., 13:46
 */

// Library file for Toshiba T6963C Graphic LCD Controller by TpSz
// Version: 1.2


#include <xc.h>

#ifndef T6963_H
#define	T6963_H

#ifdef	__cplusplus
extern "C" {
#endif

#define pgm_read_byte(x) (*(x))
#define pgm_read_word(x) (*(x))
#define pgm_read_float(x) (*(x))

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define byte unsigned char

#define LCD_E   LATBbits.LATB2
#define LCD_CD  LATBbits.LATB3
#define LCD_R   LATEbits.LATE1
#define LCD_W   LATEbits.LATE0

#define RST     LATBbits.LATB4

#define pixHoriz    240
#define pixVert 64
#define sizeMem 32
#define fontWidth 6
#define _FW fontWidth
#define fontHeight 8
#define _GA (pixHoriz / fontWidth)	//Supercedes GLCD_GRAPHIC_AREA
#define _TA (pixHoriz / fontWidth)	//Supercedes GLCD_TEXT_AREA
#define _sizeMem (constrain(sizeMem,0,64)) //size of attached memory in kb.
#define sizeGA (_GA*pixVert)	//Supercedes GLCD_GRAPHIC_SIZE
#define sizeTA (_TA*pixVert/8)     //Supercedes GLCD_TEXT_SIZE

// ------ GLCD ----------------------------------------------------------------------------

const unsigned char T6963_CURSOR_PATTERN_SELECT=0xA0; //cursor patter select command prefix or with desired size-1.
const unsigned char T6963_DISPLAY_MODE=0x90;
const unsigned char T6963_MODE_SET=0x80;
const unsigned char T6963_SET_CURSOR_POINTER=0x21;
const unsigned char T6963_SET_OFFSET_REGISTER=0x22;
const unsigned char T6963_SET_ADDRESS_POINTER=0x24;
const unsigned char T6963_SET_TEXT_HOME_ADDRESS=0x40;
const unsigned char T6963_SET_TEXT_AREA=0x41;
const unsigned char T6963_SET_GRAPHIC_HOME_ADDRESS=0x42;
const unsigned char T6963_SET_GRAPHIC_AREA=0x43;
const unsigned char T6963_SET_DATA_AUTO_WRITE=0xB0;
const unsigned char T6963_SET_DATA_AUTO_READ=0xB1;
const unsigned char T6963_AUTO_RESET=0xB2;

const unsigned char T6963_DATA_WRITE_AND_INCREMENT=0xC0;
const unsigned char T6963_DATA_READ_AND_INCREMENT=0xC1;
const unsigned char T6963_DATA_WRITE_AND_DECREMENT=0xC2;
const unsigned char T6963_DATA_READ_AND_DECREMENT=0xC3;
const unsigned char T6963_DATA_WRITE_AND_NONVARIALBE=0xC4;
const unsigned char T6963_DATA_READ_AND_NONVARIABLE=0xC5;

const unsigned char T6963_SCREEN_PEEK=0xE0;
const unsigned char T6963_SCREEN_COPY=0xE8;

unsigned int _TH=0; // text home
unsigned int _GH=0; // graphics home?


void Init_GLCD(void);
void Init_Interface(void);
unsigned char ReadStatus_GLCD();
void writeCommand_GLCD(unsigned char);
void delay_GLCD(unsigned long int);
void writeData_GLCD(unsigned char);
unsigned char readData_GLCD();
void SetAddress_GLCD (unsigned int);
void WriteDisplayData(unsigned char x);
void writeDataNon(unsigned char);
void writeDataDec(unsigned char );
unsigned char setTextAttrMode(char _mode);
void setTH (unsigned int);
void setGH (unsigned int);
void clearDispMode();
void clearGraphic();
void clearText_GLCD();
void DefineCharacter(char charCode, const unsigned char * defChar);
void writeString_GLCD(const char *);
void writeCharDec_GLCD(char);
void writeChar_GLCD(char);
void writePixel(unsigned char , unsigned char , unsigned char);
unsigned char setPixel(unsigned char x, unsigned char y);
unsigned char clearPixel(unsigned char x, unsigned char y);
void drawrectbyte(unsigned int x, unsigned int y, unsigned int HEIGHT, unsigned int BYTEWIDTH, unsigned char pattern);
void glcd_print2_P(unsigned char x,unsigned char y, char *in, const struct FONT_DEF *strcut1);
void lcd_print2(unsigned int x,unsigned int y, const char *in, const struct FONT_DEF *strcut1, unsigned char invers);
void lcd_print2_p(unsigned int x,unsigned int y, const char *in, const struct FONT_DEF *strcut1, unsigned char invers);
void clearCG();
unsigned char setMode(char , char );
void TextGoTo(unsigned char , unsigned char );
void GraphicGoTo(unsigned char x, unsigned char y);
unsigned char setDispMode(unsigned char ,unsigned char ,unsigned char, unsigned char );
void setCursorPointer(unsigned char _col,unsigned char _row);
void plot8points(int, int, int, int, unsigned char);
void plot4points(int, int, int, int, unsigned char);
void Rectangle(unsigned char , unsigned char , unsigned char , unsigned char , unsigned char );
void dsp_long (unsigned long val);
void dsp_sfloat(float);
void dsp_byte (unsigned char val);
void dsp_speed (unsigned char x, unsigned char y,unsigned char val);
void createLine(int x0,int y0,int x1,int y1, unsigned char color);
const char * byte_to_string(unsigned char, unsigned char);
void cls();

// ---- Magyar bet?k ------------------------------------------------
const unsigned char m10 [8]={ // á
   0b00000010,
   0b00000100,
   0b00001110,
   0b00000001,
   0b00001111,
   0b00010001,
   0b00001111,
   0b00000000,
};
const unsigned char m1 [8]={ // é
   0b00000010,
   0b00000100,
   0b00001110,
   0b00010001,
   0b00011111,
   0b00010000,
   0b00001110,
   0b00000000,
};
const unsigned char m2 [8]={ // í
   0b00000010,
   0b00000100,
   0b00000000,
   0b00001100,
   0b00000100,
   0b00000100,
   0b00001110,
   0b00000000,
};
const unsigned char m3 [8]={ // ó
   0b00000010,
   0b00000100,
   0b00001110,
   0b00010001,
   0b00010001,
   0b00010001,
   0b00001110,
   0b00000000,
};
const unsigned char m4 [8]={ //  ?
   0b00000101,
   0b00001010,
   0b00001110,
   0b00010001,
   0b00010001,
   0b00010001,
   0b00001110,
   0b00000000,
};
const unsigned char m5 [8]={ // ú
   0b00000010,
   0b00000100,
   0b00000000,
   0b00010001,
   0b00010001,
   0b00010011,
   0b00001101,
   0b00000000,
};
const unsigned char m6 [8]={ // ?
   0b00000101,
   0b00001010,
   0b00000000,
   0b00010001,
   0b00010001,
   0b00010011,
   0b00001101,
   0b00000000,
};
const unsigned char m7 [8]={0x0A,0x00,0x11,0x11,0x11,0x13,0x0D,0x00,};    //ü
const unsigned char m8 [8]={ // ö
   0b00010100,
   0b00000000,
   0b00011100,
   0b00100010,
   0b00100010,
   0b00100010,
   0b00011100,
   0b00000000,
};
const unsigned char m9 [8]={ // Á
   0b00001000,
   0b00010000,
   0b00001000,
   0b00010100,
   0b00100010,
   0b00111110,
   0b00100010,
   0b00000000,
};
const unsigned char m11 [8]={ // Ü
   0b00010100,
   0b00000000,
   0b00100010,
   0b00100010,
   0b00100010,
   0b00100010,
   0b00011100,
   0b00000000,
};

#ifdef	__cplusplus
}
#endif

#endif	/* T6963_H */

