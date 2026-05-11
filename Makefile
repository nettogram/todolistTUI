CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lncurses

TARGET = build/todotui
SRC = src/todotui.c 
LOGIC = build/todolistlogic
SRCLOGIC = src/todolistlogic.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

logic:
	$(CC) $(CFLAGS) -o $(LOGIC) $(SRCLOGIC)

clean: 
	rm -f $(TARGET)
