CC = gcc 
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm

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

$(BIN) $(OBJ):
	mkdir -p $@

$(OUT):
	mkdir -p $(OUT)/qs

quick_sort: $(OUT)
	$(TARGET) quicksort -v 1 -s 10 -i input.txt -o $(OUT)/qs/qs_1.txt
	$(TARGET) quicksort -v 2 -s 10 -k 3 -i input.txt -o $(OUT)/qs/qs_2_1.txt
	$(TARGET) quicksort -v 2 -s 10 -k 5 -i input.txt -o $(OUT)/qs/qs_2_2.txt
	$(TARGET) quicksort -v 2 -s 10 -k 7 -i input.txt -o $(OUT)/qs/qs_2_3.txt
	$(TARGET) quicksort -v 3 -s 10 -m 10 -i input.txt -o $(OUT)/qs/qs_3_1.txt
	$(TARGET) quicksort -v 3 -s 10 -m 100 -i input.txt -o $(OUT)/qs/qs_3_2.txt
	$(TARGET) quicksort -v 4 -s 10 -i input.txt -o $(OUT)/qs/qs_4.txt
	$(TARGET) quicksort -v 5 -s 10 -i input.txt -o $(OUT)/qs/qs_5.txt


heap_sort: $(OUT)
	$(TARGET) heapsort -v 1 -s 10 -i input.txt -o $(OUT)/hs.txt

merge_sort: $(OUT)
	$(TARGET) mergesort -v 1 -s 10 -i input.txt -o $(OUT)/ms.txt

plot:
	rm -rf images
	mkdir -p images
	python3 plot.py

clean:
	rm -rf $(BIN) $(OBJ) $(OUT)

clean_plot:
	rm -rf images
