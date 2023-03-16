#include "bison.tab.h"
#define  ENDFILE 0

// Funções para análise
void scanner();

// Numero da linha
extern int lineno;

// Funções do flex 
extern char* yytext;
extern int yylex();
