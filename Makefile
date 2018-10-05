CC = clang
RM = rm

CFLAGS = -fPIC -g -Wall
LDFLAGS = -shared -g -Wall
RMFLAGS = -rf

OBJ_DIR = obj/
INC_DIR = include/
SRC_DIR = src/
XML_SRC_DIR = xml/
LIB_DIR = lib/

LIBFILE = libMB.so
LIBXMLFILE = libMBxml.so

MB_SRC = $(shell find $(SRC_DIR) -type f -name *.cpp)
MB_OBJ = $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(MB_SRC:.cpp=.o))
XML_SRC = $(shell find $(XML_SRC_DIR) -type f -name *.cpp)
XML_OBJ = $(patsubst $(XML_SRC_DIR)%,$(OBJ_DIR)%,$(XML_SRC:.cpp=.o))

all: $(LIB_DIR)$(LIBFILE) $(LIB_DIR)$(LIBXMLFILE)

nice:
	@$(RM) $(RMFLAGS) $(OBJ_DIR) $(OBJ_DIR)*.o

clean: nice
	@$(RM) $(RMFLAGS) $(LIB_DIR) $(LIB_DIR)$(LIBFILE) $(LIB_DIR)$(LIBFILE)
	@cd test && $(MAKE) -s clean

tests:
	@echo "Building tests..."
	@cd test && $(MAKE) -s

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_DIR)%.h | $(OBJ_DIR)
	@echo "Building $<..."
	@$(CC) -c $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(OBJ_DIR)%.o: $(XML_SRC_DIR)%.cpp $(XML_SRC_DIR)%.h | $(OBJ_DIR)
	@echo "Building $<..."
	@$(CC) -c $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(LIB_DIR)$(LIBFILE): $(MB_OBJ) | $(LIB_DIR)
	@echo "Linking library $<..."
	@$(CC) $^ $(LDFLAGS) -o $@

$(LIB_DIR)$(LIBXMLFILE): $(XML_OBJ) | $(LIB_DIR)
	@echo "Linking library $<..."
	@$(CC) $^ $(LDFLAGS) -o $@ -lxerces-c -lboost_regex

$(LIB_DIR):
	@mkdir $(LIB_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

