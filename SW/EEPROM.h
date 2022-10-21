/* 
 * File:   EEPROM.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. május 10., 22:05
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define WP  LATCbits.LATC2
#define EADDR   80


    void Init_EEPROM();
    void Write_EEPROM(unsigned int address,unsigned char data);
    unsigned char Read_EEPROM(unsigned int address);



#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

