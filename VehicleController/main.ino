/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 22:32:04 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VehicleController.h"

// Pin Configuration
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
