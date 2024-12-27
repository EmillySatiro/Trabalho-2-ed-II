#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARVORE2_3.h"

ARVORE2_3 *criarNo(Informacao_memoria info)
{
    ARVORE2_3 *novoNo = (ARVORE2_3 *)malloc(sizeof(ARVORE2_3));
    if (!novoNo)
    {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    novoNo->info1 = info;
    novoNo->quant_infos = 1;
    novoNo->esquerda = novoNo->centro = novoNo->direita = NULL;
    return novoNo;
}

void cadastrarNos(ARVORE2_3 **raiz, int ultimo_endereco)
{
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
    ARVORE2_3 *atual = *raiz;

    while (info.block_fim != ultimo_endereco)
    {
        bloco_inicio = info.block_fim + 1;
        printf("Informe o bloco final do próximo nó: ");
        scanf("%d", &bloco_fim);

        state = (info.state == 'L') ? 'O' : 'L';

        Informacao_memoria novaInfo;
        novaInfo.state = state;
        novaInfo.block_inicio = bloco_inicio;
        novaInfo.block_fim = bloco_fim;

        if (atual->quant_infos == 1)
        {
            atual->info2 = novaInfo;
            atual->quant_infos = 2;
        }
        else
        {
            ARVORE2_3 *novoNo = criarNo(novaInfo);
            atual->direita = novoNo;
            atual = novoNo;
        }

        info = novaInfo;
    }
}

Informacao_memoria maior_info(ARVORE2_3 *raiz){
    return raiz->quant_infos == 2 ? raiz->info2 : raiz->info1;
}



void intercalarNos(ARVORE2_3 **raiz)
{
    if (*raiz){
        ARVORE2_3 *atual = *raiz;
        while (atual && atual->direita)
        {
            // Se info1 e info2 do nó atual tiverem o mesmo estado, ajusta
            if (atual->quant_infos == 2 && atual->info1.state == atual->info2.state)
            {
                // Move info2 para a direita
                ARVORE2_3 *novoNo = criarNo(atual->info2);
                novoNo->direita = atual->direita;
                atual->direita = novoNo;
                atual->quant_infos = 1;
            }

            // Se o estado do nó atual for o mesmo do nó à direita, ajusta
            if (atual->info1.state == atual->direita->info1.state)
            {
                if (atual->direita->quant_infos == 1)
                {
                    // Move info1 do nó à direita para a info2 do nó atual
                    atual->info2 = atual->direita->info1;
                    atual->quant_infos = 2;
                    ARVORE2_3 *temp = atual->direita;
                    atual->direita = atual->direita->direita;
                    free(temp);
                }
                else
                {
                    atual->direita->info1.state = (atual->info1.state == 'L') ? 'O' : 'L';
                }
            }

            atual = atual->direita;
        }
        
    }else{
        printf("Árvore vazia.\n");
    }

    
}

void alocarNos(ARVORE2_3 **raiz, int quantidade_blocos){
    if (*raiz){
        ARVORE2_3 *atual = *raiz;
        int contador = 0;

        printf("Blocos a serem alocados: %d\n", quantidade_blocos);
        while (atual && contador < quantidade_blocos)
        {
            if (atual->info1.state == 'L' && (atual->info1.block_fim - atual->info1.block_inicio + 1) >= quantidade_blocos)
            {
                Informacao_memoria novoInfo = {'O', atual->info1.block_inicio, atual->info1.block_fim};
                atual->info1 = novoInfo;

                printf("====================================\n");
                printf("Status: %c\n", atual->info1.state);
                printf("Bloco inicial: %d\n", atual->info1.block_inicio);
                printf("Bloco final: %d\n", atual->info1.block_fim);
                printf("====================================\n");
            }
            else if (atual->quant_infos == 2 && atual->info2.state == 'L' && (atual->info2.block_fim - atual->info2.block_inicio + 1) >= quantidade_blocos)
            {
                Informacao_memoria novoInfo = {'O', atual->info2.block_inicio, atual->info2.block_fim};
                atual->info2 = novoInfo;

                printf("====================================\n");
                printf("Status: %c\n", atual->info2.state);
                printf("Bloco inicial: %d\n", atual->info2.block_inicio);
                printf("Bloco final: %d\n", atual->info2.block_fim);
                printf("====================================\n");
            }

            // Concatenar nós adjacentes livres
            if (atual->direita && (atual->direita->info1.state == 'L' || atual->direita->info2.state == 'L')) {
                if (atual->quant_infos == 1 && atual->direita->info1.state == 'L') {
                    atual->info1.block_fim = atual->direita->info1.block_fim;
                } else if (atual->quant_infos == 2) {
                    if (atual->info2.state == 'L' && atual->direita->info1.state == 'L') {
                        atual->info2.block_fim = atual->direita->info1.block_fim;
                    } else if (atual->info2.state == 'L' && atual->direita->info2.state == 'L') {
                        atual->info2.block_fim = atual->direita->info2.block_fim;
                    }
                }
        
            }

            printf("Valor atual após a concatenação, se houve:\n");
            printf("Info1 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info1.state, atual->info1.block_inicio, atual->info1.block_fim);
            if (atual->quant_infos == 2) {
                printf("Info2 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info2.state, atual->info2.block_inicio, atual->info2.block_fim);
            }

            atual = atual->direita;
            contador++;
        }

        printf("Finalização da alocação de blocos.\n");
        intercalarNos(raiz);
    }else{
        printf("Árvore vazia.\n");
    }

    
}

void liberarBlocos(ARVORE2_3 **raiz, int quantidade_blocos)
{
    if (*raiz){
        ARVORE2_3 *atual = *raiz;
        int contador = 0;

        printf("Blocos a serem liberados: %d\n", quantidade_blocos);
        while (atual && contador < quantidade_blocos)
        {
            if (atual->info1.state == 'O' && (atual->info1.block_fim - atual->info1.block_inicio + 1) >= quantidade_blocos)
            {
                atual->info1.state = 'L';
                printf("====================================\n");
                printf("Status: %c\n", atual->info1.state);
                printf("Bloco inicial: %d\n", atual->info1.block_inicio);
                printf("Bloco final: %d\n", atual->info1.block_fim);
                printf("====================================\n");
            }
            else if (atual->quant_infos == 2 && atual->info2.state == 'O' && (atual->info2.block_fim - atual->info2.block_inicio + 1) >= quantidade_blocos)
            {
                atual->info2.state = 'L';
                printf("====================================\n");
                printf("Status: %c\n", atual->info2.state);
                printf("Bloco inicial: %d\n", atual->info2.block_inicio);
                printf("Bloco final: %d\n", atual->info2.block_fim);
                printf("====================================\n");
            }

            // Concatenar nós adjacentes livres
            if (atual->direita && atual->direita->info1.state == 'L') {
                if (atual->quant_infos == 1) {
                    atual->info1.block_fim = atual->direita->info1.block_fim;
                } else if (atual->quant_infos == 2 && atual->info2.state == 'L') {
                    atual->info2.block_fim = atual->direita->info1.block_fim;
                }
            }

            if (atual->direita && atual->quant_infos == 2 && atual->direita->info1.state == 'L') {
                if (atual->info2.state == 'L') {
                    atual->info2.block_fim = atual->direita->info1.block_fim;
                }
            }

            printf("Valor atual após a concatenação, se houve:\n");
            printf("Info1 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info1.state, atual->info1.block_inicio, atual->info1.block_fim);
            if (atual->quant_infos == 2) {
                printf("Info2 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info2.state, atual->info2.block_inicio, atual->info2.block_fim);
            }

            atual = atual->direita;
            contador++;
        }

        printf("Finalização da liberação de blocos.\n");

        
        intercalarNos(raiz);
            
    }else{
        printf("Árvore vazia.\n");
    }

    
}

void exibirNos(ARVORE2_3 *raiz){
    if (raiz){
        exibirNos(raiz->esquerda);
        printf("====================================\n");
        printf("Estado: %c\n", raiz->info1.state);
        printf("Bloco Inicial: %d\n", raiz->info1.block_inicio);
        printf("Bloco Final: %d\n", raiz->info1.block_fim);
        printf("====================================\n");
        if (raiz->quant_infos == 2)
        {
            printf("====================================\n");
            printf("Estado: %c\n", raiz->info2.state);
            printf("Bloco Inicial: %d\n", raiz->info2.block_inicio);
            printf("Bloco Final: %d\n", raiz->info2.block_fim);
            printf("====================================\n");
        }
        exibirNos(raiz->centro);
        exibirNos(raiz->direita); 
    }

}

// void no_2_3_adicionar_info_Q3(ARVORE2_3 *no, Informacao_memoria info, ARVORE2_3 *filho_maior)
// {
//     if (info.block_inicio != no->info1.block_inicio)
//     {
//         no->info2 = info;
//         no->direita = filho_maior;
//     }
//     else
//     {
//         no->info2 = no->info1;
//         no->direita = no->centro;
//         no->centro = filho_maior;
//         no->info1 = info;
//     }
//     no->quant_infos = 2;
// }

// void no_2_3_desacolar_Q3(ARVORE2_3 **no)
// {
//     free(*no);
//     *no = NULL;
// }

// int eh_folha_Q3(ARVORE2_3 *no)
// {
//     return no->esquerda == NULL;
// }

// ARVORE2_3 *no_2_3_juntar_Q3(ARVORE2_3 *filho1, Informacao_memoria info, ARVORE2_3 *maior, ARVORE2_3 **raiz)
// {
//     if (filho1->quant_infos == 2)
//         filho1->quant_infos = 1;

//     no_2_3_adicionar_info_Q3(filho1, info, maior);

//     (*raiz)->quant_infos--;

//     if ((*raiz)->quant_infos == 0)
//         no_2_3_desacolar_Q3(raiz);

//     return filho1;
// }

// int arvore_2_3_rebalancear_Q3(ARVORE2_3 **raiz, int info, ARVORE2_3 **maior)
// {
//     int balanceou = 0;
//     if (*raiz != NULL)
//     {
//         if (!eh_folha_Q3(*raiz))
//         {
//             // if((*raiz)->quant_infos == 2 && !eh_info1(**raiz, info) && !eh_info2(**raiz, info))
//             if ((*raiz)->quant_infos == 2 && (*raiz)->centro->quant_infos == 2)
//                 balanceou = -1;
//             else
//             {
//                 if (info == (*raiz)->info1.block_inicio)
//                     balanceou = arvore_2_3_rebalancear_Q3(&((*raiz)->esquerda), info, maior);
//                 else if ((*raiz)->quant_infos == 1 || info < (*raiz)->info2.block_inicio)
//                     balanceou = arvore_2_3_rebalancear_Q3(&((*raiz)->centro), info, maior);
//                 else
//                     balanceou = arvore_2_3_rebalancear_Q3(&((*raiz)->direita), info, maior);

//                 if ((*raiz)->quant_infos == 1)
//                     balanceou = balanceamento_Q3(raiz, (*raiz)->esquerda, &((*raiz)->centro), (*raiz)->info1, maior);
//                 else if ((*raiz)->quant_infos == 2)
//                     balanceou = balanceamento_Q3(raiz, (*raiz)->centro, &((*raiz)->direita), (*raiz)->info2, maior);
//             }
//         }
//     }

//     return balanceou;
// }

// static int balanceamento_Q3(ARVORE2_3 **raiz, ARVORE2_3 *filho1, ARVORE2_3 **filho2, Informacao_memoria info, ARVORE2_3 **maior)
// {
//     int balanceou = 0;
//     if (*filho2 == NULL || (*filho2)->quant_infos == 0)
//     {
//         if (*filho2 != NULL)
//             no_2_3_desacolar_Q3(filho2);

//         *maior = no_2_3_juntar_Q3(filho1, info, *maior, raiz);
//         balanceou = 1;
//     }
//     return balanceou;
// }

void liberarNos(ARVORE2_3 *raiz){
    if (raiz){
        liberarNos(raiz->esquerda);
        liberarNos(raiz->centro);
        liberarNos(raiz->direita);
        free(raiz);
    }
}