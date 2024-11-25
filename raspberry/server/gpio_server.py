import RPi.GPIO as GPIO
import socket
import json
import time
from threading import Lock

# GPIO setup
GPIO.setmode(GPIO.BCM)
ALL_GPIO_PINS = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]

# Dictionary to store pin modes (default to "unknown")
monitored_pins = {pin: "unknown" for pin in ALL_GPIO_PINS}
lock = Lock()

# Check pin modes (input/output/unknown) without altering configuration
def detect_pin_modes():
    with lock:
        for pin in ALL_GPIO_PINS:
            try:
                # Try reading the pin state without changing it
                GPIO.setup(pin, GPIO.IN) 	# Temporarily set as input
                GPIO.setup(pin, GPIO.OUT) 	# Temporarily set as output
                GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_OFF)  # Reset
                monitored_pins[pin] = "input"
            except RuntimeError:
                # If the pin is already configured as output, mark it as "output".
                monitored_pins[pin] = "output"
            except Exception:
                # If an error occurs, mark the pin's mode as "unknown".
                monitored_pins[pin] = "unknown"

# Set up the server socket for communication.
HOST = "0.0.0.0"  # Listen on all available network interfaces.
PORT = 65432  # Port number for the server to listen on.
# socket.AF_INET: Specifies the socket will use the IPv4 protocol for communication.
# socket.SOCK_STREAM: Indicates that the socket will use TCP (Transmission Control Protocol)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket.
server.bind((HOST, PORT))  # Bind the socket to the specified host and port.
server.listen(1)  # Start listening for incoming connections, allowing one client at a time.

print("Server listening for connections...")
#Server is now set up and waiting for connections

try:
    while True:  # Main loop to accept and handle client connections.
        conn, addr = server.accept()  # Wait for a client to connect.
        print(f"Connection from {addr}")  # Log the client's address.

        try:
            while True:  # Handle communication with the connected client.
                detect_pin_modes()  # Detect the current mode of each pin.

                # Collect the state and mode of all pins dynamically.
                with lock:  # Ensure thread-safe access to `monitored_pins`.
                    pin_states = {
                        f"GPIO {pin}": { # f-string syntax, {pin} dynamically inserts value of pin.
                            "mode": monitored_pins[pin],  # Retrieve the mode of the pin.
                            "state": GPIO.input(pin) if monitored_pins[pin] in ("input", "output") else "N/A"  # Get the state of pin
                        }
                        for pin in ALL_GPIO_PINS  # Process all pins.
                    }

                # Serialize the pin states as JSON data.
                json_data = json.dumps(pin_states)
                # Send the serialized data to the client, appending a newline as a delimiter.
                conn.sendall((json_data + "\n").encode('utf-8'))
                time.sleep(0.1)  # Wait for a short interval to simulate real-time updates.
        except (BrokenPipeError, ConnectionResetError):
            # Handle cases where the client disconnects unexpectedly.
            print("Connection closed")
            conn.close()  # Close the client connection.
except KeyboardInterrupt:
    # Gracefully handle a keyboard interrupt (Ctrl+C).
    print("Exiting...")
finally:
    # Perform cleanup when the program exits.
    GPIO.cleanup()  # Reset GPIO pins to their default state.
    server.close()  # Close the server socket.

#Example JSON Output
#{
#  "GPIO 2": {
#    "mode": "input",
#    "state": 1
#  },
#  "GPIO 3": {
#    "mode": "unknown",
#    "state": "N/A"
#  },
#  "GPIO 4": {
#    "mode": "output",
#    "state": "N/A"
#  }
#}
