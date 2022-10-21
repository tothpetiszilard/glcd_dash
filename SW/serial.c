#include <xc.h>

#include "Serial.h"

// ------------ RS485 ---------------------------------------------------------------------------------------------------
void serialInit ()
{
    TRISCbits.TRISC4=0; // TX Out
    TRISCbits.TRISC5=1; // RX In
    PIE1bits.RCIE = 0; // RX Int Disable
    PIE1bits.TXIE = 0; // TX Int Disable
    // TX1REG 0x0;
    TX1REG = 0x00;
    // RC1REG 0x0;
    RC1REG = 0x00;
    // ABDEN enabled; WUE disabled; RCIDL idle; ABDOVF no_overflow; SCKP async_noninverted_sync_fallingedge; BRG16 16bit_generator;
    BAUD1CON = 0x49;
    // ADDEN disabled; RX9 8-bit; RX9D 0x0; FERR no_error; CREN enabled; SPEN enabled; SREN disabled; OERR no_error;
    RC1STA = 0x90;
    // CSRC slave_mode; TRMT TSR_empty; TXEN enabled; BRGH hi_speed; SYNC asynchronous; SENDB sync_break_complete; TX9D 0x0; TX9 8-bit;
    TX1STA = 0x26;
    // Baud Rate = 9600; SP1BRGL 64;
    SP1BRGL = 0x40;
    // Baud Rate = 9600; SP1BRGH 3;
    SP1BRGH = 0x03;
    tx_head=0; // Transmit buffer empty
    rx_head=0; // Recieve buffer empty
    tx_tail=0;
    rx_tail=0;
    PIR1bits.TXIF = 0;
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1; // RX Int Enabled
    PIE1bits.TXIE = 1; // TX Int Enabled
    //writeString_485("DRZ Multimeter v1");
}

unsigned char serialRead()
{
    unsigned char data=0;
    if(rx_count==0) return 255; // Error, rx buffer empty
    else
    {
        PIE1bits.RCIE=0; // addig int off
        data = rx_buf[rx_tail++];
        if(sizeof(rx_buf) <= rx_tail)
        {
            rx_tail = 0;
        }
        rx_count--;
        PIE1bits.RCIE=1; // int vissza.
        return data;
    }
}

void serialWriteString(const char * string) // Writes null-terminated string to tx buffer
{
  while(*string){
      serialWrite(*string++);
  }
}

void serialWrite(unsigned char data)
{
    if(tx_rem==0) return ; // Error, tx buffer is full
    else
    {
        if(PIE1bits.TXIE == 0)
        {
            TXREG = data;
        }
        else
        {
            PIE1bits.TXIE = 0;
            tx_buf[tx_head++] = data;
            if(sizeof(tx_buf) <= tx_head)
            {
                tx_head = 0;
            }
            tx_rem--;
        }
        PIE1bits.TXIE = 1;
    }
}

void serialRxInt()
{
    if(RC1STAbits.OERR == 1)
    {
        // EUSART error - restart
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    rx_buf[rx_head++] = RCREG;
    if(sizeof(rx_buf) <= rx_head)
    {
        rx_head = 0;
    }
    rx_count++;
    PIR1bits.RCIF = 0;
}

void serialTxInt()
{
    if(sizeof(tx_buf) > tx_rem)
    {
        TXREG = tx_buf[tx_tail++];
        if(sizeof(tx_buf) <= tx_tail)
        {
            tx_tail = 0;
        }
        tx_rem++;
    }
    else
    {
        PIE1bits.TXIE = 0;
    }
    PIR1bits.TXIF = 0;
}
