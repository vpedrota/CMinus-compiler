%{
   #include "globals.h"
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

%%  

int yywrap(){}

int getToken(){
   int currentToken = yylex();
   printf("chanmado");
   return  currentToken;
}
