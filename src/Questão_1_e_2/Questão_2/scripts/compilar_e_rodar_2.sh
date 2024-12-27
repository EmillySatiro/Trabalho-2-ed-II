#!/bin/bash

# Diretório base do projeto
BASE_DIR="/home/Trabalho-2-ed-II"

# Nome do executável
EXECUTAVEL="programa_quest_2"

# Arquivos necessários
MAIN_FILE="$BASE_DIR/src/Questão_1_e_2/Questão_2/main_quest_2.c"
BINARIA_FILE="$BASE_DIR/src/Questão_1_e_2/Binaria/ARV_BINARIA.c"
RUBRO_NEGRA_FILE="$BASE_DIR/src/Questão_1_e_2/Questão_2/Rubro_negra.c"
EXTRAIR_RUBRO="$BASE_DIR/src/Questão_1_e_2/Questão_2/Arquivo/extrair_rubro.c"

# Verificar se os arquivos existem
if [ ! -f "$MAIN_FILE" ]; then
    echo "Erro: $MAIN_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$BINARIA_FILE" ]; then
    echo "Erro: $BINARIA_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$RUBRO_NEGRA_FILE" ]; then
    echo "Erro: $RUBRO_NEGRA_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$EXTRAIR_RUBRO" ]; then
    echo "Erro: $EXTRAIR_RUBRO não encontrado!"
    exit 1
fi  

# Compilar o programa
echo "Compilando o programa..."
gcc -o "$BASE_DIR/$EXECUTAVEL" \
    -I"$BASE_DIR" \
    "$MAIN_FILE" \
    "$BINARIA_FILE" \
    "$RUBRO_NEGRA_FILE" \
    "$EXTRAIR_RUBRO" \
   

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Executando o programa..."
    # Executar o programa
    "$BASE_DIR/$EXECUTAVEL"
else
    echo "Erro na compilação. Verifique os arquivos e tente novamente."
fi