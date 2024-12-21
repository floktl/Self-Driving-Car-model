/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESC.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:54:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/20 22:55:21 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESC_H
#define ESC_H

#include <Servo.h>

class ESCMotor
{
private:
	Servo motor;
	int pin;
	int speed;

public:
	ESCMotor(int motorPin);
	void initialize();
	void setSpeed(int newSpeed);
	int getSpeed() const;
};

class SteeringServo
{
private:
	Servo servo;
	int pin;
	int position;

public:
	const unsigned int minLeft;
	const unsigned int maxRight;
	SteeringServo(int servoPin, unsigned int minLeft, unsigned int maxRight);
	void initialize();
	void steerLeft(int step);
	void center();
	int getPosition() const;
};

#endif
