/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 18:42:13 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VehicleController.h"

// Pin Configuration
ESCMotor mainMotor(9);
SteeringServo steering(10);	// Pin, max left angle, max right angle
DistSensor frontSensor(6, 7);
DistSensor leftSensor(4, 5);
DistSensor rightSensor(2, 3);

VehicleController vehicle(mainMotor, steering, frontSensor, leftSensor, rightSensor);

//	for motor controller
int pin12 = 12;
int pin11 = 11;


void setup() {
	pinMode(pin12, OUTPUT);
	pinMode(pin11, OUTPUT);
	vehicle.setup();
}

void loop() {
	digitalWrite(pin12,HIGH);
	digitalWrite(pin11,LOW);

	vehicle.loop();
}
