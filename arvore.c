#include "globals.h"

TreeNode* alocaNo(){
    TreeNode* No = malloc(sizeof(TreeNode));
    const char* texto = "teste";
    strcpy(No->nome,texto);
    return No;
}