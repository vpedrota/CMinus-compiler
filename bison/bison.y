%{

// Importação das bibliotecas 
#define YYSTYPE TreeNode*
#include "globals.h"
#include "arvore.h"

int yyerror(char *s);
static TreeNode *root;

static int savedLineNo;
static char* savedName;

%}

/*****************************************
    Realizando a declaração dos lexemas
******************************************/

// Palavras chave para a linguagem C-
%token ELSE IF INT RETURN VOID WHILE

// Simbolos especiais
%token PLUS SUB MULT DIV LT LET GT GET COMP DIF ASSIGN PV VIR LPAR RPAR LCOL RCOL LCHA RCHA

// Marcadores
%token ID NUM

// Erro
%token ERR

%%

    programa: declaracao-lista { root =  $1; };

    declaracao-lista: declaracao-lista declaracao {
                    TreeNode* t = $1;
                    if(t != NULL){
                        while(t->sibling != NULL) { t = t->sibling;}
                        t->sibling = $2;
                        $$ = $1;
                    } else{
                        $$ = $2;
                    }
                    } | declaracao { $$ = $1; };

    declaracao: var-declaracao {$$ = $1;}  
                | fun-declaracao {$$ = $1;};

    var-declaracao: INT ID PV {
                        $$ = alocaNo();
                        $$->child[0] = $1;
                    } 
                    | INT ID LCOL NUM RCOL PV {
                        $$ = alocaNo();
                        $$->child[0] = $1;
                    };

    tipo-especificador: INT {$$ = alocaNo();} | VOID {$$ = alocaNo();};

    fun-declaracao: tipo-especificador ID {
        $$ = alocaStmt(TypeK);
        $$->type = VoidK;
        $2->nodekind = StmtK;
        strcpy($$->attr.name ,"inteiro");

    } LPAR params RPAR composto-decl {
        $$ = $3;
        $$->child[0] = $1;
        $$->child[1] = $5;
        $$->child[2] = $7;
    };
    params: param-lista {$$ = $1;} | VOID {$$ = alocaNo();};
    param-lista: param-lista PV param {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $3;
            $$ = $1;
        } else{
            $$ = $2;
        }
    } | param {$$ = $1;};
    param: tipo-especificador ID {
        $$ = alocaNo();
        $$->child[0] = $1;
    } | tipo-especificador ID LCOL RCOL {
        $$ = alocaNo();
        $$->child[0] = $1;
    };
    composto-decl: LCHA local-declaracoes statement-lista RCHA{
        $$ = alocaNo();
        $$->child[0] = $2;
        $$->child[1] = $3;
    };
    local-declaracoes: local-declaracoes var-declaracao {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $2;
            $$ = $1;
        } else{
            $$ = $2;
        }
    }  | {$$ = NULL;};
    statement-lista: statement-lista statement {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $2;
            $$ = $1;
        } else{
            $$ = $2;
        }
    } | {$$ = NULL;};
    statement: 
        expressao-decl { $$ = $1; }
        | composto-decl { $$ = $1; }
        | selecao-decl { $$ = $1; }
        | iteracao-decl { $$ = $1; }
        | retorno-decl { $$ = $1; };
    expressao-decl: expressao PV { $$ = $1; } | PV { $$ = NULL; };
    selecao-decl: IF LPAR expressao RPAR statement {
        $$ = alocaNo();
        $$->child[0] = $3;
        $$->child[1] = $5;
    } 
    | IF LPAR expressao RPAR statement ELSE statement {
        $$ = alocaNo();
        $$->child[0] = $3;
        $$->child[1] = $5;
        $$->child[2] = $7;
    };

    iteracao-decl: WHILE LPAR expressao RPAR statement {
        $$ = alocaNo();
        $$->child[0] = $3;
        $$->child[1] = $5;
    };

    retorno-decl: RETURN PV {
        $$ = alocaNo();
    } | RETURN expressao PV {
        $$ = alocaNo();
        $$->child[0] = $2;
    };

    expressao: var ASSIGN expressao {
        $$ = alocaNo();
        $$->child[0] = $1;
        $$->child[1] = $3;
    } | simples-expressao { $$ = $1;};

    var: ID {$$ = alocaNo();} | ID {
        $$ = alocaNo();
    } LCOL expressao RCOL {
        $$ = $2;
        $$->child[0] = $4;
    };

    simples-expressao: soma-expressao relacional soma-expressao {
        $$ = alocaNo();
        $$->child[0] = $1;
        $$->child[1] = $2;
        $$->child[2] = $3;
    }| soma-expressao { $$ = $1; };

    relacional: LET {$$ = alocaNo();} | LT  {$$ = alocaNo();} | GT  {$$ = alocaNo();}| GET {$$ = alocaNo();}| COMP {$$ = alocaNo();}| DIF {$$ = alocaNo();};

    soma-expressao: soma-expressao soma termo {
        $$ = alocaNo();
        $$->child[0] = $1;
        $$->child[1] = $2;
        $$->child[2] = $3;
    } | termo { $$ = $1; };
    soma: PLUS {$$ = alocaNo();}| SUB {$$ = alocaNo();};

    termo: termo mult fator {
        $$ = alocaNo();
        $$->child[0] = $1;
        $$->child[1] = $2;
        $$->child[2] = $3;
    }| fator { $$ = $1;};

    mult: MULT {$$ = alocaNo();} | DIV {$$ = alocaNo();};

    fator: LPAR expressao RPAR { $$ = $2; } | var { $$ = $1; } | ativacao { $$ = $1; } | NUM {$$ = alocaNo();};

    ativacao: ID {$$ = alocaNo();} LPAR args RPAR {
        $$ = $2;
        $$->child[0] = $4;
    };

    args: arg-lista { $$ = $1; } | { $$ = NULL; } ;
    arg-lista: arg-lista VIR expressao {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $3;
            $$ = $1;
        } else{
            $$ = $3 ;
        }
    } | expressao { $$ = $1; }; 

%%

int yyerror(char *msg){
    printf("ERRO SINTÁTICO: %s LINHA: %d\n", yytext, lineno);
}

TreeNode* parse(){
    yyparse();
    printTree(root);
    return root;
}

