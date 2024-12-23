/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DistanceSensor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:50:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 22:32:56 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

class DistSensor
{
private:
	const int trigPin;
	const int echoPin;

public:
	// Constructor
	DistSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}

	// Member functions
	void initialize()
	{
		pinMode(trigPin, OUTPUT);
		pinMode(echoPin, INPUT);
	}

	int getDistance()
	{
		digitalWrite(trigPin, LOW);
		delayMicroseconds(2);
		digitalWrite(trigPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigPin, LOW);

		long duration = pulseIn(echoPin, HIGH);
		return (static_cast<int>(duration * 0.0344 / 2));
	}
};

#endif // DISTANCE_SENSOR_H
