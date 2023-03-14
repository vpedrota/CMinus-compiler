%{
   #include "globals.h"
   #include <string.h>
   int lineNumber = 0;
%}


DIGITO [0-9]
LETRA [a-zA-Z]
whitespace  [ \t\r]+

%%

"+" {return SUM;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return EQUAL;}
"void" {return VOID;}
"int" {return INT;}
")" {return RBRAC;}
"(" {return LBRAC;}

. {return ERR;}

%%  

int yywrap(){}

void printToken(FILE *output, int token){
   switch (token){
      case SUM: 
         fprintf(output, "SUM "); 
         break;
      case EQUAL: 
         fprintf(output, "EQUAL "); 
         break;
      case VOID: 
         fprintf(output, "VOID "); 
         break;
      case LBRAC: 
         fprintf(output, "LBRAC "); 
         break;
      case RBRAC: 
         fprintf(output, "RBRAC "); 
         break;
      default:
         fprintf(output, "unknown "); 
   }
}

int getToken(FILE *output){
   int currentToken = yylex();
   printToken(output, currentToken);
   return  currentToken;
}

void scanner(){
   FILE *output = fopen("analises/lexico.txt", "w");
   if(output == NULL){
      printf("Erro ao fazer analise lexica");
      exit(1);
   }
   while(getToken(output) != EQUAL);
   fclose(output);
}
