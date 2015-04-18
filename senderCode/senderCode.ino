// External variables
const int  signal = 7;    // Pin connected to the filtered signal from the circuit
unsigned long time;   
unsigned long frequency;

// Internal variables
int period = 2000;
int starttime = 2000;
int input = 0;
int lastinput = 0;
unsigned long death = 0;
unsigned long heartBeatDiff[4];

void setup() {
  pinMode(signal, INPUT);
}

void loop() {
    time = millis();
    input = digitalRead(signal);

    if ((input != lastinput)&&(input == HIGH)) {
        // If the pin state has just changed from low to high (edge detector)
        period = time - starttime; // Compute the time between the previous beat and the one that has just been detected
        starttime = time; // Define the new time reference for the next period computing
        death = time;
    }
    lastinput = input; // Save the current pin state for comparison at the next loop iteration
    
    if (period < 0) {
        frequency = 0;
    }
    else {
        frequency = 60000/period; // Compute the heart rate in beats per minute (bpm) with the period in milliseconds
    }
  
  
    if ((time - death) > 2000) { // Detect if there is no beat after more than 2 seconds
        //tone(6,900); // Output a continuous tone to the speaker
    } 
}
