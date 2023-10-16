NAME = TP1
CC = g++ -std=c++20 
SRC_DIR = ./src
INC_DIR = ./include
BIN_DIR = ./bin
OBJ_DIR = ./obj
CFLAGS = -Wall -g
EXE = $(BIN_DIR)/$(NAME)

OBJS = \
	$(OBJ_DIR)/Puzzle.o \
	$(OBJ_DIR)/Utils.o \
	$(OBJ_DIR)/UninformedSearch.o \
	$(OBJ_DIR)/InformedSearch.o \
	$(OBJ_DIR)/LocalSearch.o \
	$(OBJ_DIR)/Hashtable.o \
	$(OBJ_DIR)/main.o

all: $(EXE)

run: all
	$(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/**/%.cpp $(INC_DIR)/%.hpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

valgrind: $(EXE)
	valgrind --leak-check=full  $(BIN_DIR)/$(NAME)
	
clean:
	rm -f $(OBJS)
	rm -f $(EXE)