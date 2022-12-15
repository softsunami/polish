CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

all: process.a run

process.a:
	$(CC) $(CFLAGS) -c polish.c stack.c -lm
	ar rc process.a *.o
	rm *.o

run:
	$(CC) $(CFLAGS) main.c process.a -o main -lm
	./main

rebuild: clean process.a run

clean:
	rm *.a