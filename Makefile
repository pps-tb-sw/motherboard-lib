CC = g++
RM = rm

CFLAGS = -fPIC
LDFLAGS = -shared
RMFLAGS = -f

OBJ_DIR = obj/
INC_DIR = include/
SRC_DIR = src/
LIB_DIR = lib/

LIBFILE = libMB.so

SRC = $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJ = $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC:.cpp=.o))

all: $(LIB_DIR)$(LIBFILE)

nice:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)*.o

clean: nice
	@$(RM) $(RMFLAGS) $(LIB_DIR)$(LIBFILE)
	@cd test && $(MAKE) clean

tests:
	@echo "Building tests..."
	cd test && $(MAKE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_DIR)%.h
	@echo "Building $<..."
	@$(CC) -c $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(LIB_DIR)$(LIBFILE): $(OBJ)
	@echo "Linking library $<..."
	@$(CC) $^ $(LDFLAGS) -o $@


