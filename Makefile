CC = g++
RM = rm

CFLAGS = -fPIC -g -Wall
LDFLAGS = -shared -lxerces-c -g -Wall
RMFLAGS = -rf

OBJ_DIR = obj/
INC_DIR = include/
SRC_DIR = src/
LIB_DIR = lib/

LIBFILE = libMB.so

SRC = $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJ = $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC:.cpp=.o))

all: $(LIB_DIR)$(LIBFILE)

nice:
	@$(RM) $(RMFLAGS) $(OBJ_DIR) $(OBJ_DIR)*.o

clean: nice
	@$(RM) $(RMFLAGS) $(LIB_DIR) $(LIB_DIR)$(LIBFILE)
	@cd test && $(MAKE) -s clean

tests:
	@echo "Building tests..."
	@cd test && $(MAKE) -s

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_DIR)%.h | $(OBJ_DIR)
	@echo "Building $<..."
	@$(CC) -c $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(LIB_DIR)$(LIBFILE): $(OBJ) | $(LIB_DIR)
	@echo "Linking library $<..."
	@$(CC) $^ $(LDFLAGS) -o $@

$(LIB_DIR):
	@mkdir $(LIB_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

