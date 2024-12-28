#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARVORE2_3.h"

/**
 * @brief Cria um novo nó para a árvore 2-3.
 *
 * Esta função aloca memória para um novo nó da árvore 2-3 e inicializa
 * seus campos com os valores fornecidos e valores padrão.
 *
 * @param info Estrutura do tipo Informacao_memoria que contém as informações
 *             a serem armazenadas no novo nó.
 * @return Ponteiro para o novo nó criado.
 *
 * @note Em caso de falha na alocação de memória, a função imprime uma mensagem
 *       de erro e encerra o programa.
 */
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


/**
 * @brief Cadastra nós em uma árvore 2-3.
 *
 * Esta função cadastra nós em uma árvore 2-3, alternando o estado dos nós entre 'L' (livre) e 'O' (ocupado).
 * O usuário é solicitado a informar o estado e o bloco final do primeiro nó, e então a função continua
 * solicitando o bloco final dos próximos nós até que o endereço final seja alcançado.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param ultimo_endereco Endereço do último bloco na memória.
 */
void cadastrarNos(ARVORE2_3 **raiz, int ultimo_endereco) {
    Informacao_memoria info;
    char state;
    int bloco_inicio = 0, bloco_fim;

    // Entrada inicial
    printf("Informe o estado do primeiro nó (L para livre, O para ocupado): ");
    scanf(" %c", &state);
    printf("Informe o bloco final do primeiro nó: ");
    scanf("%d", &bloco_fim);

    info.state = state;
    info.block_inicio = bloco_inicio;
    info.block_fim = bloco_fim;

    inserir_Elemento_ARV_2_3(raiz, info);

    // Continuar cadastrando até o último endereço
    while (info.block_fim != ultimo_endereco) {
        bloco_inicio = info.block_fim + 1;

        printf("Informe o bloco final do próximo nó: ");
        scanf("%d", &bloco_fim);

        state = (info.state == 'L') ? 'O' : 'L';

        Informacao_memoria novaInfo;
        novaInfo.state = state;
        novaInfo.block_inicio = bloco_inicio;
        novaInfo.block_fim = bloco_fim;

        inserir_Elemento_ARV_2_3(raiz, novaInfo);
        info = novaInfo;
    }
}

void inserir_Elemento_ARV_2_3(ARVORE2_3 **no, Informacao info, Informacao *sobe, ARVORE2_3 *pai) {
    Informacao sobe_sup;
    ARVORE2_3 *maior = NULL;

    if (*no == NULL) {
        // Criação do nó inicial
        *no = criar_no(info, NULL, NULL);
    } else {
        // Caso seja uma folha
        if (eh_folha_Q3(*no)) {
            // Se o nó tiver apenas um elemento
            if ((*no)->quant_infos == 1) {
                if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) != 0) {
                    add_elementos(*no, info, NULL);
                } else {
                    insere_arvore_binaria(&((*no)->info1.palavra_ingles), info.palavra_ingles->palavra_ingles, info.palavra_ingles->unidade);
                }
            } else if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) != 0) { 
                // Realiza a quebra do nó
                maior = quebra_No(no, info, sobe, NULL);
                if (pai == NULL) {
                    *no = criar_no(*sobe, *no, maior);
                }
            } else {
                insere_arvore_binaria(&((*no)->info2.palavra_ingles), info.palavra_ingles->palavra_ingles, info.palavra_ingles->unidade);
            }
        } else { // Caso não seja folha
            if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) < 0) {
                inserir_Elemento_ARV_2_3(&((*no)->esquerda), info, sobe, *no);
            } else if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) == 0) {
                insere_arvore_binaria(&((*no)->info1.palavra_ingles), info.palavra_ingles->palavra_ingles, info.palavra_ingles->unidade);
            } else if ((*no)->quant_infos == 1 || strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) < 0) {
                inserir_Elemento_ARV_2_3(&((*no)->centro), info, sobe, *no);
            } else if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) == 0) {
                insere_arvore_binaria(&((*no)->info2.palavra_ingles), info.palavra_ingles->palavra_ingles, info.palavra_ingles->unidade);
            } else {
                inserir_Elemento_ARV_2_3(&((*no)->direita), info, sobe, *no);
            }

            // Gerenciamento de nós com divisão
            if (maior) {
                if ((*no)->quant_infos == 1) {
                    add_elementos(*no, *sobe, maior);
                } else {
                    quebra_No(no, *sobe, &sobe_sup, &maior);
                    if (!pai) {
                        *no = criar_no(sobe_sup, *no, maior);
                    }
                }
            }
        }
    }
}


/**
 * @brief Retorna a maior informação armazenada na árvore 2-3.
 *
 * Esta função verifica a quantidade de informações armazenadas na raiz da árvore 2-3.
 * Se a quantidade de informações for igual a 2, retorna a segunda informação (info2).
 * Caso contrário, retorna a primeira informação (info1).
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @return A maior informação armazenada na raiz da árvore 2-3.
 */
