
#include <stdio.h>
#include "globals.h"

int lineno = 1;

int main(int argc, char * argv[]){
    
    // Verificando se a quantidade de parâmetros na chamada está correta
    if(argc < 2){
        printf("cminus: fatal error: no input files\n");
        printf("compilation terminated.\n");
        return 1;
    }

    // Abrindo arquivo para ser compilado e verificando se ele existe
    FILE *input = fopen(argv[1], "r");
    if(input == NULL){
        printf("cminus: input file not found.\n");
        return 1;
    }
    
    // como o yylex realiza o scanner da entrada padrão então o arquivo é aberto e seu ponteiro
    // é passado para o destridor que representa a entrada padrão
    stdin = input;
    scanner();
   
    // Voltando o ponteiro para o início para realizar a análise sintática
    lineno = 1;
    fseek(stdin, 0, SEEK_SET); 
    
    yyparse();

    // Fechando arquivos abertos
    fclose(input);
    return 0;
}