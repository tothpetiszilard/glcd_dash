// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR and can be enabled with ZCDSEN bit.)
#pragma config PLLEN = ON       // Phase Lock Loop enable (4x PLL is always enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include <xc.h>
#include "T6963.h"
#include "DS18B20.h"
#include "ADC.h"
#include "RS485.h"
#include "PWM.h"
#include "GUI.h"
#include <stdio.h>
#include "EEPROM.h"
#include "I2C.h"
//#include <stdlib.h>
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define byte unsigned char
#define mpsignal    1
#define tmr1preload 49152

//--------------- GLCD -----------------------------------------------------------------------------
const byte fok [8]={
	0b01110,
	0b01010,
	0b01110,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};


// ------------- Init -----------------------------------------------------------------------------------
void Init_PPS();
void Init_Interrupts ();
void Init_ZCD ();
void Init_Timer1 ();
void Init_Timer4();
void Init_Timer6();


// --------- Interrupts ! ------------------------------------------------------------------------------

volatile unsigned char button_timer=0; // Time between Falling and Rising edge
volatile unsigned char button_edge=0; // 0 Falling , 1 Rising



void Speed_int();
void Button_int();
void Timer1_int(); // Timer 1 Overflow handler


void interrupt IntHandler()
{
    if (IOCAFbits.IOCAF1 == 1 ) 
    {
    TRISEbits.TRISE2=1; // Backlight instant Off
    byte temp[4];
        temp[0] = (unsigned long int)((mileage & 0xFF000000) >> 24 );
        temp[1] = (unsigned long int)((mileage & 0x00FF0000) >> 16 );
        temp[2] = (unsigned long int)((mileage & 0x0000FF00) >> 8 );
        temp[3] = (unsigned long int)((mileage & 0X000000FF));
    byte temp1[2];
    temp1[0] = (unsigned long int)((avgdistance & 0x0000FF00) >> 8 );
    temp1[1] = (unsigned long int)((avgdistance & 0X000000FF));
    byte temp2[2];
    temp2[0] = (unsigned long int)((sptime & 0x0000FF00) >> 8 );
    temp2[1] = (unsigned long int)((sptime & 0X000000FF));
    byte temp3[2];
    temp3[0] = (unsigned long int)((distance & 0x0000FF00) >> 8 );
    temp3[1] = (unsigned long int)((distance & 0X000000FF));
    unsigned long optime = uzemora/7200;
    byte temp4[4];
        temp4[0] = (unsigned long int)((optime & 0xFF000000) >> 24 );
        temp4[1] = (unsigned long int)((optime & 0x00FF0000) >> 16 );
        temp4[2] = (unsigned long int)((optime & 0x0000FF00) >> 8 );
        temp4[3] = (unsigned long int)((optime & 0X000000FF));
    WP=0; // Write Protect Off
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x00);
        I2CWRITE(0x04);
        I2CWRITE(temp[0]);
        I2CWRITE(temp[1]);
        I2CWRITE(temp[2]);
        I2CWRITE(temp[3]);
        I2CWRITE(temp4[0]);
        I2CWRITE(temp4[1]);
        I2CWRITE(temp4[2]);
        I2CWRITE(temp4[3]);
        I2CWRITE(temp3[0]);
        I2CWRITE(temp3[1]);
        I2CWRITE(temp1[0]);
        I2CWRITE(temp1[1]);
        I2CWRITE(temp2[0]);
        I2CWRITE(temp2[1]);
        I2CSTOP();
        WP=1; // Write Protect On
    IOCAFbits.IOCAF1 = 0;
    TRISEbits.TRISE2 = 0; // Backlight Restore
    //while(1){DIAG2^=1;};
    }
    else if (INTCONbits.INTF == 1)   Speed_int();
    else if( PIR3bits.ZCDIF == 1)
    {
        rpm++;
        PIR3bits.ZCDIF = 0;
    }
    else if (PIR1bits.TMR1IF == 1) Timer1_int();
    else if (PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
    {
        Rx_485_int();
    }
        else if (PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
    {
        Tx_485_int();
    }
    else if (PIR2bits.TMR4IF == 1)
    {
        if (button_edge && button_timer!=255) button_timer++;
        PIR2bits.TMR4IF=0;
    }

    else if (PIR2bits.TMR6IF == 1)
    {
        if (softtimer!=softtimermax) softtimer++;
        PIR2bits.TMR6IF=0;
    }
    else if (INTCONbits.IOCIF == 1)
    {
         if (IOCAFbits.IOCAF0 == 1 )Button_int(); 
    }

}
void Speed_int()
{
    signalcount+=mpsignal;
    if (!(signalcount%212))
    {
        if (distance==9999) distance=0; else distance++; // Mai nap megtettünk 100m-t
        if (avgdistance==19999){ avgdistance=0; sptime=0;} else avgdistance++;
    }
    if (signalcount == 2123)
    {
        mileage++; // megtettunk egy km-ert
        signalcount=0; // megvan egy km(1000m), nem kell tovább számolni, vissza nullára
    }
    speed++; // sebesség érték növelése, majd timer 1 nulláz
    INTCONbits.INTF = 0;
}

void Timer1_int()
{
    speed_val=speed; // Gives speed data ( 942 mm/s )
    rpm_val=rpm; // Gives rpm in RPM
    rpm=0;
    speed=0;
    if (speed_val) sptime++; // Ha nem 0 a sebesség, ido növelése
    if (rpm_val) uzemora++; // Ha megy a gépállat, no az üzemóra
    TMR1=tmr1preload;
    PIR1bits.TMR1IF=0;
    
    //Speed_int();
}

void Button_int()
{
    if(button_edge)
    {
        // Felfutó él jött, döntünk és vissza tesszük lefutóra
        IOCAPbits.IOCAP0=0; // A0 Rising Edge Int
        IOCANbits.IOCAN0=1; // A0 Falling Edge Int
        if (button_timer >= longpress) button_cmd=2; // Hosszan lett megnyomva a gomb (1 mp)
        else if (button_timer >= shortpress) button_cmd=1; // Rövid volt a gombnyomás
        button_timer=0;
        button_edge=0; // Lefutó élre triggerelünk majd újra
        T4CONbits.TMR4ON=0;
        TMR4=0;
        //softtimer=0;
    }
    else
    {
        // Lefutó él jött, mehet át felfutóra, mérés indul
        IOCAPbits.IOCAP0=1; // A0 Rising Edge Int
        IOCANbits.IOCAN0=0; // A0 Falling Edge Int
        button_timer=0;
        button_edge=1; // Felfutó él van érvényben
        TMR4=0;
        T4CONbits.TMR4ON=1;
    }
    IOCAFbits.IOCAF0 = 0; // RA0 (Button) Int Flag clear
}


// ---------- Main ---------------------------------------------------------------------------------------



int main()
{
    OSCCON=0xF0; // 32 Mhz IntRC
    // Initilaize Things
    //delay_GLCD(7500);
    Init_PPS(); // Pin Configs
    Init_Timer0(); // For delays
    Init_GLCD(); // For GLCDisplay
    Init_PWM(); // For backlight control
    Init_Temp(); // For DS18b20 comm.
    Init_485 (); // For RS485 comm.
    Init_I2C(); // For IIC Comm. (RTC)
    Init_ZCD (); // ----------------------------------------------------------<<<<<<<<<<<<<<<<<<<<<<< ZCD!!!
    Init_RTC(); // For Time/Date/Temperature
    Init_EEPROM(); // For data saving (mileage, config ...)
    Init_ADC(); // For Battery / Ignition Voltage, Light sensor ...
    Init_Timer1(); // For speed, RPM calculations
    Init_Timer4(); // For button press times
    Init_Timer6(); // For GUI Times
    Init_Interrupts(); // For Speed, RPM, Button

    //Write_EEPROM(0x0000,0x30);
    //CONFIG=Read_EEPROM(0x0000); // First byte read from EEPROM
    
    set_PWM(brightness);
    //Read_Rom(0);
    DefineCharacter(0x80,fok);
    setMode('X','I');
    readConfig ();
    mileage=readMileage ();
    uzemora=readOptime ();
    distance=readDistance();
    avgdistance=readAvgdistance();
    sptime=readSptime();
    readDS();
    //check_Ignition();
    IOCANbits.IOCAN1=1; // Battery Input Falling edge Int
    home();

}


// ------------- Init  -------------------------------------------------------------------------------------------
void Init_Timer1 ()
{
     T1CONbits.TMR1CS=3; // 32628 Hz
     T1CONbits.T1CKPS=0; // No Prescaler
     T1CONbits.T1OSCEN=1; // Osc Enable
     T1GCON=0x00; // Timer 1 Gate Off
     TMR1=tmr1preload; // Preload to get 0,5 sec overflow interrupt
     PIR1bits.TMR1IF=0;
     T1CONbits.TMR1ON=1; // Turn On this shit
}

void Init_Interrupts ()
{
    INTCONbits.GIE=0;
    TRISBbits.TRISB1=1; // Speed pin Input
    TRISAbits.TRISA6=0; // Diag led 1 out
    TRISAbits.TRISA7=0; // Diag led 2 out
    ANSELBbits.ANSB1=0; // Speed pin Digital Input
    TRISCbits.TRISC0=0; // Digital out 1
    TRISCbits.TRISC1=0; // Digital out 1
    INTCON=0b01011000; // Global, Periferial, TMR0, INT0, PC Int, ...Flags
    PIE3bits.ZCDIE=1; // ZCD Interrupt (RPM Signal?)
    OPTION_REGbits.INTEDG=0; // Falling Edge Int0 // Speed Hall Sensor (10k +5V)
    INTCONbits.INTE=1;
    ANSELAbits.ANSA0=0; // A0 Digital In // Button
    TRISAbits.TRISA0=1; // A0 Input // Button
    WPUAbits.WPUA0=1;
    IOCANbits.IOCAN0=1; // A0 Falling Edge Int // Button (NO , +5V (10kOhm))
    PIR1=0x00;
    PIE1bits.TMR1IE=1;
    PIR2=0x00;
    PIE2bits.TMR4IE=1;
    PIE2bits.TMR6IE=1;
    INTCONbits.GIE=1;
}

void Init_ZCD ()
{
    // Set the ZCD to the options selected in the User Interface

    // ZCD1EN enabled; ZCD1POL not inverted; ZCD1INTP enabled; ZCD1INTN disabled;
    ZCD1CON = 0x82;

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.ZCDIF = 0;

    // Enabling ZCD interrupt.
    PIE3bits.ZCDIE = 1;
}

void Init_PPS()
{
    byte state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    SSPCLKPPSbits.SSPCLKPPS = 0x13;    // RC3->MSSP:SCL
    RC3PPSbits.RC3PPS = 0x10;    // RC3->MSSP:SCL
    SSPDATPPSbits.SSPDATPPS = 0x14;    // RC4->MSSP:SDA
    RC4PPSbits.RC4PPS = 0x11;    // RC4->MSSP:SDA
    RC6PPSbits.RC6PPS = 0x14;    // RC6->EUSART:TX
    RXPPSbits.RXPPS = 0x17;    // RC7->EUSART:RX
    RE2PPSbits.RE2PPS=0x0E;     // RE2 -> PWM3OUT
    INTPPSbits.INTPPS = 0x09; // INT0 to RB1

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}

void Init_Timer4()
{
    T4CONbits.T4CKPS=0x03;
    TMR4=0x00;
    PR4=0xFF;
    T4CONbits.TMR4ON=0;
}

void Init_Timer6()
{
    T6CONbits.T6CKPS=0x03;
    TMR6=0x00;
    PR6=0xFF;
    T6CONbits.TMR6ON=1;
}