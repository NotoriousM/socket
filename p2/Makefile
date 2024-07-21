TARGET = p_two

BIN_DIR = bin
OBJ_DIR = obj

OBJ_FILES = $(OBJ_DIR)/main.o

CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lpthread

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR)/$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

install: $(BIN_DIR)/$(TARGET)
	install ./$(BIN_DIR)/$(TARGET) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(TARGET)
