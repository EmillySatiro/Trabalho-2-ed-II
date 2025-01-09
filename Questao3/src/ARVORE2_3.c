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
ARVORE2_3 *criar_no_Q3(Informacao_memoria info, ARVORE2_3 *esq, ARVORE2_3 *centro, ARVORE2_3 *dir)
{
    ARVORE2_3 *novo = (ARVORE2_3 *)malloc(sizeof(ARVORE2_3));

    // Inicializa o novo nó com a informação e filhos passados
    novo->info1 = info;
    novo->quant_infos = 1; // Inicialmente, o nó tem uma informação

    novo->esquerda = esq;
    novo->centro = centro;
    novo->direita = dir;

    return novo;
}

void insere_Q3(ARVORE2_3 **raiz, Informacao_memoria info)
{
    Informacao_memoria sobe;
    ARVORE2_3 *novo_no = inserir_Elemento_Q3(*raiz, raiz, info, &sobe);
    if (novo_no != NULL && *raiz != NULL)
    {
        ARVORE2_3 *maior = NULL;
        if (sobe.block_fim > maior_info(raiz).block_fim)
        {
            maior = novo_no;
        }
        else
        {
            maior = quebra_No_Q3(raiz, sobe, &sobe, novo_no);
        }
        if (maior != NULL)
        {
            *raiz = no_2_3_juntar_Q3(*raiz, sobe, maior, raiz);
        }
    }
    else if (novo_no != NULL)
    {
        *raiz = criar_no_Q3(sobe, *raiz, novo_no, NULL);
    }
}

