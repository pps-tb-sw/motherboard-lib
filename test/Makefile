CC = g++
TOP_DIR = ../
INC_DIR = $(TOP_DIR)include/
LIB_DIR = $(TOP_DIR)lib/

all: register reverse xml pre

pre:
	@cd .. && $(MAKE) -s

register: register.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ -L$(LIB_DIR) -Llib -lMB -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -g

reverse: reverse.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ -L$(LIB_DIR) -Llib -lMB -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -g

xml: xml.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ -L$(LIB_DIR) -Llib -lMB -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -g -lxerces-c

clean:
	@rm -f register reverse
