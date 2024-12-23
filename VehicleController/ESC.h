/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:54:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 22:33:39 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESC_H
#define ESC_H

#include <Servo.h>
#include "VehicleController.h"

class ESCMotor
{
private:
	Servo		motor;
	const int	pin;
	int			speed;

public:
	// constructor
	ESCMotor(int motorPin);

	void initialize();
	void setSpeed(int newSpeed);
	int getSpeed() const;
};

class SteeringServo
{
private:
	Servo		servo;
	const int	pin;
	int			position;

public:
	//max steering angles
	const unsigned int minLeft;
	const unsigned int maxRight;

	// Constructor
	SteeringServo(int servoPin);

	// member functions
	void initialize();

	void steerLeft(int step);
	void steerRight(int step);
	void center();

	int getPosition() const;
};

#endif // ESC_H