Informacao_memoria criar_info(int state, int block_inicio, int block_fim)
{
    Informacao_memoria info;
    info.state = state;
    info.block_inicio = block_inicio;
    info.block_fim = block_fim;

    return info;
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
void cadastrarNos(ARVORE2_3 **raiz, int ultimo_endereco)
{
    Informacao_memoria info;
    char state;
    int bloco_inicio = 0, bloco_fim;

    // Entrada inicial com validação do estado
    printf("Informe o estado do primeiro nó (L para livre, O para ocupado): ");
    while (1)
    {
        scanf(" %c", &state);
        if (state == 'L' || state == 'O')
        {
            break;
        }
        printf("Entrada inválida. Informe L ou O: ");
    }

    // Primeira entrada de bloco_fim
    while (1)
    {
        printf("Informe o bloco final do primeiro nó (deve ser >= 0 e <= %d): ", ultimo_endereco);
        scanf("%d", &bloco_fim);

        // Validação do bloco_fim
        if (bloco_fim >= 0 && bloco_fim <= ultimo_endereco)
        {
            break;
        }
    }

    // Cria o primeiro nó
    info = criar_info(state, bloco_inicio, bloco_fim);
    insere_Q3(&(*raiz), info);

    // Imprime os valores do nó criado
    printf("====================================\n");
    printf("Estado: %c\n", info.state);
    printf("Bloco Inicial: %d\n", info.block_inicio);
    printf("Bloco Final: %d\n", info.block_fim);
    printf("====================================\n");

    // Continuar cadastrando até o último endereço
    while (info.block_fim < ultimo_endereco)
    {
        bloco_inicio = info.block_fim + 1;

        // Entrada e validação do próximo bloco_fim
        while (1)
        {
            printf("Informe o bloco final do próximo nó (máx: %d): ", ultimo_endereco);
            scanf("%d", &bloco_fim);

            // Validação do bloco_fim
            if (bloco_fim > bloco_inicio && bloco_fim <= ultimo_endereco)
            {
                break;
            }
        }

        // Atualização do estado alternado
        state = (info.state == 'L') ? 'O' : 'L';

        // Criação do novo nó
        Informacao_memoria novaInfo = criar_info(state, bloco_inicio, bloco_fim);
        insere_Q3(raiz, novaInfo);

        // Imprime os valores do nó criado
        printf("====================================\n");
        printf("Estado: %c\n", novaInfo.state);
        printf("Bloco Inicial: %d\n", novaInfo.block_inicio);
        printf("Bloco Final: %d\n", novaInfo.block_fim);
        printf("====================================\n");

        // Atualizar info com o novo nó criado
        info = novaInfo;
    }
}

void atualizar_no_Q3(ARVORE2_3 *no, Informacao_memoria info)
{
    if (info.block_fim == no->info1.block_fim)
    {
        no->info1 = info;
    }
    else
    {
        no->info2 = info;
    }
}

ARVORE2_3 *inserir_Elemento_Q3(ARVORE2_3 *pai, ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe)
{
    ARVORE2_3 *maior = NULL;

    if (*no == NULL)
    {
        *no = criar_no_Q3(info, NULL, NULL, NULL);
    }
    else
    {
        // Verifica se o elemento já existe no nó
        if (info.block_fim == (*no)->info1.block_fim)
        {
            atualizar_no_Q3(*no, info); // Atualiza a informação existente
            maior = NULL;
        }
        else if ((*no)->quant_infos == 2 && info.block_fim == (*no)->info2.block_fim)
        {
            atualizar_no_Q3(*no, info); // Atualiza a segunda informação
            maior = NULL;
        }
        else
        {
            // Verifica se é um nó folha
            if (eh_folha_Q3(*no))
            {
                if ((*no)->quant_infos == 1)
                {
                    add_elementos_Q3(*no, info, maior); // Adiciona diretamente no nó
                }
                else
                {
                    // Divide o nó em dois
                    ARVORE2_3 *novo = quebra_No_Q3(no, info, sobe, maior);
                    if (pai == NULL)
                    {
                        // Cria uma nova raiz
                        ARVORE2_3 *novo_no = criar_no_Q3(*sobe, *no, novo, NULL);
                        *no = novo_no;
                    }
                    else
                    {
                        maior = novo;
                    }
                }
            }
            else
            {
                // Nó interno - desce até encontrar o local correto
                if (info.block_fim < (*no)->info1.block_fim)
                {
                    maior = inserir_Elemento_Q3(*no, &((*no)->esquerda), info, sobe);
                }
                else if ((*no)->quant_infos == 1 || info.block_fim < (*no)->info2.block_fim)
                {
                    maior = inserir_Elemento_Q3(*no, &((*no)->centro), info, sobe);
                }
                else
                {
                    maior = inserir_Elemento_Q3(*no, &((*no)->direita), info, sobe);
                }

                // Gerencia divisão do nó após inserir no filho
                if (maior != NULL)
                {
                    if ((*no)->quant_infos == 1)
                    {
                        add_elementos_Q3(*no, *sobe, maior); // Adiciona no nó pai
                        maior = NULL;
                    }
                    else
                    {
                        Informacao_memoria sobe1;
                        ARVORE2_3 *novo = quebra_No_Q3(no, *sobe, &sobe1, maior);
                        if (pai == NULL)
                        {
                            ARVORE2_3 *novo_no = criar_no_Q3(sobe1, *no, novo, NULL);
                            *no = novo_no;
                            maior = NULL;
                        }
                        else
                        {
                            maior = novo;
                            *sobe = sobe1;
                        }
                    }
                }
            }
        }
    }
    return maior;
}

ARVORE2_3 *quebra_No_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 *filho)
{
    ARVORE2_3 *novo_no;

    // Caso 1: Novo valor (info) é menor que info1
    if (info.block_fim <= (*no)->info1.block_fim)
    {
        *sobe = (*no)->info1;
        novo_no = criar_no_Q3((*no)->info2, (*no)->centro, (*no)->direita, NULL);

        (*no)->info1 = info;
        (*no)->centro = filho;
    }
    // Caso 2: Novo valor está entre info1 e info2
    else if (info.block_fim <= (*no)->info2.block_fim)
    {
        *sobe = info;
        novo_no = criar_no_Q3((*no)->info2, filho, (*no)->direita, NULL);
    }
    // Caso 3: Novo valor é maior que info2
    else
    {
        *sobe = (*no)->info2;
        novo_no = criar_no_Q3(info, (*no)->direita, filho, NULL);
    }

    // Atualiza informações no nó atual
    (*no)->quant_infos = 1;
    (*no)->direita = NULL;

    // Depuração pós-quebra
    printf("Estado após quebra:\n");
    printf("Nó Atual: Info1 = [%d-%d]\n", (*no)->info1.block_inicio, (*no)->info1.block_fim);
    printf("Novo Nó Maior: Info1 = [%d-%d]\n",
           novo_no->info1.block_inicio, novo_no->info1.block_fim);
    printf("Elemento que Subiu = [%d-%d]\n", sobe->block_inicio, sobe->block_fim);

    return novo_no;
}

