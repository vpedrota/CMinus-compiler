TreeNode* alocaNo();
TreeNode * newStmtNode(StmtKind kind);
TreeNode * newExpNode(ExpKind kind);

char* copyString(const char *string);
void printTree(TreeNode* root);
void printTreeFile(TreeNode * tree);
void printOp(FILE *output, int token);