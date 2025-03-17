CC = gcc 
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -g -lm

BIN = bin
SRC = src
OBJ = obj
OUT = output

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS)) 

TARGET = $(BIN)/main 

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ) $(OUT): 
	rm -rf $@	
	mkdir -p $@

mem-leak: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	$(TARGET) -i medium-input.txt

test: $(OUT)
	$(TARGET) -i short-input.txt  > $(OUT)/short-output.txt
	$(TARGET) -i medium-input.txt > $(OUT)/medium-input.txt
	$(TARGET) -i large-input.txt  > $(OUT)/large-output.txt

usage: $(OUT)
	$(TARGET) -i short-input.txt -p > $(OUT)/short-output.txt
	$(TARGET) -i medium-input.txt -p > $(OUT)/medium-input.txt
	$(TARGET) -i large-input.txt -p > $(OUT)/large-output.txt

clean: 
	rm -rf $(BIN) $(OBJ) $(OUT)
