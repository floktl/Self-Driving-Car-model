import time
import sys
import threading
import signal

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

def start_display(interval=0.1):
	try:
		while True:
			GPIO._update_display()
			time.sleep(interval)
	except KeyboardInterrupt:
		print("\nExiting on Ctrl+C...")
		GPIO.cleanup()
		sys.exit(0)

def signal_handler(sig, frame):
	print("\nExiting on Ctrl+C...")
	GPIO.cleanup()
	sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

display_thread = threading.Thread(target=start_display, daemon=True)
display_thread.start()
