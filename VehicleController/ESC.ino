/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.ino                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:06:04 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 15:10:23 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ESC.h"


// ESCMotor implementation
ESCMotor::ESCMotor(int motorPin) : pin(motorPin), speed(1000) {}

void ESCMotor::initialize()
{
	motor.attach(pin);
	motor.writeMicroseconds(speed);
	delay(2000); // Allow the ESC to rrm
}

void ESCMotor::setSpeed(int newSpeed)
{
	speed = constrain(newSpeed, 1000, 2000);
	motor.writeMicroseconds(speed);
}

int ESCMotor::getSpeed() const
{
	return speed;
}

// SteeringServo implementation
SteeringServo::SteeringServo(int servoPin)
	: pin(servoPin), position(90),
		minLeft(MIN_LEFT_STEERING),
		maxRight(MAX_RIGHTSTEERING) {}

void SteeringServo::initialize()
{
	servo.attach(pin);
	servo.write(position);
}

void SteeringServo::steerLeft(int step)
{
	position = constrain(position - step, minLeft, maxRight);
	servo.write(position);
}

void SteeringServo::steerRight(int step)
{
	position = constrain(position + step, minLeft, maxRight);
	servo.write(position);
}

void SteeringServo::center()
{
	position = 90;
	servo.write(position);
}

int SteeringServo::getPosition() const
{
	return position;
}
