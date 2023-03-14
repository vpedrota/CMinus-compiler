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
. {return ERR;}

%%  

int yywrap(){}

void printToken(FILE *output, int token){
   switch (token){
      case SUM: 
         fprintf(output, "+ "); 
         break;
      case EQUAL: 
         fprintf(output, "= "); 
         break;
      case VOID: 
         fprintf(output, "VOID "); 
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
