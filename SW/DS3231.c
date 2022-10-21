#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"
#include "DS3231.h"

// ----------- RTC ---------------------------------------------------------------------------------------

void Init_RTC()
{
    //I2C_Send(0b01101000,0x0E);
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(0b01101000<<1);
    I2CWRITE(0x0E);
    I2CWRITE(0b00011100);
    I2CWRITE(0b10000111);
    I2CSTOP();
    INTCONbits.GIE=1;
}

void setTime()
{
    //I2C_Send(0b01101000,0x00);
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(0b01101000<<1);
    I2CWRITE(0x00);
    I2CWRITE(sec);
    I2CWRITE(minute);
    I2CWRITE(hour);
    I2CWRITE(dayofweek);
    I2CWRITE(day);
    I2CWRITE(month);
    I2CWRITE(year);
    I2CSTOP();
    INTCONbits.GIE=1;
}

void getTime()
{
        I2C_Send(0b01101000,0); // Write 0
        INTCONbits.GIE=0;
        I2CRSTART();
        I2CWRITE(0b11010001);
        sec=I2CREAD(); // Read
        I2CSENDACK();
        minute=I2CREAD(); // Read
        I2CSENDACK();
        hour=(I2CREAD()&0x3F); // Read
        I2CSENDACK();
        dayofweek=I2CREAD(); // Read
        I2CSENDACK();
        day=I2CREAD(); // Read
        I2CSENDACK();
        month=(I2CREAD()&0x1F); // Read
        I2CSENDACK();
        year=I2CREAD(); // Read
        I2CSENDNACK();
        I2CSTOP();
        INTCONbits.GIE=1;
}

float getRTemp()
{
    unsigned char templ,temph;
    I2C_Send(0b01101000,0x11); // Write 0
    INTCONbits.GIE=0;
    I2CRSTART();
    I2CWRITE(0b11010001);
    temph=I2CREAD(); // Read
    I2CSENDACK();
    templ=I2CREAD(); // Read
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    if (temph&128) temph=((-1)*temph);
    return (temph&0x7F)+((templ>>6)*0.25);
}
