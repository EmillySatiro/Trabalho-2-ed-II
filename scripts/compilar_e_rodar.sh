#!/bin/bash

# Se o caminho do projeto não for passado como argumento, assume o diretório atual
PROJECT_DIR="${1:-$(dirname "$(realpath "$0")")}"

# Nome do executável
EXECUTAVEL="programa"

# Arquivos necessários
MAIN_FILE="$PROJECT_DIR/main.c"
BINARIA_FILE="$PROJECT_DIR/Arvores/Binaria/ARV_BINARIA.c"
ARVORE_2_3_FILE="$PROJECT_DIR/Arvores/Arvore_2_3/ARV2_3.c"
RUBRO_NEGRA_FILE="$PROJECT_DIR/Arvores/Rubro_negra/Rubro_negra.c"

# Verificar se todos os arquivos existem
if [ ! -f "$MAIN_FILE" ] || [ ! -f "$BINARIA_FILE" ] || [ ! -f "$ARVORE_2_3_FILE" ] || [ ! -f "$RUBRO_NEGRA_FILE" ]; then
    echo "Erro: Alguns arquivos necessários não foram encontrados no diretório do projeto."
    exit 1
fi

# Compilar o programa
echo "Compilando o programa..."

gcc -o "$EXECUTAVEL" \
-I"$PROJECT_DIR" \
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
