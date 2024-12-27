#!/bin/bash

# Diretório base do projeto
BASE_DIR="/home/Trabalho-2-ed-II"

# Nome do executável
EXECUTAVEL="programa_quest_1"

# Arquivos necessários
MAIN_FILE="$BASE_DIR/src/Questão_1_e_2/Questão_1/main_quest_1.c"
BINARIA_FILE="$BASE_DIR/src/Questão_1_e_2/Binaria/ARV_BINARIA.c"
Arvore_2_3_FILE="$BASE_DIR/src/Questão_1_e_2/Questão_1/ARV2_3.c"
EXTRAIR_2_3="$BASE_DIR/src/Questão_1_e_2/Questão_1/Arquivo/Extrair.c"

# Verificar se os arquivos existem
if [ ! -f "$MAIN_FILE" ]; then
    echo "Erro: $MAIN_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$BINARIA_FILE" ]; then
    echo "Erro: $BINARIA_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$Arvore_2_3_FILE" ]; then
    echo "Erro: $Arvore_2_3_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$EXTRAIR_2_3" ]; then
    echo "Erro: $EXTRAIR_2_3 não encontrado!"
    exit 1
fi  

# Compilar o programa
echo "Compilando o programa..."
gcc -o "$BASE_DIR/$EXECUTAVEL" \
    -I"$BASE_DIR" \
    "$MAIN_FILE" \
    "$BINARIA_FILE" \
    "$Arvore_2_3_FILE" \
    "$EXTRAIR_2_3" \
   

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Executando o programa..."
    
    "$BASE_DIR/$EXECUTAVEL"
else
    echo "Erro na compilação. Verifique os arquivos e tente novamente."
fi
