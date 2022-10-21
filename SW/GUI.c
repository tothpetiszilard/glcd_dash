#include <xc.h>
#include <stdio.h>
#include "GUI.h"
#include "T6963.h"
#include "DS18B20.h"
#include "DS3231.h"
#include "Digital7__30.c"
#include "ADC.h"
#include "RS485.h"
#include "PWM.h"
#include "EEPROM.h"
#include "I2C.h"
#define byte unsigned char

void home()
{
    byte page=0;
    createLine(0,52,239,52,1); // Also vizszintes csik
    createLine(140,0,140,63,1); // speed / homersekletek közti csik
    createLine(140,35,239,35,1); // Homersekletek közti csík
    createLine(70,52,70,63,1); // Napi és osszes közti
    createLine(140,19,239,19,1); // RPM alatti csik
    TextGoTo(8,4);
    writeString_GLCD(" km/h");
    while(1)
    {
        dsp_speed(0,10,(speed_val*3.82));
        TextGoTo(8,4);
        writeString_GLCD(" km/h");
        if (speed_val>max_speed) max_speed=speed_val;
        unsigned int val = rpm_val*120;
        dsp_rpm(val);
        dsp_rpmbar(val);
        getTime();
        TextGoTo(24,7);
        dsp_time();
        if (softtimer==softtimermax)
        {
            if (page==0)
            {
                dsp_mileage();
                dsp_distance();
                dsp_dstemp(0);
                dsp_atemp();
            }
            else if (page==1)
            {
                dsp_optime();
                dsp_distance();
                dsp_avgspeed();
                dsp_maxspeed();
            }
            else if (page==2)
            {
                dsp_mileage();
                dsp_distance();
                dsp_battery();
                TextGoTo(31,5);
                dsp_dayofweek();
            }
            battery=get_ADC(Batt_ch); // Measure battery voltage (2us)
            if (CONFIG&1) autoBright();
            if (CONFIG&2) autoHeadlight();
            Req_Temps(); // Start DS conversations
            //if (battery < 200) sleep();
            softtimer=0;
            ahtimer++;
        }
        if (ahtimer==127){  ahdone=0; ahtimer=0;}
    if (button_cmd==1){if(page==HOMEMAX) page=0; else page++; button_cmd=0; clearText_GLCD();}
    else if (button_cmd==2){ button_cmd=0; menu();}
    DIAG1^=1;
    }
}

