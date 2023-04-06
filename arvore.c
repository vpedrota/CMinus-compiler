#include "globals.h"

// Variáveis utilizada para imprimir a árvore sintática
// Utilizada apenas para controlar o nível de identação
static int indentno = 0;
#define INDENT indentno+=2
#define UNINDENT indentno-=2

// Funções para alocação dos nós para árvore sintática
// Os nós se mantiveram seguindo a estrutura de Quadtrees do Tiny


// São utilizados dois tipos de nós para a criação de nós
// tipo Stmt ou do tipo Exp, mas ambos possuem até três filho e um irmão
TreeNode * newStmtNode(StmtKind kind) { 
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL){
    printf("Sem memória disponível");
    exit(1);
  }
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
    t->attr.scope = "global";
  }
  return t;
}

TreeNode * newExpNode(ExpKind kind) { 
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL){
    printf("Sem memória disponível");
    exit(1);
  }
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = VoidK;
    t->attr.scope = "global";
  }
}

static void printSpaces(void){ 
  int i;
  for (i=0;i<indentno;i++)
    printf(" ");
}

char* copyString(const char *string){
  char *str = malloc(sizeof(char)*(strlen(string)+1));
  strcpy(str, string);
  return str;
}

void printTree( TreeNode * tree ) {
  int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    switch (tree->type) {
      case IntegerK:
        printf("Integer");
        break;
      case VoidK:
        printf("Void");
        break;
      default:
        printf("erro");
    }
    printf("%d %s\n", tree->lineno, tree->name);
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}