/* 
 * File:   ADC.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. május 6., 21:57
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

// ------------ ADC ------------------------------------------------------------------------------

#define Batt_ch 1
#define Fuel_ch 2
#define Light_ch    3
#define AnIn1_ch    4
#define AnIn2_ch    5
#define Temp_ch 0b11101


    // -------------- ADC -----------------------------------------------------------------------------------
void Init_ADC(); // Set Up ADC
unsigned int get_ADC(unsigned char channel);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

