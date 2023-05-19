#include "globals.h"
#include "codegen.h"
#include <ctype.h>


int contador = 0;
int contador_if = 0;
int contador_while = 0;

int register_index(){
    contador = (contador) % 32;
    return ++contador;
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
         fprintf(output, "LET ");  
         break;
      case DIV: 
         fprintf(output, "DIV ");  
         break;
      default:
         fprintf(output, " unknown ");  
   }
}

TreeNode* find_function(TreeNode *arvore, char *name){
    TreeNode *t = arvore;

    while (t != NULL) {

        if( t->child[0]->kind.stmt == FunK && strcmp(t->child[0]->attr.name, name) == 0){
            break;
        }
        t = t->sibling;
    }
    
    if(t == NULL){
        printf("Erro: Função %s não encontrada\n", t->child[0]->attr.name);
        exit(1);
    }
    return t->child[0];
}

void generateStmt(TreeNode *tree){

    TreeNode *func, *aux;
    int reg1 = 0, reg2 = 0;
    int i = 0;
    char nome[100];
    int store = 0, store2 = 0;
    switch (tree->kind.stmt) { 

        case FunK:
            printf("(FUN, %s %s, -) \n", tree->child[0]->attr.scope,  tree->child[0]->attr.scope);
            // árvore com problemas no filho 0
            // codeGen(tree->child[0]);
            //func = find_function(arvore, tree->attr.scope);
            //printf("%s", func->child[0]->attr.name);
            codeGen(tree->child[1]);
            break;

        case CallK:
            // quant_param = 0;
            // func = find_function(arvore, tree->attr.name);
            // aux = func->child[0];
            // while(aux != NULL){
            //     printf("PARAM %s _ _\n", aux->child[0]->attr.name);
            //     aux = aux->sibling;
            //     quant_param++;
            // }
            // printf("CALL %s %d t1\n", tree->attr.name, quant_param);
            break;

        case IfK:

            codeGen(tree->child[0]);
            contador_if++;
            store = contador_if;
            printf("(IFF, t%d, L%d, -)\n", contador, contador_if);
            register_index(); 
            codeGen(tree->child[1]);
            contador_if++;
            store2 = contador_if;
            printf("(GOTO, L%d, -, -)\n", store2);
            printf("(LAB, L%d, -, - )\n", store);
            codeGen(tree->child[2]);
            printf("(LAB, L%d, -, - )\n", store2); 
            register_index(); 
            break;

        case VarK:
            printf("(ALLOC, %s, %s, -)\n", tree->attr.name, tree->attr.scope);
            break;

        case AssignK:
            reg1 = contador;
            codeGen(tree->child[0]);     
            reg2 = contador;
            codeGen(tree->child[1]);
            printf("(ASSIGN, t%d, t%d, -)\n", reg1, reg2);
            printf("(STORE, %s, t%d, -)\n", tree->child[0]->attr.name, reg1);
            register_index();
            break;

        case WhileK:
                store = contador_if;
                printf("(LAB, L%d, -, -)\n", store);
                contador_if++;
                store2 = contador_if;
                contador_if++;
                codeGen(tree->child[0]);
                printf("(IFF, t%d, L%d, -)\n", contador, store2);
                codeGen(tree->child[1]);
                printf("(GOTO, L%d, - , -)\n", store);
                printf("(LAB, L%d, -, -)\n", store2);
                break;
        case ReturnK:
            break;
        default:
            printf("não mapeado - stmt\n");
            break;
    }
}

void generateExp(TreeNode *tree){
    int aux1, aux2;
    switch (tree->kind.exp) {
    
    case TypeK:
        codeGen(tree->child[0]);
        break;
    case IdK:
        printf("(LOAD, t%d, %s, -)\n", contador, tree->attr.name);
        register_index();
        break;
    case VetK:
        printf("asfaf");
    case ConstK:
        printf("(LOAD, t%d, %d, -)\n", contador,tree->attr.val);
        register_index();
        break;
    case OpK:
        aux1 = contador;
        codeGen(tree->child[0]);
        aux2 = contador;
        codeGen(tree->child[1]);
        printf("(");
        printOperation(stdout, tree->attr.op);
        printf("t%d, t%d, t%d )\n",contador, aux1, aux2); 
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