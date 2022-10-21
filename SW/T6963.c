/*
 * File:   T6963.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. április 28., 13:46
 */

// Library file for Toshiba T6963C Graphic LCD Controller by TpSz
// Version: 1.2

#include <xc.h>
#include <stdio.h>
//#include <stdlib.h>
#include "T6963.h"
#include "font.h"
#include "Digital7__30.c"
#include "Timer0.h"

// -------- GLCD -----------------------------------------------------------------------------------------------------------

void Init_Interface(void)
{
    ANSELD=0x00;
    ANSELEbits.ANSE0=0x00;
    ANSELEbits.ANSE1=0x00;
    ANSELBbits.ANSB2=0x00;
    ANSELBbits.ANSB3=0x00;
    ANSELBbits.ANSB4=0x00;
    TRISBbits.TRISB2=0x00;
    TRISBbits.TRISB3=0x00;
    TRISBbits.TRISB4=0x00;
    TRISEbits.TRISE0=0x00;
    TRISEbits.TRISE1=0x00;
    TRISD=0x00;
    LATD=0x00;
    LCD_E=1;
    LCD_CD=1;
    LCD_R=1;
    LCD_W=1;
    RST=1;
}

unsigned char ReadStatus_GLCD()
{
    unsigned char tmp=0;
    INTCONbits.GIE=0;
    TRISD=0xFF; // Input
    LCD_CD=1;   // Command
    LCD_W=1;
    LCD_R=0;    // Read
    LCD_E=0;    // Chip Select
    delay_us(4);
    tmp = PORTD; // Status read
    LCD_E=1;    // Disable
    LCD_R=1;    // Not Read
    TRISD=0;    // Output
    INTCONbits.GIE=1;
    return tmp;
}

unsigned char readData_GLCD(void)
{
  unsigned char tmp;
  while(!(ReadStatus_GLCD()&0x03));
  INTCONbits.GIE=0;
  LATD=0;
  TRISD=0xFF; // Input
  LCD_CD=0;   // Data
  LCD_W=1;
  LCD_R=0;    // Read
  LCD_E=0;    // Chip Select
  delay_us(3);
  tmp = PORTD; // Read
  LCD_E=1;    // Disable
  LCD_R=1;    // Not Read
  LCD_CD=1;   // Command
  TRISD=0;    // Output
  INTCONbits.GIE=1;
  return tmp;
}

void writeCommand_GLCD(unsigned char command)
{
    while(!(ReadStatus_GLCD()&0x03));
    INTCONbits.GIE=0;
    TRISD=0; // PORTD Output
    LATD=command;
    LCD_R=1;
    LCD_W=0;    // Write
    LCD_CD=1;   // Command
    LCD_E=0;    // Chip Select
    delay_us(3);
    LCD_E=1;    // Disable
    LCD_W=1;    // Not Write
    INTCONbits.GIE=1;
}

void writeData_GLCD(unsigned char data)
{
  while(!(ReadStatus_GLCD()&0x03));
    INTCONbits.GIE=0;
    TRISD=0; // PORTD Output
    LATD=data;
    LCD_W=0;    // Write
    LCD_CD=0;   // Data
    LCD_E=0;    // Chip Select
    delay_us(3);
    LCD_W=1;    // Not Write
    LCD_CD=1;   // Command
    LCD_E=1;    // Disable
    INTCONbits.GIE=1;
}
void delay_GLCD(unsigned long int i)
{
    unsigned long int j=0;
    for(j=0;j<i;j++)
    {
        asm("nop");
    }
}

