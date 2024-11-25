import socket
import json
from tkinter import Tk, Frame, Label

# Server connection settings
HOST = "172.17.254.51"  # Replace with your Raspberry Pi's IP address
PORT = 65432

# Connect to the Raspberry Pi server
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

# GUI setup
root = Tk()
root.title("Raspberry Pi GPIO States")
root.geometry("600x800")  # Adjusted window size for more pins

# Frame for GPIO states
gpio_frame = Frame(root, padx=10, pady=10)
gpio_frame.pack(fill="both", expand=True)

# Dictionary to hold the labels for each pin
state_labels = {}

def update_states():
	try:
		# Receive data from the server
		data = client.recv(4096).decode('utf-8')  # Increased buffer size for large JSON
		messages = data.strip().split("\n")  # Split by newline to handle multiple JSON objects

		for message in messages:
			try:
				pin_states = json.loads(message)  # Parse each JSON message
				for pin, details in pin_states.items():
					mode = details.get("mode", "unknown")  # Pin mode (input/output)
					state = details.get("state", 0)        # Pin state (HIGH/LOW)

					# Create labels dynamically for each GPIO pin
					if pin not in state_labels:
						frame = Frame(gpio_frame, bd=1, relief="solid", padx=5, pady=5)
						frame.pack(pady=2, fill="x")

						state_label = Label(frame, text="", width=50, anchor="w", font=("Helvetica", 12))
						state_label.pack(side="left", padx=5)

						state_labels[pin] = state_label

					state_label = state_labels[pin]

					# Update label text and color based on mode and state
					if state:
						state_label.config(
							text=f"{pin} ({mode.upper()}): ON",
							fg="#228B22",  # Dim green for ON
							bg="black"
						)
					else:
						state_label.config(
							text=f"{pin} ({mode.upper()}): OFF",
							fg="#8B0000",  # Dim red for OFF
							bg="black"
						)
			except json.JSONDecodeError as e:
				print(f"Malformed JSON received: {e}")
		root.after(1000, update_states)  # Refresh every second
	except Exception as e:
		print(f"Error: {e}")
		client.close()
		root.destroy()

# Start updating the GUI
update_states()
root.mainloop()