void menu ()
{
    //byte page=1;
    byte select=1;
    clearGraphic();
    clearText_GLCD();
    TextGoTo(0,0);
    writeString_GLCD("Menü");
    createLine(0,10,239,10,1); // Elvalaszto
    TextGoTo(2,2);
    writeString_GLCD("Napi km törlés");
    TextGoTo(2,4);
    writeString_GLCD("Max seb törlés");
    TextGoTo(2,6);
    writeString_GLCD("Átlagseb törlés");
    TextGoTo(22,2);
    writeString_GLCD("Üzemóra törlés");
    TextGoTo(22,4);
    writeString_GLCD("Beállítások");
    TextGoTo(22,6);
    writeString_GLCD("Kilépés");
    drawrectbyte(15,14,11,16,0xFF);

    while(1)
    {
    if (button_cmd==1)
    {
        select++;
        if (select==7) select=1;
        clearGraphic();
        button_cmd=0;
        if(select==1) drawrectbyte(15,14,11,16,0xFF);
        else if(select==2) drawrectbyte(15,30,11,16,0xFF);
        else if(select==3) drawrectbyte(15,46,11,16,0xFF);
        else if(select==4) drawrectbyte(135,14,11,16,0xFF);
        else if(select==5) drawrectbyte(135,30,11,16,0xFF);
        else if(select==6) drawrectbyte(135,46,11,16,0xFF);
        createLine(0,10,239,10,1); // Elvalaszto
        TextGoTo(20,0);
        writeString_GLCD("                     ");
    }
    else if (button_cmd==2 && select==1) // 1es menüpont
        {
            button_cmd=0;
            distance=0;
            TextGoTo(20,0);
            writeString_GLCD("Napi km törölve");
        }
    else if (button_cmd==2 && select==2) // 2es menüpont
        {
            button_cmd=0;
            max_speed=0;
            TextGoTo(20,0);
            writeString_GLCD("Max seb törölve");
        }
    else if (button_cmd==2 && select==3) // 3mas menüpont
        {
            button_cmd=0;
            avgdistance=0;
            sptime=0;
            TextGoTo(20,0);
            writeString_GLCD("Átlagseb törölve");
        }
    else if (button_cmd==2 && select==4) // 4es menüpont
        {
            button_cmd=0;
            uzemora=0;
            TextGoTo(20,0);
            writeString_GLCD("Üzemóra törölve");
        }
    else if (button_cmd==2 && select==5) // 5ös menüpont
        {
            button_cmd=0;
            config();
            TextGoTo(0,0);
            writeString_GLCD("Menü");
            createLine(0,10,239,10,1); // Elvalaszto
            TextGoTo(2,2);
            writeString_GLCD("Napi km törlés");
            TextGoTo(2,4);
            writeString_GLCD("Max seb törlés");
            TextGoTo(2,6);
            writeString_GLCD("Átlagseb törlés");
            TextGoTo(22,2);
            writeString_GLCD("Üzemóra törlés");
            TextGoTo(22,4);
            writeString_GLCD("Beállítások");
            TextGoTo(22,6);
            writeString_GLCD("Kilépés");
            drawrectbyte(135,30,11,16,0xFF);
        }
    else if (button_cmd==2 && select==6) // 6os menüpont kilépés
        {
            button_cmd=0;
            break;
        }

    }
    clearGraphic();
    clearText_GLCD();
    createLine(0,52,239,52,1); // Also vizszintes csik
    createLine(140,0,140,63,1); // speed / homersekletek közti csik
    createLine(140,35,239,35,1); // Homersekletek közti csík
    createLine(70,52,70,63,1); // Napi és osszes közti
    createLine(140,19,239,19,1); // RPM alatti csik

}
void config()
{
    //byte page=1;
    byte select=1;
    cls();
    drawrectbyte(15,14,11,16,0xFF);
    while(1)
    {
    TextGoTo(0,0);
    writeString_GLCD("Beállítások");
    createLine(0,10,239,10,1); // Elvalaszto
    TextGoTo(2,2);
    writeString_GLCD("Id? / Dátum");
    TextGoTo(2,4);
    writeString_GLCD("Fényer?");
    TextGoTo(2,6);
    writeString_GLCD("Opciók");
    TextGoTo(22,2);
    writeString_GLCD("H?mér?k");
    TextGoTo(22,4);
    writeString_GLCD("Modulok");
    TextGoTo(22,6);
    writeString_GLCD("Kilépés");
    if (button_cmd==1)
    {
        select++;
        if (select==7) select=1;
        clearGraphic();
        button_cmd=0;
        if(select==1)      drawrectbyte(15,14,11,16,0xFF);
        else if(select==2) drawrectbyte(15,30,11,16,0xFF);
        else if(select==3) drawrectbyte(15,46,11,16,0xFF);
        else if(select==4) drawrectbyte(135,14,11,16,0xFF);
        else if(select==5) drawrectbyte(135,30,11,16,0xFF);
        else if(select==6) drawrectbyte(135,46,11,16,0xFF);
        //createLine(0,10,239,10,1); // Elvalaszto
        //TextGoTo(20,0);
        //writeString_GLCD("                     ");
    }
    else if (button_cmd==2 && select==1) // 1es menüpont
        {
            button_cmd=0;
            changeTime(0,3);
            setTime();
            clearGraphic();
            clearText_GLCD();
            drawrectbyte(15,14,11,16,0xFF);
        }
    else if (button_cmd==2 && select==2) // 2es menüpont
        {
            button_cmd=0;
            setBacklight();
            clearGraphic();
            clearText_GLCD();
            drawrectbyte(15,30,11,16,0xFF);
        }
    else if (button_cmd==2 && select==3) // 3mas menüpont
        {
            button_cmd=0;
            options();
            drawrectbyte(15,46,11,16,0xFF);

        }
    else if (button_cmd==2 && select==4) // 4es menüpont
        {
            button_cmd=0;
            listTemp();
            drawrectbyte(135,14,11,16,0xFF);
        }
    else if (button_cmd==2 && select==5) // 5ös menüpont
        {
            button_cmd=0;
            break;
        }
    else if (button_cmd==2 && select==6) // 6os menüpont kilépés
        {
            button_cmd=0;
            break;
        }

    }
    saveConfig(); // if needed
    clearGraphic();
    clearText_GLCD();
}

