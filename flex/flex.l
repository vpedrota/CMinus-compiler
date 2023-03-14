%{
   #include "globals.h"
   #include <string.h>
   int lineNumber = 0;
%}


DIGITO [0-9]
LETRA ([a-z]|[A-Z])
identificador ({LETRA}|_)({LETRA}|_|{DIGITO})*
whitespace  [ \t\r]+

%%

"+" {return SUM;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return EQUAL;}
";" {return PV;}
"," {return VIR;}
"void" {return VOID;}
"int" {return INT;}
"if" {return IF;}
"return" {return RETURN;}
"else" {return ELSE;}
")" {return RBRAC;}
"(" {return LBRAC;}
"!=" {return DIF;}
"<=" {return LT;}
">=" {return GT;}
\n	{lineNumber++;}
{whitespace} {}
{identificador} {return ID;}
. {return ERR;}


%%  

int yywrap(){}

void printToken(FILE *output, int token){
   switch (token){
      case SUM: 
         fprintf(output, "%d: SUM  \n", lineNumber); 
         break;
      case PV: 
         fprintf(output, "%d: PV  \n", lineNumber);  
         break;
      case VIR: 
         fprintf(output, "%d: VIR  \n", lineNumber);  
         break;
      case ID: 
         fprintf(output, "%d: ID  \n", lineNumber);  
         break;
      case RETURN: 
         fprintf(output, "%d: RETURN  \n", lineNumber);  
         break;
      case DIF: 
         fprintf(output, "%d: DIF  \n", lineNumber);  
         break;
      case GT: 
         fprintf(output, "%d: GT  \n", lineNumber);  
         break;
      case EQUAL: 
         fprintf(output, "%d: EQUAL  \n", lineNumber);  
         break;
      case VOID: 
         fprintf(output, "%d: VOID  \n", lineNumber);  
         break;
      case LBRAC: 
         fprintf(output, "%d: LBRAC  \n", lineNumber);  
         break;
      case RBRAC: 
         fprintf(output, "%d: RBRAC  \n", lineNumber);  
         break;
      case ERR:
         fprintf(output, "%d: ERR  \n", lineNumber); 
         break;
      case ENDFILE:
         break;
      default:
         fprintf(output, "%d: unknown  \n", lineNumber);  
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
   while(getToken(output) != ENDFILE);
   fclose(output);
}
