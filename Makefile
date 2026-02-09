SKETCH ?= $(error SKETCH not set. Usage: make compile SKETCH=./avr_asm_102/avr_asm_102.ino)
BOARD  ?= arduino:avr:uno
PORT   ?= /dev/ttyACM0
BAUD   ?= 115200

compile:
	arduino-cli compile --fqbn $(BOARD) $(SKETCH)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(BAUD)

all: compile upload monitor

.PHONY: compile upload monitor all
