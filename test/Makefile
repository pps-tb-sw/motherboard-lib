CC = g++
TOP_DIR = ../
INC_DIR = $(TOP_DIR)include/
LIB_DIR = $(TOP_DIR)lib/

all: register reverse

register: register.cpp
	@echo "Building $@..."
	@$(CC) $^ -o $@ -L$(LIB_DIR) -Llib -lMB -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -g

reverse: reverse.cpp
	@echo "Building $@..."
	@$(CC) $^ -o $@ -L$(LIB_DIR) -Llib -lMB -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -g

clean:
	@rm -f register reverse
