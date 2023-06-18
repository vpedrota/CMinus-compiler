import pandas as pd

# Variavaeis globais
stack_size = 0

# Lista utilizada para determinar se os registradores estão em uso
registradores = [''] * 24

# Função utilizaa para determinar a posição de memória de cada variével
def calculate_index(group):
    group['memory_position'] = group['Tamanho'].replace(0, 1).shift(fill_value=0).cumsum() + 1
    return group

# Função utilizada para retornar a posição da memória
def buscar_dados(df, nome, escopo):
    nome = nome.strip()
    escopo = escopo.strip()
    resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
    if resultado.empty:
        return "-1"
    return resultado.values[0][6]

# Função que retorna o próximo registardor livre
def return_register(register):
    global registradores

    register = register.strip()

    for i, valor in enumerate(registradores):
        if register == valor.strip():
            return i
        
    for i, valor in enumerate(registradores):
        if valor == '':
            return i
        
    return None 

def search_string_in_assembly(string, assembly, pos):
    for index, line in enumerate(assembly):
        line = line.split(",")

        for item in line:
            item = remover_caracteres(item) 
            item = item.strip()
            if item == string and index >= pos:
                return True
    return False

def store_register(registrador, assembly):
    global registradores

    return registrador

# Função utilizada para removar os caracteres das quádruplas lidas
def remover_caracteres(string):
    caracteres_indesejados = ["(", ",", ")"]
    for caractere in caracteres_indesejados:
        string = string.replace(caractere, "")
    return string


def gerar_quadruplas(saida, df):

    global registradores
    global stack_size

    quads = []
    assembly = []
    
    with open("analises/codigo_intermediario.txt", "r") as arquivo:
        quads = arquivo.readlines()

    escopo_atual = "global"
    for pos_quad, quad in enumerate(quads):

        # Tratando a quadrupla
        quad = quad.split(",")
        
        registers_quad = []
        for index, item in enumerate(quad):
            quad[index] = item.strip()
            quad[index] = remover_caracteres(quad[index])

            if(index > 0 and '$t' in quad[index]):
                pos_register = return_register(quad[index])
                registradores[pos_register] =  quad[index]

                registers_quad.append(pos_register)
                # print(search_string_in_assembly(quad[index], quads, pos_quad))

        if  quad[0] == "FUN":
            escopo_atual = quad[2]
            assembly.append("."+ quad[2].strip() + "\n")

        elif quad[0] == "LAB":
            assembly.append(".{}\n".format(quad[1]))

        elif quad[0] == "LOAD_WORD":
            assembly.append("LOAD_WORD $t{} {} {}\n".format(registers_quad[0], "SP", buscar_dados(df, quad[2], escopo_atual)))

        elif quad[0] == "LOAD_IMEDIATE":
            assembly.append("LOAD_IMEDIATE $t{} {}\n".format(registers_quad[0], quad[2]))

        elif quad[0] == "PLUS":
            assembly.append("ADD {} {} {}\n".format(quad[1], quad[2], quad[3]))

        elif quad[0] == "DIV":
            assembly.append("DIV $t{} $t{} $t{}\n".format(registers_quad[0], registers_quad[1], registers_quad[2]))

        elif quad[0] == "MULT":
                    assembly.append("MULT $t{} $t{} $t{}\n".format(registers_quad[0], registers_quad[1], registers_quad[2]))

        elif quad[0] == "SUB":
                    assembly.append("SUB $t{} $t{} $t{}\n".format(registers_quad[0], registers_quad[1], registers_quad[2]))

        elif quad[0] == "COMP":
            assembly.append("COMP $t{} $t{} $t{}\n".format(registers_quad[0], registers_quad[1], registers_quad[2]))

        elif quad[0] == "IFF":
            assembly.append("IFF $t{} {}\n".format(registers_quad[0], quad[2]))

        elif quad[0] == "GOTO":
            assembly.append("JUMP {}\n".format(quad[1]))

        elif quad[0] == "ALLOC":
            stack_size+=1

        elif quad[0] == "STOREVAR":
            nome = quad[2]
            escopo = quad[3]
            source = registers_quad[0]
            mem_pos = buscar_dados(df, nome, escopo)
            assembly.append("STORE_WORD $t{} {} {}\n".format( source, "SP", mem_pos))

        elif quad[0] == "PARAM":
            pass
            #assembly.append("----------" + str(registers_quad[0]) + "\n")

        elif quad[0] == "EMPILHA":
            assembly.append("STORE_WORD $t{} {} {}\n".format(registers_quad[0], "$sp", 0))
            # Release allocated register
            registradores[registers_quad[0]] = ''

        elif quad[0] == "DESEMPILHA":
            assembly.append("STORE_WORD $t{} {} {}\n".format(registers_quad[0], "$sp", 0))
            # Release allocated register
            registradores[registers_quad[0]] = ''

        elif quad[0] == "CALL":
            if quad[2].strip() == "input":
                assembly.append("IN $t{}\n".format(registers_quad[0]))

            elif quad[2].strip() == "output":
                assembly.append("OUTPUT $t{}\n".format(registers_quad[0]))

            else:
                # Utilizado para o return adress
                stack_size+=1
                print(registradores)
                for i, register in enumerate(registradores):
                    if(register != ''):
                        stack_size+=1
                        assembly.append("STORE_WORD $t{} {} $t{}\n".format(i,"$sp",stack_size))

                assembly.append("CALL\n")

                for i, register in enumerate(registradores):
                    if(register != ''):
                        stack_size+=1
                        assembly.append("LOAD_WORD $t{} {} $t{}\n".format(i,"$sp",stack_size))



        elif quad[0] == "END":

            if quad[1] == "main":
                assembly.append("HALT\n")
            else: 
                assembly.append("NÃO MAPEADO\n")

        else:
            assembly.append("NÃO MAPEADO - {} \n".format(quad[0]))


        for item in registers_quad:
                if not search_string_in_assembly(registradores[item], quads, pos_quad+1):
                    pos_register = return_register(registradores[item])
                    registradores[pos_register] =  ''

        print("-----------------------------------\n")
    for linha in assembly:
        saida.write(linha)
 

if __name__ == "__main__":

    # Abrindo arquivo para imprimir resposta
    saida = open("analises/codigo_assembly.txt", "w")

    # Carregando a tabela de símbolos
    df = pd.read_csv("./analises/tabela_simbolos_csv.csv")

    # Calculando posição de memória
    df = df.groupby('Escopo').apply(calculate_index)
    df.reset_index(drop=True, inplace=True)

    # Transformações para realizar operações entre as colunas
    df['Escopo'] = df['Escopo'].astype(str)
    df['Nome'] = df['Nome'].astype(str)
    df['Tamanho'] = df['Tamanho'].astype(str)
    df['memory_position'] = df['memory_position'].astype(str)

    for coluna in df.columns:
    # Verificar se a coluna é do tipo 'object' (string)
        if df[coluna].dtype == object:
            # Aplicar a função strip() para remover espaços em branco antes e depois das strings
            df[coluna] = df[coluna].str.strip()

    tipos_variaveis = df

    # print(tipos_variaveis)
    gerar_quadruplas(saida, df)

    saida.close()