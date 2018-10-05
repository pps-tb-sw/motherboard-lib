CC = g++
TOP_DIR = ../
INC_DIR = $(TOP_DIR)include/
XML_INC_DIR = $(TOP_DIR)/xml/
LIB_DIR = $(TOP_DIR)lib/

LDFLAGS = -Wl,-R$(LIB_DIR),-Rlib -I$(INC_DIR) -I$(XML_INC_DIR) -I$(TOP_DIR) -g

all: register reverse xml pre

pre:
	@cd .. && $(MAKE) -s

bugtracker: bugtracker.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ $(LDFLAGS) -L$(LIB_DIR) -Llib -lMB -lMBxml

register: register.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ $(LDFLAGS) -L$(LIB_DIR) -Llib -lMB

reverse: reverse.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ $(LDFLAGS) -L$(LIB_DIR) -Llib -lMB

xml: xml.cpp | pre
	@echo "Building $@..."
	@$(CC) $^ -o $@ $(LDFLAGS) -L$(LIB_DIR) -Llib -lMB -lMBxml -lxerces-c

clean:
	@rm -f register reverse xml
