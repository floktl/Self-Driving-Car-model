import RPi.GPIO as GPIO
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
running = True
pressed_keys = set()  # Store active key presses


def get_char_non_blocking():
    """Reads a single character from standard input without blocking."""
    fd = sys.stdin.fileno()
    tty.setraw(fd)
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)  # 0.1s timeout
    if rlist:
        return sys.stdin.read(1).lower()  # Convert to lowercase
    return None


def update_gpio():
    """Continuously updates GPIO states based on pressed keys and prints messages."""
    global running

    last_state = {'w': False, 's': False, 'l': False, 'r': False}  # Track previous state

    while running:
        # Determine new states
        new_state = {
            'w': 'w' in pressed_keys,
            's': 's' in pressed_keys,
            'l': 'l' in pressed_keys,
            'r': 'r' in pressed_keys
        }

        # Update GPIO outputs
        GPIO.output(FORWARD_PIN, GPIO.HIGH if new_state['w'] else GPIO.LOW)
        GPIO.output(BACKWARD_PIN, GPIO.HIGH if new_state['s'] else GPIO.LOW)
        GPIO.output(LEFT_PIN, GPIO.HIGH if new_state['l'] else GPIO.LOW)
        GPIO.output(RIGHT_PIN, GPIO.HIGH if new_state['r'] else GPIO.LOW)

        # Print only when there is a change in state
        for key in new_state:
            if new_state[key] != last_state[key]:  # Detect change
                if new_state[key]:
                    print(f"{key.upper()} key pressed → {get_pin_name(key)} HIGH")
                else:
                    print(f"{key.upper()} key released → {get_pin_name(key)} LOW")

        # Save current state for next iteration
        last_state = new_state.copy()

        time.sleep(0.05)  # Small delay to reduce CPU usage


def get_pin_name(key):
    """Returns the corresponding pin name for a given key."""
    return {
        'w': "FORWARD_PIN",
        's': "BACKWARD_PIN",
        'l': "LEFT_PIN",
        'r': "RIGHT_PIN"
    }.get(key, "UNKNOWN")


def main():
    global running, pressed_keys

    print("Hold 'L' to steer left, 'R' to steer right, 'W' to move forward, 'S' to move backward.")
    print("Press 'Q' to quit.")

    # Start GPIO control thread
    gpio_thread = threading.Thread(target=update_gpio)
    gpio_thread.start()

    try:
        while running:
            char = get_char_non_blocking()

            if char:
                if char == 'q':  # Quit program
                    print("\nExiting program...")
                    running = False
                    break

                elif char in ['w', 's', 'l', 'r']:  # Movement keys
                    pressed_keys.add(char)  # Mark key as pressed

                elif char in [' ', 'x']:  # Stop all movement
                    pressed_keys.clear()  # Clear all keys (stops movement)

            # Detect key releases (keys that are no longer being pressed)
            rlist, _, _ = select.select([sys.stdin], [], [], 0.05)
            if not rlist:  # If no input, clear pressed_keys
                pressed_keys.clear()

    except KeyboardInterrupt:
        print("\nProgram interrupted.")

    finally:
        running = False
        gpio_thread.join()
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        GPIO.cleanup()
        print("GPIO cleaned up.")


if __name__ == "__main__":
    main()