void Init_GLCD(void) // Display initalization
{
  //Set up data and control ports
  //delay_GLCD(7500);
  setTH(0);
  setGH(0);
  Init_Interface();
  RST=0;
  delay_us(30);
  RST=1;
  delay_us(3);
  //Set Graphics Home Address
  writeData_GLCD(_GH & 0xFF);
  writeData_GLCD(_GH >> 8);
  writeCommand_GLCD(T6963_SET_GRAPHIC_HOME_ADDRESS);

  //Set Graphics Area
  writeData_GLCD(_GA);
  writeData_GLCD(0x00);
  writeCommand_GLCD(T6963_SET_GRAPHIC_AREA);

  //Set Text home address
  writeData_GLCD(_TH & 0xFF);
  writeData_GLCD(_TH >> 8);
  writeCommand_GLCD(T6963_SET_TEXT_HOME_ADDRESS);

  //Set Text Area
  writeData_GLCD(_TA);
  writeData_GLCD(0x00);
  writeCommand_GLCD(T6963_SET_TEXT_AREA);

  //Set Internal CGRAM address
  writeData_GLCD(((_sizeMem/2)-1));
  writeData_GLCD(0x00);
  writeCommand_GLCD(T6963_SET_OFFSET_REGISTER);


  setDispMode(1,1,0,0);

  setMode('O','I');
  clearCG();
  clearText_GLCD();
  clearGraphic();
  delay_us(255); // Itt 100 ms volt ám...
    DefineCharacter(0x81,m1); // é
    DefineCharacter(0x82,m2); // í
    DefineCharacter(0x83,m3); // ó
    DefineCharacter(0x84,m4); // ?
    DefineCharacter(0x85,m5); // ú
    DefineCharacter(0x86,m6); // ?
    DefineCharacter(0x87,m7); // ü
    DefineCharacter(0x88,m8); // ö
    DefineCharacter(0x89,m9); // Á
    DefineCharacter(0x90,m10); // á
    DefineCharacter(0x91,m11); // Ü
}

void SetAddress_GLCD (unsigned int address) // Sets address pointer for display RAM memory
{
  writeData_GLCD (address & 0xFF);
  writeData_GLCD (address >> 8);
  writeCommand_GLCD(T6963_SET_ADDRESS_POINTER);
}
void clearText_GLCD()
{
  SetAddress_GLCD(_TH);
  int i=0;
  for(i=0;i<sizeTA;i++)
  {
    WriteDisplayData(0x00);
  }
}

void setTH (unsigned int temp)
{
    _TH=temp;
}

void setGH (unsigned int temp)
{
    if(temp == _TH){
    _GH=_TH+sizeTA;
  }
  else{
    _GH=temp;
  }
}

void clearCG() // Clears characters generator area of display RAM memory
{
  unsigned int i=((_sizeMem/2)-1)*0x800;
  SetAddress_GLCD(i);
  for(i = 0; i < 256 * 8; i++){
    WriteDisplayData(0x00);
  }
}

void clearGraphic() // Clears graphics area of display RAM memory
{
  SetAddress_GLCD(_GH);
  for(unsigned int i = 0; i < sizeGA; i++){
    WriteDisplayData(0x00);
  }
}

