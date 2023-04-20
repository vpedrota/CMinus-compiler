# Definindo compilador e flags para compilação
CC := gcc
CFLAGS := -c -Wall

all: compilador clean

compilador: scan.o arvore.o bison.tab.o  main.o
	$(CC) scan.o arvore.o bison.tab.o  main.o -o cminus

bison.tab.o: bison/bison.y globals.h
	bison -d -t bison/bison.y 
	$(CC) -c bison.tab.c

scan.o: flex/flex.l scan.h globals.h 
	flex -o scan.c flex/flex.l
	$(CC) -c scan.c

arvore.o: arvore.c arvore.h globals.h
	$(CC) -c arvore.c

clean:
	rm -f bison.tab.o scan.o arvore.o main.o

.PHONY: all clean