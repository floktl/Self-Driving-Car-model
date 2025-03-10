/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.ino                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:06:04 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/03/07 17:48:29 by gstronge         ###   ########.fr       */
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
	Serial.println("delay 1 = BEFORE");
	delay(2000);
	Serial.println("delay 1 = AFTER");
	// motor.writeMicroseconds(1000);
	// delay(2000);
	// motor.writeMicroseconds(1500);
	// int temp_speed = speed;
	// while (temp_speed < 1800)
	// {
	// 	Serial.println("1st loop: ");
	// 	Serial.println(temp_speed);
	// 	motor.writeMicroseconds(temp_speed);
	// 	delay(100); // Allow the ESC to
	// 	temp_speed++;
	// }
	// motor.writeMicroseconds(1500);
	// Serial.println("delay 2 = BEFORE");
	// delay(10000);
	// Serial.println("delay 2 = AFTER");
	// while (temp_speed > 1100)
	// {
	// 	Serial.println("2nd loop: ");
	// 	Serial.println(temp_speed);
	// 	motor.writeMicroseconds(temp_speed);
	// 	delay(100); // Allow the ESC to
	// 	temp_speed--;
	// }
	// Serial.println("delay 3 = BEFORE");
	// delay(10000);
	// Serial.println("delay 3 = AFTER");
	// while (temp_speed < 1500)
	// {
	// 	motor.writeMicroseconds(temp_speed);
	// 	delay(100); // Allow the ESC to
	// 	temp_speed++;
	// }
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
