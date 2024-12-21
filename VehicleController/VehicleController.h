/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:32:36 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 15:23:46 by fkeitel          ###   ########.fr       */
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

	int lastFrontDistance;
	const int maxTestSpeed;
	const int steerSpeed;
	const int servoDelayTime;

	void adjustSpeed(int distanceFront);
	void steerVehicle(int distanceLeft);

public:

	// Constructor
	VehicleController(ESCMotor motor, SteeringServo servo,
		DistSensor front, DistSensor left);
	// Arduino main functions
	void setup();
	void loop();
};

#endif
