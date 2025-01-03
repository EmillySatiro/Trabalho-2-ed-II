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
ARVORE2_3* criar_no_Q3(Informacao_memoria info, ARVORE2_3* esq, ARVORE2_3* centro, ARVORE2_3* dir) {
    ARVORE2_3* novo = (ARVORE2_3*) malloc(sizeof(ARVORE2_3));

    // Inicializa o novo nó com a informação e filhos passados
    novo->info1 = info;
    novo->quant_infos = 1;  // Inicialmente, o nó tem uma informação

    novo->esquerda = esq;
    novo->centro = centro;
    novo->direita = dir;

    return novo;
}

void insere_Q3(ARVORE2_3 **raiz, Informacao_memoria info)
{
    Informacao_memoria sobe;
    ARVORE2_3 *novo_no = inserir_Elemento_Q3(raiz, info, &sobe, NULL);
    if (novo_no != NULL && *raiz != NULL)
    {
        ARVORE2_3 *maior = NULL;
        if (sobe.block_fim > maior_info(*raiz).block_fim)
        {
            maior = quebra_No_Q3(raiz, sobe, &sobe, &novo_no);
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


ARVORE2_3* inserir_Elemento_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 **pai) {
    Informacao_memoria sobe_sup;
    ARVORE2_3 *maior = NULL;

    // Se o nó for NULL, cria um novo nó
    if (*no == NULL) {
        *no = criar_no_Q3(info, NULL, NULL, NULL);
    } else {
        // Verifica se é folha
        if (eh_folha_Q3(*no)) {
            // Se o nó tem 1 informação
            if ((*no)->quant_infos == 1) {
                if (info.block_fim < (*no)->info1.block_fim) {
                    add_elementos_Q3(*no, info, NULL); // Adiciona à esquerda
                } else if (info.block_fim > (*no)->info1.block_fim) {
                    add_elementos_Q3(*no, info, NULL); // Adiciona à direita
                } else {
                    atualizar_no_Q3(*no, info); // Atualiza valores caso exista
                }
            } else if (info.block_fim != (*no)->info2.block_fim) { // Para nós com duas informações
                maior = quebra_No_Q3(no, info, sobe, NULL);
                if (pai == NULL) { // Cria nova raiz caso necessário
                    *no = criar_no_Q3(*sobe, *no, maior, NULL);
                    maior = NULL;
                }
            } else {
                atualizar_no_Q3(*no, info);
            }
        } else { // Caso não seja folha
            if (info.block_fim < (*no)->info1.block_fim) {
                maior = inserir_Elemento_Q3(&((*no)->esquerda), info, sobe, no);
            } else if (info.block_fim == (*no)->info1.block_fim) {
                atualizar_no_Q3(*no, info);
                maior = NULL;
            } else if ((*no)->quant_infos == 1 || info.block_fim < (*no)->info2.block_fim) {
                maior = inserir_Elemento_Q3(&((*no)->centro), info, sobe, no);
            } else if (info.block_fim == (*no)->info2.block_fim) {
                atualizar_no_Q3(*no, info);
                maior = NULL;
            } else {
                maior = inserir_Elemento_Q3(&((*no)->direita), info, sobe, no);
            }

            // Se "maior" precisa ser reorganizado
            if (maior) {
                if ((*no)->quant_infos == 1) {
                    add_elementos_Q3(*no, *sobe, maior);
                    maior = NULL;
                } else {
                    maior = quebra_No_Q3(no, *sobe, &sobe_sup, &maior);
                    if (pai == NULL) {
                        *no = criar_no_Q3(sobe_sup, *no, maior, NULL);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return maior;
}


ARVORE2_3 *quebra_No_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 **filho)
{
    ARVORE2_3 *maior_info;

    // Depuração inicial
    printf("Quebrando nó: Novo Info = [%d-%d]\n", info.block_inicio, info.block_fim);
    printf("Estado antes da quebra: Info1 = [%d-%d], Info2 = [%d-%d]\n",
           (*no)->info1.block_inicio, (*no)->info1.block_fim,
           (*no)->info2.block_inicio, (*no)->info2.block_fim);

    // Caso 1: Novo valor (info) é maior que info2
    if (info.block_fim > (*no)->info2.block_fim)
    {
        *sobe = (*no)->info2;
        maior_info = criar_no_Q3(info, NULL, NULL, NULL); // Novo elemento é o maior
        maior_info->esquerda = (*no)->direita;
        maior_info->direita = (filho ? *filho : NULL);
        (*no)->direita = NULL;
    }
    // Caso 2: Novo valor está entre info1 e info2
    else if (info.block_fim > (*no)->info1.block_fim)
    {
        *sobe = info;
        maior_info = criar_no_Q3((*no)->info2, NULL, NULL, NULL);
        maior_info->esquerda = (filho ? *filho : NULL);
        maior_info->direita = (*no)->direita;
        (*no)->direita = NULL;
    }
    // Caso 3: Novo valor é menor ou igual a info1
    else
    {
        *sobe = (*no)->info1;
        maior_info = criar_no_Q3((*no)->info2, NULL, NULL, NULL);
        maior_info->esquerda = (*no)->centro;
        maior_info->direita = (*no)->direita;
        (*no)->info1 = info; // Atualiza o menor valor no nó atual
        (*no)->direita = NULL;
    }

    // Atualiza quantidade de informações no nó original
    (*no)->quant_infos = 1;

    // Depuração pós-quebra
    printf("Estado após quebra:\n");
    printf("Nó Atual: Info1 = [%d-%d]\n", (*no)->info1.block_inicio, (*no)->info1.block_fim);
    printf("Novo Nó Maior: Info1 = [%d-%d]\n",
           maior_info->info1.block_inicio, maior_info->info1.block_fim);
    printf("Elemento que Subiu = [%d-%d]\n", sobe->block_inicio, sobe->block_fim);

    return maior_info;
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
Informacao_memoria maior_info(ARVORE2_3 *raiz)
{
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
void alocarNos(ARVORE2_3 **raiz, int quantidade_blocos)
{
    if (*raiz == NULL)
    {
        printf("Árvore vazia.\n");
        return;
    }

    ARVORE2_3 *atual = *raiz;
    int blocos_restantes = quantidade_blocos; // Blocos ainda a serem alocados
    printf("Blocos a serem alocados: %d\n", quantidade_blocos);

    while (atual && blocos_restantes > 0)
    {
        // Verifica se o primeiro bloco possui espaço suficiente e está livre
        if (atual->info1.state == 'L' && 
            (atual->info1.block_fim - atual->info1.block_inicio + 1) >= blocos_restantes)
        {
            // Divide o bloco, se necessário
            if ((atual->info1.block_fim - atual->info1.block_inicio + 1) > blocos_restantes)
            {
                Informacao_memoria livre = {'L', atual->info1.block_inicio + blocos_restantes, atual->info1.block_fim};
                atual->info1.block_fim = atual->info1.block_inicio + blocos_restantes - 1;
                atual->info1.state = 'O';
                
                // Ajusta o próximo bloco para a porção não utilizada
                if (atual->quant_infos == 1)
                {
                    atual->info2 = livre;
                    atual->quant_infos = 2;
                }
                else
                {
                    atual->centro = criar_no_Q3(livre, NULL, NULL, NULL);
                }
            }
            else
            {
                atual->info1.state = 'O'; // Ocupa o bloco inteiro
            }

            blocos_restantes = 0; // Todos os blocos foram alocados
        }
        // Verifica o segundo bloco, se existir
        else if (atual->quant_infos == 2 &&
                 atual->info2.state == 'L' && 
                 (atual->info2.block_fim - atual->info2.block_inicio + 1) >= blocos_restantes)
        {
            // Divide o bloco, se necessário
            if ((atual->info2.block_fim - atual->info2.block_inicio + 1) > blocos_restantes)
            {
                Informacao_memoria livre = {'L', atual->info2.block_inicio + blocos_restantes, atual->info2.block_fim};
                atual->info2.block_fim = atual->info2.block_inicio + blocos_restantes - 1;
                atual->info2.state = 'O';

                atual->centro = criar_no_Q3(livre, NULL, NULL, NULL); // Cria nó adicional para o restante livre
            }
            else
            {
                atual->info2.state = 'O'; // Ocupa o bloco inteiro
            }

            blocos_restantes = 0; // Todos os blocos foram alocados
        }

        // Move para o próximo nó na árvore
        if (blocos_restantes > 0)
        {
            atual = atual->direita;
        }
    }

    if (blocos_restantes > 0)
    {
        printf("Erro: Não há espaço suficiente para alocar %d blocos.\n", quantidade_blocos);
    }
    else
    {
        printf("Blocos alocados com sucesso.\n");
    }

    // Depuração: Exibir estado atual da árvore
    intercalarNos(raiz);
    printf("Finalização da alocação de blocos.\n");
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
    if (*raiz)
    {
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
            if (atual->direita && atual->direita->info1.state == 'L')
            {
                if (atual->quant_infos == 1)
                {
                    atual->info1.block_fim = atual->direita->info1.block_fim;
                }
                else if (atual->quant_infos == 2 && atual->info2.state == 'L')
                {
                    atual->info2.block_fim = atual->direita->info1.block_fim;
                }
            }

            if (atual->direita && atual->quant_infos == 2 && atual->direita->info1.state == 'L')
            {
                if (atual->info2.state == 'L')
                {
                    atual->info2.block_fim = atual->direita->info1.block_fim;
                }
            }

            printf("Valor atual após a concatenação, se houve:\n");
            printf("Info1 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info1.state, atual->info1.block_inicio, atual->info1.block_fim);
            if (atual->quant_infos == 2)
            {
                printf("Info2 Status: %c, Bloco inicial: %d, Bloco final: %d\n", atual->info2.state, atual->info2.block_inicio, atual->info2.block_fim);
            }

            atual = atual->direita;
            contador++;
        }

        printf("Finalização da liberação de blocos.\n");

        intercalarNos(raiz);
    }
    else
    {
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