void options()
{
    cls();
    byte select=0;
    TextGoTo(0,0);
    writeString_GLCD("Auto fényszóró: ");
    TextGoTo(0,1);
    writeString_GLCD("Auto fényszóró fényer?: ");
    TextGoTo(0,2);
    writeString_GLCD("Auto fényszóró sebesség: ");
    TextGoTo(0,3);
    writeString_GLCD("Kilépés");
    TextGoTo(0,7);
    writeString_GLCD("Jelenlegi fényer?:       ");
    drawrectbyte(5,0,8,15,0xFF);
    while(1)
    {
        TextGoTo(30,0);
        if(CONFIG&2)writeString_GLCD("Be");
        else writeString_GLCD("Ki");
        TextGoTo(30,1);
        dsp_long(ahlight/10);
        writeString_GLCD(" %");
        TextGoTo(30,2);
        dsp_long(ahspeed);
        writeString_GLCD(" km/h");
        TextGoTo(19,7);
        dsp_long(get_ADC(Light_ch)/10);
        writeString_GLCD(" %");
        if (button_cmd==1)
        {

            if (select==3) select=0;
            else select++;
            clearGraphic();
            button_cmd=0;
            if(select==0)      drawrectbyte(5,0,8,15,0xFF);
            else if(select==1) drawrectbyte(5,7,9,23,0xFF);
            else if(select==2) drawrectbyte(5,15,9,24,0xFF);
            else if(select==3) drawrectbyte(5,23,9,8,0xFF);
        /*else if(select==5) drawrectbyte(135,30,11,16,0xFF);
        else if(select==6) drawrectbyte(135,46,11,16,0xFF);*/
        //createLine(0,10,239,10,1); // Elvalaszto
        //TextGoTo(20,0);
        //writeString_GLCD("                     ");
        }
        else if (button_cmd==2 && select==0) // 1es menüpont
        {
            button_cmd=0;
            CONFIG^=2;
        }
        else if (button_cmd==2 && select==1) // 2es menüpont
        {
            button_cmd=0;
            ahlight+=10;
        }
        else if (button_cmd==2 && select==2)
        {
            button_cmd=0;
            ahspeed++;
        }
        else if (button_cmd==2 && select==3)
        {
            button_cmd=0;
            break;
        }

    }
    cls();
}

void setTemp(byte id)
{
    cls();
    TextGoTo(0,7);
    writeString_GLCD("Kilépéshez nyomd hosszan a gombot");
    while (Reset_Temp())
    {
        TextGoTo(0,3);
        writeString_GLCD("A folytatáshoz húzd le az összes h?mér?t");
        if (button_cmd==2){button_cmd=0; clearText_GLCD(); return;}
        //delay_us(1);
    }
    clearText_GLCD();
    TextGoTo(0,1);
    writeString_GLCD("ID: ");
    dsp_long(id);
    TextGoTo(5,3);
    writeString_GLCD("Név: ");
    TextGoTo(10,3);
    char c=0;
    while(1)
    {
        if (button_cmd==1)
        {
            if (ds_names[id][c]=='z')ds_names[id][c]=' ';
            else ds_names[id][c]++;
            button_cmd=0;
        }
        else if (button_cmd==2 && c!=5)
        {
            c++;
            button_cmd=0;
        }
        else if (button_cmd==2 && c==5)
        {
            button_cmd=0;
            break;
        }
        if (ds_names[id][c]==0x00 || ds_names[id][c]==0xFF) ds_names[id][c]=' ';
        else if (ds_names[id][c]=='!') ds_names[id][c]='A';
        else if (ds_names[id][c]==0x5B) ds_names[id][c]='a';
        TextGoTo(10+c,3);
        writeChar_GLCD(ds_names[id][c]);
    }
    clearText_GLCD();
    
    while (!Reset_Temp())
    {
        TextGoTo(0,3);
        writeString_GLCD("Kérlek csatlakoztatsd a megadott h?mér?t");
    }
    Read_Rom(id);
    clearText_GLCD();
    saveDS();
}

