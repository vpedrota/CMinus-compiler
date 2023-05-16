# Compilador C-

    Este é um compilador para a linguagem C- que permite analisar programas escritos nessa linguagem e gerar um executável. Este README fornecerá instruções sobre como rodar o projeto e executar o compilador corretamente.

## Requisitos
    Antes de começar, certifique-se de ter os seguintes requisitos instalados em seu sistema:

- GCC (GNU Compiler Collection)

## Gerar o compilador

    Para gerar o executável, execute o seguinte comando na pasta source do projeto:
``` Make ```

## Executando o compilador

    Após a geração do executável, você pode executar o compilador passando o caminho do programa a ser analisado como argumento. Por exemplo:

``` ./cminus source/analises/fatorial.txt ```

    Nesse exemplo, estamos analisando o arquivo fatorial.txt, que está localizado na pasta source/analises. Certifique-se de fornecer o caminho correto para o arquivo que deseja analisar.

## Estrutura do projeto

    Os códigos-fonte do compilador estão localizados na pasta source. Dentro dessa pasta, você encontrará os arquivos e diretórios seguintes:

    - source/analises: Esta pasta contém os arquivos que serão analisados pelo compilador. Certifique-se de adicionar os arquivos de programa que deseja analisar aqui.
    - Outros arquivos de código-fonte e cabeçalhos necessários para o funcionamento do compilador.
