/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DistanceSensor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:50:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 15:15:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

class DistSensor
{
private:
    int trigPin;
    int echoPin;

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
        return static_cast<int>(duration * 0.0344 / 2); // Convert microseconds to centimeters
    }
};

#endif // DISTANCE_SENSOR_H
