// External variables
const int  signal = 7;    // Pin connected to the filtered signal from the circuit
unsigned long time;   

// Internal variables
int starttime = 2000;
int input = 0;
int lastinput = 0;
int index = 0;
double period[6]={1.0,1.0,1.0,1.0,1.0,1.0};

void setup() {
    pinMode(signal, INPUT);
}

void loop() {
    time = millis();
    input = digitalRead(signal);

    if ((input != lastinput)&&(input == HIGH)) {
        // If the pin state has just changed from low to high (edge detector)
        period[index] = (double)(time - starttime); // Compute the time between the previous beat and the one that has just been detected
        starttime = time; // Define the new time reference for the next period computing
        death = time;
    }
    
    lastinput = input; // Save the current pin state for comparison at the next loop iteration
    
    if(
    
    index++;
}
