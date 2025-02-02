import time
import sys
import threading
import termios
import tty
import signal
import pygame

class MockGPIO:
	BCM = "BCM"
	OUT = "OUT"
	HIGH = 1
	LOW = 0

	def __init__(self):
		self.pins = {17: self.LOW, 14: self.LOW, 15: self.LOW, 27: self.LOW}
		self.warnings_disabled = False

	def setwarnings(self, state):
		self.warnings_disabled = state
		self._update_display()

	def cleanup(self):
		self.pins = {17: self.LOW, 14: self.LOW, 15: self.LOW, 27: self.LOW}
		self._update_display()

	def setmode(self, mode):
		if mode != self.BCM:
			print("[MOCK GPIO] Invalid mode")

	def setup(self, pin, mode):
		if isinstance(pin, list):  # Allow handling multiple pins
			for p in pin:
				if p in self.pins:
					self.pins[p] = self.LOW
		else:
			if pin in self.pins:
				self.pins[pin] = self.LOW
		self._update_display()

	def output(self, pin, state):
		if isinstance(pin, list):
			for p in pin:
				if p in self.pins:
					self.pins[p] = state
		else:
			if pin in self.pins:
				self.pins[pin] = state
		self._update_display()

	def input(self, pin):
		return self.pins.get(pin, self.LOW)

	def _update_display(self):
		state_str = " | ".join([f"Pin {pin}: {'HIGH' if state == self.HIGH else 'LOW'}" for pin, state in self.pins.items()])
		sys.stdout.write(f"\r{state_str.ljust(80)}")
		sys.stdout.flush()

GPIO = MockGPIO()

running = True
pressed_keys = set()
FORWARD_PIN = 17
BACKWARD_PIN = 14
LEFT_PIN = 15
RIGHT_PIN = 27

def update_gpio():
	"""Continuously updates GPIO states based on pressed keys."""
	global running, pressed_keys
	while running:
		GPIO.output(FORWARD_PIN, GPIO.HIGH if pygame.K_w in pressed_keys and pygame.K_s not in pressed_keys else GPIO.LOW)
		GPIO.output(BACKWARD_PIN, GPIO.HIGH if pygame.K_s in pressed_keys and pygame.K_w not in pressed_keys else GPIO.LOW)
		GPIO.output(LEFT_PIN, GPIO.HIGH if pygame.K_a in pressed_keys and pygame.K_d not in pressed_keys else GPIO.LOW)
		GPIO.output(RIGHT_PIN, GPIO.HIGH if pygame.K_d in pressed_keys and pygame.K_a not in pressed_keys else GPIO.LOW)
		time.sleep(0.05)

def draw_buttons():
	"""Draws arrow buttons on the screen, changing color when pressed."""
	screen.fill(WHITE)
	for key, (x, y, w, h) in button_positions.items():
		if (key in [pygame.K_w, pygame.K_s] and pygame.K_w in pressed_keys and pygame.K_s in pressed_keys) or \
		(key in [pygame.K_a, pygame.K_d] and pygame.K_a in pressed_keys and pygame.K_d in pressed_keys):
			color = GRAY
		else:
			color = BLUE if key in pressed_keys else GRAY
		pygame.draw.rect(screen, color, (x, y, w, h))
		pygame.draw.rect(screen, (0, 0, 0), (x, y, w, h), 2)  # Border
	pygame.display.flip()

# Function to read a single key press
def get_key():
	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(fd)
		key = sys.stdin.read(1)
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return key

def start_display(interval=0.1):
	try:
		while True:
			GPIO._update_display()
			time.sleep(interval)
	except KeyboardInterrupt:
		reset_terminal()
		print("\nExiting gracefully...")
		sys.exit(0)

def reset_terminal():
	sys.stdout.write("\033[?25h")  # Show cursor again
	sys.stdout.flush()

# Signal handler for Ctrl+C
def signal_handler(sig, frame):
	reset_terminal()
	print("\nExiting on Ctrl+C...")
	sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def listen_for_exit():
	while True:
		key = get_key()
		if key == "\x1b":  # ESC key
			reset_terminal()
			print("\nExiting on ESC...")
			sys.exit(0)

display_thread = threading.Thread(target=start_display, daemon=True)
display_thread.start()

exit_thread = threading.Thread(target=listen_for_exit, daemon=True)
exit_thread.start()

sys.stdout.write("\033[?25l")  # Hide cursor
sys.stdout.flush()

while True:
	time.sleep(1)  # Keep the script running
q
