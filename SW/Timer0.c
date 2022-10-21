#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Timer0.h"

// ------------ Timer 0 fv ----------------------------------------------------------------------------------------------

void Init_Timer0()
{
    OPTION_REGbits.TMR0CS=0; // Clock Source = Internal (fosc/4)
    OPTION_REGbits.PSA=0; // Prescaler ON
    OPTION_REGbits.PS2=0; // Prescaler = 8 , 1 us per tick
    OPTION_REGbits.PS1=1; // Prescaler = 8 , 1 us per tick
    OPTION_REGbits.PS0=0; // Prescaler = 8 , 1 us per tick
}
void Start_Timer0(unsigned char preload)
{
    TMR0=preload;
    INTCONbits.TMR0IF=0;
}

void delay_us(unsigned char val)
{
    Start_Timer0(255-val); // Start Timer 0 with preload
    while(INTCONbits.TMR0IF==0); //waiting for interrupt flag
}


