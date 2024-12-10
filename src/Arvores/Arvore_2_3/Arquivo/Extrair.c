#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../../Arvore_2_3/ARV2_3.h"
#include "../../Rubro_negra/Rubro_negra.h"


#define Tamanho_linha 1024
char *trim_23(char *str) {
    if (str == NULL) return str;  // Garantir que o ponteiro não seja nulo

    // Remove espaços do início
    while (*str && (isspace((unsigned char)*str) || *str == '\t')) {
        str++;
    }

    // Se a string for esvaziada, retorne diretamente
    if (*str == '\0') {
        return str;
    }

    // Remove espaços do final
    char *end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char)*end) || *end == '\t')) {
        end--;
    }
    *(end + 1) = '\0';  // Finaliza a string corretamente

    return str;
}

ARV2_3 *Pegar_dados_arquivo_23(ARV2_3 **raiz){
  
    FILE *arquivo = fopen("Dicionario.txt", "r");
    if (!arquivo){
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[Tamanho_linha];
    int unidade;
 

    while (fgets(linha, sizeof(linha), arquivo)){
        linha[strcspn(linha, "\n")] = '\0';

        if (strstr(linha, "Unidade")){
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1){
                //printf("Unidade: %d\n", unidade);
            }
        }else{
            char *palavra_portugues = strtok(linha, ":");
            char *palavra_ingles = strtok(NULL, ":");

            Informacao info = criar_info(palavra_portugues, palavra_ingles, unidade);
            insere(raiz, info);
        }
    }
    return *raiz;

    fclose(arquivo);
}
// Função para processar o arquivo e inserir palavras na árvore 2-3
