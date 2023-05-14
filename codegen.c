#include "globals.h"
#include "codegen.h"

int contador = 0;

void register_index(){
    contador = (contador + 1) % 32;
}


void generateStmt(TreeNode *tree){
    switch (tree->kind.stmt) { 

        case FunK:
            printf("Função %s\n", tree->attr.name);
            codeGen(tree->child[1]);
            break;
        case VarK:
            // printf("Variável %s\n", tree->attr.name);
            break;
        case AssignK:
            codeGen(tree->child[1]);

            printf("\nASSIGN %s\n", tree->attr.name);
            break;
        default:
            printf("não mapeado - stmt\n");
            break;

    }
}

void generateExp(TreeNode *tree){
    switch (tree->kind.exp)
    {
    case TypeK:
        printf("declaração\n");
        codeGen(tree->child[0]);
        break;
    case IdK:
        printf("s\n");
        break;
    case ConstK:
        printf("const");
        break;
    case OpK:
        codeGen(tree->child[0]);
        if(tree->child[0]->kind.exp == OpK){
            printf("t%d", contador);
        }
        printf(" operador ");
        codeGen(tree->child[1]);
        printf(" RESULT t%d", contador);
        register_index();
        printf("\n");
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