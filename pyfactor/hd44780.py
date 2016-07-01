import RPi.GPIO as GPIO
from time import sleep

class HD44780:
	def __init__(self, pin_rs=7, pin_e=8, pins_db=[25,24,23,18]):
		GPIO.setwarnings(False)
		self.pin_rs = pin_rs
		self.pin_e = pin_e
		self.pins_db = pins_db

		GPIO.setmode(GPIO.BCM)
		GPIO.setup(self.pin_e, GPIO.OUT)
		GPIO.setup(self.pin_rs, GPIO.OUT)
		for pin in self.pins_db:
			GPIO.setup(pin, GPIO.OUT)


		self.clear()

	def clear(self):
		self.cmd(0x33)
		self.cmd(0x32)
		self.cmd(0x28)
		self.cmd(0x0c)
		self.cmd(0x06)
		self.cmd(0x01)

	def cmd(self, bits, char_mode=False):
		sleep(0.001)
		bits=bin(bits)[2:].zfill(8)

		GPIO.output(self.pin_rs, char_mode)

		for pin in self.pins_db:
			GPIO.output(pin, False)

		for i in range(4):
			if bits[i] == "1":
				GPIO.output(self.pins_db[::-1][i], True)

		GPIO.output(self.pin_e, True)
		GPIO.output(self.pin_e, False)

		for pin in self.pins_db:
			GPIO.output(pin, False)

		for i in range(4,8):
			if bits[i] == "1":
				GPIO.output(self.pins_db[::-1][i-4], True)

		GPIO.output(self.pin_e, True)
		GPIO.output(self.pin_e, False)

	def message(self, text):
		for char in text:
			if char == "\n":
				self.cmd(0xc0)
			else:
				self.cmd(ord(char), True)

