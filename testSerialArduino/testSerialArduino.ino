int count1;
int count2;
int count3;

unsigned char countChar; 

//------------------------------------------------------------------------------------------------------------------- SETUP
void setup() {
 
  count1 = 0;
  count2 = 0;
  count3 = 0;

  Serial.begin(9600);
  delay(10);
  
}
//------------------------------------------------------------------------------------------------------------------- LOOP
void loop() {

if(Serial.available()){
  count1 = int(Serial.read());
  countChar = Serial.read();
}

//----------------------------------------------
  Serial.println(countChar); 
  Serial.print("Counter1: ");
  Serial.println(count1);   
  Serial.print("Counter2: ");
  Serial.println(count2);
  Serial.print("Counter3: ");
  Serial.println(count3); 
  Serial.println("------------");

  delay(500);

}
