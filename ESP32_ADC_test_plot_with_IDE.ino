// reads analog from transducer as absolute value ± around 2206
// Uses ESP32C3 Dev Module

// MIT License benlo.com

// if ADC > Vtrig, show next 50 mSec and stops
// any key continues real time trace of Vmax in 1 mSec samples

// plot the value on the IDE


void setup() {
    // initialize serial communication
  Serial.begin(500000);
  
    //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);
}

unsigned long endT = 0;
int analogValue = 0;
int analogMax   = 3350;
int Vtrig = 75;
unsigned long stop = 1e9;

void loop() {
  // read the analog / millivolts value for GPI00 ADC1 CH1
  analogValue = analogRead(0);
  analogValue = abs(analogValue-2206);
  analogMax = max(analogMax,analogValue);

  if ( micros() >= endT )
    {
    if ( (stop == 1e9) && (analogMax > Vtrig) ) stop = micros() + 50000;  // triggered plot length

    if ( micros() < stop ) Serial.printf("%d\n",analogMax);

    if ( Serial.available() )  // key pressed on terminal?
      {
      String command = Serial.readString();
      Serial.println("Command Received");
      command.trim();
      Serial.println(command);
      stop = 1e9;
      }

    analogMax = 0;
    endT = micros()+1000;  // 1 mSec samples
    }
}
