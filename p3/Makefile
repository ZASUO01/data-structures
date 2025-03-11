CC = gcc 
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm -g

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
	mkdir -p $@

tree: ${OUT} 
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree

hash:
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000

clean:
	rm -rf $(BIN) $(OBJ) $(OUT)
