# compilador para a matéria de laboratório de compiladores

## Flex - Lexical Analyzer

### Comandos para instalar flex

```
sudo apt-get update
sudo apt-get install flex
```
- Para realizar a compilação do arquivo flex de forma individual, basta utilizar o comando:

```
flex -c flex.l
```
- As seguintes convenções lexicas foram utilizadas no arquivo .l para rearlizar a criação do analisador lexico:

    - Palavras reservadas:
        - else if int return void while      