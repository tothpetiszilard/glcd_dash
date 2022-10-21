/* 
 * File:   I2C.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. április 28., 14:06
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define timer_max   250
// -------------- I2C -------------------------------------------------------------------------------
void Init_I2C();
void I2CSTART();
void I2CSENDACK();
void I2CSENDNACK();
void I2CRSTART();
void I2CSTOP();
void I2CWRITE (unsigned char adat);
char I2CREAD ();
void I2CWAIT ();
unsigned char I2C_Read (unsigned char address);
void I2C_Send(unsigned char address, unsigned char data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

