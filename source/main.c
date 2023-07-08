
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "scan.h"
#include "arvore.h"
#include "symtab.h"
#include "analyze.h"
#include "codegen.h"

int lineno = 1;
TreeNode* arvore;

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
    printf("Análise Léxica realizada com sucesso. \n");
    // Voltando o ponteiro para o início para realizar a análise sintática
    lineno = 1;
    fseek(stdin, 0, SEEK_SET); 
    
    // Realizando construção da árvore sintática
    printf("Imprimindo análise sintática.\n");
    arvore = parse();
    printTreeFile(arvore);

    // Realizando a construação da tabela de símbolos
    printf("Imprimindo tabela de simbolos.\n");
    buildSymtab(arvore);
    
    printf("Realizando análise semântica.\n");
    analyze(arvore);
    printf("Análise semântica concluída com sucesso.\n");

    printf("Iniciando código intermediário.\n");

    // Encontrando o scopo da função main, apenas as intruções dentro deste escopo
    // devem ser convertidas

    freopen("analises/codigo_intermediario.txt", "w", stdout);
    codeGen(arvore);
    freopen("/dev/tty", "w", stdout); 
    printf("Código intermediário gerado com sucesso.\n");
    // Fechando arquivos abertos

    // Executando gerador de código assembly
    system("python gerador_asm.py");
    printf("Código binário gerado com sucesso.\n");
    fclose(input);
    return 0;
}