# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pin_change.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 16:53:44 by fkeitel           #+#    #+#              #
#    Updated: 2024/11/25 16:57:39 by fkeitel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------------------------------------------
#	test script to change the pins status of each gpio pin
#	usuage (on raspberry): python3 pin_change.py
#-------------------------------------------------------------------------------

import RPi.GPIO as GPIO
import time

# List of GPIO pins to toggle
ALL_GPIO_PINS = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
				17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]

# GPIO setup
GPIO.setmode(GPIO.BCM)

try:
	for pin in ALL_GPIO_PINS:
		# Set pin as output
		GPIO.setup(pin, GPIO.OUT)
		# Turn the pin ON
		print(f"Turning ON GPIO {pin}")
		GPIO.output(pin, GPIO.LOW)

		# Wait for 0.5 seconds
		time.sleep(2)

		# Turn the pin OFF
		print(f"Turning OFF GPIO {pin}")
		GPIO.output(pin, GPIO.HIGH)

		# Clean up the pin (optional, to reset the pin)
		#GPIO.cleanup(pin)

except KeyboardInterrupt:
	print("Script interrupted by user")

finally:
	# Clean up all GPIO configurations
	GPIO.cleanup()
	print("GPIO cleanup completed")
