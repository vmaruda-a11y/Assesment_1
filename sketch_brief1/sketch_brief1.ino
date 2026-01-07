#include <NewPing.h>

#include <NewPing.h>
#define TRIGGER_PIN 12   // Trigger pin on the ultrasonic sensor
#define ECHO_PIN 11      // Echo pin on the ultrasonic sensor
#define MAX_DISTANCE 200 // Maximum distance in cm
#define SIGNAL_PIN3 3     // Output pin (PWM to electromagnet)
#define SIGNAL_PIN5 5
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup() {
  pinMode(SIGNAL_PIN3, OUTPUT);
  pinMode(SIGNAL_PIN5, OUTPUT);
  Serial.begin(9600); // Start serial monitor
}
void loop() {
  int sensor = sonar.ping_cm();  // Get distance in cm
  int magnetism = 0;             // PWM value for electromagnet
  // --- PWM control logic ---
  if (sensor > 0 && sensor <= 10) {
    // Close range → full strength
    magnetism = 255;
  } else if (sensor > 10 && sensor <= 60) {
    // Medium range → mapped strength
    magnetism = map(sensor, 10, 60, 200, 50);
  } else {
    // Out of range → off
    magnetism = 0;
  }
  analogWrite(SIGNAL_PIN3, magnetism);
  analogWrite(SIGNAL_PIN5, magnetism);
  // --- Sensor reading ---
  Serial.print("Sensor distance: ");
  Serial.print(sensor);
  Serial.print(" cm");
  Serial.print("    -    ");
  // --- Print PWM value ---
  Serial.print("Electromagnet PWM: ");
  Serial.println(magnetism);
  delay(100); // Slight delay for stability
}