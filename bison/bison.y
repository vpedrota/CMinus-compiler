%{
#define YYSTYPE TreeNode*
#include "globals.h"
#include "arvore.h"

int yyerror(char *s);
static TreeNode *root;

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

    programa: declaracao-lista { root =  $1;};
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
    declaracao: var-declaracao {$$ = $1;}  | fun-declaracao {$$ = $1;};
    var-declaracao: INT ID PV {
        $$ = alocaNo();
        $$->child[0] = $1;
    } | INT ID LCOL NUM RCOL PV {
        $$ = alocaNo();
        $$->child[0] = $1;
    };
    tipo-especificador: INT {$$ = alocaNo();} | VOID {$$ = alocaNo();};
    fun-declaracao: tipo-especificador ID {
        $$ = alocaNo();
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
    local-declaracoes: local-declaracoes var-declaracao  | {$$ = NULL;};
    statement-lista: statement-lista statement | ;
    statement: expressao-decl | composto-decl | selecao-decl | iteracao-decl | retorno-decl;
    expressao-decl: expressao PV | PV;
    selecao-decl: IF LPAR expressao RPAR statement | IF LPAR expressao RPAR statement ELSE statement;
    iteracao-decl: WHILE LPAR expressao RPAR statement;
    retorno-decl: RETURN PV | RETURN expressao PV;
    expressao: var ASSIGN expressao | simples-expressao;
    var: ID | ID LCOL expressao RCOL;
    simples-expressao: soma-expressao relacional soma-expressao | soma-expressao;
    relacional: LET | LT | GT | GET | COMP | DIF;
    soma-expressao: soma-expressao soma termo | termo;
    soma: PLUS | SUB;
    termo: termo mult fator | fator;
    mult: MULT | DIV;
    fator: LPAR expressao RPAR | var | ativacao | NUM;
    ativacao: ID LPAR args RPAR;
    args: arg-lista | ;
    arg-lista: arg-lista VIR expressao | expressao; 

%%

int yyerror(char *msg){
    printf("ERRO SINTÁTICO: %s LINHA: %d\n", yytext, lineno);
}

TreeNode* parse(){
    yyparse();
    return root;
}

