

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENDFILE 0
#define MAXCHILDREN 3

extern int lineno;

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK, WhileK, AssignK, VarK, FunK, CallK, ReturnK, ParamK} StmtKind;
typedef enum {OpK, ConstK, IdK, VetK, TypeK} ExpKind;
typedef enum {VoidK,IntegerK,BooleanK, IntegerVetorK} ExpType;

// Nó da árvore
typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     struct { int op;
             int val;
             char *name;
             int len;
             char * scope; 
             int vetor;
            } attr;
     ExpType type;
   } TreeNode;

TreeNode* parse();

void printT(int value);

#include "parser.h"
#define MAXCHILDREN 3

