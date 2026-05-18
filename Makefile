CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude 
LDFLAGS = -lmenu -lncurses 

TARGET = build/todotui
V1TARGET = build/V1tui
SRC = src/main.c src/storage.c src/todoFunctions.c
V1SRC = src/todotui.c 


$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

$(V1TARGET): $(V1SRC) | build
	$(CC) $(CFLAGS) -o $(V1TARGET) $(V1SRC) $(LDFLAGS)

v1: $(V1TARGET)

build: 
	mkdir -p build

run-v1: $(V1TARGET)
	./$(V1TARGET)

clean-v1: 
	rm -f $(V1TARGET)

clean: 
	rm -f $(TARGET)

.PHONY: run run-v1 clean clean-v1

