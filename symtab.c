#include "globals.h"
#define TABLE_SIZE 1000

typedef struct lineno_list {
    int value;
    struct lineno_list *next;
} Lineno_list;


typedef struct node {
    char* name;
    struct lineno_list *first;
    struct node* next;
} Node;

typedef struct hash_table_list {
    char *scopeName;
    Node** table;
    struct hash_table_list *next;
} Hash_table_list;

// Ponteiro para a tabela hash que representa o escopo
// Cada tabela hash é um escopo no programa
Hash_table_list *first = NULL;

// Função utilizada para atribuir os escopos ao nós
void addScopes(TreeNode *root, char *scope){
    int i;
    while(root != NULL){
        root->attr.scope = scope;    
        for (i=0;i<MAXCHILDREN;i++)
            addScopes(root->child[i], scope);
        root = root->sibling;
    }
}

// Função hash simples que retorna o índice do nome fornecido
int hash(char* name) {
    int sum = 0;
    for (int i = 0; i < strlen(name); i++) {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}

// Função para criar um novo nó
Node* create_node(TreeNode *t) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->name = (char*) malloc(strlen(t->attr.name) + 1);
    strcpy(new_node->name, t->attr.name);
    new_node->first = malloc(sizeof(Lineno_list));
    new_node->first->value = t->lineno;
    new_node->first->next = NULL;
    new_node->next = NULL;
    return new_node;
}


// Função para inserir um nó na tabela hash
void insert_node(Node** table, TreeNode *t) {
    int index = hash(t->attr.name);
    if (table[index] == NULL) {
        table[index] = create_node(t);
    } else {
        Node* current = table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(t);
    }
}


void print_ocorrencies(Node *no){
    Lineno_list *aux = no->first;
    while(aux != NULL){
        printf("%d ", aux->value);
        aux = aux->next;
    }
}

// Função para imprimir a tabela hash
void print_table(Node** table) {
    printf("Imprimindo tabela de símbolos:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            Node* current = table[i];
            while (current != NULL) {
                printf(" %s: ", current->name);
                print_ocorrencies(current);
                current = current->next;
                printf("\n");
            }
        }
    }
}


// Função para realizar a inserção dos escopos na lista de escopos
void addScope(Hash_table_list **first, char* scopeName){

    Hash_table_list *aux = *first,  *newNode = malloc(sizeof(Hash_table_list));

    newNode = malloc(sizeof(Hash_table_list));
    newNode->next = NULL;
    newNode->scopeName = malloc(sizeof(char)*(strlen(scopeName)+1));
    strcpy(newNode->scopeName, scopeName);

    newNode->table =  (Node**) malloc(sizeof(Node*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        newNode->table [i] = NULL;
    }

    if(aux == NULL){
        (*first) = newNode;
        return;
    }

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = newNode;
}

Node **return_escope(char *scope_name){

    Hash_table_list *aux = first;
    while(aux != NULL && strcmp(aux->scopeName, scope_name) != 0)
        aux = aux->next;

    if(aux == NULL) return NULL;
    return aux->table;
}

// Função que procura na tabela hash e me retorna se o valor já está presente ou não
Node* find_name(char *name, char *scope_search){

    Node* aux = NULL;
    int h = 0;

    // A prioridade de encontrar o nome é no escopo da função
    // Realizando verificação no escopo da função passada como parâmetro
    Node** table_scope = return_escope(scope_search);
    Node** table_global = return_escope("global");
    
    if(table_scope != NULL){
        h = hash(name);
        aux = table_scope[h];
        while(aux != NULL && strcmp(aux->name, name) != 0)
            aux = aux->next;
        if(aux != NULL) return aux;
    }

    if(table_global != NULL){
        h = hash(name);
        aux = table_global[h];
        while(aux != NULL && strcmp(aux->name, name) != 0)
            aux = aux->next;
        if(aux != NULL) return aux;
    }

    return 0;
}

void add_new_lineno(Node *no,int lineno){
    Lineno_list *aux = no->first;
    Lineno_list *new_node = malloc(sizeof(Lineno_list));
    new_node->next = NULL;
    new_node->value = lineno;
    while (aux->next!=NULL) {
        aux = aux->next;
    }
    aux->next = new_node;
}

void insert_node_symtab( TreeNode * t, char *scope ) {
    Node **table = NULL;
    Node *aux = NULL;
    switch (t->nodekind) { 
        case StmtK:
            switch (t->kind.stmt){ 
                case VarK:
                    if (find_name(t->attr.name, t->attr.scope) == NULL){
                        table = return_escope(t->attr.scope);
                        insert_node(table, t);
                    }
                    else{
                        printf("Redeclaração de varivável\n");
                        exit(-1);
                    }
                    break;

                case FunK:
                    if(find_name(t->attr.name, "global") == NULL){  
                        if(strcmp(t->attr.scope, "global") != 0){
                            addScope(&first, t->attr.name);
                        }
                        table = return_escope("global");
                        insert_node(table, t);
                    }
                    else{
                        printf("Redeclaração de Função\n");
                        exit(-1);
                    }
                    break;

                case CallK:
                    aux = find_name(t->attr.name, t->attr.scope);
                    if(aux != NULL){
                        add_new_lineno(aux, t->lineno);
                    } else {
                        printf("Função não declarada\n");
                        exit(1);
                    }
                    break;
                
                default:
                    break;
            }
            break;
        case ExpK:
            switch (t->kind.exp){
            case IdK:
                aux = find_name(t->attr.name, t->attr.scope);
                if(aux != NULL){
                     add_new_lineno(aux, t->lineno);
                } else {
                    printf("Variável não declarada\n");
                    exit(1);
                }
                break;
            case VetK:
                aux = find_name(t->attr.name, t->attr.scope);
                if(aux != NULL){
                     add_new_lineno(aux, t->lineno);
                } else {
                    printf("Variável não declarada\n");
                    exit(1);
                }
                break;
            default:
                break;
            }

        default:
            break;
    }
}

void transverse(TreeNode *tree){
   
    int i; 
    if (tree != NULL){
        insert_node_symtab(tree, tree->attr.scope);
        for (i=0;i<MAXCHILDREN;i++)
            transverse(tree->child[i]);

        tree = tree->sibling;
        transverse(tree);
    }
}

void buildSymtab(TreeNode *root){

    Hash_table_list *aux;
    FILE *f = fopen("analises/tabela_simbolos.txt", "w");

    // Adicionando escopo global
    addScope(&first, "global");

    // Adiconando as funções de input e output
    TreeNode t;
    t.kind.stmt = FunK;
    t.nodekind = StmtK;
    t.attr.name = "input";
    t.attr.scope = "global";
    insert_node_symtab(&t, "global");

    t.attr.name = "output";
    insert_node_symtab(&t, "global");
    
    // Percorrendo e inserindo símbolos na árvore
    transverse(root);

    // Escrevendo tabela de símbolos no arquivo
    aux = first;
    while(aux != NULL){
        print_table(aux->table);
        aux = aux->next;
    }
    fclose(f);
}