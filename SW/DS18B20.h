/* 
 * File:   DS18B20.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. április 28., 13:58
 */

#ifndef DS18B20_H
#define	DS18B20_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#define Temp_In     PORTBbits.RB5
#define Temp_AN     ANSELBbits.ANSB5
#define Temp_Out    LATBbits.LATB5
#define Temp_Dir    TRISBbits.TRISB5

//---------- Temperature ----------------------------------------------------------------------
#define Skip_ROM    0xCC
#define Convert_T   0x44
#define Read_scratchpad 0xBE
#define Write_scratchpad    0x4E
#define Copy_scratchpad 0x48
#define Read_ROM    0x33
#define Match_ROM   0x55
#define Search_ROM  0xF0
#define Alarm_Search    0xEC
#define Read_Power  0xB4

//------------------------------------------------------------------------------------------------------
// Dallas 18B20

unsigned char Reset_Temp();
void Init_Temp();
void Write_Temp(unsigned char);
void Read_Rom(unsigned char );
void Req_Temps();
float Get_Temp(unsigned char );
unsigned char Read_Temp (unsigned char);
void delay_us(unsigned char);
void MatchROM_Temp(char *);

unsigned char ds_sensors[4][8]; // DS sensor ROM container [id][rom unsigned chars]
char ds_names[4][6]; // DS sendor Names to ID-s [id][ASCII Char of Names]

#ifdef	__cplusplus
}
#endif

#endif	/* DS18B20_H */

