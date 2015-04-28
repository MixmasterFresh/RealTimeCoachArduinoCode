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
byte message;
int addresses[50];
unsigned long time;   
unsigned long breaker; 
int stop = -1;

void setup() {
    portOne.begin(9600);
    portTwo.begin(9600);
}
 
void loop() {
    portTwo.listen();
    check = true;
    while(check) {
        if(portTwo.available() > 0) {
            message =portTwo.read();
            portOne.write(message);
            portOne.write('?');
            check = false;
        }
    }  
    portOne.listen();
    state=0;
    while(state<20) {
        if(portOne.available() > 0) {
            message = portOne.read();
            portTwo.write(message);
            state++;
        }
    }
    
}
