

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

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,WhileK,AssignK,VarK,FunK, CallK, ReturnK} StmtKind;
typedef enum {OpK, ConstK,IdK, VetK, TypeK} ExpKind;

/* ExpType is used for type checking */
typedef enum {VoidK,IntegerK,BooleanK} ExpType;

// Nó da árvore
typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     struct { int op;
             int val;
             char name[100];
             int len;
             char * scope; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

TreeNode* parse();

#include "bison.tab.h"





#define MAXCHILDREN 3

