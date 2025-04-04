/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.ino                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:06:04 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/03/10 15:02:20 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ESC.h"

// ESCMotor constructor
ESCMotor::ESCMotor(int motorPin) : pin(motorPin), speed(1500) {}

void ESCMotor::initialize()
{
	Serial.begin(9600);
	motor.attach(pin);
	motor.writeMicroseconds(speed);
	delay(3000);// to prevent damaging motor when code is changed. can be removed once everuthing works
}

void ESCMotor::setSpeed(int newSpeed)
{
	speed = constrain(newSpeed, 1100, 1700);
	motor.writeMicroseconds(speed);
}

int ESCMotor::getSpeed() const
{
	return (speed);
}

// SteeringServo constructor
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
      Serial.println(position);
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
	return (position);
}
