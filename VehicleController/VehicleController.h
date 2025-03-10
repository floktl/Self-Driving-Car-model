/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VehicleController.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:32:36 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/03/07 17:50:18 by gstronge         ###   ########.fr       */
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
	const int	steerSpeed = 30;
	const int	servoDelayTime = 2;
	const int	front_max_distance = 60;
	const int	side_max_distance = 30;

	const int 	leftPin = 8;  // Arduino pin for left signal (raspberry)
	const int 	rightPin = 3; // Arduino pin for right signal (raspberry)
	const int 	upPin = 9; // Arduino pin for forward signal (raspberry)
	const int 	downPin = 2; // Arduino pin for forward signal (raspberry)

	int			leftState;   // Read the state of leftPin
	int			rightState; // Read the state of rightPin
	int			upState; // Read the state of upPin
	int			downState; // Read the state of upPin

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
