#include <Servo.h>

Servo myservo;
int pos = 90;  // Position of the servo set to Center.
int pin12 = 12;
int pin11 = 11;
int leftPin = 3;  // Arduino pin for left signal
int rightPin = 2; // Arduino pin for right signal

void setup() {
  pinMode(pin12, OUTPUT);
  pinMode(pin11, OUTPUT);
  pinMode(leftPin, INPUT);  // Set leftPin as input
  pinMode(rightPin, INPUT); // Set rightPin as input
  myservo.attach(9);  // Attach the servo to pin 9
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  Serial.println("Arduino is ready.");
}

void loop() 
{
  int leftState = digitalRead(leftPin);   // Read the state of leftPin
  int rightState = digitalRead(rightPin); // Read the state of rightPin
  digitalWrite(pin12,HIGH);
  digitalWrite(pin11,LOW);
  if (leftState == HIGH) {  // If the left signal is HIGH, move the servo left
    Serial.print("\nLeft");
    if ( pos >= 60)
    {
      Serial.println(pos);
      pos -= 10;  // Prevent the position from going below 0
      myservo.write(pos);     // Update the servo position
      delay(100);  // Small delay for smooth movement
    }
  }
  if (rightState == HIGH) { // If the right signal is HIGH, move the servo right
    Serial.print("\nRight");
    
    if ( pos <= 120)
    {
      Serial.println(pos);
      pos += 10; // Prevent the position from going above 180
      myservo.write(pos);      // Update the servo position
      delay(100);  // Small delay for smooth movement
    }
  }
  //delay(100);  // Optional delay to prevent too much serial data output
}