void writeChar_GLCD(char charCode) // Writes a single character (ASCII code) to display RAM memory
{
      if(charCode=='é')      WriteDisplayData(0x81); //é
      else if(charCode=='í') WriteDisplayData(0x82); // í
      else if(charCode=='ó') WriteDisplayData(0x83); // ó
      else if(charCode=='?') WriteDisplayData(0x84); // ?
      else if(charCode=='ú') WriteDisplayData(0x85); // ú
      else if(charCode=='?') WriteDisplayData(0x86); // ?
      else if(charCode=='ü') WriteDisplayData(0x87); // ü
      else if(charCode=='ö') WriteDisplayData(0x88); // ö
      else if(charCode=='Á') WriteDisplayData(0x89); // Á
      else if(charCode=='á') WriteDisplayData(0x90); // á
      else if(charCode=='Ü') WriteDisplayData(0x91); // Ü
      else WriteDisplayData(charCode - 32);
}
void writeCharDec_GLCD(char charCode)
{
     writeDataDec(charCode - 32); // Writes a single character (ASCII code) to display RAM memory
}
void writeString_GLCD(const char * string) // Writes null-terminated string to display RAM memory
{
  while(*string){
      writeChar_GLCD(*string++);
  }
}
void TextGoTo(unsigned char x, unsigned char y) // Sets display coordinates
{
  unsigned int address;
  address = _TH +  x + (_TA * y);
  SetAddress_GLCD(address);
}
void DefineCharacter(char charCode, const unsigned char * defChar) // Writes single char pattern to character generator area of display RAM memory
{
  unsigned int address=(((((_sizeMem/2)-1)*0x800))|(charCode<<3));
  SetAddress_GLCD(address);
  for(unsigned char i = 0; i < 8 ; i++)
  {
    //WriteDisplayData(0xFF);
    WriteDisplayData(*(defChar + i));
  }
}
void writePixel(unsigned char x, unsigned char y, unsigned char color) //Set (if color==1) or clear (if color==0) pixel on screen
{
  unsigned char tmp;
  unsigned int address;
  address = _GH + (x / _FW) + (_GA * y);
  SetAddress_GLCD(address);
  writeCommand_GLCD(T6963_DATA_READ_AND_NONVARIABLE);
  tmp = readData_GLCD();
  if(color){
    tmp |= (1 <<  (_FW - 1 - (x % _FW)));
  }
  else{
    tmp &= ~(1 <<  (_FW - 1 - (x % _FW)));
  }
  WriteDisplayData(tmp);
}
unsigned char setPixel(unsigned char x, unsigned char y) // Set a single pixel at x,y (in pixels) to 1 (on)
{
  SetAddress_GLCD((_GH + (x / _FW) + (_GA * y)));
  byte tmp=0b11111000;
  tmp |= (_FW-1)-(x%_FW); //LSB Direction Correction
  writeCommand_GLCD(tmp);
  return tmp;
}
byte clearPixel(byte x, byte y){
  SetAddress_GLCD((_GH + (x / _FW) + (_GA * y)));
  byte tmp=0b11110000;
  tmp |= (_FW-1)-(x%_FW); //LSB Direction Correction
  writeCommand_GLCD(tmp);
  return tmp;
} // Set a single pixel at x,y (in pixels) to 0 (off)
void WriteDisplayData(byte x) // Writes display data and increment address pointer
{
	writeData_GLCD(x);
	writeCommand_GLCD(T6963_DATA_WRITE_AND_INCREMENT);
}
void writeDataNon(byte x) // Writes display data
{
	writeData_GLCD(x);
	writeCommand_GLCD(T6963_DATA_WRITE_AND_NONVARIALBE);
}
void writeDataDec(byte x) // Writes display data and decrement address pointer
{
	writeData_GLCD(x);
	writeCommand_GLCD(T6963_DATA_WRITE_AND_DECREMENT);
}
void GraphicGoTo(byte x, byte y) // Sets graphics coordinates
{
  unsigned int address;
  address = _GH + (x / _FW) + (_GA * y);
  SetAddress_GLCD(address);
}
void glcd_print2_P(unsigned char x,unsigned char y, char *in, const struct FONT_DEF *strcut1)
{
	unsigned int offset,swbyte=0;
	unsigned char width, by=0, sbyte=0, mask=0, tmp=0;
	unsigned char NrBytes;
	unsigned char i,j,map,height,Fontwidth=0;

	while((map = *in++))
	{
		map = pgm_read_byte(&strcut1->mapping_table[map]);

		width = strcut1->glyph_width;
		if(width == 0)
			width = pgm_read_byte(&strcut1->width_table[map]);

                NrBytes = ((width-1)/8)+1;

		offset = pgm_read_word(&strcut1->offset_table[map]);
		height = strcut1->glyph_height;

       		for(j=0; j<height*NrBytes; j+=NrBytes)      // height
				{
                   swbyte=0;
                   GraphicGoTo(x+Fontwidth,y+j/NrBytes); //Graphics Pointer

				for(i=0; i<NrBytes; i++)            //  width
                    {
                    by = pgm_read_byte(&strcut1->glyph_table[offset+j+i]); //Read 8bit
                        if( _FW == 6)  //fontWidth
                        {
                             switch(swbyte)         //convert 8bit to 6bit Data for 6bit Font
                            {
							 case 0:                //First Byte
                             sbyte=by>>2;           //First 6 Bit out
                             tmp=by<<4;             //Store last 2 Bits from first Byte
                             swbyte++;
                             break;
                             case 1:               //First Byte and second Byte
                             sbyte=tmp+(by>>4);    //Second 6 Bit out
                             tmp=by<<2;            //Store last 4 Bits from second Byte
                             swbyte++;
                             break;
                             case 2:               //Second and third Byte
                             sbyte=tmp+(by>>6);    //Third 6 Bit out
                             tmp=by;               //Store last 6 Bits from third Byte
                             swbyte++;
                             break;
                             case 3:               //last 6 bits from the third byte
                             sbyte=tmp;            //Fourth 6 Bit out
                             i-=1;                 //i Counter correction while read by
                             swbyte=0;
                             break;
                            }                    //End convert 8bit to 6bit Font
                        WriteDisplayData(sbyte); //6bit Font
                        }
                        else
                          WriteDisplayData(by);  // 8bit Font
					}//End i
                }// End j
		Fontwidth+=_FW*NrBytes;
	}// End K

}
/*
void lcd_print2_p(unsigned int x,unsigned int y, const char *in, const struct FONT_DEF *strcut1, unsigned char invers)
{
	register unsigned int offset,width;
	register unsigned char i,j,map,ertefah,allwidth=0;

	while((map = pgm_read_byte(in++)))
	{
		map = pgm_read_byte(&strcut1->mapping_table[map]);

		width = strcut1->glyph_width;
		if(width == 0)
			width = pgm_read_byte(&strcut1->width_table[map]);

		offset = pgm_read_word(&strcut1->offset_table[map]);
		ertefah = strcut1->glyph_height;


		for(j=0 ; j<ertefah * (((width-1)/8)+1) ; j+=(((width-1)/8)+1)    )
		{   // ertefah
			for(i=0 ; i<width  ; i++)
			{   //  width
				if( pgm_read_byte(&strcut1->glyph_table[ offset+j+(i/8) ]) & (1 << ( 7 - ( i % 8 ) ) ) )
					writePixel(  x+i+allwidth , y+j/ (((width-1)/8)+1), !invers  );
	 			else
	 				writePixel(  x+i+allwidth , y+j/ (((width-1)/8)+1), invers  );
				}//End i
			}// End j
		allwidth+=width;
	}// End K
}

void lcd_print2(unsigned int x,unsigned int y, const char *in, const struct FONT_DEF *strcut1, unsigned char invers)
{
	register unsigned int offset,width;
	register unsigned char i,j,map,ertefah,allwidth=0;

	while((map = *in++))
	{
		map = pgm_read_byte(&strcut1->mapping_table[map]);

		width = strcut1->glyph_width;
		if(width == 0)
			width = pgm_read_byte(&strcut1->width_table[map]);

		offset = pgm_read_word(&strcut1->offset_table[map]);
		ertefah = strcut1->glyph_height;


		for(j=0 ; j<ertefah * (((width-1)/8)+1) ; j+=(((width-1)/8)+1)    )
		{   // ertefah
			for(i=0 ; i<width  ; i++)
			{   //  width
				if( pgm_read_byte(&strcut1->glyph_table[ offset+j+(i/8) ]) & (1 << ( 7 - ( i % 8 ) ) ) )
					writePixel(  x+i+allwidth , y+j/ (((width-1)/8)+1), !invers  );
	 			else
	 				writePixel(  x+i+allwidth , y+j/ (((width-1)/8)+1), invers  );
				}//End i
			}// End j
		allwidth+=width;
	}// End K
}*/

