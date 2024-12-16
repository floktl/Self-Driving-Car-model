#include <Servo.h>

Servo myservo;
int initialspeed = 1000;
int maxtestspeed = 1500;
int testdelay = 2000;
int pos = 90;  // Position of the servo set to Center.
int pin12 = 12;
int pin11 = 11;
int leftPin = 3;  // Arduino pin for left signal
int rightPin = 2; // Arduino pin for right signal

// Pins for Distance Sensor (HC-SR04)
const int trigPin = 6;  // TRIG pin connected to Arduino Pin 6
const int echoPin = 7;  // ECHO pin connected to Arduino Pin 7

const unsigned int min_left = 50;
const unsigned int max_right = 130;
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
  delay(2000);                      // Wait 2 seconds for ESC to arm
  Serial.println("ESC Armed. Ready to control motor!");

  for (initialspeed = 1000; initialspeed <= maxtestspeed; initialspeed += 1) {  // Gradually increase initialspeed
    myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
   // Serial.println(initialspeed);                            // Debugging: print throttle value
    delay(10);                                        // Small delay for smooth ramp-up
  }
  delay(testdelay);
  // for (int initialspeed = maxtestspeed; initialspeed >= 1000; initialspeed -= 1) {  // Gradually decrease initialspeed
  //   myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
  //   Serial.println(initialspeed);                            // Debugging: print throttle value
  //   delay(10);                                        // Small delay for smooth ramp-down
  // }

  // delay(testdelay);
  // myservo.writeMicroseconds(0); 

   

  
  

}

void loop() {

 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Send a HIGH pulse for 10 microseconds to trigger the sensor
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

  // Read the time it takes for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters (initialspeed of sound is ~343 meters/second or 0.0344 cm/microsecond)
  distance = duration * 0.0344 / 2;

  if (distance == 0)
    distance = 1;

  // Print the distance to the Serial Monitor
  //Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("");

  //myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
    
  // If the distance is less than 10 cm, automatically turn left
  if (distance < 10 && distance > 1)
  {

  for (; initialspeed >= 1000; initialspeed -= 10) {  // Gradually decrease initialspeed
    myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
   // Serial.println(initialspeed);                            // Debugging: print throttle value
    delay(10);                                        // Small delay for smooth ramp-down
  }

  //myservo.writeMicroseconds(0); 
  }
  else if (distance < 500)
  {
    for (; initialspeed <= maxtestspeed; initialspeed += 10) {  // Gradually increase initialspeed
    myservo.writeMicroseconds(initialspeed);                 // Send throttle signal
    //Serial.println(initialspeed);                            // Debugging: print throttle value
    delay(10);                                        // Small delay for smooth ramp-up
    }
  }



 }

