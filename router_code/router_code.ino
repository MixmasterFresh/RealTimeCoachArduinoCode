#include <SoftwareSerial.h>
int ledPin = 13; 
int state = 0;
String data = "";
SoftwareSerial portOne(0,1);
SoftwareSerial portTwo(8,9);
boolean check=true;
char command = 'a';
char assembler[50];
int counter=0;
int addresses[50];
unsigned long time;   
unsigned long breaker; 

void setup() {
    portOne.begin(9600);
    portTwo.begin(9600);
}
 
void loop() {
    portTwo.listen();
    check = true;
    while(check) {
        if(portTwo.available() > 0) {
            portOne.write(portTwo.read());
            check = false;
        }
    }  
    portOne.listen();
    state=0;
    while(state<40) {
        if(portOne.available() > 0) {
            portTwo.write(portOne.read());
            state++;
        }
    }
    
}
