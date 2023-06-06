import pandas as pd

def ler_quadruplas():
    linhas = []

    try: 
        with open("analises/codigo_intermediario.txt", "r") as arquivo:
            for linha in arquivo:
                linha = linha.replace("(", "")
                linha = linha.replace(")", "")
                linhas.append(linha.strip())
    except FileNotFoundError:
        print("Erro ao encontrar os arquivos para fazer a conversão das quádruplas")

    return linhas

def encontra_label(quadruplas, valor_procurado = "main", instrucao = "FUN"):

    for index, elemento in enumerate(quadruplas):
        partes = elemento.split(',')
        if instrucao in partes[0] and  valor_procurado in partes[2]:
            return index
        
    return -1

def gera_assembly(quadruplas, saida, tabela_simbolos):

    instructions = []
    
    for quad in quadruplas:
        
        # Pegando a instrução
        partes = quad.split(',')

        # Realizando o mapeamento das quadruplas para o assembly
        if("DIV" in partes[0]):
            instructions.append("DIV" + "\n")
        elif("FUN" in partes[0]):
            pass
        else:
            instructions.append("NÃO MAPEADO" + "\n")

    for instruction in instructions:
        saida.write(instruction)


if __name__ == "__main__":

    #Abrindo arquivo para imprimir resposta
    saida = open("analises/codigo_assembly.txt", "w")

    # CArregando a tabela de símbolos
    tabela_simbolos = pd.read_csv("./analises/tabela_simbolos_csv.csv")
    
    # Realizando leitura das quádruplas para o mapeamento das instruções em assembly
    quadruplas = ler_quadruplas()

    gera_assembly(quadruplas, saida, tabela_simbolos)

    saida.close()

