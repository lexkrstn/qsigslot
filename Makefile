TARGET_FILE=test
CC=g++
CFLAGS=-c -std=c++2a
LFLAGS=
SRC_PATH=test/
TARGET_PATH=build/

all: test

test: main.o
	$(CC) $(TARGET_PATH)main.o -o $(TARGET_PATH)$(TARGET_FILE) $(LFLAGS)

main.o:
	$(CC) $(CFLAGS) $(SRC_PATH)main.cpp -o $(TARGET_PATH)main.o

clean:
	rm -rf $(TARGET_PATH)*.o $(TARGET_PATH)$(TARGET_FILE)