void listTemp()
{
    cls();
    byte select=0;
    //drawrectbyte(5,15,9,38,0xFF);
    while(1)
    {
        TextGoTo(0,0);
        writeString_GLCD("H?mér?k");
        TextGoTo(9,0);
        writeString_GLCD("ID");
        TextGoTo(13,0);
        writeString_GLCD("ROM");
        TextGoTo(30,7);
        writeString_GLCD("Kilépés");
        createLine(0,10,239,10,1); // Elvalaszto
        createLine(52,0,52,53,1);
        createLine(70,0,70,53,1);
        if(select==0) drawrectbyte(5,15,9,38,0xFF);
        else if(select==1) drawrectbyte(5,23,9,38,0xFF);
        else if(select==2) drawrectbyte(5,31,9,38,0xFF);
        else if(select==3) drawrectbyte(5,39,9,38,0xFF);
        else if(select==4) drawrectbyte(178,55,9,9,0xFF);
        if (button_cmd==1)
        {
            if (select==4) select=0;
            else select++;
            clearGraphic();
            button_cmd=0;
        }
        else if (button_cmd==2 && select==4) break;
        else if (button_cmd==2)
        {
            button_cmd=0;
            setTemp(select);

        }
        for(byte id=0; id<4;id++)
        {
            TextGoTo(0,id+2);
            if(ds_names[id][0] && ds_names[id][0]!=0xFF)
            {
                for(byte i=0;i<6;i++)
                {
                    writeChar_GLCD(ds_names[id][i]);
                }
            }
            else writeString_GLCD("H?mér?");
            TextGoTo(10,id+2);
            dsp_long(id);
            TextGoTo(13,id+2);
            if (ds_sensors[id][0])
            {
                for(byte i=0;i<8;i++)
                {
                    dsp_byte(ds_sensors[id][i]);
                }
            }
            else writeString_GLCD("------------------------");
        }
    }
    cls();
    button_cmd=0;
}
/*
void sleep()
{
    DIAG1=1; // Diag Led 2

    //DIAG2^=1;
    clearGraphic();
    clearText_GLCD();
    set_PWM(0);
    while (battery < 300)
    {
        battery=get_ADC(Batt_ch);
    }
    wake();
    return;
}

void wake ()
{
    if (CONFIG&1) autoBright();
    else set_PWM(brightness);

    createLine(0,52,239,52,1); // Also vizszintes csik
    createLine(140,0,140,63,1); // speed / homersekletek közti csik
    createLine(140,35,239,35,1); // Homersekletek közti csík
    createLine(70,52,70,63,1); // Napi és osszes közti
    createLine(140,19,239,19,1); // RPM alatti csik
    TextGoTo(8,4);
    writeString_GLCD(" km/h");
}*/

void setBacklight()
{
    byte next=1;
    cls();
    TextGoTo(0,7);
    writeString_GLCD("Beállított fény: ");
    TextGoTo(25,7);
    writeString_GLCD("Mért fény: ");
    while(next)
    {
        TextGoTo(36,7);
        dsp_long(light/10);
        writeString_GLCD(" %  ");
        TextGoTo(17,7);
        dsp_long(brightness/10);
        writeString_GLCD(" %  ");
        TextGoTo(2,2);
        writeString_GLCD("Auto fényer?: ");
        TextGoTo(16,2);
        if (CONFIG&1) { writeString_GLCD("Bekapcsolva"); autoBright();}
        else writeString_GLCD("Kikapcsolva");
        if (button_cmd==1) {CONFIG=CONFIG^1; button_cmd=0;} // short press
        if (button_cmd==2) next=0;
    }
    button_cmd=0;
    if (!(CONFIG&1)) next=1;
    brightness=600;
    while(next)
    {
        TextGoTo(2,4);
        writeString_GLCD("Fényer?: ");
         if (brightness<100) writeString_GLCD("  ");
         else if (brightness<1000) writeChar_GLCD(' ');
         else TextGoTo(11,4);
        dsp_long(brightness/10);
        TextGoTo(15,4);
        writeChar_GLCD('%');
        if (button_cmd==1) {if(brightness==1000) brightness=0; else brightness=brightness+10; button_cmd=0;} // short press
        if (button_cmd==2) next=0;
        set_PWM(brightness);
    }
    button_cmd=0;
}

