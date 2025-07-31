CC = gcc
CFLAGS = -Wall

SRC = todo.c

all: todo

todo:
	mkdir -p data
	$(CC) $(CFLAGS) -o todo $(SRC)

clean:
	rm -f todo data/tasks.txt