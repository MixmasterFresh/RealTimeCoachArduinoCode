#include <SoftwareSerial.h>
int ledPin = 13; 
int state = 0;
String data = ""; 
SoftwareSerial portTwo(8,9);
boolean check=true;
char command = 'a';
char assembler[50];
int counter=0;
int addresses[50];
unsigned long time;   
unsigned long breaker; 

void setup() {
    time = millis();
    Serial.begin(9600);
    portTwo.begin(9600);
    Serial.write("+++");
        while(check) {
            if(Serial.available()>0){
                assembler[counter] = Serial.read();
                data=data+assembler[counter];
                counter++;
                if(counter==2){
                    break;
                }
            }
       
         if(data=="OK") {
             check=false;
         }
     }
     Serial.write("ATID4567");
     delay(50);
     Serial.write("ATCH0D");
     delay(50);
     Serial.write("ATMY0");
     delay(50);
     Serial.write("CN");
     delay(1000);
}
 
void loop() {
    counter=0;
    while(true) {
        if(Serial.available() > 0) {
            assembler[counter] = Serial.read();
            if (assembler[counter]=='?') {
                break;
            }
        counter++;
        }
    }
    while(counter>=0) {
        portTwo.write(assembler[counter]);
        counter--;
    }
    if(counter!=0) {
        counter=0;
    }   
    portTwo.listen();
    if(portTwo.available() > 0) {
        command = portTwo.read();
    }
    if(command=='a') {
        Serial.write('a');
        breaker=time;
        while(time-breaker<1000) {
            if(portTwo.available() > 0) {
                addresses[counter]= Serial.read();
                counter++;
            }
        }
        counter--;
        while(counter>=0) {
            portTwo.write(assembler[counter]);
            counter--;
        }
    }
}
