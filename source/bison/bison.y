%{

// Importação das bibliotecas 
#define YYSTYPE TreeNode*
#include "globals.h"
#include "scan.h"
#include "arvore.h"
#include "symtab.h"

int yyerror(char *s);
static TreeNode *root;
static int savedLineNo;

%}

// Palavras chave para a linguagem C-
%token ASSIGN ELSE IF INT RETURN VOID WHILE

// Simbolos especiais
%token PLUS SUB MULT DIV LT LET GT GET COMP DIF PV VIR LPAR RPAR LCOL RCOL LCHA RCHA RESTO

// Marcadores
%token ID NUM

%token ERR

%%

programa : declaracao_lista   {root = $1;} ;
declaracao_lista : declaracao_lista declaracao
                  {
                    TreeNode* t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL) t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                    else $$ = $2;
                  }
                 | declaracao {$$ = $1;} ;

declaracao : var_declaracao {$$ = $1;} | fun_declaracao {$$ = $1;} ;

var_declaracao : tipo_especificador ident PV 
              {
                $$ = newExpNode(TypeK);
                $$->type = $1->type;
                $$->attr.name = $1->attr.name;
                $$->child[0] = $2;
                $2->nodekind = StmtK;
                $2->kind.stmt = VarK;
                $2->type = $1->type;
						  }
               | tipo_especificador ident LCOL num RCOL PV
                {
                  $$ = newExpNode(TypeK);
                  $$->type = $1->type;
                  $$->attr.name = $1->attr.name;
                  $$->child[0] = $2;
                  $2->nodekind = StmtK;
                  $2->kind.stmt = VarK;
                  $2->type = $1->type;
                  $2->attr.len = $4->attr.val;
                  $2->attr.vetor = 1;
                };

fun_declaracao : tipo_especificador ident LPAR params RPAR composto_decl
                {
                  $$ = newExpNode(TypeK);
                  $$->type = $1->type;
                  $$->attr.name = $1->attr.name;
                  $$->child[0] = $2;
                  $2->child[0] = $4;
                  $2->child[1] = $6;
                  $2->nodekind = StmtK;
                  $2->kind.stmt = FunK;
                  $2->type = $1->type;
                  addScopes($$, $2->attr.name);
                }

params : param_lista { $$ = $1; } | VOID
        {
				  $$ = newExpNode(TypeK);
          $$->attr.name = "void";
          $$->child[0] = NULL;
				}
       ;
param_lista : param_lista VIR param 
            {
              TreeNode* t = $1;
              if(t != NULL){
                while(t->sibling != NULL)
                  t = t->sibling;
                t->sibling = $3;
                $$ = $1;
              }
              else 
                $$ = $3;
            }
            | param 
            {
              $$ = $1;
            };

tipo_especificador : INT
                  {
                    $$ = newExpNode(TypeK);
                    $$->attr.name = "inteiro";
                    $$->type = IntegerK;
                  }
                  | VOID
                  {
                    $$ = newExpNode(TypeK);
                    $$->attr.name = "void";
                    $$->type = VoidK;
                  }
                  ;
param : tipo_especificador ident
      {
        $$ = newExpNode(TypeK);
        $$->child[0]= $2;
        $$->type = $1->type;
        $$->attr.name = $1->attr.name;
        $2->nodekind = StmtK;
        $2->kind.stmt = VarK;
        $2->type = $1->type;

      }
      | tipo_especificador ident LCOL RCOL
      {
        $$ = newExpNode(TypeK);
        $$->child[0] = $2;
        $$->type = $1->type;
        $$->attr.name = "inteiro_parametro_vetor";
        $2->nodekind = StmtK;
        $2->type = IntegerVetorK;
        $2->kind.exp = VetK;
      }
      ;
composto_decl : LCHA local_declaracoes statement_lista RCHA
              {
                TreeNode* t = $2;
                if(t != NULL){
                  while(t->sibling != NULL)
                  t = t->sibling;
                  t->sibling = $3;
                  $$ = $2;
                } 
                else $$ = $3;
              }
              | LCHA local_declaracoes RCHA //pois podem ser vazio
              {
                $$ = $2;
              }
              | LCHA statement_lista RCHA //pois podem ser vazio
              {
                $$ = $2;
              }
              | LCHA RCHA {}            //pois podem ser vazio
              ;
local_declaracoes : local_declaracoes var_declaracao 
                  {
                    TreeNode* t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL) t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }else $$ = $2;
                  }
                  | var_declaracao
                  {
                    $$ = $1;
                  }
                   /* vazio, apaguei pois estava dando erro :/ */
                  ;
statement_lista : statement_lista statement 
                {
                    TreeNode* t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL)
                      t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }else $$ = $2;
                  }
                  | statement
                  {
                    $$ = $1;
                  }
                /* vazio, apaguei pois estava dando erro :/ */
                ;
