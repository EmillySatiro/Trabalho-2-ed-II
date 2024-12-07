
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"

// Função para limpar espaços em branco à esquerda
void limpar_espacos(char *str) {
    while (*str == ' ' || *str == '\t') {
        str++;
    }
}

// Função para ler o arquivo e inserir os dados na árvore 2-3
void ler_arquivo_e_inserir(const char *nome_arquivo, ARV2_3 **raiz) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[256];
    char palavra_portugues[25], palavra_ingles[50];
    int unidade = 0;  // Variável para armazenar o número da unidade
    Informacao info;

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), file)) {
        // Ignora linhas vazias
        if (linha[0] == '\n') {
            continue;
        }

        // Verifica se a linha contém uma unidade
        if (linha[0] == '%' && strstr(linha, "Unidade")) {
            // Incrementa o número da unidade
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1) {
                continue;  // Se o número da unidade foi lido corretamente, passa para a próxima linha
            }
        }

        // Processa linhas de tradução
        if (sscanf(linha, "%24s :", palavra_portugues) == 1) {
            // Limpa espaços à esquerda da palavra em português
            limpar_espacos(palavra_portugues);

            // Processa as traduções separadas por vírgula
            char *token = strtok(linha + strlen(palavra_portugues) + 2, ",");  // Ignora o ":" após a palavra portuguesa
            while (token) {
                // Limpa espaços extras à esquerda e à direita de cada tradução
                limpar_espacos(token);

                // Se o token não estiver vazio, copia a tradução para a variável palavra_ingles
                if (strlen(token) > 0) {
                    snprintf(palavra_ingles, sizeof(palavra_ingles), "%s", token);

                    // Criar a estrutura Informacao com a unidade atual
                    info = criar_info(palavra_portugues, palavra_ingles, unidade);

                    // Inserir a informação na árvore 2-3
                    inserir_binaria_em_2_3(raiz, palavra_portugues, unidade, palavra_ingles);
                }

                // Passa para a próxima tradução
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(file);  // Fecha o arquivo após a leitura
}
