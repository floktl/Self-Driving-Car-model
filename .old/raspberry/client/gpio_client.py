# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gpio_client.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 16:45:36 by fkeitel           #+#    #+#              #
#    Updated: 2024/11/25 16:58:03 by fkeitel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------------------------------------------
#	script to receive the pin status of the raspberry pi GPIO pins using sockets
# 	with json tcp protocolls for data transmissing
# 	using tkinter graphical window management
#	usuage (on pc in the same network as rpi): python3 gpio_client.py
#-------------------------------------------------------------------------------

import socket # Module for network communication
import json
from tkinter import Tk, Frame, Label # for graphic window

# Server connection settings
HOST = "172.17.254.51"  # Replace with actual Raspberry Pi's IP address
PORT = 65432 # Must match the port number used by the server

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
root.title("Raspberry Pi GPIO States") # window title
root.geometry("600x800")  # Adjusted window size for more pins

# Frame for GPIO states
gpio_frame = Frame(root, padx=10, pady=10) # frame inside main win with padding
gpio_frame.pack(fill="both", expand=True) # widget adapting when window resized

# Dictionary to hold the labels for each pin
state_labels = {}

# Function to update GPIO states in the GUI
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
				# Loop through each GPIO pin and its details
				for pin, details in pin_states.items():
					# Extract pin mode and state
					mode = details.get("mode", "unknown") # (default to "unknown")
					state = details.get("state", "N/A") # (default to "N/A")

					# Create labels dynamically for each GPIO pin
					if pin not in state_labels: # If no label for pin, create one
						frame = Frame(
							gpio_frame, bd=1, relief="solid", padx=5, pady=5
						) # Create a bordered frame for the pin's label
						frame.pack(pady=2, fill="x")

						state_label = Label(
							frame,
							text="",  # Initialize with empty text
							width=50, # Set a fixed width
							anchor="w", # Align text to the left
							font=("Helvetica", 12),
						)
						state_label.pack(side="left", padx=5)
						state_labels[pin] = state_label
					# Retrieve the label for the current pin
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
