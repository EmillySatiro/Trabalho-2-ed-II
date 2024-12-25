#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARVORE2_3.h"

ARVORE2_3* criarNo(Informacao_memoria info) {
    ARVORE2_3* novoNo = (ARVORE2_3*)malloc(sizeof(ARVORE2_3));
    if (!novoNo) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    novoNo->info1 = info;
    novoNo->quant_infos = 1;
    novoNo->esquerda = novoNo->centro = novoNo->direita = NULL;
    return novoNo;
}

void cadastrarNos(ARVORE2_3** raiz, int ultimo_endereco) {
    Informacao_memoria info;
    char state;
    int bloco_inicio = 0, bloco_fim;

    printf("Informe o estado do primeiro nó (L para livre, O para ocupado): ");
    scanf(" %c", &state);
    printf("Informe o bloco final do primeiro nó: ");
    scanf("%d", &bloco_fim);

    info.state = state;
    info.block_inicio = bloco_inicio;
    info.block_fim = bloco_fim;

    *raiz = criarNo(info);
    ARVORE2_3* atual = *raiz;

    while (info.block_fim != ultimo_endereco) {
        bloco_inicio = info.block_fim + 1;
        printf("Informe o bloco final do próximo nó: ");
        scanf("%d", &bloco_fim);

        state = (info.state == 'L') ? 'O' : 'L';

        Informacao_memoria novaInfo;
        novaInfo.state = state;
        novaInfo.block_inicio = bloco_inicio;
        novaInfo.block_fim = bloco_fim;

        if (atual->quant_infos == 1) {
            atual->info2 = novaInfo;
            atual->quant_infos = 2;
        } else {
            ARVORE2_3* novoNo = criarNo(novaInfo);
            atual->direita = novoNo;
            atual = novoNo;
        }

        info = novaInfo;
    }
}

void alocarNos(ARVORE2_3** raiz, int quantidade_blocos) {
    int contador = 0;
    if (!*raiz) {
        printf("Árvore vazia.\n");
        return;
    }

    ARVORE2_3* atual = *raiz;

    while (atual && contador < quantidade_blocos) {
        if (atual->info1.state == 'L' && (atual->info1.block_fim - atual->info1.block_inicio + 1) >= quantidade_blocos) {
            int novo_fim = atual->info1.block_inicio + quantidade_blocos - 1;
            Informacao_memoria novoInfo = { 'O', atual->info1.block_inicio, novo_fim };

            if (novo_fim < atual->info1.block_fim) {
                Informacao_memoria restanteInfo = { 'L', novo_fim + 1, atual->info1.block_fim };
                atual->info1 = novoInfo;
                if (atual->quant_infos == 1) {
                    atual->info2 = restanteInfo;
                    atual->quant_infos = 2;
                } else {
                    ARVORE2_3* novoNo = criarNo(restanteInfo);
                    novoNo->direita = atual->direita;
                    atual->direita = novoNo;
                }
            } else {
                atual->info1 = novoInfo;
            }
            printf("====================================\n");
            printf("Status: %c\n", novoInfo.state);
            printf("Bloco inicial: %d\n", novoInfo.block_inicio);
            printf("Bloco final: %d\n", novoInfo.block_fim);
            printf("====================================\n");
        }

        // Concatenar nós adjacentes livres
        if (atual->direita && atual->direita->info1.state == atual->info1.state) {
            atual->info1.block_fim = atual->direita->info1.block_fim;
            ARVORE2_3* temp = atual->direita;
            atual->direita = atual->direita->direita;
            free(temp);
        }
        atual = atual->direita;
        contador++;
    }

}

void exibirNos(ARVORE2_3* raiz) {
    if (!raiz) {
        return;
    }

    exibirNos(raiz->esquerda);
    printf("====================================\n");
    printf("Estado: %c\n", raiz->info1.state);
    printf("Bloco Inicial: %d\n", raiz->info1.block_inicio);
    printf("Bloco Final: %d\n", raiz->info1.block_fim);
    printf("====================================\n");
    if (raiz->quant_infos == 2) {
    printf("====================================\n");
        printf("Estado: %c\n", raiz->info2.state);
        printf("Bloco Inicial: %d\n", raiz->info2.block_inicio);
        printf("Bloco Final: %d\n", raiz->info2.block_fim);
    printf("====================================\n");
    }
    exibirNos(raiz->centro);
    exibirNos(raiz->direita);
}

void liberarNos(ARVORE2_3* raiz) {
    if (!raiz) {
        return;
    }

    liberarNos(raiz->esquerda);
    liberarNos(raiz->centro);
    liberarNos(raiz->direita);
    free(raiz);
}