const int motorPin1 = 11; // IN1 pin on L298N
const int motorPin2 = 12; // IN2 pin on L298N
const int enablePin = 3;  // ENA pin on L298N (PWM)
const int triggerPin = 5; // TRIG OUT pin


const float dataPoints[100] = { 
  0.00000000, 0.00959425, 0.04325340, 0.08320370, 0.12305058, 0.16689100, 
  0.21224515, 0.25243447, 0.29386312, 0.34349087, 0.40276115, 0.44804812, 
  0.49889168, 0.54689571, 0.59802857, 0.64977649, 0.69115354, 0.73090045, 
  0.77653285, 0.82333678, 0.86631539, 0.90984048, 0.95181900, 0.98715184, 
  1.00000000, 0.97838195, 0.93873814, 0.90221127, 0.87583676, 0.87044886, 
  0.88508645, 0.91112679, 0.93550286, 0.95165308, 0.95787179, 0.94813071, 
  0.92584312, 0.89507430, 0.86174358, 0.81937268, 0.78077590, 0.74400614, 
  0.70565190, 0.66783444, 0.62858114, 0.58857778, 0.55226616, 0.51531591, 
  0.47785930, 0.43816719, 0.40406228, 0.38760960, 0.39431796, 0.41746276, 
  0.44751723, 0.46559667, 0.47358435, 0.47260245, 0.46375366, 0.45045704, 
  0.43109078, 0.40472792, 0.38055057, 0.34932716, 0.32187897, 0.29405196, 
  0.27071667, 0.25113710, 0.23461623, 0.22127095, 0.21078955, 0.20197388, 
  0.19581752, 0.19090801, 0.18669402, 0.18208844, 0.17935460, 0.17575190, 
  0.17096963, 0.16640834, 0.15827345, 0.15235088, 0.14617893, 0.14063280, 
  0.13260701, 0.12596425, 0.11998972, 0.11356386, 0.10744646, 0.10110502, 
  0.09455901, 0.08684408, 0.07899277, 0.07094664, 0.06157572, 0.05004229, 
  0.03646322, 0.02138403, 0.00627969, 0.00000000 
}; 

int index = 0; // Index to track the current data point
unsigned long previousMillis = 0; // Store the last time the data point was updated
const unsigned long interval = 10; // Interval between data points in milliseconds
const int triggerIndex = 50; // Index where trigger is fired



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Set initial motor direction
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the data point was updated
    previousMillis = currentMillis;

    // Get the current data point value and map it to the PWM range
    int motorValue = map(dataPoints[index] * 100, 0, 100, 120, 255); // Adjust scale if needed

    // Write the motor value to the enable pin (PWM control)
    analogWrite(enablePin, motorValue);

   
    // Serial output for debugging
    // Serial.print("Index: ");
    // Serial.print(index);
    // Serial.print(" | Data Point: ");
    // Serial.print(dataPoints[index]);
    // Serial.print(" | Motor Value (PWM): ");
    // Serial.println(motorValue);
    // Serial.print(" | millis() value: ");
    // Serial.println(currentMillis);
    
    // Fire trigger (ideally this should be in a function)
    if (index == triggerIndex) {
      // digitalWrite(triggerPin, HIGH);
      // delay(10); // The delay is a dirty way of sending a reliable width pulse at the cost of slowing down the rest of the code
      analogWrite(triggerPin, 255); // There might be a way to use PWM signals to control the width of the output
    }
    else {
      // digitalWrite(triggerPin, LOW);
      analogWrite(triggerPin, 0);
    }


    // Move to the next data point
    index++;
    if (index >= 100) {
      index = 0; // Reset index to loop through the data points again
    }

  }
}
