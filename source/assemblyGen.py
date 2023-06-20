import pandas as pd
import copy
from queue import LifoQueue

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

# Função utilizada para removar os caracteres das quádruplas lidas
def remover_caracteres(string):
    caracteres_indesejados = ["(", ",", ")"]
    for caractere in caracteres_indesejados:
        string = string.replace(caractere, "")
    return string

def gerar_quadruplas(saida, df):
    # Lista utilizada para determinar se os registradores estão em uso
    global registradores

    quads = []
    assembly = []
    registrador_parametros = []
    
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

        elif quad[0] == "RET":
           assembly.append("ADDI {} $t{} {}\n".format("$RR", registers_quad[0], 0))
           assembly.append("JR\n")

        elif quad[0] == "ARG":
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
            
        elif quad[0] == "LAB":
            assembly.append(".{}\n".format(quad[1]))

        elif quad[0] == "LOAD_WORD":
            assembly.append("LOAD_WORD $t{} ${} {}\n".format(registers_quad[0], "sp", buscar_dados(df, quad[2], escopo_atual)))

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
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))

        elif quad[0] == "STOREVAR":
            nome = quad[2]
            escopo = quad[3]
            source = registers_quad[0]
            mem_pos = buscar_dados(df, nome, escopo)
            assembly.append("STORE_WORD $t{} ${} {}\n".format( source, "sp", mem_pos))

        elif quad[0] == "PARAM":
            registrador_parametros.append(registers_quad[0])
            continue

        elif quad[0] == "EMPILHA":
            saved_registers = registradores.copy()
            for i, reg in enumerate(registradores):
                    if(reg != ''):

                        assembly.append("SW $t{} {} {}\n".format(str(return_register(reg)), "$sz", 0))
                        assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
                        registradores[i] = ''

        elif quad[0] == "DESEMPILHA":

            registradores = saved_registers
            for i, reg in enumerate(reversed(saved_registers)):
                if(reg != ''):
                    assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", -1))
                    assembly.append("LW $t{} {} {}\n".format(str(return_register(reg)), "$sz", 0))
                    
                

            for i in registradores:
                if not search_string_in_assembly(i, quads, pos_quad+1):
                    pos_register = return_register(i)
                    registradores[pos_register] =  ''

        
        elif quad[0] == "CALL":
            if quad[2].strip() == "input":
                assembly.append("IN $t{}\n".format(registers_quad[0]))

            elif quad[2].strip() == "output":
                reg_print =  registrador_parametros[0]
                assembly.append("OUTPUT $t{}\n".format(reg_print))

            else:    
                # Utilizado para o return adress
                assembly.append("STORE_WORD {} {} {}\n".format("$sp", "$sz", 0))
                assembly.append("ADDI {} {} {}\n".format("$sp", "$sz", 0))
                assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))

                escopo_desejado = quad[2]
                df_filtrado = df.loc[df['Escopo'] == escopo_desejado]
                maior_memory_position = int(df_filtrado['memory_position'].max())
                
                for parametro in registrador_parametros:
                    maior_memory_position +=1
                    quad_anterior = quads[index - 1]
                    quad_anterior = quad_anterior.split(",")
                    assembly.append("STORE_WORD $t{} {} {}\n".format(parametro, "$sp", str(maior_memory_position - int(buscar_dados(df, quad_anterior[2], quad[2])))))
                    registradores[parametro] = ''

                registrador_parametros = []

                assembly.append("JAL {}\n".format(quad[2]))
                assembly.append("ADDI $t{} {} {}\n".format(registers_quad[0],"$RR",0))

                assembly.append("ADDI $sz $sp {}\n".format(0))
                assembly.append("LW $sp $sp {}\n".format(0))

        elif quad[0] == "END":

            if quad[1] == "main":
                assembly.append("HALT\n")
            else: 
                assembly.append("JR\n")

        else:
            assembly.append("NÃO MAPEADO - {} \n".format(quad[0]))


        for item in registers_quad:
                if not search_string_in_assembly(registradores[item], quads, pos_quad+1):
                    pos_register = return_register(registradores[item])
                    registradores[pos_register] =  ''

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

    gerar_quadruplas(saida, df)
    print(df)
    saida.close()