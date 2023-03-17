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
    fun-declaracao: tipo-especificador ID LPAR params RPAR composto-decl;
    params: param-lista | VOID;
    param-lista: param-lista PV param | param;
    param: tipo-especificador ID | tipo-especificador ID LCOL RCOL;
    composto-decl: LCHA local-declaracoes statement-lista RCHA;
    local-declaracoes: local-declaracoes var-declaracao  | ;
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