void changeTime(byte x ,byte y)
{
    byte next=1;
    byte dyear=bcd2dec(year); // BCD to BIN konverziók: LCD és módosítás miatt
    byte dmonth=bcd2dec(month);
    byte dday=bcd2dec(day);
    byte dhour=bcd2dec(hour);
    byte dminute=bcd2dec(minute);
    cls();
    TextGoTo(x,y);
        writeString_GLCD("20");
        while(next)
        {
            TextGoTo(x+2,y);
            if(dyear<10) writeChar_GLCD('0');
            dsp_long(dyear);
            if (button_cmd==1) {if (dyear==99) dyear=0; else dyear++; button_cmd=0;} // short press
            if (button_cmd==2) next=0;
        }
        button_cmd=0;
        writeChar_GLCD('.');
        next=1;
        while(next)
        {
            TextGoTo(x+5,y);
            if(dmonth<10) writeChar_GLCD('0');
            dsp_long(dmonth);
            if (button_cmd==1) {if (dmonth==12) dmonth=0; else dmonth++; button_cmd=0;} // short press
            if (button_cmd==2) next=0;
        }
        button_cmd=0;
        writeChar_GLCD('.');
        next=1;
        while(next)
        {
          TextGoTo(x+8,y);
          if (dday<10) writeChar_GLCD('0');
          dsp_long(dday);
          if (button_cmd==1) {if (dday==31) dday=0; else dday++; button_cmd=0;} // short press
          if (button_cmd==2) next=0;
        }
        button_cmd=0;
        writeChar_GLCD(' ');
        next=1;
        while(next)
        {
          TextGoTo(x+11,y);
          if (dhour<10) writeChar_GLCD('0');
          dsp_long(dhour);
          if (button_cmd==1) {if (dhour==23) dhour=0; else dhour++; button_cmd=0;} // short press
          if (button_cmd==2) next=0;
        }
        button_cmd=0;
        writeChar_GLCD(':');
        next=1;
        while(next)
        {
          TextGoTo(x+14,y);
          if (dminute<10) writeChar_GLCD('0');
          dsp_long(dminute);
          if (button_cmd==1) {if (dminute==59) dminute=0; else dminute++; button_cmd=0;} // short press
          if (button_cmd==2) next=0;
        }
        button_cmd=0;
        writeChar_GLCD(' ');
        next=1;
        while(next)
        {
          TextGoTo(x+17,y);
          dsp_dayofweek();
          if (button_cmd==1) {if (dayofweek==7) dayofweek=1; else dayofweek++; button_cmd=0;} // short press
          if (button_cmd==2) next=0;
        }
        button_cmd=0;
        year=dec2bcd(dyear); // DEC to BCD konverziók, RTC-be visszaírás miatt
        month=dec2bcd(dmonth);
        day=dec2bcd(dday);
        hour=dec2bcd(dhour);
        minute=dec2bcd(dminute);
        sec=0x00;
}

void autoBright()
{
    light=get_ADC(Light_ch);
    if (light>brightness) brightness++;
    else if (brightness>300 && light<brightness) brightness--;
    set_PWM(brightness);
}

void autoHeadlight()
{
    if (!ahdone)
    {
        if (light<(ahlight-ahhist) || speed_val>ahspeed) DOUT_1=1;
        else if (light>(ahlight+ahhist) && speed_val<ahspeed) DOUT_1=0;
    }
    ahdone=1;
}

void dsp_dayofweek()
{
    if (dayofweek==1)      writeString_GLCD("Hétf?    ");
    else if (dayofweek==2) writeString_GLCD("Kedd     ");
    else if (dayofweek==3) writeString_GLCD("Szerda   ");
    else if (dayofweek==4) writeString_GLCD("Csütörtök");
    else if (dayofweek==5) writeString_GLCD("Péntek   ");
    else if (dayofweek==6) writeString_GLCD("Szombat  ");
    else if (dayofweek==7) writeString_GLCD("Vasárnap ");
}

void dsp_optime()
{
    unsigned long int optime=uzemora/7200;
    if (optime<10) TextGoTo(6,7);
    else if (optime<100) TextGoTo(5,7);
    else if (optime<1000) TextGoTo(4,7);
    else if (optime<10000) TextGoTo(3,7);
    else if (optime<100000) TextGoTo(2,7);
    else TextGoTo(1,7);
    dsp_long(optime);
    //writeChar_GLCD('.');
    //writeChar_GLCD(0x30 + (uzemora/720));
    writeString_GLCD(" óra");
}

