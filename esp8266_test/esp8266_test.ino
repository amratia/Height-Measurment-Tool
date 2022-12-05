#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "Amr_Laptop";   // Your Network SSID
const char* password = "12345678";       // Your Network Password

int count1;
int count2;
int count3;
int x; 
int b1,b2,b3,b4,sel0,sel1;

WiFiClient client;

unsigned long myChannelNumber = 1947398; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "GPEQ2EIN67NEDBS3"; //Your Write API Key
//------------------------------------------------------------------------------------------------------------------- SETUP
void setup() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
 
  count1 = 0;
  count2 = 0;
  count3 = 0;

  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  
}
//------------------------------------------------------------------------------------------------------------------- LOOP
void loop() {
  b1 = digitalRead(D2);
  b2 = digitalRead(D3);
  b3 = digitalRead(D4);
  b4 = digitalRead(D5);
  sel0 = digitalRead(D0);
  sel1 = digitalRead(D1);
  x = (b1*1)+(b2*2)+(b3*4)+(b4*8);
  if((sel0==0)&&(sel1==0)){count1=x;}
  if((sel0==1)&&(sel1==0)){count2=x;}
  if((sel0==0)&&(sel1==1)){count3=x;}
  ThingSpeak.writeField(myChannelNumber, 1,count1, myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 2,count2, myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 3,count3, myWriteAPIKey); //Update in ThingSpeak
  
  
//----------------------------------------------
  Serial.print("Counter1: ");
  Serial.println(count1);   
  Serial.print("Counter2: ");
  Serial.println(count2);
  Serial.print("Counter3: ");
  Serial.println(count3); 
  Serial.println("------------");

  //delay(1000);

}
