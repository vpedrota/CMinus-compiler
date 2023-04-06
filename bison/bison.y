

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

    var-declaracao: INT id PV {
                        $$ = newExpNode(TypeK);
                        $$->type = IntegerK;
                        $$->attr.name = "inteiro";
                        $$->child[0] = $2;
                        $2->nodekind = StmtK;
                        $2->kind.stmt = VarK;
                        $2->type = IntegerK;
                    } 
                    | INT id LCOL num RCOL PV {
                        $$ = newExpNode(TypeK);
                        $$->type = IntegerK;
                        $$->attr.name = "inteiro";
                        $$->child[0] = $2;
                        $2->nodekind = StmtK;
                        $2->kind.stmt = VarK;
                        $2->type = IntegerK; 
                        $2->attr.len = $4->attr.val;
                    };

    num: NUM {
        $$ = NULL;
    }
    id: ID { 
      $$ = newExpNode(IdK);
      $$->attr.name = copyString(yytext);
    };

    tipo-especificador: INT {
                            $$ = newExpNode(TypeK);
                            $$->attr.name = "inteiro";
                            $$->type = IntegerK;
                        }
                        | VOID {
                            $$ = newExpNode(TypeK);
                            $$->attr.name = "void";
                            $$->type = VoidK;
                        }

    fun-declaracao: INT id LPAR params RPAR composto-decl{
       $$ = newExpNode(TypeK);
        $$->type = IntegerK;
        $$->attr.name = "inteiro";
        $$->child[0] = $2;
        $2->child[0] = $4;
        $2->child[1] = $6;
        $2->nodekind = StmtK;
        $2->kind.stmt = FunK;
        $2->type = IntegerK;
        $4->type = IntegerK;
    } | VOID id LPAR params RPAR composto-decl{
        $$ = newExpNode(TypeK);
        $$->type = VoidK;
        $$->attr.name = "void";
        $$->child[0] = $2;
        $2->child[0] = $4;
        $2->child[1] = $6;
        $2->nodekind = StmtK;
        $2->kind.stmt = FunK;
    }

    params: param-lista {$$ = $1;} 
    | VOID {
        $$ = newExpNode(TypeK);
        $$->attr.name = "void";
        $$->child[0] = NULL; 
    }

    param-lista: param-lista PV param {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $3;
            $$ = $1;
        } else{
            $$ = $3;
        }
    } | param {$$ = $1;};
    param: tipo-especificador ID {
        $$ = newExpNode(TypeK);
        $$->child[0]= $2;
        $$->type = $1->type;
        $$->attr.name = $1->attr.name;
        $2->nodekind = StmtK;
        $2->kind.stmt = VarK;
        $2->type = $1->type;
    } | tipo-especificador ID LCOL RCOL {
        $$= newExpNode(TypeK);
        $$->child[0]= $2;
        $$->type = $1->type;
        $$->attr.name = $1->attr.name;
        $2->nodekind = StmtK;
        $2->type = $1->type;
        $2->kind.stmt = VetK;
    }

    composto-decl: LCHA local-declaracoes statement-lista RCHA{
        TreeNode* t = $2;
        if(t != NULL){
            while(t->sibling != NULL)
            t = t->sibling;
            t->sibling = $3;
            $$ = $2;
        } 
        else $$ = $3;
    }

    local-declaracoes: local-declaracoes var-declaracao {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $2;
            $$ = $1;
        } else{
            $$ = $2;
        }
    }  | var-declaracao {$$ = $1;}

    statement-lista: statement-lista statement {
        TreeNode* t = $1;
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = $2;
            $$ = $1;
        } else{
            $$ = $2;
        }
    } | statement {$$ = $1;}

    statement: 
        expressao-decl {$$ = $1;}
        | composto-decl {$$ = $1;}
        | selecao-decl {$$ = $1;}
        | iteracao-decl {$$ = $1;}
        | retorno-decl {$$ = $1;};
    expressao-decl: expressao PV { $$ = $1; } | PV;
    selecao-decl: IF LPAR expressao RPAR statement {
        $$ = newStmtNode(IfK);
        $$->child[0] = $3;
        $$->child[1] = $5;
    } 
    | IF LPAR expressao RPAR statement ELSE statement {
        $$ = newStmtNode(IfK);
        $$->child[0] = $3;
        $$->child[1] = $5;
        $$->child[2] = $7;
    };

    iteracao-decl: WHILE LPAR expressao RPAR statement {
        $$ = newStmtNode(WhileK);
        $$->child[0] = $3;
        $$->child[1] = $5;
    };

    retorno-decl: RETURN PV {
        $$ = newStmtNode(ReturnK);
    } | RETURN expressao PV {
        $$ = newStmtNode(ReturnK);
        $$->child[0] = $2;
    };

    expressao: var ASSIGN expressao {
        $$ = newStmtNode(AssignK);
        $$->attr.name = $1->attr.name;
        $$->child[0] = $1;
        $$->child[1] = $3;
    } | simples-expressao { $$ = $1;};

    var: id { $$ = $1;} 
    
    | ID LCOL expressao RCOL {
        $$ = $1;
        $$->child[0] = $3;
        $$->kind.exp = VetK;
        $$->type = IntegerK;
    };

    simples-expressao: soma-expressao relacional soma-expressao {
        $$ = $2;
        $$->child[0] = $1;
        $$->child[1] = $3;
    }| soma-expressao { $$ = $1; };

    relacional: LET { 
        $$ = newExpNode(OpK);
        $$->attr.op = LET;                            
		$$->type = BooleanK;
    } 
    | LT  {
        $$ = newExpNode(OpK);
        $$->attr.op = LT;                            
		$$->type = BooleanK;
     
    } 
    | GT  {
        $$ = newExpNode(OpK);
        $$->attr.op = GT;                            
		$$->type = BooleanK; 
    }
    | GET {
        $$ = newExpNode(OpK);
        $$->attr.op = GET;                            
		$$->type = BooleanK; 
    }
    | COMP {
        $$ = newExpNode(OpK);
        $$->attr.op = COMP;                            
		$$->type = BooleanK; 
    }
    | DIF {
        $$ = newExpNode(OpK);
        $$->attr.op = DIF;                            
		$$->type = BooleanK;
    };

    soma-expressao: soma-expressao soma termo {
        $$ = alocaNo();
        $$->child[0] = $1;
        $$->child[1] = $2;
        $$->child[2] = $3;
    } | termo { $$ = $1; };

    soma: PLUS {
        $$ = newExpNode(OpK);
        $$->attr.op = PLUS;  
    }
    | SUB {
        $$ = newExpNode(OpK);
        $$->attr.op = SUB;  
    };

    termo: termo mult fator {
        $$ = $2;
        $$->child[0] = $1;
        $$->child[1] = $3;
    } | fator { $$ = $1;};

    mult: MULT {
        $$ = newExpNode(OpK);
        $$->attr.op = MULT; 
    } | DIV {
        $$ = newExpNode(OpK);
        $$->attr.op = DIV; 
    };

    fator: LPAR expressao RPAR { $$ = $2; } 
    | var { $$ = $1; } 
    | ativacao { $$ = $1; } 
    | NUM {$$ = alocaNo();};

    ativacao: id LPAR args RPAR {
        $$ = $1;
        $$->child[0] = $3;
        $$->nodekind = StmtK;
        $$->kind.stmt = CallK;
    }
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

