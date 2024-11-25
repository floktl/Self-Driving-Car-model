import RPi.GPIO as GPIO
import socket
import json
from threading import Lock

# GPIO setup
GPIO.setmode(GPIO.BCM)
ALL_GPIO_PINS = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
				17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]

# Initialize pins dynamically
monitored_pins = {}
lock = Lock()

for pin in ALL_GPIO_PINS:
	try:
		GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_OFF)
		monitored_pins[pin] = "input"
	except RuntimeError:
		monitored_pins[pin] = "unknown"

# Socket server setup
HOST = "0.0.0.0"
PORT = 65432
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("Server listening for connections...")

try:
	while True:
		conn, addr = server.accept()
		print(f"Connection from {addr}")

		# Track the last known states to detect changes
		last_states = {}

		try:
			while True:
				current_states = {}
				with lock:
					for pin in ALL_GPIO_PINS:
						mode = monitored_pins[pin]
						state = GPIO.input(pin) if mode == "input" else 0
						current_states[pin] = {"mode": mode, "state": state}

				# Check for changes
				changes = {
					pin: data
					for pin, data in current_states.items()
					if last_states.get(pin) != data
				}

				if changes:
					json_data = json.dumps(changes)
					conn.sendall((json_data + "\n").encode('utf-8'))
					last_states.update(changes)  # Update last known states

		except (BrokenPipeError, ConnectionResetError):
			print("Connection closed")
			conn.close()
except KeyboardInterrupt:
	print("Exiting...")
finally:
	GPIO.cleanup()
	server.close()

