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


/**
 * @brief Insere uma nova informação na árvore 2-3.
 *
 * Esta função insere um novo elemento na árvore 2-3, ajustando a estrutura da árvore conforme necessário.
 * Se a inserção resultar em um nó que precisa ser dividido, a função realiza a divisão e ajusta a raiz da árvore.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param info Informação a ser inserida na árvore.
 */

void insere_Q3(ARVORE2_3 **raiz, Informacao_memoria info)
{
    Informacao_memoria sobe;
    ARVORE2_3 *novo_no = inserir_Elemento_Q3(*raiz, raiz, info, &sobe);
    if (novo_no != NULL && *raiz != NULL)
    {
        ARVORE2_3 *maior = NULL;
        if (sobe.block_fim > maior_info(*raiz))
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

/**
 * @brief Exibe os nós de uma árvore 2-3 em ordem.
 *
 * Esta função percorre a árvore 2-3 em ordem e exibe as informações armazenadas
 * em cada nó. A árvore é percorrida da seguinte maneira:
 * 1. Visita a subárvore esquerda.
 * 2. Exibe a primeira informação (info1) do nó atual, se existir.
 * 3. Visita a subárvore central (entre info1 e info2).
 * 4. Exibe a segunda informação (info2) do nó atual, se existir.
 * 5. Visita a subárvore direita.
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

/**
 * @brief Adiciona uma nova informação a um nó 2-3.
 *
 * Esta função adiciona uma nova informação (info) a um nó 2-3 (no). Dependendo do valor de 
 * info.block_inicio, a nova informação será adicionada como info1 ou info2 do nó. Além disso, 
 * ajusta os ponteiros para os filhos do nó de acordo com a nova informação.
 *
 * @param no Ponteiro para o nó 2-3 onde a informação será adicionada.
 * @param info Estrutura do tipo Informacao_memoria contendo a nova informação a ser adicionada.
 * @param filho_maior Ponteiro para o filho maior que será ajustado no nó.
 */
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

/**
 * @brief Libera a memória alocada para um nó da árvore 2-3 e define o ponteiro como NULL.
 *
 * Esta função recebe um ponteiro para um ponteiro de nó da árvore 2-3, libera a memória
 * alocada para o nó e define o ponteiro para NULL, evitando assim acessos futuros a uma
 * área de memória já liberada.
 *
 * @param no Ponteiro para um ponteiro de nó da árvore 2-3 que será desalocado.
 */
void no_2_3_desacolar_Q3(ARVORE2_3 **no)
{
    free(*no);
    *no = NULL;
}

/**
 * @brief Verifica se um nó é uma folha na árvore 2-3.
 *
 * Esta função verifica se o nó fornecido é uma folha, ou seja,
 * se ele não possui filhos à esquerda.
 *
 * @param no Ponteiro para o nó da árvore 2-3 a ser verificado.
 * @return Retorna 1 se o nó for uma folha, caso contrário, retorna 0.
 */
int eh_folha_Q3(ARVORE2_3 *no)
{
    return no->esquerda == NULL;
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

/**
 * @brief Libera a informação de um nó da árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz e marca a informação
 * correspondente como liberada ('L') se o bloco de início da informação
 * coincidir com o bloco de início fornecido.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param info Estrutura contendo a informação de memória a ser liberada.
 */
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


//a partir daquiiiiiiiiii ==============================================================================================================================================================

/**
 * @brief Verifica se o valor fornecido é igual ao valor de info1 do nó.
 *
 * Esta função compara o valor fornecido (info) com o valor de info1.block_inicio
 * do nó (no) e retorna 1 (verdadeiro) se forem iguais, ou 0 (falso) caso contrário.
 *
 * @param no Ponteiro para o nó da árvore 2-3.
 * @param info Valor a ser comparado com info1.block_inicio do nó.
 * @return int Retorna 1 se info for igual a no->info1.block_inicio, caso contrário retorna 0.
 */
static int eh_info1_Q3(ARVORE2_3 *no, int info)
{
    return info == no->info1.block_inicio;
}

/**
 * @brief Verifica se o nó possui duas informações e se a segunda informação é igual ao valor fornecido.
 *
 * @param no Ponteiro para o nó da árvore 2-3.
 * @param info Valor a ser comparado com a segunda informação do nó.
 * @return Retorna 1 se o nó possui duas informações e a segunda informação é igual ao valor fornecido, caso contrário, retorna 0.
 */
static int eh_info2_Q3(ARVORE2_3 *no, int info)
{
    return no->quant_infos == 2 && info == no->info2.block_inicio;
}

/**
 * @brief Calcula a altura de uma árvore 2-3 a partir de um nó dado.
 *
 * Esta função calcula a altura de uma árvore 2-3 recursivamente, 
 * considerando apenas a subárvore esquerda do nó fornecido.
 *
 * @param no Ponteiro para o nó da árvore 2-3 a partir do qual a altura será calculada.
 * @return A altura da árvore 2-3 a partir do nó fornecido. Retorna -1 se o nó for NULL.
 */
static int calcular_altura_Q3(ARVORE2_3 *no)
{
    int altura = -1;

    if (no != NULL)
        altura = 1 + calcular_altura_Q3(no->esquerda);

    return altura;
}

/**
 * @brief Verifica se é possível remover um nó da árvore 2-3.
 *
 * Esta função verifica se é possível remover um nó da árvore 2-3 a partir da raiz fornecida.
 * A remoção é possível se o nó raiz contiver exatamente 2 informações ou se for possível
 * remover um nó dos subárvores centro ou esquerda.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @return Retorna 1 se for possível remover um nó, caso contrário, retorna 0.
 */
static int possivel_remover_Q3(ARVORE2_3 *raiz)
{
    int possivel = 0;

    if (raiz != NULL)
    {
        possivel = raiz->quant_infos == 2;

        if (!possivel)
        {
            possivel = possivel_remover_Q3(raiz->centro);

            if (!possivel)
                possivel = possivel_remover_Q3(raiz->esquerda);
        }
    }

    return possivel;
}


/**
 * @brief Quebra um nó 2-3 em dois nós e promove uma informação para o nó pai.
 *
 * Esta função é utilizada para dividir um nó 2-3 que está cheio (contém duas informações)
 * em dois nós e promover uma das informações para o nó pai. A função recebe um nó, uma
 * informação a ser inserida, um ponteiro para armazenar a informação promovida e um
 * ponteiro para o filho maior.
 *
 * @param no Ponteiro para o nó 2-3 que será quebrado.
 * @param info Informação a ser inserida no nó.
 * @param promove Ponteiro para armazenar a informação que será promovida para o nó pai.
 * @param filho_maior Ponteiro para o filho maior que será associado ao novo nó criado.
 * @return ARVORE2_3* Ponteiro para o novo nó criado após a quebra.
 */
static ARVORE2_3 *quebrar_no_q3(ARVORE2_3 *no, Informacao_memoria info, Informacao_memoria *promove, ARVORE2_3 *filho_maior)
{
    ARVORE2_3 *maior;
    if (info.block_inicio > no->info2.block_inicio)
    {
        *promove = no->info2;
        maior = criar_no_Q3(info, no->direita, filho_maior, NULL);

    }
    else if (info.block_inicio > no->info1.block_inicio)
    {
        *promove = info;
        maior = criar_no_Q3(no->info2, filho_maior, no->direita, NULL);
    }
    else
    {
        *promove = no->info1;
        maior = criar_no_Q3(no->info2, no->centro, no->direita, NULL);
        no->info1 = info;
        no->centro = filho_maior;
    }
    no->quant_infos = 1;

    return maior;
}

/**
 * @brief Junta um nó 2-3 com uma nova informação e um nó maior, ajustando a raiz se necessário.
 *
 * Esta função adiciona uma nova informação e um nó maior a um nó 2-3 existente. 
 * Se a raiz tiver zero informações após a adição, a função desacola a raiz.
 *
 * @param filho1 Ponteiro para o nó 2-3 que receberá a nova informação e o nó maior.
 * @param info Informação a ser adicionada ao nó 2-3.
 * @param maior Ponteiro para o nó maior a ser adicionado ao nó 2-3.
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @return Retorna o ponteiro para o nó 2-3 atualizado.
 */
ARVORE2_3 *no_2_3_juntar_Q3(ARVORE2_3 *filho1, Informacao_memoria info, ARVORE2_3 *maior, ARVORE2_3 **raiz)
{
    no_2_3_adicionar_info_Q3(filho1, info, maior);

    (*raiz)->quant_infos--;

    if ((*raiz)->quant_infos == 0)
        no_2_3_desacolar_Q3(raiz);

    return filho1;
}



/**
 * @brief Retorna a maior informação armazenada em um nó 2-3.
 *
 * Esta função verifica a quantidade de informações armazenadas no nó 2-3
 * e retorna um ponteiro para a maior informação.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @return Ponteiro para a maior informação armazenada no nó.
 */
Informacao_memoria *no_2_3_maior_info_Q3(ARVORE2_3 *raiz)
{
    return raiz->quant_infos == 2 ? &(raiz->info2) : &(raiz->info1);
}


/**
 * @brief Busca um nó na árvore 2-3 que contém a informação especificada.
 *
 * Esta função realiza uma busca em uma árvore 2-3 para encontrar um nó que contém
 * a informação especificada. A busca é feita de forma recursiva, navegando pelos
 * filhos esquerdo, central ou direito, dependendo do valor da informação comparado
 * com os valores armazenados nos nós.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param info Informação a ser buscada na árvore.
 * @return Retorna um ponteiro para o nó que contém a informação especificada,
 *         ou NULL se a informação não for encontrada.
 */
ARVORE2_3 *buscar_Q3(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *no = NULL;

    if (raiz != NULL)
    {
        if (eh_info1_Q3(raiz, info) || eh_info2_Q3(raiz, info))
            no = raiz;
        else if (info < raiz->info1.block_fim)
            no = buscar_Q3(raiz->esquerda, info);
        else if (raiz->quant_infos == 1 || info < raiz->info2.block_fim)
            no = buscar_Q3(raiz->centro, info);
        else
            no = buscar_Q3(raiz->direita, info);
    }

    return no;
}

ARVORE2_3 *buscar_menor_filho_Q3(ARVORE2_3 *raiz, ARVORE2_3 **pai)
{
    ARVORE2_3 *filho = raiz;

    while (!eh_folha_Q3(filho))
    {
        *pai = filho;
        filho = filho->esquerda;
    }

    return filho;
}

ARVORE2_3 *buscar_maior_filho_Q3(ARVORE2_3 *raiz, ARVORE2_3 **pai, Informacao_memoria **maior_valor)
{
    ARVORE2_3 *filho = raiz;

    while (!eh_folha_Q3(filho))
    {
        *pai = filho;
        if (filho->quant_infos == 1)
            filho = filho->centro;
        else
            filho = filho->direita;
    }

    if (filho != NULL)
        *maior_valor = no_2_3_maior_info_Q3(filho);

    return filho;
}

ARVORE2_3 *buscar_pai_Q3(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1_Q3(raiz, info) && !eh_info2_Q3(raiz, info))
        {
            if (info < raiz->info1.block_inicio)
                pai = buscar_pai_Q3(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || info < raiz->info2.block_inicio)
                pai = buscar_pai_Q3(raiz->centro, info);
            else
                pai = buscar_pai_Q3(raiz->direita, info);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

ARVORE2_3 *buscar_maior_pai_Q3(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1_Q3(raiz, info) && !eh_info2_Q3(raiz, info))
        {
            if (info < raiz->info1.block_inicio)
                pai = buscar_maior_pai_Q3(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || info < raiz->info2.block_inicio)
                pai = buscar_maior_pai_Q3(raiz->centro, info);
            else
                pai = buscar_maior_pai_Q3(raiz->direita, info);

            if (pai == NULL && ((raiz->quant_infos == 1 && raiz->info1.block_inicio > info) || (raiz->quant_infos == 2 && raiz->info2.block_inicio > info)))
                pai = raiz;
        }
    }

    return pai;
}

ARVORE2_3 *buscar_menor_pai_Q3(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1_Q3(raiz, info) && !eh_info2_Q3(raiz, info))
        {
            if (info < raiz->info1.block_inicio)
                pai = buscar_menor_pai_Q3(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || info < raiz->info2.block_inicio)
                pai = buscar_menor_pai_Q3(raiz->centro, info);
            else
                pai = buscar_menor_pai_Q3(raiz->direita, info);

            if (pai == NULL && raiz->info1.block_inicio < info)
                pai = raiz;
        }
    }

    return pai;
}