byte setMode(char _mode, char _CG)
//-----------------------------------------------------------------------
//               Set Mode for Step 1 Text Manipulation and Show CGRam
//Example: LCD.setMode('0','I');
//
//Parameter: '0=Normal' 'X=Xor' 'A=And' 'T=Text Attribute Mode'
//			 , 'I=Intern CGram' , 'E=Extern CGram'
// Show Step 2 Example: (Set Text Attribute) to complete
//-----------------------------------------------------------------------
{
  byte tmp = T6963_MODE_SET;
  if(_mode=='X' || _mode =='x' || _mode=='^'){
    tmp |= 1;
  }
  else if(_mode == 'A' || _mode=='&' ||_mode=='a'){
    tmp |= 3;
  }
  else if(_mode == 'T'||_mode=='t'){
    tmp |=4;
  }
  else{
    tmp |= 0; //OR mode default
  }
  if(_CG =='E'||_CG=='e'){
    tmp |=8;
  }
  else{
    tmp |=0;
  }
  writeCommand_GLCD(tmp);
  return tmp;
}

byte setTextAttrMode(char _mode)    // Text only: 0=Normal display 5=Reverse display 3=Inhibit display 8=Blink of normal display D=Blink of reverse display B=Blink of inhibit display
{

  byte tmp = 0;
  if(_mode=='3'){
    tmp |= 0b0011;
  }
  else if(_mode == '5'){
    tmp |= 0b0101;
  }
  else if(_mode == '8'){
    tmp |=0b1000;
  }
  else if(_mode == 'D'||_mode=='d'){
    tmp |=0b1101;
  }
  else if(_mode == 'B'||_mode=='b'){
    tmp |=0b1011;
  }
  else{
    tmp |= 0; //Normal Text mode default
  }
   SetAddress_GLCD(_GH);
  for(unsigned int i = 0; i < sizeGA; i++){
    WriteDisplayData(tmp);
  }
  return tmp;
}
void clearDispMode()
{
  writeCommand_GLCD(T6963_DISPLAY_MODE);
}
byte setDispMode(byte _text,byte _graphics,byte _cursor, byte _blink)
//-----------------------------------------------------------------------
//                       Set Display Mode
//Example: LCD.setDispMode(true,true,false,false);    //true=ON	false=off
//
//Parameter: ('GRAPHIC', 'TEXT', 'CURSOR', 'CURSOR BLINK')
//
//Set blinking Cursor Example: 	LCD.setDispMode(true,true,true,true); //Mode all ON
//								LCD.setCursorPattern(8); // Cursor high
//								LCD.setCursorPointer(0,0); //Cursor Position
//-----------------------------------------------------------------------
{
  byte tmp=T6963_DISPLAY_MODE;
  if(_graphics){
    tmp |= 0b1000; //T6963_GRAPHIC_DISPLAY_ON
  }
  if(_text){
    tmp |= 0b0100; //T6963_TEXT_DISPLAY_ON
  }
  if(_cursor){
    tmp |= 0b0010; //T6963_CURSOR_DISPLAY_ON
  }
  if(_blink){
    tmp |=0b0001; //T6963_CURSOR_BLINK_ON
  }
  writeCommand_GLCD(tmp);
  return tmp;
}
void createLine(int x0,int y0,int x1,int y1, byte color)
//-------------------------------------------------------------------------------------------------
//                               Show Rectangel (WritePixel)
////Example: LCD.createLine (0, 0, 30, 20);
//
//Parameter: createLine(int x0,int y0,int x1,int y1) x0 and y0 left Position  x1 and y1 right Position
//-------------------------------------------------------------------------------------------------
{

  byte steep = abs(y1 - y0) > abs(x1 - x0);
  if(steep){
    //swap(x0, y0)
    //swap(x1, y1)
    int tmp=x0;
    x0=y0;
    y0=tmp;
    tmp=x1;
    x1=y1;
    y1=tmp;
  }
  if(x0 > x1){
    //swap(x0, x1)
    //swap(y0, y1)
    int tmp=x0;
    x0=x1;
    x1=tmp;
    tmp=y0;
    y0=y1;
    y1=tmp;
  }
  int deltax = x1 - x0;
  int deltay = abs(y1 - y0);
  int error = deltax / 2;
  int ystep=-1;
  int y = y0;
  if(y0 < y1){ystep= 1;}
  for(int x =x0;x<=x1;x++){
    if(steep){writePixel(y,x,color);}else{writePixel(x,y,color);}
    error = error - deltay;
    if(error < 0){
      y = y + ystep;
      error = error + deltax;
    }
  }
}
void Rectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a, byte color)
//-------------------------------------------------------------------------------------------------
//                               Show Rectangel (writePixel)
////Example: LCD.Rectangle (0, 0, 30, 20, 1);
//
//Parameter: Rectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a, color)    x1 and y1 top left Position b and a Size of the rectangle
//-------------------------------------------------------------------------------------------------
{
  unsigned char j;
  // Draw vertical lines
  for (j = 0; j < a; j++) {
		writePixel(x, y + j, color);
		writePixel(x + b - 1, y + j, color);
	}
  // Draw horizontal lines
  for (j = 0; j < b; j++)	{
		writePixel(x + j, y, color);
		writePixel(x + j, y + a - 1, color);
	}
}
void fillRect(int x1, int y1, int x2, int y2, byte color)
{
	for (int i = y1; i <= y2; i++)
		 createLine(x1, i, x2, i, color);
}
void drawrectbyte(unsigned int x, unsigned int y, unsigned int HEIGHT, unsigned int BYTEWIDTH, byte pattern)    //HEIGHT = max 64;
//Height in pixels     BYTEWIDTH = max 40;	//Width in bytes by 6x8 Font
//-------------------------------------------------------------------------------------------------
//                               Show filled Box (BYTE)
////Example: LCD.setDispMode(true,true,false,false);    //true=ON	false=off
//
//Parameter: ('GRAPHIC', 'TEXT', 'CURSOR', 'CURSOR BLINK')
//
// drawrectbyte(x, y, height, bytewidth, pattern) // x,y = Start Position, Height in Pixel, Widht in Byte, pattern in byte(0b11111111)
//-------------------------------------------------------------------------------------------------
{
  int j;

  GraphicGoTo(x,y);
  j=0;

  for(int h = 0; h < HEIGHT; h++)
  {
    GraphicGoTo(x,y+h);

         for(unsigned int i = 0; i < BYTEWIDTH; i++)     //(PIXELS PER LINE/FONT WIDTH * NUMBER OF LINES)
         {
           WriteDisplayData(pattern);
         }
	j=j+BYTEWIDTH;
       }
     }
