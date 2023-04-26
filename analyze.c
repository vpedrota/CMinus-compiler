#include "globals.h"
#include "symtab.h"

void check_node(TreeNode *node){
    Node* aux = NULL, *aux2;
    int operador1, operador2;
    switch (node->nodekind) {

    case StmtK:
        switch (node->kind.stmt) {

        case AssignK:

            if(node->child[1]->kind.exp == ConstK || node->child[1]->kind.exp == OpK)
                break;
                
            aux = find_name(node->child[1]->attr.name, node->child[1]->attr.scope);
            if(aux->type != IntegerK ){
                printf("Assign entre variável e retorno de void. Função: %s\n", aux->name);
                exit(1);
            }
            break;
        case ReturnK:

            aux = find_name(node->attr.scope, "global");

            if(node->child[0] == NULL && aux->type == IntegerK){
                printf("Erro semântico: valor retornado não corresponde ao tipo da função declarada. Função: %s\n", aux->name);
                exit(1);
            }

            else if (node->child[0] == NULL && aux->type == VoidK){
                break;
            }

            if(node->child[0]->kind.exp == IdK && aux->type == IntegerK){
                aux2 = find_name(node->child[0]->attr.name, node->child[0]->attr.scope);
                if(aux2->type != aux->type){
                    printf("Erro semântico: valor retornado não corresponde ao tipo da função declarada. Função: %s\n", aux->name);
                    exit(1);
                }
            }
            break;

        case VarK:
            if(node->type == VoidK){
                printf("Erro semântico: variável declarada do tipo void\n");
                exit(1);
            }
            break;
        
        default:
            break;
        }
        break;
    
    default:
        break;

    case ExpK:
        switch (node->kind.exp) {

        case ConstK:
        case IdK:
            node->type = IntegerK;
            break;

        case OpK:

            //  printf("qq%d %d", node->child[0]->kind.exp, node->child[0]->attr.op);
            //  printf("--%d", node->child[1]->kind.exp);
            
            // printf("%d--", node->child[0]->kind.exp);
            // printf("%d---\n", node->child[1]->kind.exp);

            operador1 = (node->child[0]->kind.exp == ConstK || node->child[0]->kind.exp == IdK || node->child[0]->kind.exp == VetK || node->child[0]->kind.exp == OpK);
            operador2 = (node->child[1]->kind.exp == ConstK || node->child[1]->kind.exp == IdK || node->child[1]->kind.exp == VetK || node->child[1]->kind.exp == OpK);

            if(operador1 && operador2){
                break;
            }

            if((node->child[0]->type != IntegerK || node->child[0]->kind.exp != OpK) || (node->child[1]->type != IntegerK || node->child[1]->kind.exp != OpK)){
                printf("%d %d", node->child[0]->kind.exp, node->child[1]->kind.exp)/
                printf("OPERAÇÃO ARITMÉTICA ENTRE DOIS VALORES NÃO INTEIROS: %d\n", node->lineno);
                exit(1);
            }

            break;
        default:
            break;
        }
        break;

    }
}

void transverse_check(TreeNode *tree){
 int i; 
    if (tree != NULL){
        //insert_node_symtab(tree, tree->attr.scope);
        for (i=0;i<MAXCHILDREN;i++)
            transverse_check(tree->child[i]);
        check_node(tree);
        tree = tree->sibling;
        transverse_check(tree);
    }
}

void analyze(TreeNode *tree){
    Node* aux = find_name("main", "global");
    if(aux == NULL){
        printf("Erro semântico: função main não declarada\n");
        exit(1);
    }
    transverse_check(tree);
}