void dsp_maxspeed()
{
    TextGoTo(24,5);
    writeString_GLCD("Max: ");
    TextGoTo(31,5);
    dsp_long(max_speed*3.82);
    TextGoTo(35,5);
    writeString_GLCD(" km/h");
}

void dsp_avgspeed()
{
    TextGoTo(24,3);
    writeString_GLCD("Átlag: ");
    if (sptime > 360 )
    {
        avg_speed = (avgdistance/(sptime/720.0));
        if (avg_speed > 99 )TextGoTo(30,3);
        else TextGoTo(31,3);
        dsp_sfloat(avg_speed);
    }
    else writeString_GLCD("--.-");
    TextGoTo(35,3);
    writeString_GLCD(" km/h");
}

void dsp_atemp()
{
        TextGoTo(24,5);
        writeString_GLCD("Leveg?:  ");
        TextGoTo(32,5);
        dsp_sfloat(getRTemp()); // RTC Temperature
        TextGoTo(37,5);
        WriteDisplayData(0x80); // fok jel
        writeString_GLCD("C");
}

void dsp_dstemp(byte id)
{
    signed float temperature=0;
    TextGoTo(24,3);
    for (byte i=0; i<6;i++)
    {
        writeChar_GLCD(ds_names[id][i]);
    }
        writeString_GLCD(":      ");

    if(Reset_Temp())
            {
                temperature=Get_Temp(id); // read temp from DS ROM ID 0
                if (temperature<10)TextGoTo(33,3);
                else TextGoTo(32,3);
                dsp_sfloat(temperature); // DS temp
            }
            else
            {
                TextGoTo(32,3);
                writeString_GLCD("-----");
            }
        TextGoTo(37,3);
        WriteDisplayData(0x80); // fok jel
        writeString_GLCD("C");
}

void dsp_rpmbar(unsigned int val)
{
    drawrectbyte(2,2,5,24,0x00);
    Rectangle(0,0,141,9,1);
    drawrectbyte(2,2,5,(val/435),0xFF);
}

void dsp_rpm(unsigned int val)
{
    TextGoTo(28,1);
    writeString_GLCD("      RPM");
    if (val<10) TextGoTo(32,1);
    else if (val<100) TextGoTo(31,1);
    else if (val<1000) TextGoTo(30,1);
    else if (val<10000) TextGoTo(29,1);
    else TextGoTo(28,1);
    dsp_long(val);
    //writeString_GLCD(" RPM");
}

void dsp_distance()
{
    TextGoTo(12,7);
    writeString_GLCD("N:");
    if (distance<100) TextGoTo(18,7);
    else if (distance<1000) TextGoTo(17,7);
    else if (distance<10000) TextGoTo(16,7);
    //else if (distance<100000) TextGoTo(15,7);
    else TextGoTo(14,7);
    dsp_long(distance/10);
    writeChar_GLCD('.');
    writeChar_GLCD(0x30 + (distance%10));
    writeString_GLCD("km");
}

void dsp_mileage()
{
             if (mileage<10) TextGoTo(6,7);
        else if (mileage<100) TextGoTo(5,7);
        else if (mileage<1000) TextGoTo(4,7);
        else if (mileage<10000) TextGoTo(3,7);
        else if (mileage<100000) TextGoTo(2,7);
        else if (mileage<1000000) TextGoTo(1,7);
        else TextGoTo(0,7);
        dsp_long(mileage);
        writeChar_GLCD('.');
        writeChar_GLCD(0x30 + (signalcount/200));
        writeString_GLCD("km");
}

void dsp_time   ()
{
        writeString_GLCD("20");
        writeChar_GLCD(((year&0xF0)>>4) + 0x30);
        writeChar_GLCD((year&0x0F) + 0x30);
        writeChar_GLCD('.');
        writeChar_GLCD(((month&0xf0)>>4) + 0x30);
        writeChar_GLCD((month&0x0f) + 0x30);
        writeChar_GLCD('.');
        writeChar_GLCD(((day&0xf0)>>4) + 0x30);
        writeChar_GLCD((day&0x0f) + 0x30);
        writeChar_GLCD(' ');
        writeChar_GLCD(((hour&0xf0)>>4) + 0x30);
        writeChar_GLCD((hour&0x0f) + 0x30);
        if(sec&1)writeChar_GLCD(':');
        else writeChar_GLCD(' ');
        writeChar_GLCD(((minute&0xf0)>>4) + 0x30);
        writeChar_GLCD((minute&0x0f) + 0x30);
       //writeChar_GLCD(':');
        //writeChar_GLCD(((sec&0xf0)>>4) + 0x30);
        //writeChar_GLCD((sec&0x0f) + 0x30);
}