void createCircle(int cx, int cy, int radius, byte color)
//-------------------------------------------------------------------------------------------------
//                               Show Circle
////Example: LCD.createCircle(30, 30, 30, 1);
//
//Parameter: createCircle(int cx, int cy, int radius, color) //cx and cy mark the distance from the origin point.
//
//-------------------------------------------------------------------------------------------------
{
	int error = -radius;
	int x = radius;
	int y = 0;

	while (x >= y){
		plot8points(cx, cy, x, y, color);

		error += y;
		++y;
		error += y;

		if (error >= 0){
			--x;
			error -= x;
			error -= x;
		}
	}
}
void plot8points(int cx, int cy, int x, int y, byte color)
{
	plot4points(cx, cy, x, y, color);
	if (x != y) plot4points(cx, cy, y, x, color);
}
void plot4points(int cx, int cy, int x, int y, byte color)
{
	writePixel(cx + x, cy + y, color);
	if (x != 0) writePixel(cx - x, cy + y, color);
	if (y != 0) writePixel(cx + x, cy - y, color);
	if (x != 0 && y != 0) writePixel(cx - x, cy - y, color);
}
byte setCursorPattern(byte _b) // Cursor Controls
{
  byte tmp = T6963_CURSOR_PATTERN_SELECT;
  _b=constrain(_b,0,7);
  tmp|=_b;
  writeCommand_GLCD(tmp);
  return tmp;
}

