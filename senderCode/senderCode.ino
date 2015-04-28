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

int lastinput = 0;

int check[]= {0,0};

int period[4]={1.0,1.0,1.0,1.0};

void setup() {
    pinMode(heart_signal, INPUT);
    Serial.begin(9600);
    digitalWrite(13,HIGH);
}

void loop() {
    time = millis();
    heart_input = digitalRead(heart_signal);
    headx_input = analogRead(headx_signal);
    heady_input = analogRead(heady_signal);
    headz_input = analogRead(headz_signal);
    bodyx_input = analogRead(bodyx_signal);
    bodyy_input = analogRead(bodyy_signal);
    bodyz_input = analogRead(bodyz_signal);

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
    if(Serial.available() > 0) {
        check[1] = check[0];
        check[0] = Serial.read();
        if(check[1] == id && check[0] == -1){
            Serial.write(hx);
            Serial.write(hy);
            Serial.write(hz);
            Serial.write(bx);
            Serial.write(by);
            Serial.write(bz);
            Serial.write(period[0]);
            Serial.write(period[1]);
            Serial.write(period[2]);
            Serial.write(period[3]);
            hx = 0;
            hy = 0;
            hz = 0;
            bx = 0;
            by = 0;
            bz = 0;
        }
    }
}
