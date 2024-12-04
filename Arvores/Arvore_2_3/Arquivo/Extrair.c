#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"

#define Tamanho_linha 1024

// Função para processar o arquivo e inserir palavras na árvore 2-3
void processar_arquivo(char *nome_txt, ARV2_3 **arvore2_3) {
    FILE *arquivo = fopen(nome_txt, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    char linha[Tamanho_linha];
    int unidade_atual = -1;

    while (fgets(linha, Tamanho_linha, arquivo)) {
        // Arrumar a tabulação e espaços
        char *linha_limpa = linha;
        while (*linha_limpa == ' ' || *linha_limpa == '\t') linha_limpa++;

        // Remover o caractere de nova linha
        linha_limpa[strcspn(linha_limpa, "\n")] = '\0';

        // Verificar se temos a marcação da unidade
        if (strncmp(linha_limpa, "% Unidade", 9) == 0) {
            unidade_atual = atoi(linha_limpa + 10); // Atualiza a unidade
        } else if (unidade_atual != -1 && strlen(linha_limpa) > 0) {
            // Se a unidade for válida e a linha não for vazia

            // Separar o inglês da tradução
            char *palavra_ingles = strtok(linha_limpa, ":");
            char *traducoes = strtok(NULL, ":");

            // Verificar se a palavra em inglês e a tradução existem
            if (palavra_ingles && traducoes) {
                Informacao Info;

                // Criar um nó da árvore binária para a palavra em inglês
                ARV_BINARIA *no_palavra_ingles = cria_arvore_binaria(palavra_ingles, 0);  // Aqui você pode passar a unidade ou outra informação, dependendo do seu caso
                if (no_palavra_ingles == NULL) {
                    printf("Erro ao criar árvore binária para a palavra: %s\n", palavra_ingles);
                    continue; // Ignorar essa palavra e continuar com o próximo item
                }

                // Armazenar o nó binário na estrutura Informacao
                Info.palavra_ingles = no_palavra_ingles;

                // Copiar a tradução para português
                if (traducoes) {
                    strncpy(Info.palavra_portugues, traducoes, sizeof(Info.palavra_portugues) - 1);
                    Info.palavra_portugues[sizeof(Info.palavra_portugues) - 1] = '\0';
                } else {
                    printf("Erro: tradução não encontrada para a palavra: %s\n", palavra_ingles);
                    continue;
                }

                // Atribuir a unidade
                Info.unidade = unidade_atual;

                // Inserir na árvore 2-3
                if (*arvore2_3 == NULL) {
                    printf("Erro: árvore 2-3 não inicializada corretamente.\n");
                    continue; // Evitar inserir em árvore nula
                }

                insere(arvore2_3, Info);
            }
        }
    }

    fclose(arquivo); // Fechar o arquivo
}