void setCursorPointer(byte _col,byte _row) // Cursor Controls
{
  _col=constrain(_col,0,(_TA-1));
  _row=constrain(_row,0,((64/8)-1));
  writeData_GLCD(_col);
  writeData_GLCD(_row);
  writeCommand_GLCD(0x21); //Cursor pointer Set
}

void dsp_long (unsigned long val)
{
    char string [7];
    sprintf(string, "%ld", val);
    writeString_GLCD(string);
}
void dsp_byte (byte val)
{
    char szazasok = '0' + (val/100);
    char tizesek = '0' + ((val/10)%100)%10;
    char egyesek = '0' + val%10 ;
    writeChar_GLCD(szazasok);
    writeChar_GLCD(tizesek);
    writeChar_GLCD(egyesek);
}
const char * byte_to_string(byte val, byte null)
{
    char string [4];
    byte i=0;
    char szazasok = '0' + (val/100);
    char tizesek = '0' + ((val/10)%100)%10;
    char egyesek = '0' + val%10 ;
    if (szazasok>0x30 || null)
    {
        string[i]=szazasok;
    }
    else
    {
        string[i]=' ';
    }
    i++;
    if (tizesek>0x30 || szazasok>0x30 || null)
    {
        string[i]=tizesek;
    }
    else
    {
        string[i]=' ';
    }
    i++;
    string[i]=egyesek;
    i++;
    string[i]=0x00;
    return string;

}

void cls()
{
    clearGraphic();
    clearText_GLCD();
}

void dsp_speed (byte x, byte y,byte val)
{
    char string [4];
    byte i=0;
    char szazasok = '0' + (val/100);
    char tizesek = '0' + ((val/10)%100)%10;
    char egyesek = '0' + val%10 ;
    if (szazasok>0x30)
    {
        string[i]=szazasok;
    }
    else
    {
        string[i]=' ';
    }
    i++;
    if (tizesek>0x30 || szazasok>0x30)
    {
        string[i]=tizesek;
    }
    else
    {
        string[i]=' ';
    }
    i++;
    string[i]=egyesek;
    i++;
    string[i]=0x00;
    glcd_print2_P(x, y, string, &Digital7__30);
}

void dsp_sfloat ( float val)
{

    int a,b;
    if (val<0)
    {
        writeChar_GLCD('-'); // Negative value
        val=(val*(-1));
    }
    a = val; //(so a=12)
    val = val-a; //(so tmp=0.3456)
    b = val * 100; //(so b=34) - if 3 digit is enough
    byte szazasok =0x30 + (a/100);
    byte tizesek = 0x30 + ((a/10)%100)%10;
    byte egyesek = 0x30 + a%10 ;
    if (szazasok>0x30) writeChar_GLCD(szazasok); // szazasok
    if (tizesek>0x30 || szazasok>0x30) writeChar_GLCD(tizesek); // tizesek
    writeChar_GLCD(egyesek); // egyesek
    writeChar_GLCD('.');
    writeChar_GLCD(0x30 + ((b/10)%100)%10); // tizesek
    writeChar_GLCD(0x30 + b%10); // egyesek
}