void dsp_battery()
{
    float val=battery/37.6;
    TextGoTo(24,3);
    writeString_GLCD("Akku:   ");
    if (val<10) TextGoTo(32,3);
    else TextGoTo(31,3);
    dsp_sfloat(val);
    TextGoTo(37,3);
    writeString_GLCD("V");
}

// Converts decimal to bcd
unsigned char dec2bcd(unsigned char num)
{
  return ((num/10 * 16) + (num % 10));
}

// Converts a BCD number to a decimal number
unsigned char bcd2dec(unsigned char num)
{
  return ((num/16 * 10) + (num % 16));
}

void saveDS()
{
        WP=0; // Write Protect Off
        INTCONbits.GIE=0;
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x01);
        I2CWRITE(0x00);
        for (byte id=0;id<4;id++)
        {
            for (byte i=0;i<6;i++)
            {
                I2CWRITE(ds_names[id][i]);
            }
        }
        for (byte id=0;id<4;id++)
        {
            for (byte i=0;i<8;i++)
            {
                I2CWRITE(ds_sensors[id][i]);
            }
        }
        I2CSTOP();
        WP=1; // Write Protect On
        INTCONbits.GIE=1;
        delay_us(255);
}

void readDS ()
{
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x01);
    I2CWRITE(0x00);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    for (byte id=0;id<4;id++)
        {
            for (byte i=0;i<6;i++)
            {
                ds_names[id][i]=I2CREAD();
                I2CSENDACK();
            }
        }
        for (byte id=0;id<4;id++)
        {
            for (byte i=0;i<8;i++)
            {
                ds_sensors[id][i]=I2CREAD();
                if (id==3 && i==7)I2CSENDNACK();
                else I2CSENDACK();
            }
        }
    I2CSTOP();
    INTCONbits.GIE=1;
}

void readConfig()
{
    CONFIG=Read_EEPROM(0x0000);
}

void saveConfig()
{
    if (CONFIG!=Read_EEPROM(0x0000)) { Write_EEPROM(0x0000,CONFIG);}
}


/*void saveAvg ()
{
    if (avgdistance!=readAvgdistance() || sptime !=readSptime())
    {
        byte temp1[2];
        temp1[0] = (unsigned long int)((avgdistance & 0x0000FF00) >> 8 );
        temp1[1] = (unsigned long int)((avgdistance & 0X000000FF));
        byte temp2[2];
        temp2[0] = (unsigned long int)((sptime & 0x0000FF00) >> 8 );
        temp2[1] = (unsigned long int)((sptime & 0X000000FF));
        WP=0; // Write Protect Off
        INTCONbits.GIE=0;
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x00);
        I2CWRITE(0x0E);
        I2CWRITE(temp1[0]);
        I2CWRITE(temp1[1]);
        I2CWRITE(temp2[0]);
        I2CWRITE(temp2[1]);
        I2CSTOP();
        WP=1; // Write Protect On
        INTCONbits.GIE=1;
    }
    
}

void saveDistance()
{
    if (distance!=readDistance())
    {
        byte temp[2];
        temp[0] = (unsigned long int)((distance & 0x0000FF00) >> 8 );
        temp[1] = (unsigned long int)((distance & 0X000000FF));
        WP=0; // Write Protect Off
        INTCONbits.GIE=0;
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x00);
        I2CWRITE(0x0C);
        I2CWRITE(temp[0]);
        I2CWRITE(temp[1]);
        I2CSTOP();
        WP=1; // Write Protect On
        INTCONbits.GIE=1;
    }
}

void saveMileage()
{
    if (mileage!=readMileage())
    {
        //LATAbits.LATA7=1; // Diag Led 2
        byte temp[4];
        temp[0] = (unsigned long int)((mileage & 0xFF000000) >> 24 );
        temp[1] = (unsigned long int)((mileage & 0x00FF0000) >> 16 );
        temp[2] = (unsigned long int)((mileage & 0x0000FF00) >> 8 );
        temp[3] = (unsigned long int)((mileage & 0X000000FF));
        WP=0; // Write Protect Off
        INTCONbits.GIE=0;
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x00);
        I2CWRITE(0x04);
        I2CWRITE(temp[0]);
        I2CWRITE(temp[1]);
        I2CWRITE(temp[2]);
        I2CWRITE(temp[3]);
        I2CSTOP();
        WP=1; // Write Protect On
        INTCONbits.GIE=1;
        delay_us(255);
    }
}

void saveOptime()
{
    unsigned long optime = uzemora/7200;
    if (optime != readOptime()/7200)
    {
        byte temp[4];
        temp[0] = (unsigned long int)((optime & 0xFF000000) >> 24 );
        temp[1] = (unsigned long int)((optime & 0x00FF0000) >> 16 );
        temp[2] = (unsigned long int)((optime & 0x0000FF00) >> 8 );
        temp[3] = (unsigned long int)((optime & 0X000000FF));
        WP=0; // Write Protect Off
        INTCONbits.GIE=0;
        I2CSTART();
        I2CWRITE(EADDR<<1);
        I2CWRITE(0x00);
        I2CWRITE(0x08);
        I2CWRITE(temp[0]);
        I2CWRITE(temp[1]);
        I2CWRITE(temp[2]);
        I2CWRITE(temp[3]);
        I2CSTOP();
        WP=1; // Write Protect On
        INTCONbits.GIE=1;
        delay_us(255);
    }
}*/