Informacao_memoria maior_info(ARVORE2_3 *raiz){
    return raiz->quant_infos == 2 ? raiz->info2 : raiz->info1;
}

/**
 * @brief Aloca blocos livres na árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 e tenta alocar a quantidade de blocos especificada
 * em nós que estão livres (com estado 'L'). Caso o nó tenha blocos livres suficientes,
 * o estado é alterado para 'O' (ocupado) e o intervalo de blocos é atualizado. Além disso,
 * a função tenta concatenar blocos livres de nós adjacentes à direita.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param quantidade_blocos Número de blocos a serem alocados.
 *
 * @note A função imprime informações sobre a alocação e a concatenação de blocos. 
 *       Caso a árvore esteja vazia, uma mensagem de erro é exibida.
 *       Após a alocação, a função `intercalarNos` é chamada para ajustar a árvore, 
 *       caso necessário.
 */
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

/**
 * @brief Intercala nós em uma árvore 2-3.
 *
 * Esta função ajusta os nós de uma árvore 2-3 de acordo com o estado das informações
 * contidas nos nós. Se dois nós consecutivos tiverem o mesmo estado, eles são ajustados
 * para manter a propriedade da árvore 2-3.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 *
 * A função percorre a árvore a partir da raiz e realiza os seguintes ajustes:
 * - Se um nó tiver duas informações com o mesmo estado, a segunda informação é movida
 *   para um novo nó à direita.
 * - Se o estado da primeira informação de um nó for o mesmo do nó à direita, a informação
 *   do nó à direita é movida para o nó atual, ou o estado do nó à direita é ajustado.
 *
 * Se a árvore estiver vazia, uma mensagem é exibida.
 */
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

/**
 * @brief Aloca blocos de memória em uma árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 e aloca blocos de memória conforme a quantidade especificada.
 * Se um nó com estado 'L' (livre) e tamanho suficiente for encontrado, ele será marcado como 'O' (ocupado).
 * Além disso, a função tenta concatenar nós adjacentes livres.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param quantidade_blocos Quantidade de blocos de memória a serem alocados.
 */
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

/**
 * @brief Libera blocos de memória em uma árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 e libera os blocos de memória que estão ocupados ('O') e que têm tamanho 
 * maior ou igual à quantidade de blocos especificada. Após liberar os blocos, a função tenta concatenar nós 
 * adjacentes que estão livres ('L') para otimizar o uso da memória.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param quantidade_blocos Quantidade de blocos a serem liberados.
 *
 * A função imprime informações detalhadas sobre os blocos liberados e os estados dos nós após a liberação e 
 * possível concatenação. No final, chama a função `intercalarNos` para realizar operações adicionais na árvore.
 */
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

/**
 * @brief Exibe os nós de uma árvore 2-3.
 *
 * Esta função percorre recursivamente a árvore 2-3 e exibe as informações
 * armazenadas em cada nó. Para cada nó, são exibidos o estado e os blocos
 * inicial e final das informações contidas nele.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 */
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

void no_2_3_adicionar_info_Q3(ARVORE2_3 *no, Informacao_memoria info, ARVORE2_3 *filho_maior)
{
    if (info.block_inicio != no->info1.block_inicio)
    {
        no->info2 = info;
        no->direita = filho_maior;
    }
    else
    {
        no->info2 = no->info1;
        no->direita = no->centro;
        no->centro = filho_maior;
        no->info1 = info;
    }
    no->quant_infos = 2;
}

void no_2_3_desacolar_Q3(ARVORE2_3 **no)
{
    free(*no);
    *no = NULL;
}

int eh_folha_Q3(ARVORE2_3 *no)
{
    return no->esquerda == NULL;
}

ARVORE2_3 *no_2_3_juntar_Q3(ARVORE2_3 *filho1, Informacao_memoria info, ARVORE2_3 *maior, ARVORE2_3 **raiz)
{
    if (filho1->quant_infos == 2)
        filho1->quant_infos = 1;

    no_2_3_adicionar_info_Q3(filho1, info, maior);

    (*raiz)->quant_infos--;

    if ((*raiz)->quant_infos == 0)
        no_2_3_desacolar_Q3(raiz);

    return filho1;
}

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

/**
 * @brief Libera todos os nós de uma árvore 2-3.
 *
 * Esta função percorre recursivamente a árvore 2-3 a partir da raiz e libera
 * a memória de todos os nós, incluindo os nós filhos (esquerda, centro e direita).
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 */
void liberarNos(ARVORE2_3 *raiz){
    if (raiz){
        liberarNos(raiz->esquerda);
        liberarNos(raiz->centro);
        liberarNos(raiz->direita);
        free(raiz);
    }
}

