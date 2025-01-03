/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:32:36 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/27 15:31:13 by Florian Kei      ###   ########.fr       */
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
	ESCMotor		mainMotor; // motor for moving forward and backwards
	SteeringServo	steering; // motor for steering left and right
	DistSensor		frontSensor; // Ultrasonic front sensor
	DistSensor		leftSensor; // Ultrasonic left side sensor
	DistSensor		rightSensor; // Ultrasonic right side sensor

	int 		lastFrontDistance;
	const int	maxTestSpeed = 1500;
	const int	steerSpeed = 10;
	const int	servoDelayTime = 10;
	const int	front_max_distance = 60;
	const int	side_max_distance = 30;

	const int 	leftPin = 8;  // Arduino pin for left signal (raspberry)
	const int 	rightPin = 9; // Arduino pin for right signal (raspberry)

	int			leftState;   // Read the state of leftPin
	int			rightState; // Read the state of rightPin

	void adjustSpeed(int distanceFront);
	void steerVehicle(int distanceLeft, int distanceright);

public:

	// Constructor
	VehicleController(ESCMotor motor, SteeringServo servo,
		DistSensor front, DistSensor left, DistSensor right);

	// Arduino main functions
	void vehicle_setup();
	void loop();
};

#endif
