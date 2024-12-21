/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.ino                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:06:04 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 17:13:36 by Florian Kei      ###   ########.fr       */
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
	delay(10);
}

void SteeringServo::steerLeft(int step)
{
	position = constrain(position - step, minLeft, maxRight);
	servo.write(position);
	delay(10);
}

void SteeringServo::steerRight(int step)
{
	position = constrain(position + step, minLeft, maxRight);
	servo.write(position);
	delay(10);
}

void SteeringServo::center()
{
	position = 90;
	servo.write(position);
	delay(10);
}

int SteeringServo::getPosition() const
{
	return position;
}
