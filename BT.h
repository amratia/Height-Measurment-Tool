#ifndef BT_H
#define BT_H

void Initialize_Bluetooth(){
    //Set the pins of RX and TX//
    TRISC6=1;
    TRISC7=1;
    //Set the baud rate using the look up table in datasheet(pg114)//
    BRGH=1;      //Always use high speed baud rate with Bluetooth else it wont work
    SPBRG=25;    // Baud rate 9600
    //Turn on Asyc. Serial Port//
    SYNC=0; //0 = Asynchronous mode
    SPEN=1; //1 = Serial port enabled (configures RC7/RX/DT and RC6/TX/CK pins as serial port pins)
    //Set 8-bit reception and transmission
    RX9=0; //0 = Selects 8-bit reception
    TX9=0; //0 = Selects 8-bit transmission
    //Enable transmission and reception//
    TXEN=1; // TXEN: Transmit Enable bit --> 1 = Transmit enabled 
    CREN=1; // CREN: Continuous Receive Enable bit --> 1 = Enables continuous receive in Asynchronous mode
}
//___________BT initialized_____________//

//Function to load the Bluetooth Rx. buffer with one char.//
void BT_load_char(char byte)  {
    TXREG = byte; // load char to buffer 
    while(!TXIF); // only exit while loop if 1 --> 1 means the TXREG is empty and data transfered to TSR  
    while(!TRMT); // bit TRMT shows the status of the TSR register. TRMT =1 --> TSR empty 
}

//Function to Load Bluetooth Rx. buffer with string//
void BT_load_string(char* string){
    while(*string)
    BT_load_char(*string++);
}

//Function to broadcast data from RX. buffer//
void broadcast_BT(){
  TXREG = 13;  
  __delay_ms(300);
}

//Function to get a char from Rx.buffer of BT//
char BT_get_char(void)   {
    if(OERR){ // check for over run error
        CREN = 0;
        CREN = 1; //Reset CREN
    }
    if(RCIF==1){ //if the user has sent a char return the char (ASCII value)
    while(!RCIF);  
    return RCREG;
    }
    else{ //if user has sent no message return 0
        return 0;
    }
}

#endif /* BT_H */