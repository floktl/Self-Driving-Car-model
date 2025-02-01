import pygame
from mock_gpio_library import GPIO  # Mock GPIO for testing
import time
import threading

# Initialize Pygame
pygame.init()

# Set up display
screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Key Detection Example")

# Disable warnings and cleanup at the start
GPIO.setwarnings(False)
GPIO.cleanup()

# Pin setup
LEFT_PIN = 17
RIGHT_PIN = 27
FORWARD_PIN = 14
BACKWARD_PIN = 15

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(LEFT_PIN, GPIO.OUT)
GPIO.setup(RIGHT_PIN, GPIO.OUT)
GPIO.setup(FORWARD_PIN, GPIO.OUT)
GPIO.setup(BACKWARD_PIN, GPIO.OUT)

# Initialize pins to LOW
GPIO.output(LEFT_PIN, GPIO.LOW)
GPIO.output(RIGHT_PIN, GPIO.LOW)
GPIO.output(FORWARD_PIN, GPIO.LOW)
GPIO.output(BACKWARD_PIN, GPIO.LOW)

# Shared flag
running = True
pressed_keys = set()  # Store active key presses

def update_gpio():
	"""Continuously updates GPIO states based on pressed keys."""
	global running, pressed_keys
	while running:
		if (pygame.K_s not in pressed_keys):
			GPIO.output(FORWARD_PIN, GPIO.HIGH if pygame.K_w in pressed_keys else GPIO.LOW) #forward
		if (pygame.K_w not in pressed_keys):
			GPIO.output(BACKWARD_PIN, GPIO.HIGH if pygame.K_s in pressed_keys else GPIO.LOW) #backward
		if (pygame.K_d not in pressed_keys):
			GPIO.output(LEFT_PIN, GPIO.HIGH if pygame.K_a in pressed_keys else GPIO.LOW) #left
		if (pygame.K_a not in pressed_keys):
			GPIO.output(RIGHT_PIN, GPIO.HIGH if pygame.K_d in pressed_keys else GPIO.LOW) #right
		time.sleep(0.05)  # Small delay to reduce CPU usage

def main():
	global running, pressed_keys

	# Start GPIO control thread
	gpio_thread = threading.Thread(target=update_gpio)
	gpio_thread.start()

	while running:
		pygame.time.delay(50)  # Reduce CPU usage

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
			elif event.type == pygame.KEYDOWN:
				pressed_keys.add(event.key)
			elif event.type == pygame.KEYUP:
				pressed_keys.discard(event.key)

	running = False
	gpio_thread.join()
	GPIO.cleanup()
	pygame.quit()
	print("GPIO cleaned up.")

if __name__ == "__main__":
	main()
