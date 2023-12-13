#include "globals.h"
#include "symtab.h"

#define TABLE_SIZE 1000

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
    new_node->type = t->type;
    new_node->stmt = t->kind.stmt;
    new_node->vetor = 0;
    return new_node;
}


// Função para inserir um nó na tabela hash
void insert_node(Node** table, TreeNode *t) {
    int index = hash(t->attr.name);
    Node* current, *aux;
    if (table[index] == NULL) {
        aux = create_node(t);
        table[index] = aux;
    } else {
        current = table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        aux =  create_node(t);
        current->next = aux;
    }

    if(t->attr.vetor){
        aux->vetor = t->attr.len;
    }

}


void print_ocorrencies(Node *no, FILE *f){
    Lineno_list *aux = no->first;
    while(aux != NULL){
        fprintf(f, "%d ", aux->value);
        aux = aux->next;
    }
}

void print_table_csv(Hash_table_list *table_list, FILE *f) {
    Node** table = table_list->table;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {  
            Node* current = table[i];
            while (current != NULL) {
                fprintf(f, "%s,%s,", current->name, table_list->scopeName);
                if(current->type == IntegerK){
                    fprintf(f, "inteiro,");
                }
                else if(current->type == IntegerVetorK) {
                    fprintf(f, "VetorParametroInteiro,");
                }
                else {
                    fprintf(f, "void,");
                }
                if(current->stmt == FunK){
                    fprintf(f, "Função,");
                }
                else if(current->stmt == VarK){
                    if(current->vetor){
                        fprintf(f, "Vetor,");
                    }else{
                        fprintf(f, "Variável,");
                    }
                    
                }
                else{
                    fprintf(f, "Tipo não mapeado,");
                }
               
                fprintf(f, "%d,", current->vetor);
                
                print_ocorrencies(current, f);
                current = current->next;
                fprintf(f, "\n");
            }
        }
    }
}

// Função para imprimir a tabela hash
void print_table(Hash_table_list *table_list, FILE *f) {
    Node** table = table_list->table;
    if(table == NULL) return;
    fprintf(f, "+---------------------+---------------------+---------------------+---------------------+---------------------+\n");
    fprintf(f, "| %-20s | %-20s | %-20s | %-20s | %-20s | \n", "Nome", "Escopo", "Tipo", "Tipo" , "Ocorrências");
    fprintf(f, "+---------------------+---------------------+---------------------+---------------------+---------------------+\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {  
            Node* current = table[i];
            while (current != NULL) {
                fprintf(f, "| %-20s | %-20s |", current->name, table_list->scopeName);
                if(current->type == IntegerK){
                    fprintf(f, " %-20s |", "inteiro");
                } else {
                    fprintf(f, " %-20s |", "void");
                }
                if(current->stmt == FunK){
                    fprintf(f, " %-20s |", "Função");
                }
                else if(current->stmt == VarK){
                    fprintf(f, " %-20s |", "Variável");
                }
                else{
                    fprintf(f, " %-20s |", "Tipo não mapeado");
                }
               
                print_ocorrencies(current, f);
                current = current->next;
                fprintf(f, "\n");
            }
        }
    }
    fprintf(f, "\n\n");
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
                        printf("ERRO SEMÂNTICO: Redeclaração da Função %s\n", t->attr.name);
                        exit(-1);
                    }
                    break;

                case CallK:
                    aux = find_name(t->attr.name, t->attr.scope);
                    if(aux != NULL && aux->stmt == FunK){
                        add_new_lineno(aux, t->lineno);
                        t->type = aux->type;
                    }else {
                        printf("ERRO SEMÂNTICO: Função %s não declarada\n", t->attr.name);
                        exit(-1);
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
                if(aux != NULL && aux->stmt == VarK){
                     add_new_lineno(aux, t->lineno);
                }
                else if(aux != NULL && aux->stmt == FunK){
                    printf("Erro semântico: chamada inválida de função: %s\n", t->attr.name);
                    exit(1);
                } else {
                    printf("Erro semântico: Variável não declarada %s\n", t->attr.name);
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
    t.attr.len = 0;
    t.type = IntegerK;
    insert_node_symtab(&t, "global");

    t.attr.name = "output";
    insert_node_symtab(&t, "global");

    t.attr.name = "set_quantum_value";
    insert_node_symtab(&t, "global");

    t.attr.name = "PC_INTERRUPTION";
    insert_node_symtab(&t, "global");

    t.attr.name = "STACK_SIZE";
    insert_node_symtab(&t, "global");
    
    t.attr.name = "change_context";
    insert_node_symtab(&t, "global");

    t.attr.name = "copy_registers_to_bank";
    insert_node_symtab(&t, "global");

    t.attr.name = "copy_registers_to_ram";
    insert_node_symtab(&t, "global");

    t.attr.name = "set_hd_track";
    insert_node_symtab(&t, "global");

    t.attr.name = "set_lcd_message";
    insert_node_symtab(&t, "global");

    t.attr.name = "set_process_bcd";
    insert_node_symtab(&t, "global");

    t.attr.name = "clean_ram";
    insert_node_symtab(&t, "global");


    // Percorrendo e inserindo símbolos na árvore
    transverse(root);

    FILE *f_csv = fopen("analises/tabela_simbolos_csv.csv", "w");
    fprintf(f_csv,  "Nome,Escopo,Tipo_var,Tipo,Tamanho,Ocorrências\n");

    // Escrevendo tabela de símbolos no arquivo
    aux = first;
    while(aux != NULL){
        print_table(aux, f);
        print_table_csv(aux, f_csv);
        aux = aux->next;
    }
    fclose(f_csv);
    fclose(f);
}