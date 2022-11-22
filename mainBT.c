/*
 * File:   mainBT.c
 * Author: Amr Atia
 *
 * Created on November 6, 2022, 8:33 PM
 */
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF// Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG
//#include <pic16f877a.h>
#include <xc.h>

#define _XTAL_FREQ 4000000
#include "sensor.h"
#include "LCD.h"
#include "BT.h"
int door_CM = 60;

void main(void)
{
  TRISB = 0; //LCD
  TRISC2 = 0; // RS
  TRISC3 = 0; // RW
  TRISD0 = 0; // EN
  // LEDs for testing ultrasonic project ------------------
  TRISD1 = 0; // 150 cm
  TRISD2 = 0; // 170 cm
  TRISD3 = 0; // 190 cm
  // Ultra-Sonic Sensor ------------------------------------
  TRISD7 = 0; // 190 Trig OUTPUT
  TRISD6 = 1; // 190 Echo INPUT
  TRISD5 = 0; // 170 Trig OUTPUT
  TRISD4 = 1; // 170 Echo INPUT
  TRISC5 = 0; // 150 Trig OUTPUT
  TRISC4 = 1; // 150 Echo INPUT
  // Timer Pre-scaler ---------------------------------------
  T1CKPS0 = 0;
  T1CKPS1 = 0;
  // clock select for timers ------------------------------
  TMR1CS = 0;
   
  float distance1;
  float distance2;
  float distance3;
     
  int count3 =0;
  int count2 =0;
  int count1 =0;
  char c3;
  char c2;
  char c1;
 
   LCD_init();
   LCD_Clear();
   LCD_Command(0x80);
   LCD_string("before While");
   __delay_ms(500);
   
   
   LCD_Clear();
   LCD_Command(0x80);
   LCD_string("5-7 7-9 over 9");
   LCD_Command(0xC0);
   LCD_string("0");
   LCD_Command(0xC5);
   LCD_string("0");
   LCD_Command(0xCC);
   LCD_string("0");
   __delay_ms(500);
//------------------------------------------------------------------------
   Initialize_Bluetooth();
    while(1)
  {  
        RD1=0;
        RD2=0;
        RD3=0;
        __delay_ms(50);

      distance3 =dist3();
      if (distance3 >60)// no person at 150
      {
          __delay_ms(500);
         
      }
      if(distance3 <60){// person detected at 150
         RD1=1;
         distance2=dist2();
         if(distance2>60)// no person at 170
         {
              //LCD_Clear();
             LCD_Command(0xC0);
             count3++;
             c3=itoa(count3);
             LCD_string(c3);
             BT_load_string("People between 150-170:  ");
            broadcast_BT();
            BT_load_string(c3);
            broadcast_BT();
            BT_load_string("\n");
            broadcast_BT();
            BT_load_string("------------------------\n");
            broadcast_BT();
              __delay_ms(500);
         }
         
         if(distance2<60){// Person at 170
             RD2=1;
             distance1= dist1();
             if(distance1>60){// no person at 190
              //LCD_Clear();
             LCD_Command(0xC5);
             count2++;
             c2=itoa(count2);
             LCD_string(c2);
             BT_load_string("People between 170-190:  ");
             broadcast_BT();
                BT_load_string(c2);
                broadcast_BT();
                BT_load_string("\n");
                broadcast_BT();
                BT_load_string("------------------------\n");
                broadcast_BT();
              __delay_ms(500);
             
         }
             if(distance1<60){
                 RD3=1;
                 LCD_Command(0xCC);
                 count1++;
                 c1=itoa(count1);
                 LCD_string(c1);
                 BT_load_string("People over 190:  ");
                 broadcast_BT();
                 BT_load_string(c1);
                 broadcast_BT();
                 BT_load_string("\n");
                 broadcast_BT();
                 BT_load_string("------------------------\n");
                 broadcast_BT();
                 __delay_ms(500);
             }
             
         }
   

      }
   
   
  }
 
}