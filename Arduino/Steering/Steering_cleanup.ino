// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Steering.ino                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/09 18:21:44 by Florian Kei       #+#    #+#             */
// /*   Updated: 2024/12/09 18:57:52 by Florian Kei      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// //-----------------------------------------------------------------------------
// //-------------------- Steering control for arduino ---------------------------
// //-----------------------------------------------------------------------------

// //------------------------------- libraries -----------------------------------
// #include <Servo.h>

// Servo myservo;

// // Pin declarations for the Servo and Distance Sensor
// int pos = 90;  // Position of the servo set to Center.
// int pin12 = 12;
// int pin11 = 11;
// int leftPin = 3;  // Arduino pin for left signal
// int rightPin = 2; // Arduino pin for right signal

// // Pins for Distance Sensor (HC-SR04)
// const int trigPin = 6;  // TRIG pin connected to Arduino Pin 6
// const int echoPin = 7;  // ECHO pin connected to Arduino Pin 7

// //	variables for max steering positions
// const unsigned int min_left = 50;
// const unsigned int max_right = 130;
// const unsigned int steer_speed = 10;
// const unsigned int servo_delay_time = 10;

// // Variables for Distance Sensor
// long duration;
// int distance;

// //------------------------------- setup -----------------------------------

// void setup()
// {
// 	pinMode(pin12, OUTPUT);
// 	pinMode(pin11, OUTPUT);
// 	pinMode(leftPin, INPUT);  // Set leftPin as input
// 	pinMode(rightPin, INPUT); // Set rightPin as input
// 	myservo.attach(9);  // Attach the servo to pin 9
// 	Serial.begin(9600);  // Start serial communication at 9600 baud rate
// 	Serial.println("Arduino is ready.");

// 	// Set up Distance Sensor
// 	pinMode(trigPin, OUTPUT);
// 	pinMode(echoPin, INPUT);
// }

// void move_servo(int value)
// {
//   digitalWrite(pin12,HIGH);
// 	digitalWrite(pin11,LOW);
// 	pos += steer_speed;
// 	myservo.write(pos);
// 	delay(servo_delay_time);
// }

// int distance_sensor(int leftState, int rightState)
// {
// 	// Read Distance Sensor
// 	// Send a LOW pulse to TRIG to ensure it starts in a clean state
// 	digitalWrite(trigPin, LOW);
// 	delayMicroseconds(2);

// 	// Send a HIGH pulse for 10 microseconds to trigger the sensor
// 	digitalWrite(trigPin, HIGH);
// 	delayMicroseconds(10);
// 	digitalWrite(trigPin, LOW);

// 	// Read the time it takes for the echo to return
// 	duration = pulseIn(echoPin, HIGH);

// 	// Calculate the distance in centimeters
//   // (speed of sound is ~343 meters/second or 0.0344 cm/microsecond)
// 	distance = duration * 0.0344 / 2;

// 	// Print the distance to the Serial Monitor
// 	Serial.print("Distance: ");
// 	Serial.print(distance);
// 	Serial.println(" cm");

// 	// If the distance is less than 10 cm, automatically turn left
// 	if (leftState != HIGH && rightState != HIGH && distance < 10 && distance > 0)
// 	{
//     if (pos + steer_speed > min_left)
//     {
//       move_servo(+steer_speed);
//     }
//     return (1);
// 	}
// 	return (0);
// }

// void loop() {
// 	// safety check, to avoid mechanical damage
// 	if (pos > max_right || pos < min_left)
// 		return;
// 	// Read the state of the left and right signals from Raspberry Pi
//   //  steering from raspberry has highest priority due to safety reasons
// 	int leftState = digitalRead(leftPin);   // Read the state of leftPin
// 	int rightState = digitalRead(rightPin); // Read the state of rightPin

// 	if (distance_sensor(leftState, rightState) == 0)
// 	{
//     if (leftState == HIGH) //move the servo left
// 		{
// 			if (pos - steer_speed > min_left)
// 				move_servo(-steer_speed);
// 		}
// 		else if (rightState == HIGH) //move the servo right
// 		{
// 			if (pos + steer_speed < max_right)
// 				move_servo(+steer_speed);
// 		}
// 	}
// }
