/* 
 * File:   Timer0.h
 * Author: T�thpeti Szil�rd
 *
 * Created on 2015. �prilis 28., 14:10
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif

// Timer 0

void Init_Timer0();
void Start_Timer0(unsigned char );
void delay_us(unsigned char );


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

