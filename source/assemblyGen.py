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
def return_register(registradores,register):

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

def return_arguments(quads, fun_name):
    args = []
    for index, quad in enumerate(quads):
        quad = quad.split(",")
        if  "FUN" in quad[0]:
            index+=1
            print(quad)
            while "ARG" in quads[index]:
                print(quad)
                args.append(quads[index])
                index+=1
    return args



def gerar_quadruplas(saida, df):
    # Lista utilizada para determinar se os registradores estão em uso
    global registradores

    quads = []
    assembly = []
    registrador_parametros = []
    
    assembly.append("JUMP main\n")

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
                pos_register = return_register(registradores,quad[index])
                registradores[pos_register] =  quad[index]
                registers_quad.append(pos_register)
                # print(search_string_in_assembly(quad[index], quads, pos_quad))

        if  quad[0] == "FUN":
    
            escopo_atual = quad[2]
            assembly.append("."+ quad[2].strip() + "\n")

            if quad[2] != "main":
                assembly.append("SW {} {} {}\n".format("$sz", "$r31", 1))
                assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))


        elif quad[0] == "RET":
            assembly.append("ADDI $t{} $RR {}\n".format(registers_quad[0], 0))
            assembly.append("JUMP FIMFUN {}\n".format(escopo_atual))
          

        elif quad[0] == "ARG":
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
            
        elif quad[0] == "LAB":
            assembly.append(".{}\n".format(quad[1]))

        elif quad[0] == "LOAD_WORD":
            assembly.append("LW ${} $t{} {}\n".format("sp",registers_quad[0] , buscar_dados(df, quad[2], escopo_atual)))

        elif quad[0] == "LOAD_IMEDIATE":
            assembly.append("ADDI {} $t{} {}\n".format(quad[2], registers_quad[0], 0))

        elif quad[0] == "PLUS":
            assembly.append("ADD {} {} {}\n".format(quad[2], quad[1], quad[3]))

        elif quad[0] == "DIV":
            assembly.append("DIV $t{} $t{} $t{}\n".format(registers_quad[1], registers_quad[0], registers_quad[2]))

        elif quad[0] == "MULT":
                    assembly.append("MULT $t{} $t{} $t{}\n".format(registers_quad[1], registers_quad[0], registers_quad[2]))

        elif quad[0] == "SUB":
                    assembly.append("SUB $t{} $t{} $t{}\n".format(registers_quad[1], registers_quad[0], registers_quad[2]))

        elif quad[0] == "COMP":
            assembly.append("COMP $t{} $t{} $t{}\n".format(registers_quad[1], registers_quad[0], registers_quad[2]))

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
            assembly.append("SW ${} $t{} {}\n".format("sp", source, mem_pos))

        elif quad[0] == "PARAM":
            registrador_parametros.append(registers_quad[0])
            continue

        elif quad[0] == "LT":
            assembly.append("LT $t{} $t{} $t{} \n".format(registers_quad[1], registers_quad[0], registers_quad[2]))

        elif quad[0] == "LOAD_WORD_VETOR":
            deslocamento = return_register(registradores, quad[3])
            pos_mem = buscar_dados(df, quad[2], escopo_atual)
            assembly.append("ADDI $t{} $t{} {}\n".format(deslocamento, deslocamento, pos_mem))
            assembly.append("LOAD_WORD_vetor $t{} $t{} 0\n".format(deslocamento, registers_quad[0]))

        elif quad[0] == "EMPILHA":
            saved_registers = registradores.copy()
            for i, reg in enumerate(registradores):
                    if(reg != ''):
                        assembly.append("SW {} $t{} {}\n".format( "$sz", str(return_register(registradores,reg)), 0))
                        assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
                        registradores[i] = ''

        elif quad[0] == "DESEMPILHA":

            registradores = saved_registers
            for i, reg in enumerate(reversed(saved_registers)):
                if(reg != ''):
                    assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", -1))
                    assembly.append("LW {} $t{} {}\n".format("$sz",str(return_register(registradores,reg)), 0))
                    
                

            for i in registradores:
                if not search_string_in_assembly(i, quads, pos_quad+1):
                    pos_register = return_register(registradores,i)
                    registradores[pos_register] =  ''

        elif quad[0] == "ALLOC_VET":
                assembly.append("ADDI $sz $sz {}\n".format(quad[2]) )
        
        elif quad[0] == "CALL":

            if quad[2].strip() == "input":
                assembly.append("IN $t{}\n".format(registers_quad[0]))

            elif quad[2].strip() == "output":
                reg_print =  registrador_parametros[0]
                assembly.append("OUTPUT $t{}\n".format(reg_print))

            else:    
                # Utilizado para o return adress
                assembly.append("SW {} {} {}\n".format( "$sz", "$sp", 0))
                assembly.append("ADDI {} {} {}\n".format("$sz", "$sp", 0))
                assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))

                escopo_desejado = quad[2]
                df_filtrado = df.loc[df['Escopo'] == escopo_desejado]
                maior_memory_position = int(df_filtrado['memory_position'].max())
                
                args = return_arguments(quads, quad[2])

                for i, parametro in enumerate(registrador_parametros):
                    maior_memory_position +=1
                    quad_anterior = quads[index - 1]
                    quad_anterior = quad_anterior.split(",")
                    arg = args[i].split(",")
                    arg2 = remover_caracteres(arg[2])
                    assembly.append("SW {} $t{}  {}\n".format("$sp",parametro,  str(int(buscar_dados(df, arg2, escopo_desejado)))))
                    registradores[parametro] = ''

                registrador_parametros = []

                assembly.append("JAL {}\n".format(quad[2]))

                pos_register = return_register(saved_registers, quad[1])
                print(saved_registers)
                saved_registers[pos_register] = quad[1]
                assembly.append("ADDI {} $t{}  {}\n".format("$RR",pos_register,0))
                assembly.append("ADDI $sp $sz  {}\n".format(0))
                assembly.append("LW $sp $sp {}\n".format(0))


        elif quad[0] == "END":

            if quad[1] == "main":
                assembly.append("HALT\n")
            else: 
                assembly.append(".FIMFUN {}\n".format( quad[1]))
                assembly.append("LW {} {} {}\n".format("$sp", "$t31", "1"))
                assembly.append("JR {}\n".format("$t31") )

        else:
            assembly.append("NÃO MAPEADO - {} \n".format(quad[0]))


        for item in registers_quad:
                if not search_string_in_assembly(registradores[item], quads, pos_quad+1):
                    pos_register = return_register(registradores,registradores[item])
                    registradores[pos_register] =  ''

    for linha in assembly:
        saida.write(linha)

    return assembly

