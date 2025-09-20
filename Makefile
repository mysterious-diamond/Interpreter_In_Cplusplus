CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC_DIR = src
OBJ_DIR = obj
BIN = main

# Find all .cpp files in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Turn them into .o files inside obj/
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(BIN)

# Link step
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile step
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure obj dir exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
