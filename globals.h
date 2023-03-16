#include "bison.tab.h"
#define  ENDFILE 0
void scanner();

// Numero da linha
extern int lineno;

// funções do bison 
extern char* yytext;
extern int yylex();
