/* 
 * File:   GUI.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. május 7., 15:27
 */
#include <xc.h>
#include <stdio.h>

// -------- GUI define -------------------------------------------------------------------------
#define longpress   250 // *2,04 msec
#define shortpress  20 // *2,04 msec

#define byte unsigned char

#define softtimermax    200

#define DOUT_1  LATCbits.LATC0
#define DOUT_2  LATCbits.LATC1
#define DIAG1   LATAbits.LATA6
#define DIAG2   LATAbits.LATA7

// -------------- GUI ---------------------------------------------------------------------------------
void dsp_time   ();
void dsp_mileage();
void home();
void menu();
void sleep();
void wake();
void dsp_distance();
void dsp_rpm(unsigned int val);
void dsp_rpmbar(unsigned int val);
void dsp_dstemp(byte id);
void dsp_atemp();
void dsp_avgspeed();
void dsp_maxspeed();
void dsp_optime();
void dsp_dayofweek();
void dsp_battery();
void config();
void changeTime(byte x ,byte y);
void setBacklight();
void listTemp();
void setTemp(byte id);
void autoBright();
void autoHeadlight();
void options();

void readConfig();
unsigned long int readOptime();
unsigned long int readMileage ();
void readDS();
unsigned int readDistance();
unsigned int readAvgdistance();
unsigned int readSptime();

void saveConfig();
void saveDS();
/*void saveOptime();
void saveMileage();

void saveAvg ();
void saveDistance();*/
//void saveAll();

unsigned char dec2bcd(unsigned char num);
unsigned char bcd2dec(unsigned char num);

unsigned char ahhist=10;
unsigned char ahdone=0;
volatile unsigned int speed=0; // speed signal counter
unsigned char speed_val=0; // Current speed value
unsigned char ahspeed=70; // Speed when headlights ON
volatile unsigned int rpm=0; // rpm signal? (zcd) counter
unsigned char rpm_val=0; // Current RPM data/120
volatile unsigned int signalcount=0; // Distance in meters below 1 km
unsigned long mileage=0; // all kms in km
unsigned int distance=0; // napi km
unsigned int avgdistance=0; // átlagszámításhoz km
unsigned char max_speed=0; // Ennyivel mentünk eddig max
float avg_speed=0;
volatile unsigned long int sptime=0; // mozgassal eltelt ido (fél mp)
volatile unsigned long int uzemora=0; // összes üzemóra
volatile byte button_cmd=0; // 0 = Not pressed, 1 short pressed , 2 long pressed, sw cleared
unsigned int brightness=600;
byte CONFIG=0; // 0. bit = AutoLight; 1.bit = ;
volatile byte softtimer=0;
byte ahtimer=0;
unsigned int battery=0;
unsigned int light=0;
unsigned int ahlight=30; // Lightness when Headlights ON
const unsigned char HOMEMAX=2;
 
#ifndef GUI_H
#define	GUI_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GUI_H */

