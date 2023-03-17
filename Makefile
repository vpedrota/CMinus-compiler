# Definindo compilador e flags para compilação
CC := gcc
CFLAGS := -c -Wall

all: compilador clean

compilador: lex.yy.o arvore.o bison.tab.o  main.o
	$(CC) lex.yy.o arvore.o bison.tab.o  main.o -o cminus

bison.tab.o: bison/bison.y globals.h
	bison -d -t bison/bison.y 
	$(CC) -c bison.tab.c

lex.yy.o: flex/flex.l globals.h
	flex flex/flex.l
	$(CC) -c lex.yy.c

arvore.o: arvore.c arvore.h globals.h
	$(CC) -c arvore.c

clean:
	rm -f bison.tab.o lex.yy.o arvore.o main.o

.PHONY: all clean