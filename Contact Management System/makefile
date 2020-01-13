CC=gcc
CFLAGS=-ansi -Wall -Iincludes
All:functions.o contactList.o
	$(CC) $(CFLAGS) -o bin/contactList bin/functions.o bin/contactList.o

functions.o: src/functions.c includes/functions.h
	$(CC) $(CFLAGS) -c src/functions.c -o bin/functions.o

contactList.o: src/contactList.c includes/functions.h
	$(CC) $(CFLAGS) -c src/contactList.c -o bin/contactList.o

clean:
	rm bin/*
