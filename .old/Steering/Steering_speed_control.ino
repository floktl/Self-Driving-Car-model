#include <Servo.h>

Servo myservo;
int initialspeed = 1000;
int maxtestspeed = 1500;
int testdelay = 2000;

// Pins for Distance Sensor (HC-SR04)
const int trigPin = 6;  // TRIG pin connected to Arduino Pin 6
const int echoPin = 7;  // ECHO pin connected to Arduino Pin 7

const unsigned int steer_speed = 10;
const unsigned int servo_delay_time = 10;

// Variables for Distance Sensor
long duration;
int distance;

void setup() {

  myservo.attach(9);       // Attach the ESC signal wire to pin 9
  Serial.begin(9600);      // For debugging purposes

  // Set up Distance Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  Serial.println("Initializing ESC...");
  myservo.writeMicroseconds(1000);  // Minimum throttle (ESC arming)
  delay(2000);
  Serial.println("ESC Armed. Ready to control motor!");
}

void loop() {



 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
  // Send a HIGH pulse for 10 microseconds to trigger the sensor
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

  // Read the time it takes for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters (initialspeed of sound is ~343 meters/second or 0.0344 cm/microsecond)
  distance = duration * 0.0344 / 2;

  // Print the distance to the Serial Monitor
  //Serial.print("Distance: ");
  // if (distance > 0 && distance < 500)
  // {
  //   Serial.print(distance);
  //   Serial.println("");
  // }
  
  if (distance > 0 && distance < 500)
  {
    if (distance < 10)
    {

      if (initialspeed > 1300) {
        initialspeed -= 100;
      }
    }
    else
    {
      if (initialspeed< maxtestspeed) 
        initialspeed += 100;
    }
  }


  Serial.println(initialspeed);
  Serial.println(distance);
  Serial.println("");

  myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
  delay(10);
}

