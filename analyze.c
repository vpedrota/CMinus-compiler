#include "globals.h"
#include "symtab.h"

void check_node(TreeNode *node){
    Node* aux = NULL;
    switch (node->nodekind) {

    case StmtK:
        switch (node->kind.stmt) {

        case AssignK:

            if(node->child[1]->kind.exp == ConstK || node->child[1]->kind.exp == OpK)
                break;
                
            aux = find_name(node->child[1]->attr.name, node->child[1]->attr.scope);
            if(aux->type != IntegerK ){
                printf("Assign entre variável e retorno de void\n");
                exit(1);
            }
            break;


        case ConstK:
            node->type = IntegerK;
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
        switch (node->kind.exp)
        {
        case OpK:

            //printf("%s", node->child[0]->attr.name);

            if(node->child[1]->type == IntegerK)
                printf("1%s", node->child[1]->attr.name);

            if(node->child[0]->type == IntegerK)
                printf("-%s", node->child[0]->attr.name);

            if(node->child[0]->type != IntegerK || node->child[1]->type != IntegerK){
                printf("OPERAÇÃO ARITMÉTICA ENTRE DOIS VALORES NÃO INTEIROS");
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
