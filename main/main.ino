#include <Servo.h>

const int ESC_PIN = 9;

const int MIN_PWM = 1000;
const int MAX_PWM =  2000;

Servo esc;
bool run_started = false;

void begin_esc_calibration() {
  Serial.println("Starting ESC calibration...");
  
  Serial.println("Full throttle - Power on ESC now!");
  esc.writeMicroseconds(MAX_PWM);
  delay(3000);
  
  Serial.println("Zero throttle - Calibration should complete.");
  esc.writeMicroseconds(MIN_PWM);
  delay(3000);

  Serial.println("Calibration complete!");
}
void setup() {
  esc.attach(ESC_PIN, MIN_PWM, MAX_PWM);
  Serial.begin(9600);
  
  begin_esc_calibration();
}

void loop() {
  // little program that tests the max speed, half speed, and no speed
  Serial.println("Begin loop");
  delay(3000);
  esc.write(180);
  delay(3000);
  esc.write(90);
  delay(3000);
  esc.write(0);
}
