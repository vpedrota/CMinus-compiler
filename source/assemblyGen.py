import pandas as pd

stack_size = 0

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

    global stack_size

    # Adicionando memory position
    tabela_simbolos["memory_position"] = -1
    instructions = []
    
    for quad in quadruplas:
        
        # Pegando a instrução
        partes = quad.split(',')

        # Realizando o mapeamento das quadruplas para o assembly
        if "ALLOC" in partes[0]:
            instructions.append("ADDI r30 r30 1" + "\n")
            tabela_simbolos.loc[tabela_simbolos['Nome'] == partes[1].strip(), 'memory_position'] = stack_size
            stack_size += 1
        elif "LOAD" in partes[0]:
            search = tabela_simbolos.loc[tabela_simbolos['Nome'] == partes[2].strip()]
            if not search.empty:
                instructions.append("LW " + partes[1]+ " r29 " + str(search.values[0][5])+"\n")
        elif "CALL" in partes[0]:
            #no caso de chamadas de função deve ser analisar se é do tipo input ou output
            if partes[2].strip() == "input":
                instructions.append("INPUT" + partes[1] + "\n")
            elif partes[2].strip() == "output":
                instructions.append("OUTPUT" + partes[1] + "\n")
            else: 
                instructions.append("SW r30 r29 0 \n")
                instructions.append("CALL" + partes[2] + "\n")
                for i in range(0,int(partes[3])):
                    instructions.append("ADDI r30 r30 -1 \n")
        elif "STOREVAR" in partes[0]:
            search  = tabela_simbolos.query("Nome == '{}' and Escopo == '{}'".format(partes[2].strip(), partes[3].strip()))
            instructions.append("SW " + partes[1] + " r29 " + str(search.values[0][5])+"\n")
        elif "DIV" in partes[0]:
            instructions.append("DIV" + "\n")
        elif "PARAM" in partes[0]:
            instructions.append("SW r30 "+ partes[1]+" 0 \n")
            instructions.append("ADDI r30 r30 1 \n")
        elif "FUN" in partes[0]:
            instructions.append(".main\n")
        else:
            instructions.append("NÃO MAPEADO" + "\n")

    for instruction in instructions:
        saida.write(instruction)

    print(tabela_simbolos)

if __name__ == "__main__":

    #Abrindo arquivo para imprimir resposta
    saida = open("analises/codigo_assembly.txt", "w")

    # CArregando a tabela de símbolos
    tabela_simbolos = pd.read_csv("./analises/tabela_simbolos_csv.csv")
    
    # Realizando leitura das quádruplas para o mapeamento das instruções em assembly
    quadruplas = ler_quadruplas()

    gera_assembly(quadruplas, saida, tabela_simbolos)

    saida.close()

