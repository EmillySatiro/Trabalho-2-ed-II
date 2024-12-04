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
        if (strncmp(linha_limpa,  " Unidade", 9) == 0) {
            unidade_atual = atoi(linha_limpa + 10); // Atualiza a unidade
        } else if (unidade_atual != -1 && strlen(linha_limpa) > 0) {
            // Se a unidade for válida e a linha não for vazia

            // Separar o inglês da tradução
            char *palavra_ingles = strtok(linha_limpa, ":");
            if (palavra_ingles == NULL) {
                printf("Erro: palavra em inglês não encontrada na linha: %s\n", linha_limpa);
                continue; // Ignorar e continuar com a próxima linha
            }

            char *traducoes = strtok(NULL, ":");
            if (traducoes == NULL) {
                printf("Erro: tradução não encontrada para a palavra: %s\n", palavra_ingles);
                continue; // Ignorar e continuar com a próxima linha
            }
            // Inserir na árvore 2-3
            if (*arvore2_3 != NULL) {
                inserir_binaria_em_2_3(arvore2_3,traducoes,unidade_atual,palavra_ingles);
            }

           
  
        }
    }

    fclose(arquivo); // Fechar o arquivo
}
