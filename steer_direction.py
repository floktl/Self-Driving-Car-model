import RPi.GPIO as GPIO
import time
import curses

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

def main(stdscr):
	curses.cbreak()
	stdscr.keypad(True)
	stdscr.clear()
	stdscr.addstr("Press 'L' to turn left, 'R' to turn right, 'Q' to quit.\n")

	try:
		while True:
			key = stdscr.getch()

			if key in [ord('l'), ord('L')]:  # Turn left
				GPIO.output(LEFT_PIN, GPIO.HIGH)
				GPIO.output(RIGHT_PIN, GPIO.LOW)
				stdscr.addstr("Turning left\n")

			elif key in [ord('r'), ord('R')]:  # Turn right
				GPIO.output(LEFT_PIN, GPIO.LOW)
				GPIO.output(RIGHT_PIN, GPIO.HIGH)
				stdscr.addstr("Turning right\n")

			elif key in [ord('q'), ord('Q')]:  # Quit program
				stdscr.addstr("Exiting program...\n")
				break

			else:
				# Set both pins to LOW if no key is pressed
				GPIO.output(LEFT_PIN, GPIO.LOW)
				GPIO.output(RIGHT_PIN, GPIO.LOW)

	finally:
		GPIO.cleanup()
		curses.endwin()

if __name__ == "__main__":
	curses.wrapper(main)
