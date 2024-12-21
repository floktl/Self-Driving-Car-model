/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.ino                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:53:24 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/21 15:02:36 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VehicleController.h"

// Pin Configuration
ESCMotor mainMotor(9);
SteeringServo steering(10);	// Pin, max left angle, max right angle
DistSensor frontSensor(6, 7);
DistSensor leftSensor(4, 5);

VehicleController vehicle(mainMotor, steering, frontSensor, leftSensor);

void setup() {
	vehicle.setup();
}

void loop() {
	vehicle.loop();
}