void add_elementos_Q3(ARVORE2_3 *no, Informacao_memoria Info, ARVORE2_3 *filho)
{

    if (Info.block_fim > no->info1.block_fim)
    {
        no->info2 = Info;
        no->direita = filho;
    }
    else
    {
        no->info2 = no->info1;
        no->direita = no->centro;
        no->info1 = Info;
        no->centro = filho;
    }
    no->quant_infos = 2;
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
Informacao_memoria maior_info(ARVORE2_3 **raiz)
{
    return (*raiz)->quant_infos == 2 ? (*raiz)->info2 : (*raiz)->info1;
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
void alocarBlocoRecursivo(ARVORE2_3 *atual, int *blocos_restantes)
{
    if (atual == NULL || *blocos_restantes == 0)
    {
        return; // Base da recursão: Nó vazio ou blocos alocados
    }

    // Tenta alocar em info1
    if (atual->info1.state == 'L')
    {
        int tamanho_info1 = atual->info1.block_fim - atual->info1.block_inicio + 1;
        if (tamanho_info1 >= *blocos_restantes)
        {
            if (tamanho_info1 > *blocos_restantes)
            {
                Informacao_memoria livre = {'L', atual->info1.block_inicio + *blocos_restantes, atual->info1.block_fim};
                atual->info1.block_fim = atual->info1.block_inicio + *blocos_restantes - 1;
                atual->info1.state = 'O';

                // Cria nó central para o restante dos blocos livres
                atual->centro = criar_no_Q3(livre, NULL, NULL, NULL);
            }
            else
            {
                atual->info1.state = 'O';
            }

            printf("Bloco alocado no nó atual (info1).\n");
            *blocos_restantes = 0;
            return;
        }
    }

    // Tenta alocar em info2
    if (atual->quant_infos == 2 && atual->info2.state == 'L')
    {
        int tamanho_info2 = atual->info2.block_fim - atual->info2.block_inicio + 1;
        if (tamanho_info2 >= *blocos_restantes)
        {
            if (tamanho_info2 > *blocos_restantes)
            {
                Informacao_memoria livre = {'L', atual->info2.block_inicio + *blocos_restantes, atual->info2.block_fim};
                atual->info2.block_fim = atual->info2.block_inicio + *blocos_restantes - 1;
                atual->info2.state = 'O';

                // Cria nó central para o restante dos blocos livres
                atual->centro = criar_no_Q3(livre, NULL, NULL, NULL);
            }
            else
            {
                atual->info2.state = 'O';
            }

            printf("Bloco alocado no nó atual (info2).\n");
            *blocos_restantes = 0;
            return;
        }
    }

    // Recursão para os nós filhos (esquerda, centro e direita)
    alocarBlocoRecursivo(atual->esquerda, blocos_restantes);
    alocarBlocoRecursivo(atual->centro, blocos_restantes);
    alocarBlocoRecursivo(atual->direita, blocos_restantes);
}

void alocarBloco(ARVORE2_3 **raiz, int quantidade_blocos)
{
    if (*raiz == NULL)
    {
        printf("Árvore vazia.\n");
        return;
    }

    int blocos_restantes = quantidade_blocos;

    // Chamada inicial para o algoritmo recursivo
    alocarBlocoRecursivo(*raiz, &blocos_restantes);

    if (blocos_restantes > 0)
    {
        printf("Não foi possível alocar todos os blocos. Restantes: %d\n", blocos_restantes);
    }
    else
    {
        printf("Alocação de blocos concluída com sucesso.\n");
    }

    // Ajusta a estrutura da árvore após a alocação
    intercalarNos(raiz);
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
    if (*raiz)
    {
        ARVORE2_3 *atual = *raiz;
        while (atual && atual->direita)
        {
            // Se info1 e info2 do nó atual tiverem o mesmo estado, ajusta
            if (atual->quant_infos == 2 && atual->info1.state == atual->info2.state)
            {
                // Move info2 para a direita
                ARVORE2_3 *novoNo = criar_no_Q3(atual->info2, NULL, NULL, NULL);
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
    }
    else
    {
        printf("Árvore vazia.\n");
    }
}

void concatenarBlocos(ARVORE2_3 *atual, int *blocos_restantes)
{

    int tamanho_info1 = atual->info1.block_fim - atual->info1.block_inicio + 1;
    int tamanho_info2 = atual->info2.block_fim - atual->info2.block_inicio + 1;

    if (tamanho_info1 + tamanho_info2 >= *blocos_restantes)
    {
        Informacao_memoria nova_info;
        nova_info.state = 'L';
        nova_info.block_inicio = atual->info1.block_inicio;
        nova_info.block_fim = atual->info2.block_fim;

        ARVORE2_3 *novo_no = criar_no_Q3(nova_info, NULL, NULL, NULL);

        // Atualiza o nó atual para ter apenas a nova informação
        atual->info1 = nova_info;
        atual->quant_infos = 1;
        atual->centro = NULL;
        atual->direita = NULL;

        *blocos_restantes = 0;

        printf("Blocos concatenados e novo nó criado: de %d a %d\n", nova_info.block_inicio, nova_info.block_fim);
    }
}

ARVORE2_3 *encontrarProximo(ARVORE2_3 *atual)
{
    if (atual == NULL)
    {
        return NULL;
    }

    ARVORE2_3 *proximo = atual->direita;
    while (proximo && proximo->esquerda)
    {
        proximo = proximo->esquerda;
    }

    return proximo;
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
void liberarBlocos(ARVORE2_3 **raiz, int *blocos_restantes, int ultimo_endereco)
{
    if (*raiz == NULL || *blocos_restantes <= 0)
    {
        return; // Nada para liberar ou árvore vazia.
    }

    // Processa o lado esquerdo
    liberarBlocos(&(*raiz)->esquerda, blocos_restantes, ultimo_endereco);

    if (*blocos_restantes <= 0) return;

    // Verifica o primeiro bloco na raiz
    int size_info1 = (*raiz)->info1.block_fim - (*raiz)->info1.block_inicio + 1;
    if (*blocos_restantes >= size_info1)
    {
        (*raiz)->info1.state = 'L';
        *blocos_restantes -= size_info1;
    }
    else
    {
        // Fragmenta o bloco se sobrar espaço
        Informacao_memoria nova_info;
        nova_info.block_inicio = (*raiz)->info1.block_inicio;
        nova_info.block_fim = nova_info.block_inicio + (*blocos_restantes) - 1;
        nova_info.state = 'L';

        (*raiz)->info1.block_inicio += *blocos_restantes;
        insere_Q3(raiz, nova_info);
        *blocos_restantes = 0;
    }

    // Se houver mais blocos e info2 está presente
    if ((*raiz)->quant_infos == 2 && *blocos_restantes > 0)
    {
        int size_info2 = (*raiz)->info2.block_fim - (*raiz)->info2.block_inicio + 1;
        if (*blocos_restantes >= size_info2)
        {
            (*raiz)->info2.state = 'L';
            *blocos_restantes -= size_info2;
        }
        else
        {
            Informacao_memoria nova_info;
            nova_info.block_inicio = (*raiz)->info2.block_inicio;
            nova_info.block_fim = nova_info.block_inicio + (*blocos_restantes) - 1;
            nova_info.state = 'L';

            (*raiz)->info2.block_inicio += *blocos_restantes;
            insere_Q3(raiz, nova_info);
            *blocos_restantes = 0;
        }
    }

    if (*blocos_restantes <= 0) return;

    // Processa o centro e direita
    liberarBlocos(&(*raiz)->centro, blocos_restantes, ultimo_endereco);
    liberarBlocos(&(*raiz)->direita, blocos_restantes, ultimo_endereco);
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
void exibirNos(ARVORE2_3 *raiz)
{
    if (raiz)
    {
        // Visita o subárvore esquerda
        exibirNos(raiz->esquerda);

        // Exibe info1
        if (raiz->quant_infos >= 1)
        {
            printf("====================================\n");
            printf("Estado: %c\n", raiz->info1.state);
            printf("Bloco Inicial: %d\n", raiz->info1.block_inicio);
            printf("Bloco Final: %d\n", raiz->info1.block_fim);
            printf("====================================\n");
        }

        // Visita a subárvore central entre info1 e info2
        exibirNos(raiz->centro);

        // Exibe info2 (se houver)
        if (raiz->quant_infos == 2)
        {
            printf("====================================\n");
            printf("Estado: %c\n", raiz->info2.state);
            printf("Bloco Inicial: %d\n", raiz->info2.block_inicio);
            printf("Bloco Final: %d\n", raiz->info2.block_fim);
            printf("====================================\n");
        }

        // Visita o subárvore direita
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

/**
 * @brief Libera todos os nós de uma árvore 2-3.
 *
 * Esta função percorre recursivamente a árvore 2-3 a partir da raiz e libera
 * a memória de todos os nós, incluindo os nós filhos (esquerda, centro e direita).
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 */
void liberarNos(ARVORE2_3 *raiz)
{
    if (raiz)
    {
        liberarNos(raiz->esquerda);
        liberarNos(raiz->centro);
        liberarNos(raiz->direita);
        free(raiz);
    }
}

void liberarInfo(ARVORE2_3 *raiz, Informacao_memoria info)
{
    if (raiz)
    {
        if (raiz->info1.block_inicio == info.block_inicio)
        {
            raiz->info1.state = 'L';
        }
        else if (raiz->info2.block_inicio == info.block_inicio)
        {
            raiz->info2.state = 'L';
        }
        else
        {
            liberarInfo(raiz->esquerda, info);
            liberarInfo(raiz->centro, info);
            liberarInfo(raiz->direita, info);
        }
    }
}

int arvore23_remover_nao_folha1_q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu = 0;
    ARVORE2_3 *filho = NULL, *pai = raiz;
    Informacao_memoria info_filho;

    // Busca o maior bloco na subárvore à esquerda
    filho = buscar_maior_filho(filho1, &pai, &info_filho);

    if (filho->quant_infos == 2)
    {
        // Se o nó possui duas informações, reduzimos a contagem e movemos os blocos
        *info = info_filho;                     // Atualiza a informação a ser removida
        filho->info2 = (Informacao_memoria){0}; // Marca info2 como vazia
        filho->quant_infos = 1;
        removeu = 1; // Marca que a remoção foi realizada
    }
    else
    {
        // Caso contrário, busca o menor bloco na subárvore à direita
        filho = buscar_menor_filho(filho2, &pai);

        // Usa uma função auxiliar para tratar a remoção e reorganização dos blocos
        removeu = ondinha_1(info_filho, info, pai, origem, &raiz, maior, _1_remover_2_3);
    }

    return removeu;
}
int arvore23_remover_nao_folha2_q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu = 0;
    ARVORE2_3 *filho = NULL, *pai = raiz;
    Informacao_memoria info_filho;

    // Busca o maior bloco na subárvore à esquerda
    filho = buscar_maior_filho(filho1, &pai, &info_filho);

    if (filho->quant_infos == 2)
    {
        // Se o nó possui duas informações, reduzimos a contagem e movemos os blocos
        *info = info_filho;                     // Atualiza a informação a ser removida
        filho->info2 = (Informacao_memoria){0}; // Marca info2 como vazia
        filho->quant_infos = 1;
        removeu = 1; // Marca que a remoção foi realizada
    }
    else
    {
        // Caso contrário, busca o menor bloco na subárvore à direita
        filho = buscar_menor_filho(filho2, &pai);

        // Usa uma função auxiliar para tratar a remoção e reorganização dos blocos
        removeu = ondinha_1(info_filho, info, pai, origem, &raiz, maior, _2_remover_2_3);
    }

    return removeu;
}

int ondinha_1(Informacao_memoria saindo, Informacao_memoria *entrada, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **raiz, ARVORE2_3 **maior, int (*funcao_remover)(ARVORE2_3 **, int *, ARVORE2_3 *, ARVORE2_3 **, ARVORE2_3 **))
{
    // Chama a função de callback para remover o nó desejado
    int removeu = funcao_remover(raiz, &saindo.fim, pai, origem, maior);

    if (removeu)
    {
        // Atualiza a entrada com a informação do bloco removido
        *entrada = saindo;
    }

    return removeu;
}

ARVORE2_3 *buscar_menor_filho(ARVORE2_3 *raiz, ARVORE2_3 **pai)
{

    ARVORE2_3 *filho;

    filho = raiz;

    while (!eh_folha_Q3(filho))
    {
        *pai = filho;
        filho = filho->esquerda;
    }

    return filho;
}

ARVORE2_3 *buscar_maior_filho(ARVORE2_3 *raiz, ARVORE2_3 **pai, Informacao_memoria *info)
{
    ARVORE2_3 *filho;

    filho = raiz;

    while (!eh_folha_Q3(filho))
    {
        *pai = filho;
        filho = filho->direita;
    }

    *info = maior_info(&filho);

    return filho;
}

int _1_remover_2_3(ARVORE2_3 **raiz, int *info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior)
{
    int removeu = 0;

    // Verifica se a raiz não é NULL
    if (*raiz != NULL)
    {
        // Verifica se a informação buscada é igual à info1 ou info2 do nó
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1; // Marca que o item foi encontrado e será removido

            if (eh_folha_Q3(*raiz))
            {
                // Caso o nó seja uma folha, ajusta as informações
                if ((*raiz)->quant_infos == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2; // A primeira informação recebe a segunda
                    (*raiz)->quant_infos = 1;            // O nó passa a ter uma só informação
                }
                else
                {
                    // Se o nó for uma folha e a quantidade de informações for 1
                    if (pai == NULL)
                        no_2_3_desacolar(raiz); // Caso o nó não tenha pai, desacola
                    else
                    {
                        ARVORE2_3 *pai_aux;
                        Informacao_memoria info_pai;

                        // Caso o nó seja filho da esquerda ou do centro
                        if (*raiz == pai->esquerda || (pai->quant_infos == 2 && *raiz == pai->centro))
                        {
                            pai_aux = buscar_pai(*origem, pai->info1.block_inicio);

                            // Identifica qual informação do pai será utilizada
                            if (*raiz == pai->esquerda)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            // Realiza o ajuste em um dos filhos do nó
                            removeu = ondinha_1(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, _1_remover_2_3);
                        }
                        else
                        { // Caso seja filho do centro ou da direita
                            pai_aux = buscar_maior_pai(*origem, (*raiz)->info1.block_inicio);
                            ARVORE2_3 *menor_pai = buscar_menor_pai(*origem, (*raiz)->info1.block_inicio);

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                // Verifica qual pai tem o maior valor de palavra
                                if (pai_aux->info1.block_inicio > (*raiz)->info1.block_inicio)
                                {
                                    info_pai = pai_aux->info1;
                                }
                                else
                                {
                                    info_pai = pai_aux->info2;
                                }
                            }

                            int alt_menor_pai = calcular_altura(menor_pai);
                            int alt_pai_aux = calcular_altura(pai_aux);

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && alt_menor_pai <= alt_pai_aux &&
                                                    (pai_aux->info1.block_inicio > (*raiz)->info1.block_inicio || pai_aux->info2.block_inicio > (*raiz)->info1.block_inicio)))
                            {
                                info_pai = menor_pai->info1;
                            }
                            else
                            {
                                ARVORE2_3 *avo = buscar_pai(*origem, pai_aux->info1.block_fim);
                                removeu = ondinha_1(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, _1_remover_2_3);
                            }
                        }
                    }
                }
            }
            else if (info2)
            {
                // Remover não-folha com 2 informações no nó
                removeu = arvore23_remover_nao_folha1_q3(origem, *raiz, &((*raiz)->info2), (*raiz)->centro, (*raiz)->direita, maior);
            }
            else if (info1)
            {
                // Remover não-folha com 1 informação no nó
                removeu = arvore23_remover_nao_folha1_q3(origem, *raiz, &((*raiz)->info1), (*raiz)->esquerda, (*raiz)->centro, maior);
            }
        }
        else
        {
            // A árvore tem mais filhos, buscando nas diferentes opções de filhos
            if ((info < &(*raiz)->info1.block_inicio))
                removeu = _1_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if ((*raiz)->quant_infos == 1 || info < &(*raiz)->info2.block_inicio)
                removeu = _1_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _1_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }

    return removeu;
}

int _2_remover_2_3(ARVORE2_3 **raiz, int *info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1; // Item encontrado

            if (eh_folha_Q3(*raiz))
            {
                // Remoção de folha
                if ((*raiz)->quant_infos == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if (pai == NULL)
                        no_2_3_desacolar(raiz); // Desacola se não houver pai
                    else
                    {
                        ARVORE2_3 *pai_aux;
                        Informacao_memoria info_pai;

                        if (*raiz == pai->centro || (pai->quant_infos == 2 && *raiz == pai->direita))
                        {
                            pai_aux = buscar_pai(*origem, pai->info1.block_inicio);
                            info_pai = (*raiz == pai->centro) ? pai->info1 : pai->info2;

                            removeu = ondinha_1(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, _2_remover_2_3);
                        }
                        else
                        {
                            pai_aux = buscar_menor_pai(*origem, (*raiz)->info1.block_inicio);
                            ARVORE2_3 *menor_pai = buscar_menor_pai_2_info(*origem, (*raiz)->info1.block_inicio);
                            ARVORE2_3 *avo;

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                info_pai = (pai_aux->quant_infos == 2 && (pai_aux->info2.block_inicio < (*raiz)->info1.block_inicio)) ? pai_aux->info2 : pai_aux->info1;
                                avo = buscar_pai(*origem, info_pai.block_inicio);
                                removeu = ondinha_1(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, _2_remover_2_3);
                            }
                        }
                    }
                }
            }
            else if (info2)
            {
                // Remoção de nó não-folha com 2 informações
                removeu = arvore23_remover_nao_folha2_q3(origem, *raiz, &((*raiz)->info2), (*raiz)->direita, (*raiz)->centro, maior);
            }
            else if (info1)
            {
                // Remoção de nó não-folha com 1 informação
                removeu = arvore23_remover_nao_folha2_q3(origem, *raiz, &((*raiz)->info1), (*raiz)->centro, (*raiz)->esquerda, maior);
            }
        }
        else
        {
            // Busca nas subárvores de acordo com a comparação de blocos
            if (*info < (*raiz)->info1.block_inicio)
                removeu = _2_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if ((*raiz)->quant_infos == 1 || (*info < (*raiz)->info2.block_inicio))
                removeu = _2_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _2_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }

    return removeu;
}

ARVORE2_3 *buscar_pai(ARVORE2_3 *raiz, int block_inicio)
{
    ARVORE2_3 *pai = NULL; // Inicia o ponteiro pai como NULL

    if (raiz != NULL)
    { // Verifica se o nó raiz é válido
        // Verifica se o bloco procurado não corresponde ao bloco_inicio nem ao bloco_fim das informações no nó
        if (!(raiz->info1.block_inicio == block_inicio || raiz->info2.block_inicio == block_inicio))
        {
            // Se o bloco procurado for menor que o bloco_inicio do nó atual
            if (block_inicio < raiz->info1.block_inicio)
            {
                pai = buscar_pai(raiz->esquerda, block_inicio); // Busca o pai no nó da esquerda
            }
            else if (raiz->quant_infos == 1 || (block_inicio < raiz->info2.block_inicio))
            {
                // Se o nó tiver apenas uma informação ou o bloco procurado for menor que o bloco_fim da info2
                pai = buscar_pai(raiz->centro, block_inicio); // Busca o pai no nó do centro
            }
            else
            {
                // Caso contrário, busca o pai no nó da direita
                pai = buscar_pai(raiz->direita, block_inicio);
            }

            // Se o pai for NULL, significa que o bloco procurado não foi encontrado em nenhum dos filhos
            // Então, o nó raiz é considerado como o pai
            if (pai == NULL)
            {
                pai = raiz;
            }
        }
    }

    return pai; // Retorna o ponteiro para o pai
}

ARVORE2_3 *buscar_menor_pai_2_info(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, &info) && !eh_info2(*raiz, &info))
        {
            if (info < raiz->info1.block_inicio)
                pai = buscar_menor_pai_2_info(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || info < raiz->info2.block_inicio)
                pai = buscar_menor_pai_2_info(raiz->centro, info);
            else
                pai = buscar_menor_pai_2_info(raiz->direita, info);

            if (pai == NULL && info < raiz->info1.block_inicio)
                pai = raiz;
        }
    }

    return pai;
}

