#!/usr/bin/env python
# coding: utf-8

# In[7]:


# carregando tabela de símbolos
import pandas as pd

# Carregando tabela de símbolos do arquivo gerado pelo compilador
tabela_simbolos = pd.read_csv("./analises/tabela_simbolos_csv.csv")

# Convertendo os tipos para realizar operações entre as colunas
tabela_simbolos['Escopo'] = tabela_simbolos['Escopo'].astype(str)
tabela_simbolos['Nome'] = tabela_simbolos['Nome'].astype(str)
tabela_simbolos['Tamanho'] = tabela_simbolos['Tamanho'].astype(str)

# Adicionando coluna memory_position com zeros inicialmente
tabela_simbolos['memory_position'] = 0

escopos = tabela_simbolos['Escopo'].unique()

for escopo in escopos:
    mask = (tabela_simbolos['Escopo'] == escopo) & (tabela_simbolos['Tipo'] != 'Função')
    tabela_simbolos.loc[mask, 'memory_position'] = tabela_simbolos.loc[mask, 'Tamanho'].replace('0', '1').astype(int).shift(fill_value=0).cumsum()+1

# Colocando a posição nas funções para considerar o return address
tabela_simbolos.loc[~tabela_simbolos['Escopo'].isin(['main', 'global']), 'memory_position'] = tabela_simbolos.loc[~tabela_simbolos['Escopo'].isin(['main', 'global']), 'memory_position'] + 1

# Convertendo memory_position para string
tabela_simbolos['memory_position'] = tabela_simbolos['memory_position'].astype(str)

# Resetando o index
tabela_simbolos.reset_index(drop=True, inplace=True)

for coluna in tabela_simbolos.columns:
    # Verificar se a coluna é do tipo 'object' (string)
        if tabela_simbolos[coluna].dtype == object:
            # Aplicar a função strip() para remover espaços em branco antes e depois das strings
            tabela_simbolos[coluna] = tabela_simbolos[coluna].str.strip()
            
        
#tabela_simbolos['memory_position'] = tabela_simbolos['memory_position'].astype(int) - 1           
tabela_simbolos


# In[8]:


# Funções para utilização na geração do código assembly
# Função utilizada para removar os caracteres das quádruplas lidas
def processar_string(string):
    nova_string = string.replace("(", "").replace(")", "").replace(" ", "").replace("\n", "")
    lista_palavras = nova_string.split(",")
    return lista_palavras

# Função que verifica se o registrador ainda vai ser utilizado para liberar ele
def search_string_in_assembly(string, quads, pos):
    
    for index, line in enumerate(quads):
        line = processar_string(line)

        for item in line:
            item = remover_caracteres(item) 
            if item == string and index >= pos:
                return True
    return False

# Função que retorna o próximo registardor livre
def return_register_position(registradores,registrador):


    if("$context_register" in registrador):
        return "$context_register"

    for i, valor in enumerate(registradores):
        if registrador == valor:
            return '$t' + str(i)
        
    for i, valor in enumerate(registradores):
        if valor == '':
            registradores[i] = registrador
            return '$t' + str(i)
        
    return None 

# Função utilizada para retornar a posição da memória
def buscar_dados(df, nome, escopo):
    nome = nome.strip()
    escopo = escopo.strip()
    resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
    if resultado.empty:
        escopo = "global"
        resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
        return resultado.values[0][6], "$zero"
    return resultado.values[0][6], "$sp"

def liberar_registradores(quad, assembly, pos, registradores):
    
    for item in quad[1:]:
        if not search_string_in_assembly(item, assembly, pos):
            liberar_registrador(registradores, item)
            
def verifica_vetor_parametro(df, nome, escopo):
    nome = nome.strip()
    escopo = escopo.strip()
    resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
    if resultado.empty:
        escopo = "global"
        resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
        
    return resultado['Tipo_var'].values[0] == 'VetorParametroInteiro'

def verifica_vetor(df, nome, escopo):
    nome = nome.strip()
    escopo = escopo.strip()
    resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
    if resultado.empty:
        escopo = "global"
        resultado = df.query("`Nome` == @nome and `Escopo` == @escopo")
        
    return resultado['Tipo'].values[0] == 'Vetor'

