#include <Servo.h>

const int START_BUTTON_PIN = 2;
const int SKIP_CALIBRATION_BUTTON_PIN = 3;
const int ESC_PIN = 9;

const int MIN_PWM = 1000;
const int MAX_PWM = 2000;

Servo esc;
bool runStarted = false;

const int RUN_DURATION_MILLISECONDS = 5000;

/*
const float MOTOR_KV = 980;
const float BATTERY_VOLTAGE = 12.0;
const float GEAR_RATIO = 2;

const float WHEEL_DIAMETER_METERS = 2 * 0.0254;

const float TARGET_DISTANCE_METERS = 5;
*/

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
  Serial.begin(9600);

  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SKIP_CALIBRATION_BUTTON_PIN, INPUT_PULLUP);
  esc.attach(ESC_PIN, MIN_PWM, MAX_PWM);

  if (digitalRead(SKIP_CALIBRATION_BUTTON_PIN) == LOW) {
    Serial.println("Skipped ESC calibration.");
    esc.write(0);
  } else {
    begin_esc_calibration();
  }
}

void loop() { 
  if (digitalRead(START_BUTTON_PIN) == LOW && !runStarted) {
    runStarted = true;
    Serial.println("RUN HAS STARTED!");
    moveForDuration(RUN_DURATION_MILLISECONDS);
  }
}

void moveForDuration(float milliseconds) {
  esc.write(180);
  delay(milliseconds);
  esc.write(0);
}

/*
void moveDistance(float targetDistanceMeters) {
  float motorRPM = MOTOR_KV * BATTERY_VOLTAGE;
  float wheelRPM = motorRPM / GEAR_RATIO;
  float wheelCircumferenceMeters = PI * WHEEL_DIAMETER_METERS;
  float maxMetersPerSecond = (wheelRPM / 60) * wheelCircumferenceMeters;

  float runTimeSeconds = targetDistanceMeters / maxMetersPerSecond;

  // NOTE: this code doesn't account for torque and stuff and just assumes
  // the motor's at max speed. 

  esc.write(180);
  delay(runTimeSeconds * 1000);
  esc.write(0);
} */