ARVORE2_3 *buscar_menor_pai_2_infos_Q3(ARVORE2_3 *raiz, int info)
{
    ARVORE2_3 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1_Q3(raiz, info) && !eh_info2_Q3(raiz, info))
        {
            if (info < raiz->info1.block_inicio)
                pai = buscar_menor_pai_2_infos_Q3(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || info < raiz->info2.block_inicio)
                pai = buscar_menor_pai_2_infos_Q3(raiz->centro, info);
            else
                pai = buscar_menor_pai_2_infos_Q3(raiz->direita, info);

            if (pai == NULL && raiz->quant_infos == 2 && raiz->info2.block_inicio < info)
                pai = raiz;
        }
    }

    return pai;
}

static int ondinha_Q3(Informacao_memoria saindo, Informacao_memoria *entrada, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **raiz, ARVORE2_3 **maior, int (*funcao_remover)(ARVORE2_3 **, int, ARVORE2_3 *, ARVORE2_3 **, ARVORE2_3 **))
{
    int removeu = funcao_remover(raiz, saindo.block_inicio, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

static int remover_no_interno1_Q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu;
    ARVORE2_3 *filho, *pai;
    Informacao_memoria *info_filho;

    pai = raiz;

    filho = buscar_maior_filho_Q3(filho1, &pai, &info_filho);

    if (filho->quant_infos == 2)
    {
        *info_filho = *info;
        filho->quant_infos = 1;
    }
    else
    {
        filho = buscar_menor_filho_Q3(filho2, &pai);
        removeu = ondinha_Q3(filho->info1, info, pai, origem, &filho, maior, remover1_Q3);
    }

    return removeu;
}

static int remover_no_interno2_Q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu;
    ARVORE2_3 *filho, *pai;
    Informacao_memoria *info_filho;

    pai = raiz;

    filho = buscar_menor_filho_Q3(filho1, &pai);

    if (filho->quant_infos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->quant_infos = 1;
    }
    else
    {
        filho = buscar_maior_filho_Q3(filho2, &pai, &info_filho);
        removeu = ondinha_Q3(*info_filho, info, pai, origem, &filho, maior, remover2_Q3);
    }

    return removeu;
}

