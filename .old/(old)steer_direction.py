# this raspberry script reads the keys from the remote keyboard via ssh
# (old version, in build)

import RPi.GPIO as GPIO # type: ignore
import sys
import termios
import tty
import time
import select

# Disable warnings and cleanup at the start
GPIO.setwarnings(False)
GPIO.cleanup()

# Pin setup
LEFT_PIN = 17   # GPIO pin for left
RIGHT_PIN = 27  # GPIO pin for right
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

fd = sys.stdin.fileno()
old_settings = termios.tcgetattr(fd)

# function to read a key fromn the keyboard input
def get_char_non_blocking():
    """
    Reads a single character from standard input without blocking.
    Uses select to check if input is available.
    """
    fd = sys.stdin.fileno()
    #old_settings = termios.tcgetattr(fd)
    tty.setraw(fd)
    rlist, _, _ = select.select([sys.stdin], [], [], 0.2)  # Non-blocking with short timeout
    if rlist:
        char = sys.stdin.read(1)
        sys.stdin.flush()
        return char
    sys.stdin.flush()
    return None


def main():
    print("Hold 'L' to steer left, 'R' to steer right. Release to stop. Press 'Q' to quit.")

    left_pressed = False
    right_pressed = False
    forward_pressed = False
    backward_pressed = False
    try:
        while True:
            left_pressed = False
            right_pressed = False
            forward_pressed = False
            backward_pressed = False

            char = None
            char = get_char_non_blocking()

            # Update key states based on the character read
            if char:
                if char.lower() == 'q':  # Quit program
                    print("\nExiting program...")
                    break
                if char.lower() == 'l' or char.lower() == 'a':
                    right_pressed = False  # Prevent conflict
                    left_pressed = True
                elif char.lower() == 'r' or char.lower() == 'd':
                    left_pressed = False  # Prevent conflict
                    right_pressed = True
                if char.lower() == 'w':
                    backward_pressed = False  # Prevent conflict
                    forward_pressed = True
                elif char.lower() == 's':
                    forward_pressed = False
                    backward_pressed = True  # Prevent conflict

            GPIO.output(LEFT_PIN, GPIO.LOW)
            GPIO.output(RIGHT_PIN, GPIO.LOW)
            GPIO.output(FORWARD_PIN, GPIO.LOW)
            GPIO.output(BACKWARD_PIN, GPIO.LOW)
            # Apply states to GPIO
            if left_pressed:
                GPIO.output(LEFT_PIN, GPIO.HIGH)
                GPIO.output(RIGHT_PIN, GPIO.LOW)
                #print("Steering left      ")
            elif right_pressed:
                GPIO.output(LEFT_PIN, GPIO.LOW)
                GPIO.output(RIGHT_PIN, GPIO.HIGH)
                #print("Steering right     ")

            if forward_pressed:
                GPIO.output(FORWARD_PIN, GPIO.HIGH)
                GPIO.output(BACKWARD_PIN, GPIO.LOW)
                #print("Steering left      ")
            elif backward_pressed:
                GPIO.output(FORWARD_PIN, GPIO.LOW)
                GPIO.output(BACKWARD_PIN, GPIO.HIGH)
                #print("Steering right     ")

    except KeyboardInterrupt:
        print("\nProgram interrupted.")

    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        GPIO.cleanup()
        print("GPIO cleaned up.")

if __name__ == "__main__":
    main()
