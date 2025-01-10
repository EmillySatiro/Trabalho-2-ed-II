#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARVORE2_3.h"







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
int maior_info(ARVORE2_3 *raiz)
{
    return raiz->quant_infos == 2 ? raiz->info2.block_fim : raiz->info1.block_fim;
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

/**
 * @brief Encontra o menor filho de uma árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz fornecida e encontra o menor filho,
 * que é o nó mais à esquerda da árvore. Além disso, atualiza o ponteiro do pai do menor filho.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param pai Ponteiro para o ponteiro do pai do menor filho encontrado.
 * @return Ponteiro para o menor filho encontrado.
 */
ARVORE2_3 *menor_filho_Q3(ARVORE2_3 *raiz, ARVORE2_3 **pai)
{
    ARVORE2_3 *filho = raiz;

    while (!eh_folha_Q3(filho))
    {
        *pai = filho;
        filho = filho->esquerda;
    }

    return filho;
}

/**
 * @brief Encontra o maior filho de uma árvore 2-3 e retorna o nó folha correspondente.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz até encontrar o maior filho folha.
 * Durante a travessia, ela atualiza o ponteiro do pai e o maior valor encontrado.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param pai Ponteiro para armazenar o pai do maior filho encontrado.
 * @param maior_valor Ponteiro para armazenar a maior informação encontrada no nó folha.
 * @return ARVORE2_3* Ponteiro para o maior filho folha encontrado.
 */
ARVORE2_3 *maior_filho_Q3(ARVORE2_3 *raiz, ARVORE2_3 **pai, Informacao_memoria **maior_valor)
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

/**
 * @brief Busca o nó pai de um nó que contém a informação especificada em uma árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz, procurando o nó pai do nó que contém
 * a informação especificada. Se a informação não estiver presente na árvore, a função retorna
 * NULL. Caso contrário, retorna o nó pai.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param info Informação a ser buscada na árvore.
 * @return Ponteiro para o nó pai do nó que contém a informação especificada, ou NULL se a
 *         informação não estiver presente na árvore.
 */
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

/**
 * @brief Busca o maior pai de um nó em uma árvore 2-3 que possui um valor menor que o valor fornecido.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz e busca o maior pai de um nó que possui um valor menor que o valor fornecido (info).
 * A função retorna o ponteiro para o nó pai encontrado ou NULL se nenhum pai for encontrado.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param info Valor inteiro a ser buscado na árvore.
 * @return ARVORE2_3* Ponteiro para o nó pai encontrado ou NULL se nenhum pai for encontrado.
 */
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

/**
 * @brief Busca o nó pai que possui a menor chave maior que a chave fornecida.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz e busca o nó pai que possui a menor chave
 * maior que a chave fornecida (info). Se a chave fornecida já estiver presente na árvore, a função
 * retorna NULL.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param info Chave a ser buscada na árvore.
 * @return Ponteiro para o nó pai que possui a menor chave maior que a chave fornecida, ou NULL se
 *         a chave fornecida já estiver presente na árvore ou se a árvore estiver vazia.
 */
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

/**
 * @brief Busca o nó pai que possui duas informações e cujo valor da segunda informação é menor que o valor fornecido.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz em busca do nó pai que possui duas informações (quant_infos == 2)
 * e cuja segunda informação (info2.block_inicio) é menor que o valor fornecido (info). A busca é realizada de forma
 * recursiva, navegando pelos filhos esquerdo, centro e direito da árvore conforme o valor da informação fornecida.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param info Valor da informação a ser buscada.
 * @return Retorna um ponteiro para o nó pai que possui duas informações e cuja segunda informação é menor que o valor fornecido.
 *         Retorna NULL se não encontrar tal nó.
 */
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

/**
 * @brief Função auxiliar para remoção e substituição de um nó em uma árvore 2-3.
 *
 * Esta função realiza a remoção de um nó especificado pela estrutura `saindo` e 
 * substitui o conteúdo de `entrada` com os dados removidos. A função de remoção 
 * é fornecida como um parâmetro.
 *
 * @param saindo Estrutura `Informacao_memoria` que contém os dados do nó a ser removido.
 * @param entrada Ponteiro para a estrutura `Informacao_memoria` onde os dados removidos serão armazenados.
 * @param pai Ponteiro para o nó pai na árvore 2-3.
 * @param origem Ponteiro duplo para o nó de origem na árvore 2-3.
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param maior Ponteiro duplo para o maior nó na árvore 2-3.
 * @param funcao_remover Função que realiza a remoção de um nó na árvore 2-3.
 *
 * @return Retorna um inteiro indicando se a remoção foi bem-sucedida.
 */
static int ondinha_Q3(Informacao_memoria saindo, Informacao_memoria *entrada, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **raiz, ARVORE2_3 **maior, int (*funcao_remover)(ARVORE2_3 **, int, ARVORE2_3 *, ARVORE2_3 **, ARVORE2_3 **))
{
    int removeu = funcao_remover(raiz, saindo.block_inicio, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

/**
 * @brief Remove um nó interno de uma árvore 2-3.
 *
 * Esta função remove um nó interno de uma árvore 2-3, ajustando a estrutura da árvore conforme necessário.
 *
 * @param origem Ponteiro duplo para a árvore de origem.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param info Ponteiro para a informação de memória a ser removida.
 * @param filho1 Ponteiro para o primeiro filho da raiz.
 * @param filho2 Ponteiro para o segundo filho da raiz.
 * @param maior Ponteiro duplo para armazenar o maior nó.
 * @return int Retorna 1 se a remoção foi bem-sucedida, caso contrário, retorna 0.
 */
static int remover_no_interno1_Q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu;
    ARVORE2_3 *filho, *pai;
    Informacao_memoria *info_filho;

    pai = raiz;

    filho = maior_filho_Q3(filho1, &pai, &info_filho);

    if (filho->quant_infos == 2)
    {
        *info_filho = *info;
        filho->quant_infos = 1;
    }
    else
    {
        filho = menor_filho_Q3(filho2, &pai);
        removeu = ondinha_Q3(filho->info1, info, pai, origem, &filho, maior, remover1_Q3);
    }

    return removeu;
}


/**
 * @brief Remove um nó interno de uma árvore 2-3.
 *
 * Esta função remove um nó interno de uma árvore 2-3, ajustando os ponteiros e informações conforme necessário.
 *
 * @param origem Ponteiro duplo para a árvore de origem.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param info Ponteiro para a informação de memória a ser removida.
 * @param filho1 Ponteiro para o primeiro filho.
 * @param filho2 Ponteiro para o segundo filho.
 * @param maior Ponteiro duplo para o maior nó.
 * @return int Retorna 1 se a remoção foi bem-sucedida, caso contrário, retorna 0.
 */
static int remover_no_interno2_Q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info, ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior)
{
    int removeu;
    ARVORE2_3 *filho, *pai;
    Informacao_memoria *info_filho;

    pai = raiz;

    filho = menor_filho_Q3(filho1, &pai);

    if (filho->quant_infos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->quant_infos = 1;
    }
    else
    {
        filho = maior_filho_Q3(filho2, &pai, &info_filho);
        removeu = ondinha_Q3(*info_filho, info, pai, origem, &filho, maior, remover2_Q3);
    }

    return removeu;
}

/**
 * @brief Remove um nó de uma árvore 2-3.
 *
 * Esta função remove um nó contendo a informação especificada de uma árvore 2-3.
 * A função lida com diferentes casos, incluindo a remoção de folhas e nós internos,
 * e ajusta a árvore conforme necessário para manter suas propriedades.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param info Informação a ser removida da árvore.
 * @param pai Ponteiro para o nó pai do nó atual.
 * @param origem Ponteiro duplo para a raiz original da árvore.
 * @param maior Ponteiro duplo para armazenar o maior nó durante a remoção.
 * @return int Retorna 1 se a remoção foi bem-sucedida, -1 se houve um caso especial de remoção, ou 0 se a informação não foi encontrada.
 */
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

/**
 * @brief Remove um nó de uma árvore 2-3.
 *
 * Esta função remove um nó contendo a informação especificada de uma árvore 2-3.
 * A função lida com diferentes casos, incluindo a remoção de folhas e nós internos,
 * e ajusta a árvore conforme necessário para manter suas propriedades.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param info Informação a ser removida da árvore.
 * @param pai Ponteiro para o nó pai do nó atual.
 * @param origem Ponteiro duplo para a raiz original da árvore.
 * @param maior Ponteiro duplo para armazenar o maior nó durante a remoção.
 * @return int Retorna 1 se a remoção foi bem-sucedida, -1 se houve um caso especial de remoção, ou 0 se a informação não foi encontrada.
 */
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

/**
 * @brief Remove um nó com a informação especificada de uma árvore 2-3.
 *
 * Esta função remove um nó contendo a informação especificada da árvore 2-3.
 * Se a remoção causar um desequilíbrio na árvore, a função tenta rebalancear
 * a árvore para manter suas propriedades.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param info Informação a ser removida da árvore.
 * @return Retorna 1 se a remoção foi bem-sucedida, -1 caso contrário.
 */
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

/**
 * @brief Realiza o balanceamento de uma árvore 2-3.
 *
 * Esta função verifica se o segundo filho é nulo ou se não possui informações.
 * Se for o caso, ele desacopla o nó e junta os nós filhos com a raiz, 
 * ajustando a árvore para manter suas propriedades de balanceamento.
 *
 * @param raiz Ponteiro para a raiz da árvore.
 * @param filho1 Ponteiro para o primeiro filho.
 * @param filho2 Ponteiro para o segundo filho.
 * @param info Informação de memória a ser utilizada no balanceamento.
 * @param maior Ponteiro para o maior nó após o balanceamento.
 * @return Retorna 1 se o balanceamento foi realizado, caso contrário, retorna 0.
 */
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

/**
 * @brief Rebalanceia uma árvore 2-3 após a remoção de um nó.
 *
 * Esta função percorre a árvore 2-3 a partir da raiz, procurando o nó que contém a informação
 * especificada por 'info'. Se necessário, realiza operações de balanceamento para manter as
 * propriedades da árvore 2-3.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param info Informação a ser utilizada para encontrar o nó a ser rebalançado.
 * @param maior Ponteiro duplo para armazenar o maior nó durante o processo de rebalanceamento.
 * @return Retorna 1 se o rebalanceamento foi realizado com sucesso, -1 se não foi possível
 *         realizar o rebalanceamento, ou 0 se não houve necessidade de rebalanceamento.
 */
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

/**
 * @brief Concatena um valor no endereço final e remove um valor da árvore 2-3.
 *
 * Esta função define o valor do endereço final como o limite fornecido e, em seguida,
 * remove um valor específico da árvore 2-3.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param endereco_final Ponteiro para o endereço final que será atualizado com o limite.
 * @param limite Valor que será atribuído ao endereço final.
 * @param valor_remover Valor que será removido da árvore 2-3.
 */
void concatenar_no_Q3(ARVORE2_3 **raiz, int *endereco_final, int limite, int valor_remover)
{
    *endereco_final = limite;
    remover_Q3(raiz, valor_remover);
}

/**
 * @brief Modifica um nó na árvore 2-3 com base nas informações de memória fornecidas.
 *
 * Esta função modifica um nó na árvore 2-3, ajustando os blocos de memória conforme necessário.
 * Se o estado da informação de memória for 'O' (ocupado), a função verifica se a quantidade
 * fornecida é menor ou igual ao tamanho do bloco de memória. Dependendo do resultado, a função
 * pode inserir novos dados na árvore, concatenar blocos de memória ou alterar o estado do bloco.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param no Ponteiro para o nó atual na árvore 2-3.
 * @param info Ponteiro para a estrutura de informação de memória que contém os dados a serem modificados.
 * @param quant Quantidade de memória a ser modificada.
 */
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


/**
 * @brief Busca o menor bloco em uma árvore 2-3.
 *
 * Esta função busca o menor bloco de memória em uma árvore 2-3 a partir de um nó específico.
 * Se o nó fornecido for uma folha, a função verifica se o bloco de memória do nó é diferente
 * do bloco de memória fornecido. Se for diferente, o nó é considerado o menor. Caso contrário,
 * a função busca o menor bloco no pai do nó.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param no Ponteiro para o nó a partir do qual a busca será realizada.
 * @param info Ponteiro para a informação de memória que está sendo buscada.
 * @param valor_menor Ponteiro para armazenar a informação de memória do menor bloco encontrado.
 * @return Ponteiro para o nó que contém o menor bloco de memória encontrado.
 */
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
        menor = maior_filho_Q3(no->esquerda, &pai, valor_menor);
    else
        menor = maior_filho_Q3(no->centro, &pai, valor_menor);

    return menor;
}

