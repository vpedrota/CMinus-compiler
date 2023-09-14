%{
   #include "globals.h"
   #include "scan.h"
%}


DIGITO [0-9]
numero {DIGITO}+
LETRA ([a-z]|[A-Z])
identificador ({LETRA}|_)({LETRA}|_|{DIGITO})*
whitespace  [ \t]+

%%

"+" {return PLUS;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"=" {return ASSIGN;}
"%" {return RESTO;}
";" {return PV;}
"," {return VIR;}
"void" {return VOID;}
"int" {return INT;}
"if" {return IF;}
"return" {return RETURN;}
"else" {return ELSE;}
"while" {return WHILE;}
")" {return RPAR;}
"(" {return LPAR;}
"]" {return RCOL;}
"[" {return LCOL;}
"}" {return RCHA;}
"{" {return LCHA;}
"!=" {return DIF;}
"<" {return LT;}
">" {return GT;}
"<=" {return LET;}
">=" {return GET;}
"==" {return COMP;}
"/*" {
   char c;
      while(1){
      c = input();
      if(c == 0) break;
      if(c =='\n') lineno++;
      if(c =='*'){
         c = input();
         if(c=='/') break;
      }
   }
}
\n	{lineno++;}
{numero}  {return NUM;}
{whitespace} {}
{identificador} {return ID;}
. {return ERR;}


%%  

int yywrap(){}

void printT(int value){
   switch(value){
      case GT:
         printf(">\n");
         break;
      default:
         printf("Erro\n");
   }
}

void printToken(FILE *output, int token, char *tokenString){
   switch (token){
      case COMP: 
         fprintf(output, "%d: COMP  \n", lineno); 
         break;
      case ELSE: 
         fprintf(output, "%d: ELSE  \n", lineno); 
         break;
      case INT: 
         fprintf(output, "%d: INT  \n", lineno); 
         break;
      case PLUS: 
         fprintf(output, "%d: PLUS  \n", lineno); 
         break;
      case SUB: 
         fprintf(output, "%d: SUB  \n", lineno); 
         break;
      case MULT: 
         fprintf(output, "%d: MULT  \n", lineno); 
         break;
      case WHILE: 
         fprintf(output, "%d: WHILE  \n", lineno); 
         break;
      case RCHA: 
         fprintf(output, "%d: RCHA  \n", lineno); 
         break;
      case LCHA: 
         fprintf(output, "%d: LCHA  \n", lineno); 
         break;
      case IF: 
         fprintf(output, "%d: IF  \n", lineno); 
         break;
      case PV: 
         fprintf(output, "%d: PV  \n", lineno);  
         break;
      case VIR: 
         fprintf(output, "%d: VIR  \n", lineno);  
         break;
      case ID: 
         fprintf(output, "%d: ID, name = %s \n", lineno, tokenString);  
         break;
      case NUM: 
         fprintf(output, "%d: NUM, value = %s \n", lineno, tokenString);  
         break;
      case RETURN: 
         fprintf(output, "%d: RETURN  \n", lineno);  
         break;
      case DIF: 
         fprintf(output, "%d: DIF  \n", lineno);  
         break;
      case GT: 
         fprintf(output, "%d: GT  \n", lineno);  
         break;
      case LT: 
         fprintf(output, "%d: LT  \n", lineno);  
         break;
      case GET: 
         fprintf(output, "%d: GT  \n", lineno);  
         break;
      case LET: 
         fprintf(output, "%d: LT  \n", lineno);  
         break;
      case ASSIGN: 
         fprintf(output, "%d: ASSIGN  \n", lineno);  
         break;
      case VOID: 
         fprintf(output, "%d: VOID   \n", lineno);  
         break;

      case RESTO: 
         fprintf(output, "%d: RESTO   \n", lineno);  
         break;
      case LPAR: 
         fprintf(output, "%d: LPAR  \n", lineno);  
         break;
      case RPAR: 
         fprintf(output, "%d: RPAR  \n", lineno);  
         break;
      case RCOL: 
         fprintf(output, "%d: RCOL  \n", lineno);  
         break;
      case LCOL: 
         fprintf(output, "%d: LCOL  \n", lineno);  
         break;
      case ERR:
         fprintf(output, "%d: ERR  \n", lineno); 
         printf("ERRO LÉXICO: %s LINHA: %d\n", tokenString, lineno);
         exit(1);
         break;
      case ENDFILE:
         break;
      default:
         fprintf(output, "%d: unknown  \n", lineno);  
   }
}

int getToken(FILE *output){
   int currentToken = yylex();
   if(output != NULL)
      printToken(output, currentToken, yytext);
   return  currentToken;
}

void scanner(){
   FILE *output = fopen("analises/lexico.txt", "w");
   if(output == NULL){
      printf("Erro ao fazer analise lexica");
      exit(1);
   }
   while(getToken(output) != ENDFILE);
   fclose(output);
}
