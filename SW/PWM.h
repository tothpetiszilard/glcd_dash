/* 
 * File:   PWM.h
 * Author: T�thpeti Szil�rd
 *
 * Created on 2015. m�jus 6., 22:00
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>


// -------------- PWM   --------------------------------------------------------------------------------
void set_PWM(unsigned int val);
void Init_PWM();


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

