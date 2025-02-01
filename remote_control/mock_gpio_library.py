import time
import sys
import threading

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
        if pin in self.pins:
            self.pins[pin] = self.LOW
        self._update_display()

    def output(self, pin, state):
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
    while True:
        GPIO._update_display()
        time.sleep(interval)

display_thread = threading.Thread(target=start_display, daemon=True)
display_thread.start()
