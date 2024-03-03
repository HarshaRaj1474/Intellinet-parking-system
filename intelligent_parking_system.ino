/*
  Developed by :- Harshavardhan Talap
  Contact :- closesup1474@gmail.com
  contact No:- +91 9373694534


  for any query feel free to contact
  try to contact on weekend
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int servoMotorPin = 13;  // Servo motor control pin

Servo gateServo;

const int numSensors = 11;
const int sensorPins[numSensors] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12 };
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the I2C address if needed
int num;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();
    pinMode(sensorPins[10], INPUT);
  gateServo.attach(servoMotorPin);

  for (int i = 0; i <10; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  
  lcd.print("  Intelligent  ");
  lcd.setCursor(0, 1);
  lcd.print(" Parking system");
  delay(2000);
}

void loop() {
  // Read sensor inputs for 3 seconds
  delay(1000);

  // Display ON sensor numbers on the I2C LCD after a 2-second delay
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Occupied:");

  for (int i = 0; i < 10; i++) {
    if (digitalRead(sensorPins[i]) == LOW) {
      num = (sensorPins[i]) - 1;
      lcd.print(num);
      lcd.print(" ");
      if (i == 1) {
        lcd.setCursor(0, 1);
      }
    }
  }
  // Display OFF sensor numbers on the I2C LCD after a 2-second delay
  delay(1000);
  lcd.clear();
  lcd.print("Free Space: ");

  for (int i = 0; i < 10; i++) {
    if (digitalRead(sensorPins[i]) == HIGH) {
      num = (sensorPins[i]) - 1;
      lcd.print(num);
      lcd.print(" ");

      if (i == 1) {
        lcd.setCursor(0, 1);
      }
    }
  }
   if (digitalRead(sensorPins[10]) == HIGH) {
    // IR sensor detects an obstacle (gate closed)
    openGate();
    delay(1000);  // Wait for 5 seconds to keep the gate open (adjust as needed)
  } else {
    // IR sensor doesn't detect an obstacle (gate open)
    closeGate();
  }
}

void openGate() {
  gateServo.write(90);  // Assuming 0 degrees is the open position
  delay(1000);  // Adjust delay as needed for the servo to reach the position
}

void closeGate() {
  gateServo.write(0);  // Assuming 180 degrees is the closed position for a 270-degree servo
  delay(1000);  // Adjust delay as needed for the servo to reach the position
}

