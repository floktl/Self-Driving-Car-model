# import RPi.GPIO as GPIO
from mock_gpio_library import GPIO  # Assuming this is saved as mock_gpio_library.py
import sys
import termios
import tty
import time
import select
import threading

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

fd = sys.stdin.fileno()
old_settings = termios.tcgetattr(fd)

# Shared flags
left_pressed = False
right_pressed = False
forward_pressed = False
backward_pressed = False
running = True


def get_char_non_blocking():
    """Reads a single character from standard input without blocking."""
    fd = sys.stdin.fileno()
    tty.setraw(fd)
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)  # Non-blocking with timeout
    if rlist:
        return sys.stdin.read(1)
    return None


def movement_control():
    """Thread to control forward/backward movement independently."""
    global forward_pressed, backward_pressed, running

    while running:
        if forward_pressed:
            GPIO.output(FORWARD_PIN, GPIO.HIGH)
            GPIO.output(BACKWARD_PIN, GPIO.LOW)
        elif backward_pressed:
            GPIO.output(FORWARD_PIN, GPIO.LOW)
            GPIO.output(BACKWARD_PIN, GPIO.HIGH)
        else:
            GPIO.output(FORWARD_PIN, GPIO.LOW)
            GPIO.output(BACKWARD_PIN, GPIO.LOW)

        # Print status when pins are set LOW
        if GPIO.input(FORWARD_PIN) == GPIO.LOW:
            print("Forward pin: LOW")
        if GPIO.input(BACKWARD_PIN) == GPIO.LOW:
            print("Backward pin: LOW")

        time.sleep(0.1)


def steering_control():
    """Thread to control left/right steering independently."""
    global left_pressed, right_pressed, running

    while running:
        if left_pressed:
            GPIO.output(LEFT_PIN, GPIO.HIGH)
            GPIO.output(RIGHT_PIN, GPIO.LOW)
        elif right_pressed:
            GPIO.output(LEFT_PIN, GPIO.LOW)
            GPIO.output(RIGHT_PIN, GPIO.HIGH)
        else:
            GPIO.output(LEFT_PIN, GPIO.LOW)
            GPIO.output(RIGHT_PIN, GPIO.LOW)

        # Print status when pins are set LOW
        if GPIO.input(LEFT_PIN) == GPIO.LOW:
            print("Left pin: LOW")
        if GPIO.input(RIGHT_PIN) == GPIO.LOW:
            print("Right pin: LOW")

        time.sleep(0.1)


def main():
    global left_pressed, right_pressed, forward_pressed, backward_pressed, running

    print("Hold 'L' to steer left, 'R' to steer right, 'W' to move forward, 'S' to move backward.")
    print("Press 'Q' to quit.")

    # Start movement and steering control threads
    movement_thread = threading.Thread(target=movement_control)
    steering_thread = threading.Thread(target=steering_control)

    movement_thread.start()
    steering_thread.start()

    try:
        while running:
            char = get_char_non_blocking()

            if char:
                char = char.lower()

                if char == 'q':  # Quit program
                    print("\nExiting program...")
                    running = False
                    break

                # Movement controls
                elif char == 'l':
                    right_pressed = False
                    left_pressed = True
                elif char == 'r':
                    left_pressed = False
                    right_pressed = True
                elif char == 'w':
                    backward_pressed = False
                    forward_pressed = True
                elif char == 's':
                    forward_pressed = False
                    backward_pressed = True
                elif char in [' ', 'x']:  # Stop all movements
                    left_pressed = False
                    right_pressed = False
                    forward_pressed = False
                    backward_pressed = False

    except KeyboardInterrupt:
        print("\nProgram interrupted.")

    finally:
        running = False  # Ensure threads exit gracefully
        movement_thread.join()
        steering_thread.join()
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        GPIO.cleanup()
        print("GPIO cleaned up.")


if __name__ == "__main__":
    main()