int eh_info1(ARVORE2_3 no, int *info)
{
    return no.info1.block_inicio == *info;
}

int eh_info2(ARVORE2_3 no, int *info)
{
    return no.quant_infos == 2 && no.info2.block_inicio == *info;
}

void no_2_3_desacolar(ARVORE2_3 **no)
{
    if (*no != NULL)
    {
        free(*no);
        *no = NULL;
    }
}

ARVORE2_3 *buscar_menor_pai(ARVORE2_3 *raiz, int block_inicio)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (raiz->info1.block_inicio == block_inicio || (raiz->quant_infos == 2 && raiz->info2.block_inicio == block_inicio))
            pai = raiz;
        else
        {
            if (block_inicio < raiz->info1.block_inicio)
                pai = buscar_menor_pai(raiz->esquerda, block_inicio);
            else if (raiz->quant_infos == 1 || block_inicio < raiz->info2.block_inicio)
                pai = buscar_menor_pai(raiz->centro, block_inicio);
            else
                pai = buscar_menor_pai(raiz->direita, block_inicio);
        }
    }

    return pai;
}

ARVORE2_3 *buscar_maior_pai(ARVORE2_3 *raiz, int block_inicio)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (raiz->info1.block_inicio == block_inicio || (raiz->quant_infos == 2 && raiz->info2.block_inicio == block_inicio))
            pai = raiz;
        else
        {
            if (block_inicio < raiz->info1.block_inicio)
                pai = buscar_maior_pai(raiz->esquerda, block_inicio);
            else if (raiz->quant_infos == 1 || block_inicio < raiz->info2.block_inicio)
                pai = buscar_maior_pai(raiz->centro, block_inicio);
            else
                pai = buscar_maior_pai(raiz->direita, block_inicio);
        }
    }

    return pai;
}

