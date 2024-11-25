
#-------------------------------------------------------------------------------
# script to receive the pin status of the raspberry pi GPIO pins using sockets
#  with json tcp protocolls for data transmissing
# using tkinter graphical window management
#-------------------------------------------------------------------------------

import socket
import json
from tkinter import Tk, Frame, Label # for graphic window

# Server connection settings
HOST = "172.17.254.51"  # Replace with your Raspberry Pi's IP address
PORT = 65432 # same port  as in the server

# Connect to the Raspberry Pi server (IPv4 and TCP protocoll)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# When connect() is called, the client initiates a TCP handshake with server:
#
# Step 1 (SYN): The client sends a synchronization (SYN) request to the server,
# 	indicating that it wants to establish a connection.
# Step 2 (SYN-ACK): The server acknowledges the request with a SYN-ACK
# 	(synchronization acknowledgment) response.
# Step 3 (ACK): The client sends an acknowledgment (ACK) back to the server,
# 	completing the handshake.
try:
    client.connect((HOST, PORT))
    print(f"Connected to the server at {HOST}:{PORT}")
except Exception as e:
    print(f"Failed to connect to the server: {e}")
    exit(1)

# GUI setup
root = Tk() # init tkinter
root.title("Raspberry Pi GPIO States")
root.geometry("600x800")  # Adjusted window size for more pins

# Frame for GPIO states
gpio_frame = Frame(root, padx=10, pady=10)
gpio_frame.pack(fill="both", expand=True) # widget adapting when window resized

# Dictionary to hold the labels for each pin
state_labels = {}

def update_states():
	try:
		# Buffer to handle potential large JSON messages
		buffer = ""
		chunk = client.recv(4096).decode('utf-8')  # Receive data from server
		if not chunk:
			raise ConnectionResetError("Server closed the connection.")
		buffer += chunk

		# Process complete JSON messages
		while "\n" in buffer:
			message, buffer = buffer.split("\n", 1)
			try:
				pin_states = json.loads(message)  # Parse the JSON message
				for pin, details in pin_states.items():
					# Extract pin mode and state
					mode = details.get("mode", "unknown")
					state = details.get("state", "N/A")

					# Create labels dynamically for each GPIO pin
					if pin not in state_labels:
						frame = Frame(
							gpio_frame, bd=1, relief="solid", padx=5, pady=5
						)
						frame.pack(pady=2, fill="x")

						state_label = Label(
							frame,
							text="",
							width=50,
							anchor="w",
							font=("Helvetica", 12),
						)
						state_label.pack(side="left", padx=5)
						state_labels[pin] = state_label
					state_label = state_labels[pin]

					# Update label text and color based on mode and state
					if mode == "unknown":
						state_label.config(
							text=f"{pin} (UNKNOWN): N/A",
							fg="#FFA500",  # Orange for unknown
							bg="black",
						)
					elif state == 1:
						state_label.config(
							text=f"{pin} ({mode.upper()}): ON",
							fg="#228B22",  # Dim green for ON
							bg="black",
						)
					else:
						state_label.config(
							text=f"{pin} ({mode.upper()}): OFF",
							fg="#8B0000",  # Dim red for OFF
							bg="black",
						)
			except json.JSONDecodeError as e:
				print(f"Malformed JSON received: {e}")

		# Schedule the next update
		root.after(100, update_states)  # Refresh every 100 ms
	except Exception as e:
		print(f"Error: {e}")
		client.close()
		root.destroy()

# Start updating the GUI
update_states()
root.mainloop()