/**
 * @brief Busca o maior bloco de memória a partir de um nó específico em uma árvore 2-3.
 *
 * Esta função busca o maior bloco de memória a partir de um nó específico em uma árvore 2-3.
 * Se o nó fornecido for uma folha, a função verifica se o nó contém duas informações e se a
 * primeira informação corresponde ao bloco de início fornecido. Caso contrário, a função busca
 * o maior pai a partir da raiz. Se o nó não for uma folha, a função busca o menor filho a partir
 * do nó central ou direito, dependendo da correspondência do bloco de início.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param no Ponteiro para o nó a partir do qual a busca será realizada.
 * @param info Ponteiro para a estrutura de informação de memória que contém o bloco de início a ser buscado.
 * @param valor_maior Ponteiro para um ponteiro que será atualizado para apontar para a maior informação de memória encontrada.
 * @return Ponteiro para o nó que contém o maior bloco de memória encontrado, ou NULL se nenhum bloco for encontrado.
 */
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
            maior = menor_filho_Q3(no->centro, &pai);
        else
            maior = menor_filho_Q3(no->direita, &pai);

        if (maior != NULL)
            *valor_maior = &(maior->info1);
    }

    return maior;
}

/**
 * @brief Desaloca um nó em uma árvore 2-3.
 *
 * Esta função busca um nó na memória com base no status fornecido e, se encontrado,
 * modifica o nó de acordo com as informações de memória associadas.
 *
 * @param arvore Ponteiro duplo para a árvore 2-3.
 * @param quant_nos Quantidade de nós na árvore.
 * @param status Status do nó a ser buscado na memória.
 * @return Retorna 1 se um nó foi encontrado e modificado, caso contrário, retorna 0.
 */
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

/**
 * @brief Busca um nó na árvore 2-3 que atenda aos critérios especificados.
 *
 * Esta função percorre a árvore 2-3 em busca de um nó que contenha uma informação
 * com estado 'O' e que tenha um bloco de memória disponível com tamanho suficiente
 * para a quantidade especificada. A busca é realizada em pré-ordem (esquerda, centro, direita).
 *
 * @param arvore Ponteiro duplo para a raiz da árvore 2-3.
 * @param quant Quantidade de blocos de memória necessários.
 * @param status Estado desejado da informação ('O' para ocupado).
 * @param info_escolhido Ponteiro duplo para armazenar a informação escolhida, se encontrada.
 * @return Ponteiro para o nó da árvore que contém a informação escolhida, ou NULL se não encontrado.
 */
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