/* 
 * File:   LCD.h
 * Author: Amr Atia
 *
 * Created on November 6, 2022, 8:33 PM
 */

#ifndef LCD_H
#define LCD_H

#define RS RC2
#define RW RC3
#define EN RD0

// Function to Write Characters on the LCD
void LCD_Data(unsigned char data)
{
PORTB = data; // loading the data to PORTB
RS    = 1  ;   // Data Register
RW    = 0 ;    //Writing
EN    = 1;     //Enable the clock
__delay_ms(5);
EN = 0;
}

// Writing to the instruction register
void LCD_Command(unsigned char cmd)
{
PORTB = cmd; // loading the data to PORTB
RS    = 0 ;    // instruction Register
RW    = 0;     //Writing
EN    = 1  ;   //Enable the clock
__delay_ms(5);
EN = 0;
}

void LCD_init()
{
LCD_Command(0x38); //16x2 model
LCD_Command(0x06); //Increment cursor (shift cursor to right)
LCD_Command(0x0C); // Display ON, cursor OFF
LCD_Command(0x01); // CLEAR

}

void LCD_string (unsigned char *str)
{
int i;
for(i=0;str[i]!='\0';i++)
  LCD_Data(str[i]);
}


char *itoa(int value){
     static char buffer[12];        // 12 bytes is big enough for an INT32
     int original = value;        // save original value
     int c = sizeof(buffer)-1;
     buffer[c] = 0;                // write trailing null in last byte of buffer    
     if (value < 0)                 // if it's negative, note that and take the absolute value
         value = -value;
     
     do                             // write least significant digit of value that's left
     {
         buffer[--c] = (value % 10) + '0';    
         value /= 10;
     } while (value);
 
     if (original < 0)
         buffer[--c] = '-';

     return &buffer[c];
 }






void LCD_Clear()
{
LCD_Command(0x01); // CLEAR
}

// 0x80+col number - row 1
// 0xC0 + col number - row 2
#endif /* LCD_H */


