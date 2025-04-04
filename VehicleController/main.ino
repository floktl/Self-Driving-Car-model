/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/04/04 14:30:58 by gstronge         ###   ########.fr       */
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
DistSensor frontSensor(4, 6);//(trigger, echo)
DistSensor leftSensor(5, 7);
DistSensor rightSensor(11, 12);

// constructing the vehicle class with subcomponents
VehicleController car(mainMotor, steering, frontSensor, leftSensor, rightSensor);


void setup() {
	car.vehicle_setup();
}

// main loop
void loop() {
	car.loop();
}
