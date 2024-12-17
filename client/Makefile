# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

BIN = GameMenu

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

re: clean all 	

.PHONY: all clean re