unsigned long int readOptime ()
{
    byte temp[4];
    unsigned long int data;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x00);
    I2CWRITE(0x08);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    temp[0]=I2CREAD(); // Read
    I2CSENDACK();
    temp[1]=I2CREAD();
    I2CSENDACK();
    temp[2]=I2CREAD();
    I2CSENDACK();
    temp[3]=I2CREAD();
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    data  = ((unsigned long int) temp[0]) << 24;
    data |= ((unsigned long int) temp[1]) << 16;
    data |= ((unsigned long int) temp[2]) << 8;
    data |= ((unsigned long int) temp[3]);
    return (data*7200);
}

unsigned int readDistance()
{
    byte temp[2];
    unsigned long int data=0;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x00);
    I2CWRITE(0x0C);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    temp[0]=I2CREAD(); // Read
    I2CSENDACK();
    temp[1]=I2CREAD();
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    data |= ((unsigned long int) temp[0]) << 8;
    data |= ((unsigned long int) temp[1]);
    return data;
}

unsigned long int readMileage ()
{
    byte temp[4];
    unsigned long int data;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x00);
    I2CWRITE(0x04);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    temp[0]=I2CREAD(); // Read
    I2CSENDACK();
    temp[1]=I2CREAD();
    I2CSENDACK();
    temp[2]=I2CREAD();
    I2CSENDACK();
    temp[3]=I2CREAD();
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    data  = ((unsigned long int) temp[0]) << 24;
    data |= ((unsigned long int) temp[1]) << 16;
    data |= ((unsigned long int) temp[2]) << 8;
    data |= ((unsigned long int) temp[3]);
    return data;
}

unsigned int readAvgdistance()
{
    byte temp[2];
    unsigned long int data=0;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x00);
    I2CWRITE(0x0E);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    temp[0]=I2CREAD(); // Read
    I2CSENDACK();
    temp[1]=I2CREAD();
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    data |= ((unsigned long int) temp[0]) << 8;
    data |= ((unsigned long int) temp[1]);
    return data;
    
}
unsigned int readSptime()
{
    byte temp[2];
    unsigned long int data=0;
    INTCONbits.GIE=0;
    I2CSTART();
    I2CWRITE(EADDR<<1);
    I2CWRITE(0x00);
    I2CWRITE(0x10);
    I2CSTOP();
    I2CRSTART();
    I2CWRITE((EADDR<<1)+1);
    temp[0]=I2CREAD(); // Read
    I2CSENDACK();
    temp[1]=I2CREAD();
    I2CSENDNACK();
    I2CSTOP();
    INTCONbits.GIE=1;
    data |= ((unsigned long int) temp[0]) << 8;
    data |= ((unsigned long int) temp[1]);
    return data;
    
}