def verificar_igualdade(string, lista):
    for item in lista:
        if string == item:
            return True
    return False

def return_arguments(quads, nome_funcao):
    args = []
    for index, quad in enumerate(quads):
        quad = quad.split(",")
        if  "FUN" in quad[0] and nome_funcao in quad[2]:
            index+=1
           
            while "ARG" in quads[index]:
                
                args.append(quads[index])
                index+=1
    return args

def remover_caracteres(string):
    caracteres_indesejados = ["(", ",", ")"]
    for caractere in caracteres_indesejados:
        string = string.replace(caractere, "")
    return string

def liberar_registrador(registradores, registrador):
    for index, item in enumerate(registradores):
        if item == registrador:
            registradores[index] = ''
            
def replace_labels_with_line_distance(lines):
    label_to_line = {}
    processed_lines = []

    # First, enumerate over lines to map labels to line numbers
    for i, line in enumerate(lines):
        # If the line is a label
        if line.startswith('.'):
            label = line.strip('.')
            # Record the label with adjusted line number
            label_to_line[label] = len(processed_lines)
        else:
            processed_lines.append(line)

    # Now, replace labels with line distances in the processed lines
    for i, line in enumerate(processed_lines):
        for label, line_number in label_to_line.items():
            if label in line:
                if 'IFF' in line:  # If the line contains the IFF instruction
                    # Replace the label with its distance from the current line
                    processed_lines[i] = line.replace(label, str(abs(i - line_number) - 1) + "\n")
                else:
                    # For other lines, replace the label with its line number
                    processed_lines[i] = line.replace(label, str(line_number) + "\n")

    return processed_lines


# In[17]:


def asm_to_binary(assembly_instructions):

    saida = open("analises/binario.txt", "w")
    binario = []

    opcodes = {
        "ADDI": "001000", 
        "SW": "101011",
        "LW": "100011", 
        "JUMP": "000010",
        "SUBI": "101010",
        "MULT": "000000",
        "DIV": "000000",
        "RESTO": "000000",
        "COMP": "000000",
        "SUB": "000000",
        "JAL": "000011",
        "OUTPUT": "101110",
        "SET_HD_TRACK": "110010",
        "STACK_SIZE": "011001",
        "CHANGE_CONTEXT": "110011",
        "SET_QUANTUM_VALUE": "101111",
        "SET_LCD_MESSAGE": "101100",
        "IN": "111110",
        "LAST_PC": "110110",
        "JR": "001111", 
        "ADD ": "000000",
        "PLUS ": "000000",
        "HALT": "111111",
        "IFF": "000101", 
        "LESSTHAN": "000000",
        "LETEQUAL": "000000",
        "GT": "000000",
        "GET": "000000",
        "SET_JP_ADDRESS":"001110",
        "DFT": "000000",
        "SET_PROCESS_BCD":"111011"
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
        '$t24': '11000',
        '$t25': '11001',
        '$sz': '11110', 
        '$sp': '11101', 
        '$ra' :'11111',
        '$zero': '11011',
        '$RR' : '11100'
    }


    # registers  = {
    #     '$t13': '01101',
    #     '$t14': '01110',
    #     '$t15': '01111',
    #     '$t16': '10000',
    #     '$t17': '10001',
    #     '$t18': '10010',
    #     '$t19': '10011',
    #     '$t20': '10100',
    #     '$sz': '10101', 
    #     '$sp': '10110', 
    #     '$ra' :'10111',
    #     '$zero': '11000',
    #     '$RR' : '11001'
    # }
    


    funct = {
        "ADD ": "100000",
        "PLUS" : "100000",
        "MULT ": "011000", 
        "DIV ": "011010", 
        "SUB ": "100010", 
        "COMP ":  "111111",
        "LETEQUAL ": "100110",
        "LESSTHAN ": "101010",
        "GT": "111111",
        "GET":"111110",
        "RESTO":  "100111", 
        "DFT": "011111"
    }

    operations_16bits_imediate = ["ADDI", "SW", "LW", "SUBI", "LAST_PC", "IN", "OUTPUT", "SET_LCD_MESSAGE"]
        
    operations_26bits_imediate = [ "JR", "SET_QUANTUM_VALUE", "CHANGE_CONTEXT", "STACK_SIZE"]


    for instruction in assembly_instructions:
        final_binary = instruction
        
        for inst, opcode in opcodes.items():
            final_binary = final_binary.replace(inst, opcode)
    
        for reg, address in reversed(registers.items()):
            final_binary = final_binary.replace(reg, address)

        #final_binary = final_binary.replace("$context_register", "11010")
        final_binary = final_binary.replace("$stack_size", "11010")

        parts = final_binary.split()

        if any(op in instruction for op in ["JUMP", "JAL"]):
            parts[1] = format(int(parts[1]), '026b') + "\n"
            final_binary = "".join(parts)

        if any(op in instruction for op in ["IFF"]):
            parts[2] = format(int(parts[2]), '016b') + "\n"
            parts[1] = format("11011" + parts[1])
            final_binary = "".join(parts)

        if any(op in instruction for op in operations_16bits_imediate):
            parts[3] = format(int(parts[3]), '016b') + "\n"
            final_binary = "".join(parts)

        for inst_ula, ula_code in funct.items(): 
            if inst_ula in instruction:
                parts.append("00000{}\n".format(ula_code))
                final_binary = "".join(parts)
            
        if any(op in instruction for op in operations_26bits_imediate):
            parts.append("000000000000000000000\n")
            final_binary = "".join(parts)
            
        if "HALT" in instruction:
            parts.append("00000000000000000000000000\n")
            final_binary = "".join(parts)

        if "SET_HD_TRACK" in instruction:
            parts.insert(2, "11011")
            parts[3] = format(int(parts[3]), '016b') + "\n"
            final_binary = "".join(parts)

        if "SET_PROCESS_BCD" in instruction:
            parts[3] = format(int(parts[3]), '016b') + "\n"
            final_binary = "".join(parts)

        if "SET_JP_ADDRESS" in instruction:
            print(parts)
            parts.insert(3, "000000000000000000000\n")
            final_binary = "".join(parts)
        

        binario.append(final_binary)

    for instruction in binario:
        saida.write(instruction)

    saida.close()


