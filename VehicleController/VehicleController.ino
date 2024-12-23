/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.ino                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:33:13 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 22:41:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VehicleController.h"

// ----------------------- VehicleController implementation -------------------
VehicleController::VehicleController(ESCMotor motor,
									SteeringServo servo,
									DistSensor front,
									DistSensor left,
									DistSensor right)
	: mainMotor(motor),
		steering(servo),
		frontSensor(front),
		leftSensor(left),
		rightSensor(right),
		lastFrontDistance(0) {}

// setup function to setup all pins and start values for the vehicle
void VehicleController::vehicle_setup()
{
	// init all subcomponents
	mainMotor.initialize();
	steering.initialize();
	frontSensor.initialize();
	leftSensor.initialize();
	rightSensor.initialize();

	// set pins from raspberry as input
	pinMode(leftPin, INPUT);  // Set leftPin as input
	pinMode(rightPin, INPUT); // Set rightPin as input

	// debugging
	Serial.begin(9600);
	Serial.println("Vehicle Initialized and Ready!");
}

// main loop. which will run continiously
void VehicleController::loop()
{
	int distanceFront = frontSensor.getDistance();
	int distanceLeft = leftSensor.getDistance();
	int distanceright = rightSensor.getDistance();

	leftState = digitalRead(leftPin);   // Read the state of raspberry left
	rightState = digitalRead(rightPin); // Read the state of raspberry right
	Serial.println(leftPin);

	//	steer with sensor
	if (leftState != HIGH && rightState != HIGH &&  distanceFront > 0
		&& distanceFront != lastFrontDistance)
	{
		adjustSpeed(distanceFront);
		steerVehicle(distanceLeft, distanceright);
		lastFrontDistance = distanceFront;
	}
	else // manuial control over raspberry commands
	{
		if (leftState == HIGH)
		{  // If the left signal is HIGH, move the servo left
			Serial.println("Left");
			if (steering.getPosition() - steerSpeed > steering.minLeft)
			{
				steering.steerLeft(10);
			}
		}
		if (rightState == HIGH)
		{ // If the right signal is HIGH, move the servo right
			Serial.println("Right");
			if (steering.getPosition() + steerSpeed < steering.maxRight)
			{
				steering.steerRight(10);
			}
		}
	}
	delay(servoDelayTime);
}

//------------------------------- private functions ----------------------------

// adjust the speed, if the front distance is free of objects
void VehicleController::adjustSpeed(int distanceFront)
{
	int speed = mainMotor.getSpeed();

	if (distanceFront < front_max_distance)
	{
		speed = (speed > 1300) ? speed - 100 : speed + 100;
	}
	mainMotor.setSpeed(speed);
}

//	steer the vehcicle,
void VehicleController::steerVehicle(int distanceLeft, int distanceright)
{
	if (distanceLeft < 30 && distanceLeft > 0)
	{
		if (steering.getPosition() >= steering.minLeft)
		{
			steering.steerLeft(steerSpeed);
		}
	}
	else if (distanceright < 30 && distanceright > 0)
	{
		if (steering.getPosition() <= steering.maxRight)
		{
			steering.steerRight(steerSpeed);
		}
	}
	else if (steering.getPosition() != 90)
	{
		steering.center();
	}
}
