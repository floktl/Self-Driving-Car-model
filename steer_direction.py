import RPi.GPIO as GPIO
import sys
import termios
import tty
import time

# Disable warnings and cleanup at the start
GPIO.setwarnings(False)
GPIO.cleanup()

# Pin setup
LEFT_PIN = 17   # GPIO pin for left
RIGHT_PIN = 27  # GPIO pin for right

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(LEFT_PIN, GPIO.OUT)
GPIO.setup(RIGHT_PIN, GPIO.OUT)

# Initialize pins to LOW
GPIO.output(LEFT_PIN, GPIO.LOW)
GPIO.output(RIGHT_PIN, GPIO.LOW)

def get_char():
	"""
	Read a single character from standard input without waiting for Enter.
	"""
	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(fd)
		char = sys.stdin.read(1)
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return char

def main():
	print("Hold 'L' to steer left, 'R' to steer right. Release to stop. Press 'Q' to quit.")

	left_pressed = False
	right_pressed = False

	try:
		while True:
			# Non-blocking character read
			char = None
			fd = sys.stdin.fileno()
			old_settings = termios.tcgetattr(fd)
			try:
				tty.setraw(fd)
				char = sys.stdin.read(1)
			except:
				pass
			finally:
				termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

			# Update key states based on the character read
			if char:
				if char.lower() == 'l':
					left_pressed = True
					right_pressed = False  # Prevent conflict
				elif char.lower() == 'r':
					right_pressed = True
					left_pressed = False  # Prevent conflict
				elif char.lower() == 'q':  # Quit program
					print("\nExiting program...")
					break
				else:
					left_pressed = False
					right_pressed = False

			# Apply states to GPIO
			if left_pressed:
				GPIO.output(LEFT_PIN, GPIO.HIGH)
				GPIO.output(RIGHT_PIN, GPIO.LOW)
				print("Steering left", end="\r")
			elif right_pressed:
				GPIO.output(LEFT_PIN, GPIO.LOW)
				GPIO.output(RIGHT_PIN, GPIO.HIGH)
				print("Steering right", end="\r")
			else:
				GPIO.output(LEFT_PIN, GPIO.LOW)
				GPIO.output(RIGHT_PIN, GPIO.LOW)

			time.sleep(0.05)  # Small delay for smooth operation
			left_pressed = False
			right_pressed = False
			print("Stopped       ", end="\r")  # Clear previous text


	except KeyboardInterrupt:
		print("\nProgram interrupted.")

	finally:
		GPIO.cleanup()
		print("GPIO cleaned up.")

if __name__ == "__main__":
	main()
