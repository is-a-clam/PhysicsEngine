TARGET = app.out

C++FLAGS = -std=c++11
CFLAGS = -Wall $(shell pkg-config --cflags glfw3 assimp)
LDFLAGS = -Wall $(shell pkg-config --libs glfw3 assimp)

SRC_DIR = src
OBJ_DIR = obj

INCLUDE = $(wildcard $(SRC_DIR)/*.h)
SRC_C   = $(wildcard $(SRC_DIR)/*.c)
SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)

OBJ_C   = $(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CPP = $(SRC_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJ_C) $(OBJ_CPP)
	g++ $(LDFLAGS) -o $@ $^

$(OBJ_C): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	gcc $(CFLAGS) -c -o $@ $<

$(OBJ_CPP): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE)
	g++ $(C++FLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ_C) $(OBJ_CPP) $(TARGET)