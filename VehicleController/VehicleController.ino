/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.ino                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:33:13 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 15:23:12 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VehicleController.h"

// ----------------------- VehicleController implementation -------------------
VehicleController::VehicleController(ESCMotor motor,
									SteeringServo servo,
									DistSensor front,
									DistSensor left)
	: mainMotor(motor),
		steering(servo),
		frontSensor(front),
		leftSensor(left),
		lastFrontDistance(0),
		maxTestSpeed(1500),
		steerSpeed(10),
		servoDelayTime(10) {}

// setup function to setup all pins and start values for the vehicle
void VehicleController::setup()
{
	mainMotor.initialize();
	steering.initialize();
	frontSensor.initialize();
	leftSensor.initialize();
	Serial.begin(9600);
	Serial.println("Vehicle Initialized and Ready!");
}

// main loop. which will run continiously
void VehicleController::loop()
{
	int distanceFront = frontSensor.getDistance();
	int distanceLeft = leftSensor.getDistance();

	if (distanceFront > 0 && distanceFront != lastFrontDistance)
	{
		adjustSpeed(distanceFront);
		steerVehicle(distanceLeft);
		lastFrontDistance = distanceFront;
	}

	delay(servoDelayTime);
}

// adjust the speed, if the front distance is free of objects
void VehicleController::adjustSpeed(int distanceFront)
{
	int speed = mainMotor.getSpeed();
	if (distanceFront < 60)
	{
		speed = (speed > 1300) ? speed - 100 : speed + 100;
	}
	mainMotor.setSpeed(speed);
}

//	steer the vehcicle,
void VehicleController::steerVehicle(int distanceLeft)
{
	if (distanceLeft < 30 && distanceLeft > 0)
	{
		if (steering.getPosition() >= steering.minLeft)
		{
			steering.steerLeft(steerSpeed);
		}
	}
	else if (steering.getPosition() != 90)
	{
		steering.center();
	}
}
