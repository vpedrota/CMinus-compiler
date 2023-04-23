# Definindo compilador e flags para compilação
CC := gcc
CFLAGS := -c -Wall

all: compilador clean

compilador: scan.o arvore.o parser.o  symtab.o main.o
	$(CC) scan.o arvore.o parser.o symtab.o main.o -o cminus

parser.o: bison/bison.y globals.h
	bison -d -t -o parser.c bison/bison.y 
	$(CC) -c parser.c

scan.o: flex/flex.l scan.h globals.h 
	flex -o scan.c flex/flex.l
	$(CC) -c scan.c

arvore.o: arvore.c arvore.h globals.h
	$(CC) -c arvore.c

symtab.o: symtab.c symtab.h globals.h
	$(CC) -c symtab.c

clean:
	rm -f bison.tab.o scan.o arvore.o symtab.o main.o

.PHONY: all clean