# In[18]:


# Carregando lista em memória para realizar as geração do assembly
with open("analises/codigo_intermediario.txt", "r") as arquivo:
    quads = arquivo.readlines()
    
# lista que vai ficar a saída com o assembly
assembly = []

# variável que irá representar o escopo que está sendo gerado atualmente,
# pode ser útil para utilizar nas pesquisas na tabela de símbolos
escopo_atual = "global" 

# registradores que estão em uso
registradores = [''] * 12

# lista que terá os parêmetros de uma função
registradores_parametros = []

# flag para jump para main
jump_main = True

# Registradores para processos
# registers = {
#         '$t0': '00000',
#         '$t1': '00001',
#         '$t2': '00010',
#         '$t3': '00011',
#         '$t4': '00100',
#         '$t5': '00101',
#         '$t6': '00110',
#         '$t7': '00111',
#         '$t8': '01000',
#         '$t9': '01001',
#         '$t10': '01010',
#         '$t11': '01011',
#         '$t12': '01100',
#         '$sz': '11110', 
#         '$sp': '11101', 
#         '$ra' :'11111',
#         '$zero': '11011',
#         '$RR' : '11100'
#     }

register_process = {
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
    '$t25': '11001',
}

#     registers  = {
#     '$t13': '01101',
#     '$t14': '01110',
#     '$t15': '01111',
#     '$t16': '10000',
#     '$t17': '10001',
#     '$t18': '10010',
#     '$t19': '10011',
#     '$t20': '10100',
#     '$sz': '10101', 
#     '$sp': '10110', 
#     '$ra' :'10111',
#     '$zero': '11000',
#     '$RR' : '11001'
# }

