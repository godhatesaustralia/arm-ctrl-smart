#include <Servo.h>

Servo myServo;
const int X_PIN = A0;          
const int Y_PIN = A1;          
const int SERVO_PIN = 9;

float currentAngle = 90.0;     
const int CENTER = 512;
const int DEADZONE = 50;       
const float MAX_SPEED = 2.5;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(115200);        // Must match Python baud rate
}

void loop() {
  unsigned long startTime = micros(); 

  int xVal = analogRead(X_PIN);
  int yVal = analogRead(Y_PIN);

  int xError = xVal - CENTER;
  int yError = yVal - CENTER;

  bool xActive = abs(xError) > DEADZONE;
  bool yActive = abs(yError) > DEADZONE;

  if (xActive && yActive) {
    if (abs(xError) > abs(yError)) {
      yActive = false; 
    } else {
      xActive = false; 
    }
  }

  if (yActive) {
    float magnitude = (float)(abs(yError) - DEADZONE) / (512 - DEADZONE);
    magnitude = constrain(magnitude, 0.0, 1.0);
    float speedStep = magnitude * MAX_SPEED;

    if (yError > 0) {
      currentAngle += speedStep; 
    } else {
      currentAngle -= speedStep; 
    }
  }

  currentAngle = constrain(currentAngle, 0.0, 180.0);
  myServo.write((int)currentAngle);

  unsigned long endTime = micros(); 
  unsigned long processingTime = endTime - startTime;

  // --- OUTPUT CLEAN CSV DATA FOR PYTHON ---
  Serial.print(millis());          // Column 1: System uptime
  Serial.print(",");
  Serial.print(processingTime);    // Column 2: Execution time (microseconds)
  Serial.print(",");
  Serial.println(currentAngle);    // Column 3: Current servo angle

  delay(15); 
}