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


void cadastrarNos(ARVORE2_3** raiz, unsigned long ultimo_endereco) {
    Informacao_memoria info;
    char state;
    int bloco_inicio = 0, bloco_fim;
    unsigned long endereco_fim;


    printf("Informe o estado do primeiro nó (L para livre, O para ocupado): ");
    scanf(" %c", &state);
    printf("Informe o bloco final do primeiro nó: ");
    scanf("%d", &bloco_fim);

    info.state = state;
    info.block_inicio = bloco_inicio * 1024 * 1024;
    info.block_fim = (bloco_fim + 1) * 1024 * 1024 - 1;

    *raiz = criarNo(info);
    ARVORE2_3* atual = *raiz;

    while (info.block_fim < ultimo_endereco) {
        bloco_inicio = info.block_fim + 1;
        printf("Informe o bloco final do próximo nó: ");
        scanf("%d", &bloco_fim);

        state = (info.state == 'L') ? 'O' : 'L';

        Informacao_memoria novaInfo;
        novaInfo.state = state;
        novaInfo.block_inicio = bloco_inicio * 1024 * 1024;
        novaInfo.block_fim = (bloco_fim + 1) * 1024 * 1024 - 1;

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

