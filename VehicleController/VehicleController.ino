/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.ino                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:33:13 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/04/04 14:15:01 by gstronge         ###   ########.fr       */
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
		minFrontDist(10) {}

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
	pinMode(upPin, INPUT); // Set rightPin as input
	pinMode(downPin, INPUT); // Set rightPin as input

	// debugging
	Serial.begin(9600);
	Serial.println("Vehicle Initialized and Ready!");
  steering.center();
  }

int counter = 0;
int distanceFront = 100;

// main loop. which will run continiously
void VehicleController::loop()
{
	Serial.println("xxxxx");
	counter++;
	if (counter % 20 == 0)
		distanceFront = frontSensor.getDistance();
	// int distanceLeft = leftSensor.getDistance();
	// int distanceright = rightSensor.getDistance();

	leftState = digitalRead(leftPin);   // Read the state of raspberry left
	rightState = digitalRead(rightPin); // Read the state of raspberry right
	upState = digitalRead(upPin); // Read the state of raspberry right
	downState = digitalRead(downPin); // Read the state of raspberry right
	// Serial.println("Position: ");
	// Serial.println(steering.getPosition());

		// steer with sensor overrides user steering
	Serial.println(distanceFront);
	if (SENSOR_OVERRIDES && distanceFront < minFrontDist && downState == LOW)//) || distanceLeft < minSideDist  || distanceRight < minSideDist))
		sensorSteering(distanceFront);//), distanceLeft, distanceright);	// steer with sensor
	else // manual control over remote commands
		{
		if (leftState == HIGH && rightState == LOW)
		{  // If the left signal is HIGH, move the servo left
			steering.steerLeft(steerSpeed);
			Serial.println("===================RRRRRRRRRRRRR");
		}
		else if (rightState == HIGH && leftState == LOW)
		{ // If the right signal is HIGH, move the servo right
			Serial.println("-------------------------------------LLLLLLLL");
			steering.steerRight(steerSpeed);
		}
		if (upState == HIGH)
		{
			if (mainMotor.getSpeed() < 1600)
			mainMotor.setSpeed(1600);
		mainMotor.setSpeed(mainMotor.getSpeed() + driveSpeed);
	}
	else if (downState == HIGH)
	{
			Serial.println("HIGHHIGHHIGH");
			if (mainMotor.getSpeed() > 1400)
				mainMotor.setSpeed(1400);
			mainMotor.setSpeed(mainMotor.getSpeed() - driveSpeed);
		}
		else if (mainMotor.getSpeed() > 1500)
		{
			mainMotor.setSpeed(mainMotor.getSpeed() - driveSpeed);
		}
		else if (mainMotor.getSpeed() < 1500)
		{
			mainMotor.setSpeed(mainMotor.getSpeed() + driveSpeed);
		}

	}
	delay(servoDelayTime);
}

//------------------------------- private functions ----------------------------


void VehicleController::sensorSteering(int distanceFront)
{
	Serial.println("sensor steering");
	if (distanceFront < minFrontDist)
	{
		while (constrain(mainMotor.getSpeed(), 1400, 1600))
		{
			mainMotor.setSpeed(mainMotor.getSpeed() - 50);
			delay(servoDelayTime);
		}
	}
	
	// if (distanceFront != minFrontDist)
	// {
	// 	adjustSpeed(distanceFront);
	// 	steerVehicle(distanceLeft, distanceright);
	// 	minFrontDist = distanceFront;
	// }
}

// adjust the speed, if the front distance is free of objects
void VehicleController::adjustSpeed(int distanceFront)
{
	int speed = mainMotor.getSpeed();

	speed = (speed > 1500) ? speed - 100 : speed + 100;
	mainMotor.setSpeed(speed);
}

//	steer the vehcicle,
void VehicleController::steerVehicle(int distanceLeft, int distanceright)
{
	if (distanceLeft < side_max_distance && distanceLeft > 0)
	{
		if (steering.getPosition() >= steering.minLeft)
		{
			steering.steerLeft(steerSpeed);
		}
	}
	else if (distanceright < side_max_distance && distanceright > 0)
	{
		if (steering.getPosition() <= steering.maxRight)
		{
			steering.steerRight(steerSpeed);
		}
	}
	else if (steering.getPosition() != steering.middle_pos)
	{
		steering.center();
	}
}
