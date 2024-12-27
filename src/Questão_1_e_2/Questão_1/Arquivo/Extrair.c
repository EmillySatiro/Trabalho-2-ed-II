#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../../Questão_1/ARV2_3.h"


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

ARV2_3 *Pegar_dados_arquivo_23(ARV2_3 **raiz) {
    FILE *arquivo = fopen("Dicionario.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[100];
    int unidade;
    char palavra_ingles[100];

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strstr(linha, "Unidade")) {
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1) {
                //printf("Unidade: %d\n", unidade);
            }
        } else {
            char *pt = strtok(linha, ":,;");
            pt = trim_23(pt);

            if (pt) {
                strcpy(palavra_ingles, pt);
                //printf("Palavra em ingles: %s\n", palavra_ingles);
                while ((pt = strtok(NULL, ":,;")) != NULL) {
                    pt = trim_23(pt);
                    Informacao info = criar_info(pt, palavra_ingles, unidade);
                    if (&info != NULL) {
                        //printf("Palavra em portugues: %s\n", info->palavra_portugues);
                        insere(raiz, info);
                    } else {
                        fprintf(stderr, "Erro ao criar Informacao_VP\n");
                    }
                }
            }
        }
    }

    printf("Palavras extraídas do arquivo com sucesso!!\n");

    fclose(arquivo);
    return *raiz;
}