int remover1_Q3(ARVORE2_3 **raiz, int info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1_Q3(*raiz, info);
        int info2 = eh_info2_Q3(*raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (eh_folha_Q3(*raiz))
            {
                if ((*raiz)->quant_infos == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if (pai == NULL)
                        no_2_3_desacolar_Q3(raiz);
                    else
                    {
                        ARVORE2_3 *pai_aux;
                        Informacao_memoria info_pai;
                        if (*raiz == pai->esquerda || (pai->quant_infos == 2 && *raiz == pai->centro))
                        {
                            pai_aux = buscar_pai_Q3(*origem, pai->info1.block_inicio);

                            if (*raiz == pai->esquerda)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = ondinha_Q3(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, remover1_Q3);
                        }
                        else
                        {
                            pai_aux = buscar_maior_pai_Q3(*origem, (*raiz)->info1.block_inicio);

                            ARVORE2_3 *menor_pai;
                            menor_pai = buscar_menor_pai_2_infos_Q3(*origem, (*raiz)->info1.block_inicio);

                            if (pai_aux != NULL)
                            {
                                if (pai_aux->info1.block_inicio > (*raiz)->info1.block_inicio)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calcular_altura_Q3(menor_pai);
                            int altura_pai_aux = calcular_altura_Q3(pai_aux);

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && altura_menor_pai <= altura_pai_aux && info_pai.block_inicio > menor_pai->info2.block_inicio))
                            {
                                *maior = pai;
                                (*raiz)->quant_infos = 0;
                                removeu = -1;
                            }
                            else
                            {
                                ARVORE2_3 *avo;
                                avo = buscar_pai_Q3(*origem, info_pai.block_inicio);
                                removeu = ondinha_Q3(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, remover1_Q3);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = remover_no_interno1_Q3(origem, *raiz, &((*raiz)->info2), (*raiz)->centro, (*raiz)->direita, maior);
            else if (info1)
                removeu = remover_no_interno1_Q3(origem, *raiz, &((*raiz)->info1), (*raiz)->esquerda, (*raiz)->centro, maior);
        }
        else
        {
            if (info < (*raiz)->info1.block_inicio)
                removeu = remover1_Q3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if ((*raiz)->quant_infos == 1 || info < (*raiz)->info2.block_inicio)
                removeu = remover1_Q3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = remover1_Q3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int remover2_Q3(ARVORE2_3 **raiz, int info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1_Q3(*raiz, info);
        int info2 = eh_info2_Q3(*raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (eh_folha_Q3(*raiz))
            {
                if ((*raiz)->quant_infos == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if (pai == NULL)
                        no_2_3_desacolar_Q3(raiz);
                    else
                    {
                        ARVORE2_3 *pai_aux;
                        Informacao_memoria info_pai;
                        if (*raiz == pai->centro || (pai->quant_infos == 2 && *raiz == pai->direita))
                        {
                            pai_aux = buscar_pai_Q3(*origem, pai->info1.block_inicio);

                            if (*raiz == pai->centro)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = ondinha_Q3(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior,remover2_Q3);
                        }
                        else // Filho da esquerda
                        {
                            pai_aux = buscar_menor_pai_Q3(*origem, (*raiz)->info1.block_inicio);

                            ARVORE2_3 *menor_pai;
                            menor_pai = buscar_menor_pai_2_infos_Q3(*origem, (*raiz)->info1.block_inicio);

                            ARVORE2_3 *avo;
                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if (pai_aux->quant_infos == 2 && pai_aux->info2.block_inicio < (*raiz)->info1.block_inicio)
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = buscar_pai_Q3(*origem, info_pai.block_inicio);
                                removeu = ondinha_Q3(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, remover2_Q3);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = remover_no_interno2_Q3(origem, *raiz, &((*raiz)->info2), (*raiz)->direita, (*raiz)->centro, maior);
            else if (info1)
                removeu = remover_no_interno2_Q3(origem, *raiz, &((*raiz)->info1), (*raiz)->centro, (*raiz)->esquerda, maior);
        }
        else
        {
            if (info < (*raiz)->info1.block_inicio)
                removeu = remover2_Q3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if ((*raiz)->quant_infos == 1 || info < (*raiz)->info2.block_inicio)
                removeu = remover2_Q3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = remover2_Q3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int remover_Q3(ARVORE2_3 **raiz, int info)
{
    ARVORE2_3 *maior, *posicao_juncao;
    int removeu = remover1_Q3(raiz, info, NULL, raiz, &posicao_juncao);

    if (removeu == -1)
    {
        removeu = 1;
        Informacao_memoria valor_juncao = *(no_2_3_maior_info_Q3(posicao_juncao));
        maior = NULL;
        int removeu_aux = rebalancear_Q3(raiz, valor_juncao.block_inicio, &maior);

        if (removeu_aux == -1)
        {
            ARVORE2_3 *pai, *posicao_juncao2;
            Informacao_memoria *entrada;
            pai = buscar_pai_Q3(*raiz, valor_juncao.block_fim);

            if (eh_info1_Q3(posicao_juncao, valor_juncao.block_fim))
                entrada = &(posicao_juncao->centro->info1);
            else
                entrada = &(posicao_juncao->direita->info1);


            removeu_aux = ondinha_Q3(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, remover2_Q3);

            if (removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = buscar_pai_Q3(*raiz, valor_juncao.block_fim);
                removeu_aux = ondinha_Q3(valor_juncao, &(posicao_juncao2->esquerda->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, remover1_Q3);

                valor_juncao = *(no_2_3_maior_info_Q3(posicao_juncao));
                maior = NULL;
                removeu_aux = rebalancear_Q3(raiz, valor_juncao.block_inicio, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

static int balanceamento_Q3(ARVORE2_3 **raiz, ARVORE2_3 *filho1, ARVORE2_3 **filho2, Informacao_memoria info, ARVORE2_3 **maior)
{
    int balanceou = 0;
    if (*filho2 == NULL || (*filho2)->quant_infos == 0)
    {
        if (*filho2 != NULL)
            no_2_3_desacolar_Q3(filho2);

        *maior = no_2_3_juntar_Q3(filho1, info, *maior, raiz);
        balanceou = 1;
    }
    return balanceou;
}

int rebalancear_Q3(ARVORE2_3 **raiz, int info, ARVORE2_3 **maior)
{
    int balanceou = 0;
    if (*raiz != NULL)
    {
        if (!eh_folha_Q3(*raiz))
        {
            if (info < (*raiz)->info1.block_fim)
                balanceou = rebalancear_Q3(&((*raiz)->esquerda), info, maior);
            else if ((*raiz)->quant_infos == 1 || info < (*raiz)->info2.block_fim)
            {
                if ((*raiz)->esquerda->quant_infos == 2 && !possivel_remover_Q3((*raiz)->centro))
                    balanceou = -1;
                else
                    balanceou = rebalancear_Q3(&((*raiz)->centro), info, maior);
            }
            else
            {
                if ((*raiz)->centro->quant_infos == 2 && !possivel_remover_Q3((*raiz)->direita))
                    balanceou = -1;
                else
                    balanceou = rebalancear_Q3(&((*raiz)->direita), info, maior);
            }

            if (balanceou != -1)
            {
                if ((*raiz)->quant_infos == 1)
                    balanceou = balanceamento_Q3(raiz, (*raiz)->esquerda, &((*raiz)->centro), (*raiz)->info1, maior);
                else if ((*raiz)->quant_infos == 2)
                    balanceou = balanceamento_Q3(raiz, (*raiz)->centro, &((*raiz)->direita), (*raiz)->info2, maior);
            }
        }
    }

    return balanceou;
}

void concatenar_no_Q3(ARVORE2_3 **raiz, int *endereco_final, int limite, int valor_remover)
{
    *endereco_final = limite;
    remover_Q3(raiz, valor_remover);
}

void modificar_no(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, int quant)
{
    ARVORE2_3 *menor;
    Informacao_memoria *valor_menor;

    menor = buscar_menor_bloco_Q3(raiz, no, info, &valor_menor);
    if(info->state == 'O'){

        if (quant <= (info->block_fim - info->block_inicio + 1))
        {
            if (menor == NULL)
            {
                Informacao_memoria data;
                data.block_inicio = info->block_inicio;
                data.block_fim = info->block_fim;
                data.inicio = info->inicio;
                data.fim = info->fim + quant - 1;
                data.state = 'L';
                info->inicio += quant;
                insere_Q3(raiz, data);
            }
            else
            {
                valor_menor->block_fim += quant; 
                info->inicio += quant; 
                concatenar_no_Q3(raiz, &(valor_menor->fim), info->block_fim, info->inicio);
                
                
            }
        }
        else
        {
            ARVORE2_3 *maior;
            Informacao_memoria *valor_maior;

            maior = buscar_maior_bloco_Q3(raiz, no, info, &valor_maior);

            if (menor == NULL && maior == NULL)
                info->state = 'L';
            else
            {
                if (menor == NULL)
                {
                    info->state = 'L';
                    concatenar_no_Q3(raiz, &(info->block_fim), valor_maior->fim, valor_maior->inicio);
                }
                else if (maior == NULL)
                    concatenar_no_Q3(raiz, &(valor_menor->fim), info->block_fim, info->inicio);
                else
                {
                    int numero = valor_maior->block_inicio;
                    concatenar_no_Q3(raiz, &(valor_menor->fim), valor_maior->fim, info->inicio);
                    remover_Q3(raiz, numero); 
                }
            }
        }
    }

   
   
}


ARVORE2_3 *buscar_primeiro_no_maior_que_a_info(ARVORE2_3 *raiz, Informacao_memoria info)
{
    ARVORE2_3 *no = NULL;

    if (raiz != NULL)
    {
        if (raiz->info1.block_inicio > info.block_inicio)
            no = raiz;
        else if (raiz->quant_infos == 2 && raiz->info2.block_inicio > info.block_inicio)
            no = raiz;
        else
        {
            if (raiz->info1.block_inicio > info.block_inicio)
                no = buscar_primeiro_no_maior_que_a_info(raiz->esquerda, info);
            else if (raiz->quant_infos == 1 || raiz->info2.block_inicio > info.block_inicio)
                no = buscar_primeiro_no_maior_que_a_info(raiz->centro, info);
            else
                no = buscar_primeiro_no_maior_que_a_info(raiz->direita, info);
        }
    }

    return no;
}

ARVORE2_3 *buscar_menor_bloco_Q3(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_menor)
{
    ARVORE2_3 *menor, *pai;
    *valor_menor = NULL;

    if (eh_folha_Q3(no))
    {
        if (no->info1.block_inicio != info->block_inicio)
            menor = no;
        else
            menor = buscar_menor_pai_Q3(*raiz, info->block_inicio);

        if (menor != NULL)
        {
            if (menor->quant_infos == 2 && menor->info2.block_inicio < info->block_inicio)
                *valor_menor = &(menor->info2);
            else
                *valor_menor = &(menor->info1);
        }
    }
    else if (no->info1.block_inicio == info->block_inicio)
        menor = buscar_maior_filho_Q3(no->esquerda, &pai, valor_menor);
    else
        menor = buscar_maior_filho_Q3(no->centro, &pai, valor_menor);

    return menor;
}

ARVORE2_3 *buscar_maior_bloco_Q3(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_maior)
{
    ARVORE2_3 *maior, *pai;
    *valor_maior = NULL;

    if (eh_folha_Q3(no))
    {
        if (no->quant_infos == 2 && no->info1.block_inicio == info->block_inicio)
            maior = no;
        else
            maior = buscar_maior_pai_Q3(*raiz, info->block_inicio);

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
            maior = buscar_menor_filho_Q3(no->centro, &pai);
        else
            maior = buscar_menor_filho_Q3(no->direita, &pai);

        if (maior != NULL)
            *valor_maior = &(maior->info1);
    }

    return maior;
}

int desalocar_no_Q3(ARVORE2_3 **arvore, int quant_nos, char status)
{
    Informacao_memoria *info_escolhido = NULL;
    ARVORE2_3 *no_escolhido = buscar_no_memoria_Q3(arvore, quant_nos, status, &info_escolhido);

    if (info_escolhido != NULL)
    {
        printf("\nNó escolhido: \n");
        printf("Estado: %c\n", info_escolhido->state);
        printf("Bloco Inicial: %d\n", info_escolhido->block_inicio);
        printf("Bloco Final: %d\n", info_escolhido->block_fim);

        modificar_no(arvore, no_escolhido, info_escolhido, quant_nos);
    }
    else
    {
        printf("\nNão há nó disponível\n");
    }
    return info_escolhido != NULL;
}

ARVORE2_3 *buscar_no_memoria_Q3(ARVORE2_3 **arvore, int quant, char status, Informacao_memoria **info_escolhido)
{
    ARVORE2_3 *no = NULL;
    if (*arvore != NULL)
    {
        no = buscar_no_memoria_Q3(&((*arvore)->esquerda), quant, status, info_escolhido);

        if (*info_escolhido == NULL)
        {
            if ((*arvore)->info1.state == 'O' && ((*arvore)->info1.block_fim - (*arvore)->info1.block_inicio + 1) >= quant)
            {
                *info_escolhido = &((*arvore)->info1);
                no = *arvore;
            }
            else
            {
                no = buscar_no_memoria_Q3(&((*arvore)->centro), quant, status, info_escolhido);
                if ((*arvore)->quant_infos == 2)
                {
                    if ((*arvore)->info2.state == '0' && ((*arvore)->info2.block_fim - (*arvore)->info2.block_inicio + 1) >= quant)
                    {
                        *info_escolhido = &((*arvore)->info2);
                        no = *arvore;
                    }
                    else if (*info_escolhido == NULL)
                    {
                        no = buscar_no_memoria_Q3(&((*arvore)->direita), quant, status, info_escolhido);
                    }
                }
            }
        }
    }
    else
    {
        *info_escolhido = NULL;
    }

    return no;
}