#include <SoftwareSerial.h>
int ledPin = 13; 
int state = 0;
String data = "";
SoftwareSerial portOne(11,12);
SoftwareSerial portTwo(8,9);
int check=0;
char command = 'a';
char assembler[50];
int counter=0;
byte message;
byte message1;
byte message2;
int addresses[50];
unsigned long time;   
unsigned long breaker; 
int stop = -1;

void setup() {
    portOne.begin(9600);
    portTwo.begin(9600);
}
 
void loop() {
    time = millis();
    portTwo.listen();
    check = 0;
    while(check<2) {
        if(portTwo.available() > 0) {
            message = portTwo.read();
            portOne.write(message);
            check++;
        }
    }
    portOne.listen();
    writeIntAsBinary(-1);  
    state=0;
    breaker = time;
    while(state<20 && time - breaker <1000) {
        if(portOne.available() > 0) {
            message = portOne.read();
            portTwo.write(message);
            state++;
        }
    }
}
void writeIntAsBinary(int value){
    portOne.write(lowByte(value));
    portOne.write(highByte(value));
}
