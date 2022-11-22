/* 
 * File:   sensor.h
 * Author: Amr Atia
 *
 * Created on November 6, 2022, 8:33 PM
 */

#ifndef SENSOR_H
#define SENSOR_H

float dist1(void)//190 cm
{
    float distance1 = 0.0;
    TMR1 = 0;
    RD7 = 1;
    __delay_us(10);
    RD7 = 0;
    while(!RD6);
    TMR1ON = 1;
    while(RD6);
    TMR1ON = 0;
    distance1 = TMR1/58.8;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
 
    return distance1;
}
//---------------------------------------------
float dist2(void) // 170 cm
{
    float distance2 = 0.0;
    TMR1 = 0;
    RD5 = 1;
    __delay_us(10);
    RD5 = 0;
    while(!RD4);
    TMR1ON = 1;
    while(RD4);
    TMR1ON = 0;
    distance2 = TMR1/58.8;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
 
    return distance2;
}
//---------------------------------------------
float dist3(void) // 150 cm
{
    float distance3 = 0.0;
    TMR1 = 0;
    RC5 = 1;
    __delay_us(10);
    RC5 = 0;
    while(!RC4);
    TMR1ON = 1;
    while(RC4);
    TMR1ON = 0;
    distance3 = TMR1/58.8;
    T1CKPS0=0;
    T1CKPS1=0;
 
    return distance3;
}



#endif	/* SENSOR_H */



