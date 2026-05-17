CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude 
LDFLAGS = -lncurses

TARGET = build/todotui
SRC = src/main.c src/storage.c src/todoFunctions.c

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

build: 
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(TARGET)

.PHONY: clean
