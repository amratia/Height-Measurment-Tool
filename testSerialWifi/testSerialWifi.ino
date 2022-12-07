#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "Amr_Laptop";   // Your Network SSID
const char* password = "12345678";       // Your Network Password

int count1;
int count2;
int count3;
int temp;

WiFiClient client;

unsigned long myChannelNumber = 1947141; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "YK1PILKQC6CB5XX8"; //Your Write API Key
//-------------------------------------------------------------------------------------------- SETUP
void setup() {
  count1 = 0;
  count2 = 0;
  count3 = 0;
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}
//--------------------------------------------------------------------------------------------- LOOP
void loop() {
  if(Serial.available()){
    temp = int(Serial.read());
    if(temp < 50){count1 = temp;}
    if((temp > 49) && (temp < 99)){count2 = temp - 50;}
    if(temp > 99){count3 = temp - 100;}
  }
  ThingSpeak.writeField(myChannelNumber, 1,count1, myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 2,count2, myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 3,count3, myWriteAPIKey); //Update in ThingSpeak
  //----------------------------------------------
  //  Serial.println(countChar); 
  //  Serial.print("Counter1: ");
  //  Serial.println(count1);   
  //  Serial.print("Counter2: ");
  //  Serial.println(count2);
  //  Serial.print("Counter3: ");
  //  Serial.println(count3); 
  //  Serial.println("------------");

  delay(100);
}
