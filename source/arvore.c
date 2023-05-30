#include "globals.h"
#include "scan.h"

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
    t->attr.vetor = 0;
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
    t->attr.vetor = 0;
  }
}

static void printSpaces(FILE *output){ 
  int i;
  for (i=0;i<indentno;i++)
    fprintf(output, " ");
}

char* copyString(const char *string){
  char *str = malloc(sizeof(char)*(strlen(string)+1));
  strcpy(str, string);
  return str;
}

void printOp(FILE *output, int token){
   switch (token){
      case PLUS: 
         fprintf(output, " PLUS  \n"); 
         break;
      case SUB: 
         fprintf(output, " SUB  \n"); 
         break;
      case MULT: 
         fprintf(output, " MULT  \n"); 
         break;
      case DIF: 
         fprintf(output, " DIF  \n");  
         break;
      case GT: 
         fprintf(output, " GT  \n");  
         break;
      case LT: 
         fprintf(output, " LT  \n");  
         break;
      case GET: 
         fprintf(output, " GT  \n");  
         break;
      case LET: 
         fprintf(output, " LT  \n");  
         break;
      default:
         fprintf(output, " unknown  \n");  
   }
}

void printTree( TreeNode * tree, FILE *output){
  
  int i;
  INDENT;
  while (tree != NULL) {
    
    printSpaces(output);
    //fprintf(output, "-%s-", tree->attr.scope);
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt)
            {
            case IfK:
                fprintf(output, "If\n");
                break;
            case AssignK:
                fprintf(output, "Atribuicao\n");
                break;
            case WhileK:
                fprintf(output, "While\n");
                break;
            case VarK:
                fprintf(output, "Variavel %s\n", tree->attr.name);
                break;
            case FunK:
                fprintf(output, "Funcao %s\n", tree->attr.name);
                break;
            case CallK:
                fprintf(output, "Chamada de Funcao %s \n", tree->attr.name);
                break;
            case ReturnK:
                fprintf(output, "Return\n");
                break;

            default:
                fprintf(output, "No de Declaracao desconhecido\n");
                break;
            }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(output, "Op: ");
          printOp(output, tree->attr.op);
          break;
        case ConstK:
          fprintf(output, "Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(output, "Id: %s\n",tree->attr.name);
          break;
        case VetK:
              fprintf(output, "Vetor: %s\n", tree->attr.name);
              break;
        case TypeK:
            fprintf(output, "Tipo %s\n", tree->attr.name);
            break;
        default:
          fprintf(output, "No de expressao desconhecido.\n");
          break;
      }
    }
    else fprintf(output, "No desconhecido.\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i], output);
    tree = tree->sibling;
  }
  UNINDENT;
}

void printTreeFile(TreeNode * tree){
  FILE *output = fopen("analises/sintatico.txt", "w");
  printTree( tree, output);
  fclose(output);
}