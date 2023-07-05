typedef struct lineno_list {
    int value;
    struct lineno_list *next;
} Lineno_list;

typedef struct node {
    char* name;
    struct lineno_list *first;
    struct node* next;
    StmtKind stmt;
    ExpType type;
    int vetor;
    char* tipo_variavel;
} Node;

typedef struct hash_table_list {
    char *scopeName;
    Node** table;
    struct hash_table_list *next;
} Hash_table_list;

void addScopes(TreeNode *root, char *scope);
Node* find_name(char *name, char *scope_search);
void buildSymtab(TreeNode *root);