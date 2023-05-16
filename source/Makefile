# Definindo compilador e flags para compilação
CC := gcc
CFLAGS := -c -Wall

all: compilador clean

compilador: scan.o arvore.o parser.o symtab.o analyze.o codegen.o main.o
	$(CC) scan.o arvore.o parser.o symtab.o analyze.o main.o codegen.o -o cminus

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

analyze.o: analyze.c analyze.h globals.h
	$(CC) -c analyze.c

codegen.o: codegen.c codegen.h globals.h
	$(CC) -c codegen.c

clean:
	rm -f parser.o scan.o arvore.o symtab.o analyze.o main.o

.PHONY: all clean