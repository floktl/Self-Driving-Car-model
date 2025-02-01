import sys
import time
import select
import threading

try:
    import RPi.GPIO as GPIO
except ModuleNotFoundError:
    import fake_rpi.RPi.GPIO as GPIO  # Use fake GPIO on non-RPi devices

# Handle cross-platform input
try:
    import termios
    import tty
    unix_platform = True
except ImportError:
    import msvcrt  # Windows alternative
    unix_platform = False

# Mock GPIO output function for testing on a laptop
def mock_gpio_output(pin, state):
    print(f"GPIO Pin {pin} set to {'HIGH' if state else 'LOW'}")

GPIO.output = mock_gpio_output  # Override GPIO output with mock function

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

if unix_platform:
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)

# Shared flags for movement control
left_pressed = False
right_pressed = False
forward_pressed = False
backward_pressed = False
running = True  # To control thread execution

def get_char_non_blocking():
    if unix_platform:
        fd = sys.stdin.fileno()
        tty.setraw(fd)
        rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
        if rlist:
            char = sys.stdin.read(1)
            sys.stdin.flush()
            return char
    else:
        if msvcrt.kbhit():
            return msvcrt.getch().decode('utf-8')
    return None

def movement_control():
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
        time.sleep(0.1)

def steering_control():
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
        time.sleep(0.1)

def main():
    global left_pressed, right_pressed, forward_pressed, backward_pressed, running

    print("Hold 'L' to steer left, 'R' to steer right, 'W' to move forward, 'S' to move backward.")
    print("Press 'Q' to quit.")

    movement_thread = threading.Thread(target=movement_control)
    steering_thread = threading.Thread(target=steering_control)
    movement_thread.start()
    steering_thread.start()

    try:
        while True:
            char = get_char_non_blocking()
            if char:
                if char.lower() == 'q':
                    print("\nExiting program...")
                    running = False
                    break
                if char.lower() == 'l' or char.lower() == 'a':
                    right_pressed = False
                    left_pressed = True
                elif char.lower() == 'r' or char.lower() == 'd':
                    left_pressed = False
                    right_pressed = True
                elif char.lower() == 'w':
                    backward_pressed = False
                    forward_pressed = True
                elif char.lower() == 's':
                    forward_pressed = False
                    backward_pressed = True
                elif char.lower() in [' ', 'x']:
                    left_pressed = False
                    right_pressed = False
                    forward_pressed = False
                    backward_pressed = False
    except KeyboardInterrupt:
        print("\nProgram interrupted.")
    finally:
        running = False
        movement_thread.join()
        steering_thread.join()
        if unix_platform:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        print("GPIO cleanup simulated.")

if __name__ == "__main__":
    main()