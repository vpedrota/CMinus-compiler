#include "globals.h"
#include "codegen.h"


int contador = 0;

void register_index(){
    contador = (contador + 1) % 32;
}

void printOperation(FILE *output, int token){
   switch (token){
      case PLUS: 
         fprintf(output, "PLUS "); 
         break;
      case SUB: 
         fprintf(output, "SUB  "); 
         break;
      case MULT: 
         fprintf(output, "MULT "); 
         break;
      case DIF: 
         fprintf(output, "IF ");  
         break;
      case GT: 
         fprintf(output, "GT ");  
         break;
      case LT: 
         fprintf(output, "LT ");  
         break;
      case GET: 
         fprintf(output, "GT ");  
         break;
      case LET: 
         fprintf(output, "LT ");  
         break;
      default:
         fprintf(output, " unknown ");  
   }
}


void generateStmt(TreeNode *tree){
    switch (tree->kind.stmt) { 

        case FunK:
            //printf("Função %s\n", tree->attr.name);
            codeGen(tree->child[1]);
            break;
        case IfK:
            break;
        case VarK:
            // printf("Variável %s\n", tree->attr.name);
            break;
        case AssignK:
            if(tree->child[1]->kind.exp == IdK){
                printf("ASSIGN ");
                codeGen(tree->child[1]);
                printf("_ ");
                printf("%s\n", tree->attr.name);
            }
            else{
                codeGen(tree->child[1]);
                printf("ASSIGN %s _ t%d\n", tree->attr.name, contador);
            }
            
            break;
        default:
            printf("não mapeado - stmt\n");
            break;
    }
}

void generateExp(TreeNode *tree){
    int aux1, aux2;
    switch (tree->kind.exp)
    {
    case TypeK:
        //printf("declaração\n");
        codeGen(tree->child[0]);
        break;
    case IdK:
        printf("%s ", tree->attr.name);
        break;
    case ConstK:
        printf("%d ", tree->attr.val);
        break;
    case OpK:
        if(tree->child[0]->kind.exp != OpK && tree->child[1]->kind.exp != OpK){
            printOperation(stdout, tree->attr.op);
            codeGen(tree->child[0]);
            codeGen(tree->child[1]);
            register_index();
            printf("t%d \n", contador); 
        }
        else if(tree->child[0]->kind.exp == OpK && tree->child[1]->kind.exp != OpK){
            codeGen(tree->child[0]);
            aux1 = contador;
            printOperation(stdout, tree->attr.op);
            printf("t%d ", aux1);
            codeGen(tree->child[1]);
            register_index();
            printf("t%d \n", contador);
        }
        else if(tree->child[0]->kind.exp != OpK && tree->child[1]->kind.exp == OpK){
            codeGen(tree->child[1]);
            aux1 = contador;
            printOperation(stdout, tree->attr.op);
            printf("t%d ", aux1);
            codeGen(tree->child[0]);
            register_index();
            printf("t%d \n", contador);
        }
        else if (tree->child[0]->kind.exp == OpK && tree->child[1]->kind.exp == OpK){
            codeGen(tree->child[0]);
            aux1 = contador;
            codeGen(tree->child[1]);
            aux2 = contador;
            printOperation(stdout, tree->attr.op);
            printf("t%d ", aux1);
            printf("t%d ", aux2);
            register_index();
            printf("t%d \n", contador);
        }
        break;
    
    default:
        printf("não mapeado - expr\n");
        break;
    }
}

void codeGen(TreeNode *tree){
    if(tree != NULL){
        switch (tree->nodekind) {
            case StmtK:
                generateStmt(tree);
                break;
            case ExpK:
                generateExp(tree);
                break;
            default:
                break;
        }
        codeGen(tree->sibling);
    }
}   