/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:32:36 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/20 23:12:28 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEHICLE_CONTROLLER_H
#define VEHICLE_CONTROLLER_H

#include <Servo.h>
#include "ESC.h"
#include "DistanceSensor.h"

class VehicleController
{
private:
	ESCMotor mainMotor;
	SteeringServo steering;
	DistSensor frontSensor;
	DistSensor leftSensor;

	int lastFrontDistance;
	const int maxTestSpeed;
	const int steerSpeed;
	const int servoDelayTime;

public:
	VehicleController(ESCMotor motor, SteeringServo servo,
		DistSensor front, DistSensor left);
	void setup();
	void loop();

private:
	void adjustSpeed(int distanceFront);
	void steerVehicle(int distanceLeft);
};

#endif
