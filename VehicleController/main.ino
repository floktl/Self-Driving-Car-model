/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/02/24 18:32:11 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	C++ Program to steer the vehicle automously or via remote control
 */

#include "VehicleController.h"

// Pin Configuration on arduino
ESCMotor mainMotor(13);
SteeringServo steering(10);	// Pin, max left angle, max right angle

// trigger and echo pins for sensor
DistSensor frontSensor(6, 7);
DistSensor leftSensor(4, 5);
DistSensor rightSensor(2, 3);

// constructing the vehicle class with subcomponents
VehicleController car(mainMotor, steering, frontSensor, leftSensor, rightSensor);

//	for L293d servo controller
int high_signal1 = 12;
int high_signal2 = 11;

void setup() {

	pinMode(high_signal1, OUTPUT);
	pinMode(high_signal2, OUTPUT);

	car.vehicle_setup();
}

// main loop
void loop() {

	digitalWrite(high_signal1,HIGH);
	digitalWrite(high_signal2,LOW);

	car.loop();
}
