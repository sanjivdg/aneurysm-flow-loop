const int motorPin1 = 11; // IN1 pin on L298N
const int motorPin2 = 12; // IN2 pin on L298N
const int enablePin = 3;  // ENA pin on L298N (PWM)

// Factor to drop the output voltage
const float voutFactor = 0.5000000; // use a potentiometer to control this

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

  // Get the factor and map it to the PWM range
  int motorValue = map(voutFactor * 100, 0, 100, 0, 255); // Adjust scale if needed

  // Write the motor value to the enable pin (PWM control)
  analogWrite(enablePin, motorValue);

  Serial.print("Motor Value (PWM): ");
  Serial.println(motorValue);

}
