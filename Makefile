CFLAGS=-g -fsanitize=address,leak -c
CFLAGS_OCOMPILE=-fsanitize=address,leak
CC = g++

all: list

list: list.o list.h main.o
	$(CC) $(CFLAGS_OCOMPILE) main.o list.o -o list

list.o: list.cpp list.h
	$(CC) $(CFLAGS) list.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp