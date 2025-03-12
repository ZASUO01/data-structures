CC = gcc 
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -g -lm

BIN = bin
SRC = src
OBJ = obj
OUT = output
IMG = images

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

run: $(OUT)
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000

memory: $(OUT)
	$(TARGET) -i short_input.txt -o $(OUT)/short-tree.txt -t tree -l -m $(OUT)/mem-tree.txt
	$(TARGET) -i short_input.txt -o $(OUT)/short-hash.txt -t hash -s 50 -l -m $(OUT)/mem-hash.txt

usage: $(OUT)
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt
	$(TARGET) -i input.txt -o $(OUT)/tree.txt -t tree -p -u $(OUT)/usage-tree.txt
	$(TARGET) -i input.txt -o $(OUT)/hash.txt -t hash -s 5000 -p -u $(OUT)/usage-hash.txt


plot:
	rm -rf images
	mkdir -p images
	python3 mem-plot.py
	python3 usage-plot.py

clean: 
	rm -rf $(BIN) $(OBJ) $(OUT) $(IMG)
