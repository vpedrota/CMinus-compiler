#include "globals.h"
#include "codegen.h"
#include <ctype.h>


int contador = 0;
int contador_if = 0;
int contador_while = 0;
int registrador_retorno = 0;

int calls_param_change_context = 0;

int register_index(){
    contador = (contador);
    return ++contador;
}

void printOperation(FILE *output, int token){
   switch (token){
      case PLUS: 
         fprintf(output, "PLUS, "); 
         break;
      case SUB: 
         fprintf(output, "SUB,  "); 
         break;
      case MULT: 
         fprintf(output, "MULT, "); 
         break;
      case DIF: 
         fprintf(output, "DFT, ");  
         break;
      case GT: 
         fprintf(output, "GT, ");  
         break;
      case LT: 
         fprintf(output, "LT, ");  
         break;
      case GET: 
         fprintf(output, "GET, ");  
         break;
      case LET: 
         fprintf(output, "LET, ");  
         break;
      case DIV: 
         fprintf(output, "DIV, ");  
         break;
      case COMP: 
         fprintf(output, "COMP, ");  
         break;

     case RESTO: 
        fprintf(output, "RESTO, ");  
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
    if(tree == NULL) return;
    TreeNode *func, *aux;
    int reg1 = 0, reg2 = 0;
    int i = 0;
    char nome[100];
    int store = 0, store2 = 0;
    int quant_param = 0;

    switch (tree->kind.stmt) { 
        case FunK:

            if(tree->type == IntegerK)
                printf("(FUN, int, %s, -) \n",  tree->child[0]->attr.scope);
            else
                printf("(FUN, void, %s, -) \n",  tree->child[0]->attr.scope);

            aux = tree->child[0];
            while(aux != NULL){
                if(aux->child[0] != NULL){
                    printf("(ARG, %s, %s, %s)\n",aux->attr.name, aux->child[0]->attr.name, aux->child[0]->attr.scope);
                } 
                aux = aux->sibling;
            }

            // aux = tree->child[0];
            // while(aux != NULL){
            //     if(aux->child[0] != NULL){
            //         printf("(LOAD, $t%d, %s, -)\n", contador, aux->child[0]->attr.name);
            //         register_index();
            //     } 
            //     aux = aux->sibling;
            // }
            
            codeGen(tree->child[1]);
            printf("(END, %s, -, -)\n", tree->attr.name);
            break;

        case CallK:
            
            quant_param = 0;
            aux = tree->child[0];
            
            
            while(aux != NULL){
                //printf("--%s--, %d", aux->attr.name, aux->attr.op);
                if(aux->nodekind == ExpK) {

                    if(aux->kind.exp == IdK){

                        register_index();

                       
                        printf("(PARAM_ID, %s, %s, $t%d)\n", aux->attr.name, tree->attr.name, contador);
                        
                       
                        aux = aux->sibling;
                        quant_param++;
                        continue;
                        
                    }

                    generateExp(aux);
                    
    
                } 
                else{
                   
                    generateStmt(aux);
                }

                
                
                // if(strcmp(tree->attr.name, "change_context") == 0 && calls_param_change_context == 0){
                //     int a = contador;
                //     register_index();
                //     printf("(LOAD_IMEDIATE, $t%d, 0, -)\n", contador);
                //     printf("(PLUS, $context_register, $t%d, $t%d)\n", a, contador);
                //     printf("(PARAM, $context_register, %s, -)\n", tree->attr.name);
                //     calls_param_change_context++;

                    
                // }else{
                    printf("(PARAM, $t%d, %s, -)\n", contador, tree->attr.name);
                //     calls_param_change_context = 0;
                // }

                
                aux = aux->sibling;
                quant_param++;
            }


            if(strcmp(tree->attr.name, "input") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "copy_registers_to_bank") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "copy_registers_to_ram") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }

             if(strcmp(tree->attr.name, "set_hd_track") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }


            if(strcmp(tree->attr.name, "PC_INTERRUPTION") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "STACK_SIZE") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 0)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "output") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 1)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "set_quantum_value") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 1)\n", contador, tree->attr.name);
                return;
            }

            if(strcmp(tree->attr.name, "change_context") == 0){
                register_index();
                printf("(CALL, $t%d, %s, 2)\n", contador, tree->attr.name);
                return;
            }

            register_index();
            registrador_retorno = contador;

            // printf("(EMPILHA, - , -, -)\n");
            printf("(CALL, $t%d, %s, %d)\n", contador, tree->attr.name, quant_param);
            //printf("(DESEMPILHA, - , -, -)\n");
            
            break;

        case IfK:

            codeGen(tree->child[0]);
            
            store = contador_if;
            contador_if++; 
            store2 = contador_if;
            contador_if++;
            printf("(IFF, $t%d, L%d, -)\n", contador, store);
            
            register_index(); 
            codeGen(tree->child[1]);
           
            printf("(GOTO, L%d, -, -)\n", store2);
            printf("(LAB, L%d, -, - )\n", store);
            codeGen(tree->child[2]);
            printf("(LAB, L%d, -, - )\n", store2); 
            register_index(); 
            break;

        case VarK:
            if(tree->attr.vetor){
                printf("(ALLOC_VET, %s, %d, %s)\n", tree->attr.name, tree->attr.len, tree->attr.scope);
                break;
            }
            printf("(ALLOC, %s, %s, -)\n", tree->attr.name, tree->attr.scope);
            break;
            
        case AssignK:
            
           
            registrador_retorno = 0; 
            codeGen(tree->child[1]);
            reg2 = contador; 
            
            if(tree->child[0]->kind.exp == VetK){
                codeGen(tree->child[0]->child[0]);
            }
          
   
            reg1 = contador;

            if(tree->child[0]->kind.exp == VetK){
                printf("(STOREVAR_VETOR, $t%d, %s, $t%d)\n", reg2, tree->child[0]->attr.name, reg1);
            }
            else{
                printf("(STOREVAR, $t%d, %s, %s)\n", reg2, tree->child[0]->attr.name, tree->child[0]->attr.scope);
            }
            
            register_index();
            break;

        case WhileK:

                store = contador_if;
                contador_if++;
                store2 = contador_if;
                contador_if++;

                printf("(LAB, L%d, -, -)\n", store);
                
                codeGen(tree->child[0]);
                printf("(IFF, $t%d, L%d, -)\n", contador, store2);
                codeGen(tree->child[1]);
                printf("(GOTO, L%d, - , -)\n", store);
                printf("(LAB, L%d, -, -)\n", store2);
                break;

        case ReturnK:
            codeGen(tree->child[0]);
            printf("(RET, $t%d, -, -)\n", contador);
            break;

        default:
            printf("não mapeado - stmt\n");
            break;
    }
}

void generateExp(TreeNode *tree){
    if(tree == NULL) return;
    int aux1, aux2;
    switch (tree->kind.exp) {
    
    case TypeK:
        codeGen(tree->child[0]);
        break;
    case IdK:
        register_index();
        printf("(LOAD_WORD, $t%d, %s, -)\n", contador, tree->attr.name);
        break;
    case VetK:
        codeGen(tree->child[0]);
        aux1=contador;
        aux2=contador;
        register_index();
        printf("(LOAD_WORD_VETOR, $t%d, %s, ($t%d))\n", contador, tree->attr.name, aux2);
        break;
    case ConstK:
        register_index();
        printf("(LOAD_IMEDIATE, $t%d, %d, -)\n", contador,tree->attr.val);
        break;
    case OpK:   
       
        codeGen(tree->child[0]);
        aux1 = contador;
        
        codeGen(tree->child[1]);
        aux2 = contador;
        
        register_index();
        printf("(");
        printOperation(stdout, tree->attr.op);
        printf("$t%d, $t%d, $t%d )\n", contador, aux1, aux2); 
        break;

    default:
        printf("%d",tree->kind.exp);
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