def asm_to_binary(assembly_instructions):

    saida = open("analises/binario.txt", "w")
    binario = []

    opcodes = {
        "ADDI": "001001", 
        "SW": "101011",
        "LW": "100011", 
        "JUMP": "000010"
    }

    registers = {
        '$t0': '00000',
        '$t1': '00001',
        '$t2': '00010',
        '$t3': '00011',
        '$t4': '00100',
        '$t5': '00101',
        '$t6': '00110',
        '$t7': '00111',
        '$t8': '01000',
        '$t9': '01001',
        '$t10': '01010',
        '$t11': '01011',
        '$t12': '01100',
        '$t13': '01101',
        '$t14': '01110',
        '$t15': '01111',
        '$t16': '10000',
        '$t17': '10001',
        '$t18': '10010',
        '$t19': '10011',
        '$t20': '10100',
        '$t21': '10101',
        '$t22': '10110',
        '$t23': '10111',
        '$t24': '11000',
        '$sz': '11110', 
        '$sp': '11101', 
        '$31' :'11111'
    }

    for instruction in assembly_instructions:
        final_binary = instruction

        for inst, opcode in opcodes.items():
            final_binary = final_binary.replace(inst, opcode)
    
        for reg, address in registers.items():
            final_binary = final_binary.replace(reg, address)
            
        binario.append(final_binary)

    for instruction in binario:
        saida.write(instruction)

    saida.close()

if __name__ == "__main__":

    # Abrindo arquivo para imprimir resposta
    saida = open("analises/codigo_assembly.txt", "w")

    # Carregando a tabela de símbolos
    df = pd.read_csv("./analises/tabela_simbolos_csv.csv")

    # Calculando posição de memória
    df = df.groupby('Escopo').apply(calculate_index)
    df.reset_index(drop=True, inplace=True)
    df.loc[~df['Escopo'].isin(['main', 'global']), 'memory_position'] += 1
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

    

    assembly = gerar_quadruplas(saida, df)
    asm_to_binary(assembly)
    print(df)
    saida.close()