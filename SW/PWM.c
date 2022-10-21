#include <xc.h>
#include <stdio.h>

void Init_PWM()
{
    TRISEbits.TRISE2=1; // PORTE.2 Input -> PWM Output Disabled
    ANSELEbits.ANSE2=1; // E2 Analog In = High Impedance , biztos ami tuti
    PWM3CON=0x00; // Clear PWM3CON register
    PR2=0xFF;
    PWM3DCH=0x00; // PWM Duty Cycle High Value
    PWM3DCL=0x00; // PWM Duty Cycle Low Value
    PIR1bits.TMR2IF=0; // Timer 2 Int Flag Clear
    T2CONbits.T2CKPS=1; // Timer 2 Prescaler = 1
    T2CONbits.TMR2ON=1; // Timer 2 ON
    ANSELEbits.ANSE2=0; // E2 Digital Output
    while(!PIR1bits.TMR2IF); // Wait for Interrupt flag
    TRISEbits.TRISE2=0; // PORTE.2 Output -> PWM Output Enabled
    PWM3CONbits.PWM3EN=1; // PWM3 Module Enabled
}

void set_PWM(unsigned int val)
{
    PWM3DCH=((val>>2)&0xFF);
    PWM3DCL=((val<<6)&0xFF);
}
