# definitions
SRCS = main test_extram
OBJS = usart.cpp poisson.cpp extram.cpp
HDRS = usart.hpp poisson.hpp extram.hpp

GXX = avr-g++
GCCFLAGS = -Wall -g -Os -mmcu=atmega328 -DF_CPU=16000000UL


# select the first arduino connected to the computer by serial id
$(eval serialid=$(shell find /dev/serial/by-id/ -name "*Arduino*" | head -1))


# help
help:
	@echo "USAGE: make one of the following recipies"
	@echo "\nC++ programs:"
	@echo $(SRCS) | tr " " "\n" 
	@echo "\nTools:"
	@echo "screen"
	@echo "cu"


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
%: %.cpp $(OBJS) $(HDRS)
	@echo "COMPILING..."
	$(GXX) $(GCCFLAGS) $@.cpp $(OBJS) -o $@.bin
	@echo "\n\n\nCONVERTING TO HEX..."
	avr-objcopy -j .text -j .data -O ihex $@.bin $@.hex
	@echo "\n\n\nFLASHING..."
	avrdude -v -p m328p -c arduino -P $(serialid) -D -U flash:w:$@.hex
	@echo "\n\n\nALL STEPS SUCCEDED!"


# clean
clean:
	rm -rf */**/*.hex
	rm -rf */**/*.bin