for quads_index, quad in enumerate(quads):
    
    # Retirando caracteres indesejados e pegando os itens da quad
    quad = processar_string(quad)
    
    if quad[0] == "FUN":
        
        if jump_main:
            assembly.append("JUMP main\n")
            jump_main = False
        
        escopo_atual = quad[2]
        assembly.append(".{}\n".format(quad[2]))
        
        if quad[2] != "main":
            assembly.append("SW {} {} {}\n".format("$sp", "$ra", 1))
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1)) 
        else:
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sp", 0))
            
    elif quad[0] == "RET":
            registrador = return_register_position(registradores, quad[1])
            assembly.append("ADDI {} $RR {}\n".format(registrador, 0))
            assembly.append("JUMP FIMFUN_{}\n".format(escopo_atual))
            
    elif quad[0] == "ARG":
        assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
            
    elif quad[0] == "ALLOC":
        assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
        
    elif quad[0] == "ALLOC_VET":
        assembly.append("ADDI $sz $sz {}\n".format(quad[2]))
            
    elif quad[0] == "LAB":
        
        assembly.append(".{}\n".format(quad[1]))
        
    elif quad[0] == "STOREVAR":
        
        escopo = quad[3]
        mem_pos, registrador_base = buscar_dados(tabela_simbolos, quad[2], escopo)
        registrador = return_register_position(registradores, quad[1])
        assembly.append("SW {} {} {}\n".format(registrador_base, registrador, mem_pos))
        
    elif quad[0] == "STOREVAR_VETOR":
        # assembly.append("----------------\n")
        nome = quad[2]
        registrador = return_register_position(registradores, quad[1])
        registrador_deslocamento = return_register_position(registradores, quad[3])
        mem_pos, registrador_base = buscar_dados(tabela_simbolos, nome, escopo_atual)
        
        if verifica_vetor_parametro(tabela_simbolos, nome, escopo_atual):
            
            registrador_aux = return_register_position(registradores, '$t25')
            
            assembly.append("LW {} {} {}\n".format(registrador_base, registrador_aux, mem_pos))
            assembly.append("ADD {} {} {}\n".format(registrador_aux, registrador_deslocamento, registrador_deslocamento))
            assembly.append("SW {} {} {}\n".format(registrador_deslocamento, registrador, 0))
            liberar_registrador(registradores, '$t25')
            
        else:
            assembly.append("ADD {} {} {}\n".format(registrador_base, registrador_deslocamento, registrador_deslocamento))
            assembly.append("SW {} {} {}\n".format(registrador_deslocamento, registrador, mem_pos))
        # assembly.append("----------------\n")
            
    elif quad[0] == "LOAD_WORD":
        
        mem_pos, registrador_base = buscar_dados(tabela_simbolos, quad[2], escopo_atual)
        registrador = return_register_position(registradores, quad[1])
        assembly.append("LW {} {} {}\n".format(registrador_base, registrador, mem_pos))
        
    elif quad[0] == "LOAD_WORD_VETOR":
        # assembly.append("******************\n")
        nome = quad[2]
        registrador = return_register_position(registradores, quad[1])
        registrador_deslocamento = return_register_position(registradores, quad[3])
        mem_pos, registrador_base = buscar_dados(tabela_simbolos, quad[2], escopo_atual)
        
        if verifica_vetor_parametro(tabela_simbolos, nome, escopo_atual):
            assembly.append("LW {} {} {}\n".format(registrador_base, registrador, mem_pos))
            assembly.append("ADD {} {} {}\n".format(registrador_deslocamento, registrador, registrador_deslocamento))
            assembly.append("LW {} {} {}\n".format(registrador_deslocamento, registrador, 0))
        else:
            assembly.append("ADD {} {} {}\n".format(registrador_base, registrador_deslocamento, registrador_deslocamento))
            assembly.append("LW {} {} {}\n".format(registrador_deslocamento, registrador, mem_pos))
        # assembly.append("******************\n")
    elif quad[0] == "LOAD_IMEDIATE":
        
        imediato = quad[2]
        registrador = return_register_position(registradores, quad[1])
        assembly.append("ADDI {} {} {}\n".format("$zero", registrador, imediato))
        
    elif verificar_igualdade(quad[0], ["RESTO", "PLUS", "DIV", "MULT", "SUB", "COMP", "LET", "LET", "LT", "GT", "GET", "DFT"]):
        
        registrador1 = return_register_position(registradores, quad[1])    
        registrador2 = return_register_position(registradores, quad[2])
        registrador3 = return_register_position(registradores, quad[3])
        quad[0] = quad[0].replace("LET", "LETEQUAL")
                                       
        if not "MULT" in quad[0]:
            quad[0] = quad[0].replace("LT", "LESSTHAN")
                                       
        assembly.append("{} {} {} {}\n".format(quad[0], registrador2, registrador3 , registrador1))

    elif quad[0] == "IFF":
        
        registrador1 =  return_register_position(registradores, quad[1])
        assembly.append("IFF {} {}\n".format(registrador1, quad[2]))

    elif quad[0] == "GOTO":
        assembly.append("JUMP {}\n".format(quad[1]))
    
    elif quad[0] == "PARAM":
        registrador1 = return_register_position(registradores, quad[1])
        registradores_parametros.append(quad[1])
        continue
        
    elif quad[0] == "PARAM_ID":
    
        registrador = return_register_position(registradores, quad[3])
        pos_mem, registrador_base = buscar_dados(tabela_simbolos, quad[1], escopo_atual)
        
        if verifica_vetor(tabela_simbolos, quad[1], escopo_atual):
             assembly.append("ADDI {} {} {}\n".format(registrador_base, registrador, pos_mem))
        else:
            assembly.append("LW {} {} {}\n".format(registrador_base, registrador, pos_mem))
        
        registradores_parametros.append(quad[3])
        continue
        
    elif quad[0] == "END":

        if quad[1] == "main":
            assembly.append(".FIMFUN_{}\n".format( "main"))
            assembly.append("HALT\n")
        else: 
            assembly.append(".FIMFUN_{}\n".format( quad[1]))
            assembly.append("LW {} {} {}\n".format("$sp", "$ra", "1"))
            assembly.append("JR {}\n".format("$ra"))
            
    elif quad[0] == "CALL":
        # assembly.append("----------------\n")
        if quad[2].strip() == "input":
            registrador = return_register_position(registradores, quad[1])
            assembly.append("IN {} {} 0\n".format(registrador, registrador))

        elif quad[2].strip() == "PC_INTERRUPTION":
            registrador = return_register_position(registradores, quad[1])
            assembly.append("LAST_PC {} {} {}\n".format("$zero", registrador, "0"))

        elif quad[2].strip() == "STACK_SIZE":
            registrador = return_register_position(registradores, quad[1])
            #assembly.append("STACK_SIZE {}\n".format(registrador))
            assembly.append("ADD $zero  $stack_size {}\n".format(registrador))

            

        elif quad[2].strip() == "output":
            registrador = return_register_position(registradores, registradores_parametros[0])
            assembly.append("OUTPUT {} {} 0\n".format(registrador, registrador))
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []

        elif quad[2].strip() == "set_hd_track":
            registrador = return_register_position(registradores, registradores_parametros[0])
            assembly.append("SET_HD_TRACK {} {} {}\n".format(registrador, registrador, 0))
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []

        elif quad[2].strip() == "set_process_bcd":
            registrador = return_register_position(registradores, registradores_parametros[0])
            assembly.append("SET_PROCESS_BCD {} {} {}\n".format(registrador, registrador, 0))
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []

        elif quad[2].strip() == "copy_registers_to_bank":
            registrador = return_register_position(registradores, registradores_parametros[0])
            
            for indice_registrador, valor in enumerate(register_process.keys()):
                assembly.append("LW {} {} {}\n".format(valor, registrador, indice_registrador))
            
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []

        elif quad[2].strip() == "copy_registers_to_ram":
            registrador = return_register_position(registradores, quad[1])

            for indice_registrador, valor in enumerate(register_process.keys()):
                assembly.append("SW {} {} {}\n".format( "$stack_size", valor, indice_registrador))

            registradores_parametros = []

        elif quad[2].strip() == "set_quantum_value":
            registrador = return_register_position(registradores, registradores_parametros[0])
            assembly.append("SET_QUANTUM_VALUE {}\n".format(registrador))
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []

        elif quad[2].strip() == "set_lcd_message":
            registrador = return_register_position(registradores, registradores_parametros[0])
            # registrador2 = return_register_position(registradores, registradores_parametros[1])
            assembly.append("SET_LCD_MESSAGE {} {} 0\n".format(registrador, registrador))
            liberar_registrador(registradores,  registradores_parametros[0])
            # liberar_registrador(registradores,  registradores_parametros[1])
            registradores_parametros = []

        elif quad[2].strip() == "clean_ram":
            registrador = return_register_position(registradores, registradores_parametros[0])
            # registrador2 = return_register_position(registradores, registradores_parametros[1])
            assembly.append("SET_HD_TRACK {} {}\n".format(registrador, 0))

            for indice_registrador, valor in enumerate(register_process.keys()):
                assembly.append("SW {} {} {}\n".format( "$zero", "$zero", indice_registrador))

            assembly.append("SET_HD_TRACK {} {}\n".format("$zero", 0))
            
            liberar_registrador(registradores,  registradores_parametros[0])
            # liberar_registrador(registradores,  registradores_parametros[1])
            registradores_parametros = []

        elif quad[2].strip() == "change_context":

            registrador = return_register_position(registradores, registradores_parametros[0])
            registrador2 = return_register_position(registradores, registradores_parametros[1])
            registrador3 =  return_register_position(registradores, registradores_parametros[2])

            assembly.append("SET_JP_ADDRESS {}\n".format(registrador3))

            assembly.append("SET_HD_TRACK {} {}\n".format(registrador2, 0))

            for indice_registrador, valor in enumerate(register_process.keys()):
                assembly.append("LW {} {} {}\n".format("$zero", valor, indice_registrador))

            
            
            assembly.append("SET_HD_TRACK {} {}\n".format(registrador2, 32))
        
            assembly.append("CHANGE_CONTEXT {}\n".format(registrador))
            
            assembly.append("SET_JP_ADDRESS {}\n".format("$zero"))
            
            assembly.append("SET_HD_TRACK {} {}\n".format(registrador2, 0))

            for indice_registrador, valor in enumerate(register_process.keys()):
                assembly.append("SW {} {} {}\n".format( "$zero", valor, indice_registrador))

            assembly.append("SET_HD_TRACK {} {}\n".format("$zero", 0))
                
            liberar_registrador(registradores,  registradores_parametros[0])
            registradores_parametros = []
        
        else:
            
            for registrador in registradores:
                if registrador != "":
                    assembly.append("SW {} {} {}\n".format( "$sz", return_register_position(registradores, registrador), 0))
                    assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
                    
            
            assembly.append("SW {} {} {}\n".format( "$sz", "$sp", 0))
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sp", 0))
            assembly.append("ADDI {} {} {}\n".format("$sz", "$sz", 1))
            
            args = return_arguments(quads, quad[2])
            escopo_desejado = quad[2]
            
            for index_parametro, parametro in enumerate(registradores_parametros): # rrro aqui
                arg = args[index_parametro].split(",")
                arg2 = remover_caracteres(arg[2])
                # print(arg2)
                # print(parametro)
                # print(registradores)
                # print(escopo_desejado)
                mem_pos, registrador_base = buscar_dados(tabela_simbolos, arg2, escopo_desejado)
                # print(mem_pos)
                # print(return_register_position(registradores, parametro))
                registrador = return_register_position(registradores, parametro)
                assembly.append("SW {} {} {}\n".format("$sp", registrador,  mem_pos))    
                
            assembly.append("JAL {}\n".format(quad[2]))
            assembly.append("ADDI $sp $sz {}\n".format(0))
            assembly.append("LW $sp $sp {}\n".format(0))
            
            for i, registrador in enumerate(reversed(registradores)):
                if(registrador != ''):
                    assembly.append("SUBI {} {} {}\n".format("$sz", "$sz", 1))
                    assembly.append("LW {} {} {}\n".format("$sz", return_register_position(registradores, registrador), 0))
            
            for index_parametro, parametro in enumerate(registradores_parametros):
                liberar_registrador(registradores, parametro)
            registradores_parametros = []
            
            pos_register = return_register_position(registradores, quad[1])
            return_register_number = quad[1]
           
            assembly.append("ADDI {} {} {}\n".format("$RR", pos_register, 0))
            # assembly.append("----------------\n")
    else:
        assembly.append("NÃO MAPEADO {}\n".format(quad[0]))
    
    #print(registradores)
    liberar_registradores(quad, quads, quads_index+1, registradores)
    
assembly = replace_labels_with_line_distance(assembly)    
file_output = open("analises/asm.txt", "w")
for line in assembly:
    file_output.write(line)
    
file_output.close()
asm_to_binary(assembly)


# In[ ]:




