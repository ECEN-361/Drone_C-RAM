import RPi.GPIO as GPIO
import time
import sys
import termios
import tty

# ======== CONFIG ========
# Motor 1 (left)
PUL1 = 17
DIR1 = 27
# Motor 2 (right)
PUL2 = 22
DIR2 = 23

STEP_DELAY = 0.001  # seconds between pulses (lower = faster)
STEP_COUNT = 50     # steps per key press

# ======== SETUP ========
GPIO.setmode(GPIO.BCM)
for pin in [PUL1, DIR1, PUL2, DIR2]:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.HIGH)  # inactive

# ======== HELPER FUNCTIONS ========
def step_motor(pul, dir_pin, direction=True, steps=STEP_COUNT):
    GPIO.output(dir_pin, GPIO.LOW if direction else GPIO.HIGH)
    for _ in range(steps):
        GPIO.output(pul, GPIO.LOW)
        time.sleep(STEP_DELAY)
        GPIO.output(pul, GPIO.HIGH)
        time.sleep(STEP_DELAY)

def get_key():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        ch = sys.stdin.read(3)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def move_forward():
    step_motor(PUL1, DIR1, True)
    step_motor(PUL2, DIR2, True)

def move_backward():
    step_motor(PUL1, DIR1, False)
    step_motor(PUL2, DIR2, False)

def turn_left():
    step_motor(PUL1, DIR1, False)
    step_motor(PUL2, DIR2, True)

def turn_right():
    step_motor(PUL1, DIR1, True)
    step_motor(PUL2, DIR2, False)

# ======== MAIN LOOP ========
print("Use arrow keys to move steppers. Press 'q' to quit.")
try:
    while True:
        key = get_key()
        if key == '\x1b[A':      # Up arrow
            print("Forward")
            move_forward()
        elif key == '\x1b[B':    # Down arrow
            print("Backward")
            move_backward()
        elif key == '\x1b[D':    # Left arrow
            print("Turn Left")
            turn_left()
        elif key == '\x1b[C':    # Right arrow
            print("Turn Right")
            turn_right()
        elif key == 'q':
            print("Quitting...")
            break
        else:
            print("Unknown key:", repr(key))
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
    print("GPIO released. Exiting.")
