/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DistanceSensor.ino                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:00:02 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/20 23:00:28 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--------------------- DistanceSensor implementation -------------------------

#include "DistanceSensor.h"

DistSensor::DistSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}

void DistSensor::initialize()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

int DistSensor::getDistance()
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	long duration = pulseIn(echoPin, HIGH);
	return duration * 0.0344 / 2; // Convert to centimeters
}
