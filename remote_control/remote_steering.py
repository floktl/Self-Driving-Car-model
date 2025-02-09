# script for steering the car remotly, data needs to transmitted wirelessly

from mock_gpio_library import GPIO  # Mock GPIO for testing
#import RPi.GPIO as GPIO  #Real GPIO lybrary
import pygame
import time
import threading
import sys
import signal
import termios

fd = sys.stdin.fileno()
old_settings = termios.tcgetattr(fd)

# Initialize Pygame
pygame.init()

# Set up display
WIDTH, HEIGHT = 500, 500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Car Remote Data")

# Colors
WHITE = (255, 255, 255)
GRAY = (200, 200, 200)
BLUE = (0, 0, 255)

# Button positions
button_positions = {
	pygame.K_w: (200, 150, 100, 50),  # Up
	pygame.K_s: (200, 250, 100, 50),  # Down
	pygame.K_a: (100, 250, 100, 50),  # Left
	pygame.K_d: (300, 250, 100, 50)   # Right
}

# GPIO Setup
GPIO.setwarnings(False)
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)
LEFT_PIN, RIGHT_PIN, FORWARD_PIN, BACKWARD_PIN = 17, 27, 14, 15
GPIO.setup([LEFT_PIN, RIGHT_PIN, FORWARD_PIN, BACKWARD_PIN], GPIO.OUT)
GPIO.output([LEFT_PIN, RIGHT_PIN, FORWARD_PIN, BACKWARD_PIN], GPIO.LOW)

# Shared variables
running = True
pressed_keys = set()

def update_gpio():
	"""Continuously updates GPIO states based on pressed keys."""
	global running, pressed_keys
	while running:
		GPIO.output(FORWARD_PIN, GPIO.HIGH if pygame.K_w in pressed_keys and pygame.K_s not in pressed_keys else GPIO.LOW)
		GPIO.output(BACKWARD_PIN, GPIO.HIGH if pygame.K_s in pressed_keys and pygame.K_w not in pressed_keys else GPIO.LOW)
		GPIO.output(LEFT_PIN, GPIO.HIGH if pygame.K_a in pressed_keys and pygame.K_d not in pressed_keys else GPIO.LOW)
		GPIO.output(RIGHT_PIN, GPIO.HIGH if pygame.K_d in pressed_keys and pygame.K_a not in pressed_keys else GPIO.LOW)
		time.sleep(0.05)

def draw_buttons():
	"""Draws arrow buttons on the screen, changing color when pressed."""
	screen.fill(WHITE)
	for key, (x, y, w, h) in button_positions.items():
		if (key in [pygame.K_w, pygame.K_s] and pygame.K_w in pressed_keys and pygame.K_s in pressed_keys) or \
		(key in [pygame.K_a, pygame.K_d] and pygame.K_a in pressed_keys and pygame.K_d in pressed_keys):
			color = GRAY
		else:
			color = BLUE if key in pressed_keys else GRAY
		pygame.draw.rect(screen, color, (x, y, w, h))
		pygame.draw.rect(screen, (0, 0, 0), (x, y, w, h), 2)  # Border
	pygame.display.flip()

def handle_exit():
	"""Cleans up and exits the program."""
	global running
	running = False
	GPIO.cleanup()
	pygame.quit()
	print("GPIO cleaned up. Exiting...")
	termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)  # Restore settings
	sys.exit(0)

def signal_handler(sig, frame):
	"""Handles Ctrl+C signal."""
	print("\nCtrl+C detected, exiting gracefully...")
	handle_exit()

signal.signal(signal.SIGINT, signal_handler)

def main():
	global running, pressed_keys

	gpio_thread = threading.Thread(target=update_gpio)
	gpio_thread.start()

	while running:
		pygame.time.delay(50)
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				handle_exit()
			elif event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:  # Exit on ESC key
					print("\nESC key detected, exiting gracefully...")
					handle_exit()
				pressed_keys.add(event.key)
			elif event.type == pygame.KEYUP:
				pressed_keys.discard(event.key)
		draw_buttons()

	gpio_thread.join()

if __name__ == "__main__":
	main()
