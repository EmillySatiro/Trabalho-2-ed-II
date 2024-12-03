#!/bin/bash

# Diretório base do projeto
BASE_DIR="/home/Trabalho-2-ed-II"

# Nome do executável
EXECUTAVEL="programa"

# Arquivos necessários
MAIN_FILE="$BASE_DIR/main.c"
BINARIA_FILE="$BASE_DIR/Arvores/Binaria/ARV_BINARIA.c"
ARVORE_2_3_FILE="$BASE_DIR/Arvores/Arvore_2_3/ARV2_3.c"
RUBRO_NEGRA_FILE="$BASE_DIR/Arvores/Rubro_negra/Rubro_negra.c"

# Compilar o programa
echo "Compilando o programa..."
gcc -o "$EXECUTAVEL" \
-I"$BASE_DIR" \
"$MAIN_FILE" \
"$BINARIA_FILE" \
"$ARVORE_2_3_FILE" \
"$RUBRO_NEGRA_FILE"

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Executando o programa..."
    # Executar o programa
    ./"$EXECUTAVEL"
else
    echo "Erro na compilação. Verifique os arquivos e tente novamente."
fi
