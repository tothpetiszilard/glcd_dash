#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "DS18B20.h"
#include "Timer0.h"

#define byte unsigned char

// ------- Temp -----------------------------------------------------------------------------------------------------------

void Req_Temps()
{
    if(Reset_Temp())
    {
        Write_Temp(Skip_ROM);
        Write_Temp(Convert_T);
    }
}

float Get_Temp(byte id)
{
          float temperature=0;
          byte temp=0;
          byte negative=0;
          if (Reset_Temp())
          {
            Write_Temp(Match_ROM);
            MatchROM_Temp(ds_sensors[id]);
            Write_Temp(Read_scratchpad);
            byte tempL = Read_Temp(8);
            byte tempH = Read_Temp(8);
            if(tempH&128) // Negative temperature
            {
                tempL=~tempL;
                tempH=~tempH;
                negative=1;
            }
            temp = (tempL&0xF0) >> 4 ; // 0b00001111
            temp += (tempH&0x07)<<4; // 0b00010000
            temperature = temp + ((tempL&0x0F)*0.0625);
            if (negative) temperature=((-1)*temperature);
            return temperature ;
          }
          else
              return 255;
}

void Init_Temp()
{
    Temp_AN=0; // PortB5 Digital
    Temp_Out = 1;
    Temp_Dir = 1; // Input
}

byte Reset_Temp()
{
    INTCONbits.GIE=0;
    Temp_Dir=0; // Output
    Temp_Out=0; // Send 0;
    delay_us(255);
    delay_us(225); //255+225 = 480 us
    Temp_Out=1;
    Temp_Dir=1; // Input
    delay_us(70); // 70 us
    byte tmp = Temp_In;
    INTCONbits.GIE=1;
    if ( tmp == 0)
    { // if there is a presence pluse
        delay_us(70); // 70 us
        return 1; // return 1 ( 1-wire is presence)
    }
    else
    {
        delay_us(70); // 70 us
        return 0; // return 0 ( 1-wire is NOT presence)
    }    
}

void Write_Temp (byte cmd)
{
     byte i;
     Temp_Out = 1;
     Temp_Dir = 1;                     // set pin# to input (1)
     INTCONbits.GIE=0;
     for(i = 0; i < 8; i++){
         if((cmd & (1<<i))!= 0)
         {
          // write 1
          Temp_Dir = 0;              // set pin# to output (0)
          Temp_Out = 0;             // set pin# to low (0)
          delay_us(10); // 10 us
          Temp_Out = 1;
          Temp_Dir = 1;            // set pin# to input (release the bus)
          delay_us(45); // 45 us
         }
         else
         {
           //write 0
          Temp_Dir = 0;              // set pin# to output (0)
          Temp_Out = 0;              // set pin# to low (0)
          delay_us(90); // 90 us          // 1 wire require time delay
          Temp_Out = 1;
          Temp_Dir = 1;              // set pin# to Input
         }
         INTCONbits.GIE=1;
     }

}

byte Read_Temp (byte bits)
{
     unsigned char i,result = 0;
     Temp_Dir = 1;              // set pin# to Input
     INTCONbits.GIE=0;
     for(i = 0; i < bits; i++){
         Temp_Dir = 0;              // set pin# to output (0)
         Temp_Out = 0;             // set pin# to low (0)
         delay_us(1); // 1 us
         Temp_Out = 1;
         Temp_Dir = 1;              // set pin# to Input
         if(Temp_In != 0) result |= 1<<i;
         delay_us(70); // 70 us    // wait for recovery time
     }
     INTCONbits.GIE=1;
     return result;
}

void Read_Rom (byte device_id)
{
    if(Reset_Temp())
        {
            Write_Temp(Read_ROM);
            for(byte i=0;i<8;i++)
            {
                ds_sensors[device_id][i]=Read_Temp(8);
            }
        }
}

void MatchROM_Temp(byte *pt)
{
     byte i;
     for(i=0; i<8; i++){
         Write_Temp(*pt);
         *pt++;
     }
}
