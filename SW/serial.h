/* 
 * File:   RS485.h
 * Author: Tóthpeti Szilárd
 *
 * Created on 2015. május 6., 21:53
 */

#ifndef SERIAL_H
#define	SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include "types.h"
    // -------------- RS485 -------------------------------------------------------------------------------

#define rx_size 32
#define tx_size 32

unsigned char rx_buf[rx_size];    // Recieve buffer
unsigned char tx_buf[tx_size];    // Transmit buffer
unsigned char rx_head=0;   // Rx buffer pointer head
unsigned char rx_tail=0;   // Rx buffer pointer tail
unsigned char rx_count=0;   // Rx buffer pointer tail
unsigned char tx_head=0;   // Tx buffer pointer
unsigned char tx_tail=0;   // Tx buffer pointer
unsigned char tx_rem=tx_size; // Tx Buffer remaining space

void serialInit (); // Initilaize RS485 Port
unsigned char serialRead (); // Gives a unsigned char of data from 485 tx buffer
void serialWrite (unsigned char); // Writes a char to tx buffer
void serialWriteString(const char * string);
void serialRxInt(); // Recieve Data RS485
void serialTxInt(); // Data Transmitted RS485


#ifdef	__cplusplus
}
#endif

#endif	/* RS485_H */

