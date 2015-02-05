int ledPin = 13; 
int state = 0;
String data; 
SoftwareSerial portTwo(8,9);
int[] team;
boolean check=true;
 
void setup() {
 Serial.begin(9600); // Default connection rate for my BT module
 portTwo.begin(9600);
 Serial.write(+++);
 while(check) {
   data=Serial.read();
   if(data=="OK") {
     check=false;
   }
 }
 Serial.write(ATID4567);
 Serial.write(ATCH0x0D);
 Serial.write(ATMY0);
 Serial.write(CN);
 
}
 
void loop() {

 if(Serial.available() > 0){
 data = Serial.read();
 }
 PortTwo.write(data)

 }
 }
}
