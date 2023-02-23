# definitions
SRCS := $(wildcard test*.cpp)
TESTS := $(patsubst %.cpp,%,$(SRCS))
LIBS := $(wildcard lib*.cpp)
HDRS := $(wildcard *.hpp)
TOOLS := screen cu

# definitions
GXX := avr-g++
GCCFLAGS := -Wall -g -O3 -mmcu=atmega328 -DF_CPU=16000000UL #-fpermissive


# select the first arduino connected to the computer by serial id
$(eval serialid=$(shell find /dev/serial/by-id/ -name "*Arduino*" | head -1))


# help
help:
	@echo "USAGE: make one of the following recipies"
	@echo "\nC++ programs:"
	@echo $(TESTS) | tr " " "\n" 
	@echo "\nTools:"
	@echo $(TOOLS) | tr " " "\n" 
	

# connect to serial port using screen
screen:
	@echo "opening serial port with baud rate 9600"
	@screen -S serialmonitor $(serialid) 9600
	@screen -S serialmonitor -X "quit"
	@ echo "closed serial port"
	

# connect to serial port using cu
cu:
	@echo "opening serial port with baud rate 9600"
	@cu -l $(serialid) -s 9600
	@ echo "closed serial port"


# C: compiling and flashing
%: %.cpp $(LIBS) $(HDRS)
	@echo "COMPILING..."
	$(GXX) $(GCCFLAGS) $@.cpp $(LIBS) -o $@.bin
	@echo "\n\n\nCONVERTING TO HEX..."
	avr-objcopy -j .text -j .data -O ihex $@.bin $@.hex
	@echo "\n\n\nFLASHING..."
	avrdude -v -p m328p -c arduino -P $(serialid) -D -U flash:w:$@.hex
	@echo "\n\n\nALL STEPS SUCCEDED!"


# clean
clean:
	rm -rf *.hex
	rm -rf *.bin