statement : expressao_decl
          {
            $$ = $1;
          }
          | composto_decl 
          {
            $$ = $1;
          }
          | selecao_decl 
          {
            $$ = $1;
          }
          | iteracao_decl 
          {
            $$ = $1;
          }
          | retorno_decl
          {
            $$ = $1;
          }
          ;
expressao_decl : expressao PV 
                {
                  $$ = $1;
                }
               | PV
               ;
selecao_decl : IF LPAR expressao RPAR statement 
              {
                $$ = newStmtNode(IfK);
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
             | IF LPAR expressao RPAR statement ELSE statement
             {
                $$ = newStmtNode(IfK);
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[2] = $7;
             }
             ;
iteracao_decl : WHILE LPAR expressao RPAR statement
              {
                $$ = newStmtNode(WhileK);
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
              ;
retorno_decl : RETURN PV 
              {
                $$ = newStmtNode(ReturnK);
              }
             | RETURN expressao PV
              {
                $$ = newStmtNode(ReturnK);
                $$->child[0] = $2;
              }
             ;
expressao : var ASSIGN expressao 
          {
            $$ = newStmtNode(AssignK);
            $$->attr.name = $1->attr.name;
            $$->child[0] = $1;
            $$->child[1] = $3;
          }
          |
          var ASSIGN ativacao 
          {
            $$ = newStmtNode(AssignK);
            $$->attr.name = $1->attr.name;
            $$->child[0] = $1;
            $$->child[1] = $3;
          }
          | simples_expressao
          {
            $$ = $1;
          }
          ;
var : ident 
    {
      $$ = $1;
    }
    | ident LCOL expressao RCOL
    {
      $$ = $1;
      $$->child[0] = $3;
      $$->kind.exp = VetK;
      $$->type = IntegerK;
    }
    ;
simples_expressao : soma_expressao relacional soma_expressao 
                  {
                      $$ = $2;
                      $$->child[0] = $1;
                      $$->child[1] = $3;
                  }
                  | soma_expressao
                  {
                    $$ = $1;
                  }
                  ;
relacional : LET 
            {
              $$ = newExpNode(OpK);
              $$->attr.op = LET;                            
              $$->type = BooleanK;
            }
           | LT 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = LT;                            
						$$->type = BooleanK;
           }
           | GT 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = GT;                            
						$$->type = BooleanK;
           }
           | GET 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = GET;                            
						$$->type = BooleanK;
           }
           | COMP 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = COMP;                            
						$$->type = BooleanK;
           }
           | DIF
           {
            $$ = newExpNode(OpK);
            $$->attr.op = DIF;                            
						$$->type = BooleanK;
           }
           ;
soma_expressao : soma_expressao soma termo 
              {
                $$ = $2;
                $$->child[0] = $1;
                $$->child[1] = $3;
              }
               | termo
               {
                $$ = $1;
               }
               ;
soma : PLUS 
      {
        $$ = newExpNode(OpK);
        $$->attr.op = PLUS;  
      }
     | SUB
     {
      $$ = newExpNode(OpK);
      $$->attr.op = SUB;  
     }
     ;
termo : termo mult fator
      {
        $$ = $2;
        $$->child[0] = $1;
        $$->child[1] = $3;
      }
      | fator
      {
        $$ = $1;
      }
      ;
mult : MULT 
      {
        $$ = newExpNode(OpK);
        $$->attr.op = MULT; 
      }
      | DIV
      {
        $$ = newExpNode(OpK);
        $$->attr.op = DIV; 
      } 
     ;
fator : LPAR expressao RPAR 
      {
        $$ = $2;
      }
      | var 
      {
        $$ = $1;
      }
      | ativacao 
      {
        $$ = $1;
      }
      | num
      {
        $$ = $1;
      }
      ;
ativacao : ident LPAR arg_lista RPAR
          {
            $$ = $1;
            $$->child[0] = $3;
            $$->nodekind = StmtK;
            $$->kind.stmt = CallK;
          }
          | ident LPAR RPAR
          {
            $$ = $1;
            $$->nodekind = StmtK;
            $$->kind.stmt = CallK;
          }
          ;
arg_lista : arg_lista VIR expressao 
          {
            TreeNode* t = $1;
            if(t != NULL){
              while(t->sibling != NULL)
              t = t->sibling;
              t->sibling = $3;
              $$ = $1;
            } else $$ = $3;
          }
          | expressao
          {
            $$ = $1;
          }
          ;
ident : ID
      {
      $$ = newExpNode(IdK);
      $$->attr.name = copyString(yytext);
      }
;
num : NUM
      {
        $$ = newExpNode(ConstK);
        $$->attr.val = atoi(yytext);
        $$->type = IntegerK;
      }
;

%%


int yyerror(char *msg){
    printf("ERRO SINTÁTICO: %s LINHA: %d\n", yytext, lineno);
    exit(-1);
}

TreeNode* parse(){
    yyparse();
    return root;
}