#include <xc.h>
#include <stdio.h>

#include "ADC.h"

// ----------- ADC ---------------------------------------------------------------------------------------
void Init_ADC()
{
    TRISAbits.TRISA1=1; // Battery voltage / ignition input
    TRISAbits.TRISA2=1; // Fuel In
    TRISAbits.TRISA3=1; // Light sensor Input
    TRISAbits.TRISA4=1; // AIN1
    TRISAbits.TRISA5=1; // AIN2
    ANSELAbits.ANSA1=0; // Batt voltage / Ign. Analog In
    ANSELAbits.ANSA2=1; // Fuel
    ANSELAbits.ANSA3=1; // Light sensor Analog In
    ANSELAbits.ANSA4=1; // AIN1
    ANSELAbits.ANSA5=1; // AIN2
    ADCON1bits.ADFM=1; // Right justified result
    FVRCONbits.FVREN=0; // Fixed Voltage Reference Disabled
    //while(!FVRCONbits.FVRRDY);
    //FVRCONbits.ADFVR=3; // FVR multiplier
    ADCON1bits.ADCS=6; // fosc/64 (32Mhz/64) t = 2 us
    ADCON1bits.ADNREF=0; // Neg Vref to GND
    ADCON1bits.ADPREF=0; // Reference source VDD (5V)
    ADCON0bits.ADON=1; // Turn on ADC

}

unsigned int get_ADC(unsigned char channel)
{
        IOCANbits.IOCAN1=0; // Battery Input Falling edge Int

    ANSELAbits.ANSA1=1; // for battery voltage read
    ADCON0bits.CHS=channel;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO);
    ANSELAbits.ANSA1=0; // relase battery voltage level
        IOCANbits.IOCAN1=1; // Battery Input Falling edge Int

    return ADRES;
    
}