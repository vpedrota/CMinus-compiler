#include "globals.h"

TreeNode* alocaNo(){
    TreeNode* No = malloc(sizeof(TreeNode));
    const char* texto = "teee";
    strcpy(No->attr.name,texto);
    int i;
    for(i = 0; i < MAXCHILDREN; i++){
        No->child[i] = NULL;
    }
    No->sibling = NULL;
    return No;
}

TreeNode* alocaStmt(StmtKind kind){
    TreeNode* No = malloc(sizeof(TreeNode));
    if(No == NULL){
        printf("Sem memória para alocação");
        exit(1);
    }

    for(int i = 0; i < MAXCHILDREN; i++){
        No->child[i] = NULL;
    }
    No->sibling = NULL;

    No->sibling = NULL;
    No->nodekind = StmtK;
    No->kind.stmt = kind;
    No->lineno = lineno;
    return No;
}

static int indentno = 0;

#define INDENT indentno+=2
#define UNINDENT indentno-=2

static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    printf(" ");
}

void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          printf("If\n");
          break;
        case WhileK:
          printf("While\n");
          break;
        case AssignK:
          printf("Assign to: %s\n",tree->attr.name);
          break;
        case VarK:
          printf("Var: %s\n",tree->attr.name);
          break;
        case FunK:
          printf("Fun: %s\n",tree->attr.name);
          break;
        case CallK:
          printf("Call: %s\n",tree->attr.name);
          break;
        case ReturnK:
          printf("Return\n");
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          printf("Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          printf("Const: %d\n",tree->attr.val);
          break;
        case IdK:
          printf("Id: %s\n",tree->attr.name);
          break;
        case VetK:
          printf("Vet: %s\n",tree->attr.name);
          break;
        case TypeK:
          printf("Type: %s\n",tree->attr.name);
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else printf("Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}