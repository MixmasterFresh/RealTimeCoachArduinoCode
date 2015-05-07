const int  heart_signal = 8;
const int  headx_signal = 0;
const int  heady_signal = 1;
const int  headz_signal = 2;
const int  bodyx_signal = 3;
const int  bodyy_signal = 4;
const int  bodyz_signal = 5;
unsigned long time;

//////////////////////////////////////////////////////////////////////////////////
// The ID variable. ID's on the same network are not allowed
const int id = 7;
//////////////////////////////////////////////////////////////////////////////////

unsigned long starttime = 2000;

int heart_input = 0;
int headx_input = 0;
int heady_input = 0;
int headz_input = 0;
int bodyx_input = 0;
int bodyy_input = 0;
int bodyz_input = 0;

int hx = 0;
int hy = 0;
int hz = 0;
int bx = 0;
int by = 0;
int bz = 0;

int hxrest = 0;
int hyrest = 0;
int hzrest = 0;
int bxrest = 0;
int byrest = 0;
int bzrest = 0;

int lastinput = 0;

boolean right = true;

byte check_i[]= {0,0,0,0};
int check[] ={0,0};

int period[4]={1.0,1.0,1.0,1.0};

void setup() {
    pinMode(heart_signal, INPUT);
    Serial.begin(9600);
    int hxrest = analogRead(headx_signal);
    int hyrest = analogRead(heady_signal);
    int hzrest = analogRead(headz_signal);
    int bxrest = analogRead(bodyx_signal);
    int byrest = analogRead(bodyy_signal);
    int bzrest = analogRead(bodyz_signal);
}

void loop() {
    time = millis();
    heart_input = digitalRead(heart_signal);
    headx_input = analogRead(headx_signal) - hxrest;
    heady_input = analogRead(heady_signal) - hyrest;
    headz_input = analogRead(headz_signal) - hzrest;
    bodyx_input = analogRead(bodyx_signal) - bxrest;
    bodyy_input = analogRead(bodyy_signal) - byrest;
    bodyz_input = analogRead(bodyz_signal) - bzrest;

    if ((heart_input != lastinput)&&(heart_input == HIGH)) {
        // If the pin state has just changed from low to high (edge detector)
        period[3] = period[2];
        period[2] = period[1];
        period[1] = period[0];
        period[0] = (int)(time - starttime); // Compute the time between the previous beat and the one that has just been detected
        starttime = time; // Define the new time reference for the next period computing
    }
    lastinput = heart_input; // Save the current pin state for comparison at the next loop iteration
    if (headx_input + heady_input + headz_input > hx + hy + hz) {
        // If the pin state has just changed from low to high (edge detector)
        hx = headx_input;
        hy = heady_input;
        hz = headz_input;
    }
    if (bodyx_input + bodyy_input + bodyz_input > bx + by + bz) {
        // If the pin state has just changed from low to high (edge detector)
        bx = bodyx_input;
        by = bodyy_input;
        bz = bodyz_input;
    }
    if(time-starttime>5000) {
        period[3] = 256;
        period[2] = 256;
        period[1] = 256;
        period[0] = 256;
    }
    while(Serial.available() > 0) {
        check_i[3] = check_i[2];
        check_i[2] = check_i[1];
        check_i[1] = check_i[0];
        check_i[0] = Serial.read();
        right = !right;
        if(right){
            check[1] = check[0];
            check[0] = Combine(check_i[1],check_i[0]);
        }
        if(check[1] == id && check[0] == 5000){
            writeIntAsBinary(hx);
            writeIntAsBinary(hy);
            writeIntAsBinary(hz);
            writeIntAsBinary(bx);
            writeIntAsBinary(by);
            writeIntAsBinary(bz);
            writeIntAsBinary(period[0]);
            writeIntAsBinary(period[1]);
            writeIntAsBinary(period[2]);
            writeIntAsBinary(period[3]);
            hx = 0;
            hy = 0;
            hz = 0;
            bx = 0;
            by = 0;
            bz = 0;
            
        }
    }
}
int Combine( unsigned char x_high, unsigned char x_low)
{
  int combined; 
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in                                                             //rightmost 8 bits
  return combined;
}
void writeIntAsBinary(int value){
    Serial.write(lowByte(value));
    Serial.write(highByte(value));
    
}
