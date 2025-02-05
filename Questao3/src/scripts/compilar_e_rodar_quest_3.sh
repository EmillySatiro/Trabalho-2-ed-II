#!/bin/bash

# Diretório base do projeto
BASE_DIR="/home/walison/Trabalho-2-ed-II"

# Nome do executável
EXECUTAVEL="programa_quest_3"

# Arquivos necessários
MAIN_FILE="$BASE_DIR/Questao3/src/main_quest_3.c"
ARVORE2_3_FILE="$BASE_DIR/Questao3/src/ARVORE2_3.c"


# Verificar se os arquivos existem
if [ ! -f "$MAIN_FILE" ]; then
    echo "Erro: $MAIN_FILE não encontrado!"
    exit 1
fi

if [ ! -f "$ARVORE2_3_FILE" ]; then
    echo "Erro: $ARVORE2_3_FILE não encontrado!"
    exit 1
fi

# Compilar o programa
echo "Compilando o programa..."
gcc -o "$BASE_DIR/$EXECUTAVEL" \
    -I"$BASE_DIR" \
    "$MAIN_FILE" \
    "$ARVORE2_3_FILE" \

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Executando o programa..."
    # Executar o programa
    "$BASE_DIR/$EXECUTAVEL"
else
    echo "Erro na compilação. Verifique os arquivos e tente novamente."
fi