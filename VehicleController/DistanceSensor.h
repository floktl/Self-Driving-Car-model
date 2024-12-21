/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DistanceSensor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:50:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2024/12/20 23:03:07 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

class DistSensor
{
private:
	int trigPin;
	int echoPin;

public:
	DistSensor(int trig, int echo);
	void initialize();
	int getDistance();
};

#endif
