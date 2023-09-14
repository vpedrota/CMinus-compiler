#!/bin/bash

# Compila o projeto usando o makefile
make

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    # Executa o executável passando o caminho do arquivo de entrada
    ./cminus programas/lab_so/vetores/vetores.txt
else
    echo "A compilação falhou."
fi