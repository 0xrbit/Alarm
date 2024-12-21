compile:
	arduino-cli compile -v

upload:
	arduino-cli upload . --fqbn arduino:avr:uno --port /dev/ttyUSB0 -v

connect-serial:
	screen /dev/ttyUSB0 115200
