/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:32:36 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 17:51:13 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEHICLE_CONTROLLER_H
#define VEHICLE_CONTROLLER_H

#include <Servo.h>
#include "ESC.h"
#include "DistanceSensor.h"

#define MIN_LEFT_STEERING 50
#define MAX_RIGHTSTEERING 130

class VehicleController
{
private:
	ESCMotor mainMotor; // motor for moving forward and backwards
	SteeringServo steering; // motor for steering left and right
	DistSensor frontSensor; // Ultrasonic front sensor
	DistSensor leftSensor; // Ultrasonic left side sensor
	DistSensor rightSensor; // Ultrasonic right side sensor

	int lastFrontDistance;
	const int maxTestSpeed;
	const int steerSpeed;
	const int servoDelayTime;

	void adjustSpeed(int distanceFront);
	void steerVehicle(int distanceLeft, int distanceright);

public:

	// Constructor
	VehicleController(ESCMotor motor, SteeringServo servo,
		DistSensor front, DistSensor left, DistSensor right);
	// Arduino main functions
	void setup();
	void loop();
};

#endif
