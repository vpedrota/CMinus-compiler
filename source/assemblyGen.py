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


if __name__ == "__main__":

    #Abrindo arquivo para imprimir resposta
    saida = open("analises/codigo_assembly.txt", "w")


    # Realizando leitura das quádruplas para o mapeamento das instruções em assembly
    quadruplas = ler_quadruplas()
    posicao_main = encontra_label(quadruplas)

    saida.write("jump " + str(posicao_main))

    saida.close()

