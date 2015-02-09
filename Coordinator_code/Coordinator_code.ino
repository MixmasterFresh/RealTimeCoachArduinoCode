#include <SoftwareSerial.h>
int ledPin = 13; 
int state = 0;
String data = ""; 
SoftwareSerial portTwo(8,9);
boolean check=true;
String command = "";
char assembler[20];
int counter=0;


void setup() {
 Serial.begin(9600); // Default connection rate for my BT module
 portTwo.begin(9600);
 Serial.write("+++");
 while(check) {
   if(Serial.available()>0){
   char[ = Serial.read();
   }
   if(data=="OK") {
     check=false;
   }
 }
 Serial.write("ATID4567");
 delay(50);
 Serial.write("ATCH0x0D");
 delay(50);
 Serial.write("ATMY0");
 delay(50);
 Serial.write("CN");
 delay(1000);
}
 
void loop() {
 Serial.listen();
 while(
   if(Serial.available() > 0){
     data = Serial.read();
   }
 while() {
 portTwo.write(data)
 portTwo.listen();
 if(portTwo.available() > 0){
   command = portTwo.read();
 }
}

