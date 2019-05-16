CC = gcc
CFLAGS= -Wall -c -std=c99
GDBFLAG = -g
RM = rm -f

all: movies.o list.o binaryTree.o graph.o helpers.o queue.o labirint.o graphDij.o multiset.o helpers.o
	$(CC) movies.o list.o binaryTree.o graph.o helpers.o queue.o -o movies
	$(CC) labirint.o list.o multiset.o graphDij.o helpers.o binaryTree.o -o labirint -g
build: movies.c list.c binaryTree.c graph.c helpers.c queue.c labirint.c graphDij.c multiset.c
	$(CC) $(CFLAGS) movies.c list.c binaryTree.c graph.c helpers.c queue.c
	$(CC) $(CFLAGS) labirint.c list.c multiset.c graphDij.c helpers.c binaryTree.c -g
	make
clean:
	$(RM) *.o movies labirint