int calcular_altura(ARVORE2_3 *raiz)
{
    if (raiz == NULL)
        return 0;

    int altura_esq = calcular_altura(raiz->esquerda);
    int altura_centro = calcular_altura(raiz->centro);
    int altura_dir = calcular_altura(raiz->direita);

    int max_altura = altura_esq > altura_centro ? altura_esq : altura_centro;
    max_altura = max_altura > altura_dir ? max_altura : altura_dir;

    return max_altura + 1;
}

void remover(ARVORE2_3 **raiz, int *info)
{
    ARVORE2_3 *maior, *posicao_juncao;
    int removeu = _1_remover_2_3(raiz, info, NULL, raiz, &posicao_juncao);

    if (removeu == -1)
    {
        removeu = 1;
        Informacao_memoria valor_juncao = maior_info(&posicao_juncao);
        maior = NULL;
        int removeu_aux = _2_remover_2_3(raiz, &valor_juncao.block_inicio, maior, raiz, &posicao_juncao);

        if (removeu_aux == -1)
        {
            ARVORE2_3 *pai, *posicao_juncao2;
            Informacao_memoria *entrada;
            pai = buscar_pai(*raiz, valor_juncao.block_inicio);

            if (eh_info1(*posicao_juncao, &valor_juncao.block_inicio))
                entrada = &(posicao_juncao->centro->info1);
            else
                entrada = &(posicao_juncao->direita->info1);

            removeu_aux = ondinha_1(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, _2_remover_2_3);

            if (removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = buscar_pai(*raiz, valor_juncao.block_inicio);
                removeu_aux = ondinha_1(valor_juncao, &(posicao_juncao2->esquerda->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, _1_remover_2_3);

                valor_juncao = maior_info(&posicao_juncao);
                maior = NULL;
                removeu_aux = _2_remover_2_3(raiz, &valor_juncao.block_inicio, maior, raiz, &posicao_juncao);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }
}

void concatenar_no(ARVORE2_3 **raiz, int *endereco_final, int limite, int valor_remover)
{
    *endereco_final = limite;
    remover(raiz, &valor_remover);
}

ARVORE2_3 *buscar_maior_bloco(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_maior)
{
    ARVORE2_3 *maior;
    ARVORE2_3 *pai;
    *valor_maior = NULL;

    if (eh_folha_Q3(no))
    {
        if (no->quant_infos == 2 && no->info1.block_inicio == info->block_inicio)
            maior = no;
        else
            maior = buscar_maior_pai(*raiz, info->block_inicio);

        if (maior != NULL)
        {
            if (maior->info1.block_inicio > info->block_inicio)
                *valor_maior = &(maior->info1);
            else
                *valor_maior = &(maior->info2);
        }
    }
    else
    {
        if (no->info1.block_inicio == info->block_inicio)
            maior = buscar_menor_filho(no->centro, &pai);
        else
            maior = buscar_menor_filho(no->direita, &pai);

        if (maior != NULL)
            *valor_maior = &(maior->info1);
    }

    return maior;
}

ARVORE2_3 *buscar_menor_bloco(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_menor)
{
    ARVORE2_3 *menor, *pai;
    *valor_menor = NULL;

    if (eh_folha_Q3(no))
    {
        if (no->info1.block_inicio != info->block_inicio)
            menor = no;
        else
            menor = buscar_menor_pai(*raiz, info->block_inicio);

        if (menor != NULL)
        {
            if (menor->quant_infos == 2 && menor->info2.block_inicio < info->block_inicio)
                *valor_menor = &(menor->info2);
            else
                *valor_menor = &(menor->info1);
        }
    }
    else if (no->info1.block_inicio == info->block_inicio)
        menor = buscar_maior_filho(no->esquerda, &pai, *valor_menor);
    else
        menor = buscar_maior_filho(no->centro, &pai, *valor_menor);

    return menor;
}