/*
 * File:   mainBT.c
 * Author: Amr Atia
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
//#include <pic16f877a.h>
#include <xc.h>
#include <math.h>
#define _XTAL_FREQ 4000000
#include "sensor.h"
#include "LCD.h"
#include "BT.h"
int door_CM = 60;

void person150_170(void);
void person170_190(void);
void personOver_190(void);
//-------------------------------------------------------------------------------MAIN
void main(void){
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
  
  int count3 = 0;
  int count2 = 0;
  int count1 = 0;
  
  unsigned char c3;
  unsigned char c2;
  unsigned char c1;
     
  Initialize_Bluetooth();
  
  LCD_init();
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
   
//------------------------------------------------------------------------While Loop inside Main
  while(1){
    RD1=0; // LED 150
    RD2=0; // LED 170
    RD3=0; // LED 190  
    __delay_ms(50);
    distance3 = dist3();                         // go get distance at 150 and store it in distance3
    if(distance3 > door_CM){__delay_ms(500);}    // no person at 150 --> do Nothing
    if(distance3 < door_CM){                     // person detected at 150
      RD1=1;                                     // Turn on LED 150
      distance2=dist2();                         // go get distance at 170 and store it in distance2
      if(distance2 > door_CM){                   // no person at 170 --> PERSON (150 - 170) 
        count3 = count3 + 1;
        c3=itoa(count3);
        LCD_Command(0xC0); LCD_string(c3);
        BT_load_char(count3);
        __delay_ms(1000);
      } // End if PERSON (150 - 170)           
      if(distance2 < door_CM){             // Person at 170
          RD2=1;                           // Turn on LED 170
          distance1= dist1();              // go get distance at 190 and store it in distance1
          if(distance1 > door_CM){         // no person at 190 --> PERSON (170 - 190)
            count2 = count2 + 1;
            c2=itoa(count2);
            LCD_Command(0xC5); LCD_string(c2);
            BT_load_char(50+count2);
            __delay_ms(1000);
          } // End if PERSON (170 - 190)      
          if(distance1 < door_CM){         // person detected at 190 --> PERSON (over 190)
            RD3=1;                         // Turn on LED 190
            count1 = count1 + 1;
            c1=itoa(count1);
            LCD_Command(0xCC); LCD_string(c1);
            BT_load_char(100+count1);
            __delay_ms(1000);
          } // End if PERSON (over 190)    
       }
    }
  } // End While 
} // End Main


//------------------------------------------------------------------------------------------------------
//--------USE THESE FUNCTIONS IF USING BLUETOOTH MODULE AT THE RX/TX PINS-------------------------------
//------------------------------------------------------------------------------------------------------
//void person150_170(void){
//    //------------------- BT update
//    BT_load_string("People between 150-170:  ");
//    broadcast_BT();
//    BT_load_string(c3);
//    broadcast_BT();
//    BT_load_string("\n");
//    broadcast_BT();
//    BT_load_string("------------------------\n");
//    broadcast_BT();
//}
////----------------------------------------------------------
//void person170_190(void){
//    //------------------- BT update
//    BT_load_string("People between 170-190:  ");
//    broadcast_BT();
//    BT_load_string(c2);
//    broadcast_BT();
//    BT_load_string("\n");
//    broadcast_BT();
//    BT_load_string("------------------------\n");
//    broadcast_BT();
//}
////-----------------------------------------------------------
//void personOver_190(void){
//    //------------------- BT update
//    BT_load_string("People over 190:  ");
//    broadcast_BT();
//    BT_load_string(c1);
//    broadcast_BT();
//    BT_load_string("\n");
//    broadcast_BT();
//    BT_load_string("------------------------\n");
//    broadcast_BT();
//}