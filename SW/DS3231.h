/* 
 * File:   DS3231.h
 * Author: T�thpeti Szil�rd
 *
 * Created on 2015. �prilis 28., 14:16
 */

#ifndef DS3231_H
#define	DS3231_H

#ifdef	__cplusplus
extern "C" {
#endif

// ----------------- RTC --------------------------------------------------------------------------------
unsigned char year, month, day, dayofweek;
unsigned char hour, minute,sec;

void Init_RTC();
void setTime();
void getTime();
float getRTemp();


#ifdef	__cplusplus
}
#endif

#endif	/* DS3231_H */

