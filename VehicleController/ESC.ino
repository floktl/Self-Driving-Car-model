/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.ino                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:06:04 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/03/03 16:30:10 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ESC.h"

// ESCMotor constructor
ESCMotor::ESCMotor(int motorPin) : pin(motorPin), speed(1700) {}

void ESCMotor::initialize()
{
	motor.attach(pin);
	int temp_speed = speed;
	while (temp_speed > 1300)
	{
		motor.writeMicroseconds(temp_speed);
		delay(100); // Allow the ESC to
		temp_speed--;
	}
}

void ESCMotor::setSpeed(int newSpeed)
{
	speed = constrain(newSpeed, 1300, 1700);
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
        // Serial.println("POSITION LEFT: ");
        // Serial.println(steering.getPosition());
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
