

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  ENDFILE 0

// Funções para análise
void scanner();

// Numero da linha
extern int lineno;

// Funções do flex 
extern char* yytext;
extern int yylex();

#define MAXCHILDREN 3

// Nó da árvore
typedef struct treeNode {
    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling;
    char nome[100];
} TreeNode;

TreeNode* parse();

#include "bison.tab.h"
