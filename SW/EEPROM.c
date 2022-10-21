#include <xc.h>
#include "I2C.h"
#include "EEPROM.h"
#include "Timer0.h"
#define byte unsigned char

void Init_EEPROM()
{
    ANSELCbits.ANSC2=0;
    TRISCbits.TRISC2=0;
    WP=1;
}

unsigned char Read_EEPROM(unsigned int address)
{
    unsigned char data;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE((address&0xff00)>>8);
    I2CWRITE(address&0xFF);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    data=I2CREAD(); // Read
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    return data;
}

void Write_EEPROM(unsigned int address, unsigned char data)
{
    WP=0; // Write Protect Off
    //delay_us(100);
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE((address&0xff00)>>8);
    I2CWRITE(address&0xFF);
    I2CWRITE(data);
    I2CSTOP();
    WP=1; // Write Protect On
    INTCONbits.GIE=1;
}
