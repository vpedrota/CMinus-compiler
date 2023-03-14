%{

#include <stdio.h>
int yyerror(char *s);
static int yylex();

%}

/*****************************************
    Realizando a declaração dos lexemas
******************************************/

// Condidionais
%token IF ELSE

// Operações aritméticas
%token SUM SUB MULT DIV MOD

// Operações Lógicas
%token EQUAL DIF GT LT

// Escopos
%token VOID INT RETURN ID VIR PV

// Demais caracters
%token LBRAC RBRAC ENDFILE

%token ERR


%%

prog:
    stmts
stmts: IF
%%

static int yylex(){
    return 1;
}

int yyerror(char *s){
    return 1;
}