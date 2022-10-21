#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"


// ------------ I2C ----------------------------------------------------------------------------------------------------
void Init_I2C()
{
    
    ANSELCbits.ANSC4=0; // SDA Digital IO
    ANSELCbits.ANSC3=0; // SCL Digital IO
    TRISCbits.TRISC4=1; // SDA Input
    TRISCbits.TRISC3=1; // SCL Input
    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Idle to Active; D_nA lastbyte_address;
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD;
    SSP1CON1 = 0x28;
    // BOEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; DHEN disabled; ACKTIM ackseq; PCIE disabled; SCIE disabled;
    SSP1CON3 = 0x60;
    // Baud Rate Generator Value: SSP1ADD 79;
    SSP1ADD = 0x4F; // 32Mhz --> 100kHz
        // clear the master interrupt flag
    SSP1CON1bits.SSPEN=1;

    PIR1bits.SSP1IF = 0;
    // disable the master interrupt
    PIE1bits.SSP1IE = 0;
}

void I2C_Send(unsigned char address, unsigned char data)
{
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(address<<1);
    I2CWRITE(data);
    I2CSTOP();
    INTCONbits.GIE=1;
}
unsigned char I2C_Read (unsigned char address)
{
    unsigned char data=0;
        INTCONbits.GIE=0;
        I2CRSTART();
        I2CWRITE((address<<1)+1);
        data=I2CREAD(); // Read
        I2CSENDACK();
        I2CSTOP();
        INTCONbits.GIE=1;
        return data;
}

void I2CSTART()
{
    unsigned char timer=0;
    SSP1CON2bits.SEN=1;
    while(SSP1CON2bits.SEN)
    {
        timer++;
        if (timer==timer_max) break;
    }
}

void I2CSENDACK()
{
    unsigned char timer=0;
    SSPCON2bits.ACKDT=0;
    SSPCON2bits.ACKEN=1;
    while(SSP1CON2bits.ACKEN)
    {
        timer++;
        if (timer==timer_max) break;
    }
}
void I2CSENDNACK()
{
    unsigned char timer=0;
    SSPCON2bits.ACKDT=1;
    SSPCON2bits.ACKEN=1;
    while(SSP1CON2bits.ACKEN)
    {
        timer++;
        if (timer==timer_max) break;
    }
return;
}

void I2CRSTART()
{
    unsigned char timer=0;
    SSPCON2bits.RSEN=1;
    while(SSP1CON2bits.RSEN)
    {
        timer++;
        if (timer==timer_max) break;
    }
}

void I2CSTOP()
{
    unsigned char timer=0;
    SSPCON2bits.PEN=1;
    while(SSP1CON2bits.PEN)
    {
        timer++;
        if (timer==timer_max) break;
    }
}
void I2CWRITE (unsigned char adat)
{
    unsigned char timer=0;
    I2CWAIT();
    SSPBUF=adat;
    while(SSP1STATbits.R_nW)
    {
        timer++;
        if (timer==timer_max) break;
    }
    timer=0;
    while(ACKSTAT)
    {
        timer++;
        if (timer==timer_max) break;
    }
}

char I2CREAD ()
{
    unsigned char timer=0;
    I2CWAIT ();
    SSPCON2bits.RCEN=1;
    while (SSP1CON2bits.RCEN)
    {
        timer++;
        if (timer==timer_max) return 0xFF;
    }
    return (SSPBUF);
}

void I2CWAIT ()
{
    unsigned char timer=0;
    while (SSP1STATbits.R_nW)
    {
        timer++;
        if (timer==timer_max) break;
    }
    timer=0;
    while (SSP1CON2&0b00011111)
    {
        timer++;
        if (timer==timer_max) break;
    }
}

