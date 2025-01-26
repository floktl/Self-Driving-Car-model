/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/01/26 11:08:08 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	C++ Program to steer the vehicle automously or via remote control
 */

#include "VehicleController.h"

// Pin Configuration on arduino
ESCMotor mainMotor(9);
SteeringServo steering(10);	// Pin, max left angle, max right angle

// trigger and echo pins for sensor
DistSensor frontSensor(6, 7);
DistSensor leftSensor(4, 5);
DistSensor rightSensor(2, 3);

// constructing the vehicle class with subcomponents
VehicleController car(mainMotor, steering, frontSensor, leftSensor, rightSensor);

//	for L293d servo controller
int high_signal = 12;
int high_signal = 11;

void setup() {

	pinMode(high_signal, OUTPUT);
	pinMode(high_signal, OUTPUT);

	car.vehicle_setup();
}

// main loop
void loop() {

	digitalWrite(high_signal,HIGH);
	digitalWrite(high_signal,LOW);

	car.loop();
}
