#include "globals.h"


void addScopes(TreeNode *root, char *scope){
    int i;
    
    //percorrendo árvore
    while(root != NULL){
        root->attr.scope = malloc(sizeof(char)*100);
        if(root->kind.stmt == FunK){
            strcpy(scope, root->attr.name);
        }
        strcpy(root->attr.scope, scope);
        for (i=0;i<MAXCHILDREN;i++)
            addScopes(root->child[i], scope);
        root = root->sibling;
    }
}