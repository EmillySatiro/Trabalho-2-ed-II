#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Rubro_negra.h"
#include "../Binaria/ARV_BINARIA.h"

// alocar nó
Rubronegra *alocar_no(Informacao_VP *info)
{
    Rubronegra *no = (Rubronegra *)malloc(sizeof(Rubronegra));
    if (no != NULL)
    {
        no->info = (Informacao_VP *)malloc(sizeof(Informacao_VP));
        if (no->info != NULL)
        {
            no->info->palavra_portugues = malloc(strlen(info->palavra_portugues) + 1);
            if (no->info->palavra_portugues != NULL)
            {
                strcpy(no->info->palavra_portugues, info->palavra_portugues);
            }
            else
            {
                printf("Erro ao alocar memória para 'palavra_portugues'!\n");
                free(no->info);
                free(no);
                return NULL;
            }
            no->info->unidade = info->unidade;
            no->info->palavras_ingles = info->palavras_ingles;
            no->cor = VERMELHO;
            no->direita = NULL;
            no->esquerda = NULL;
        }
        else
        {
            printf("Erro ao alocar memória para 'info'!\n");
        }
    }
    else
    {
        printf("erro ao alocar memoria para nó !!\n");
        exit(1);
    }
    return no;
}

Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP *info)
{
    Rubronegra *inserido = NULL;
    if (*raiz == NULL)
    {
        *raiz = alocar_no(info);
        inserido = *raiz;
    }
    else
    {
        if (strcmp(info->palavra_portugues, (*raiz)->info->palavra_portugues) < 0)
        {
            // esquerda
            inserido = inserir_rubro(&((*raiz)->esquerda), info);
        }
        else if (strcmp(info->palavra_portugues, (*raiz)->info->palavra_portugues) > 0)
        {
            // direita
            inserido = inserir_rubro(&((*raiz)->direita), info);
        }
        else
        {
            insere_arvore_binaria(&((*raiz)->info->palavras_ingles), info->palavras_ingles->palavra_ingles, info->unidade);
            inserido = NULL;
        }
    }

    if (inserido != NULL)
    {
        conferindo_regras(raiz);
    }

    return *raiz;
}

Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP *info)
{
    raiz = inserir_rubro(&raiz, info);
    if (raiz != NULL)
    {
        raiz->cor = PRETO;
    }
    return raiz;
}

void conferindo_regras(Rubronegra **raiz)
{
    if (*raiz != NULL)
    {

        // balencear se o filho da  e as esquerda preto direita for vermelho
        if (Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->direita) == VERMELHO)
        {
            girar_esquerda(raiz);
        }

        // balancear se o filho á esquerda e o neto são vermelhos
        if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->esquerda->esquerda) == VERMELHO)
        {
            girar_direita(raiz);
        }

        // ver se os dois filhos são vermelhos
        if (Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->direita) == VERMELHO)
        {
            troca_cor(raiz);
        }
    }
}

int Qual_a_cor(Rubronegra *no)
{
    if (no == NULL)
    {
        return PRETO;
    }
    return no->cor;
}

void troca_cor(Rubronegra **no)
{
    if (no != NULL)
    {
        (*no)->cor = !(*no)->cor; // inverte a cor
        if ((*no)->esquerda)
        {
            (*no)->esquerda->cor = !(*no)->esquerda->cor;
        }

        if ((*no)->direita)
        {
            (*no)->direita->cor = !(*no)->direita->cor;
        }
    }
}

void girar_esquerda(Rubronegra **raiz)
{
    if (*raiz != NULL && (*raiz)->direita != NULL)
    {
        Rubronegra *novo_no = (*raiz)->direita;

        // fiz a rotação aqui lek
        (*raiz)->direita = novo_no->esquerda;
        novo_no->esquerda = *raiz;

        // ajustar cor
        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;

        // atualiza a raiz
        *raiz = novo_no;
    }
}

void move_esquerda(Rubronegra **no)
{
    if (*no != NULL)
    {
        troca_cor(no);
        if ((*no)->direita != NULL && (*no)->direita->esquerda != NULL && Qual_a_cor((*no)->direita->esquerda) == VERMELHO)
        {
            girar_direita(&(*no)->direita);
            girar_esquerda(no);
            troca_cor(no);
        }
    }
}

void girar_direita(Rubronegra **raiz)
{
    if (*raiz != NULL && (*raiz)->esquerda != NULL)
    {
        Rubronegra *novo_no = (*raiz)->esquerda;

        // roda
        (*raiz)->esquerda = novo_no->direita;
        novo_no->direita = *raiz;

        // troca cor
        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;

        // att raiz
        *raiz = novo_no;
    }
}

void mover_direita(Rubronegra **no)
{
    if (*no != NULL)
    {
        troca_cor(no);
        if ((*no)->esquerda != NULL && (*no)->esquerda->esquerda != NULL && Qual_a_cor((*no)->esquerda->esquerda) == VERMELHO)
        {
            girar_direita(no);
            troca_cor(no);
        }
    }
}

void remover_elemento_min(Rubronegra **raiz)
{
    if (*raiz != NULL)
    {
        if ((*raiz)->esquerda == NULL)
        {
            free(*raiz);
            *raiz = NULL;
        }
        else
        {
            if (Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO)
            {
                move_esquerda(raiz);
            }

            remover_elemento_min(&((*raiz)->esquerda));
        }

        if (*raiz)
            conferindo_regras(raiz);
    }
}

Rubronegra *procurar_menor(Rubronegra **raiz)
{
    Rubronegra *no1 = NULL;

    if (*raiz != NULL)
    {
        no1 = *raiz;
        Rubronegra *no2 = (*raiz)->esquerda;

        while (no2 != NULL)
        {
            no1 = no2;
            no2 = no2->esquerda;
        }
    }

    return no1;
}

int remover_no_rubro(Rubronegra **raiz, char *palavra)
{
    int encontrado = 0; // não encontrado

    if (*raiz)
    {
        if (strcmp(palavra, (*raiz)->info->palavra_portugues) < 0)
        {
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO)
            {
                move_esquerda(raiz);
            }

            encontrado = remover_no_rubro(&((*raiz)->esquerda), palavra);
        }
        else
        {
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO)
            {
                girar_direita(raiz);
            }

            if (strcmp(palavra, (*raiz)->info->palavra_portugues) == 0 && (*raiz)->direita == NULL)
            {
                free(*raiz);
                *raiz = NULL;
            }
            else
            {
                if ((*raiz)->direita && Qual_a_cor((*raiz)->direita) == PRETO && Qual_a_cor((*raiz)->direita->esquerda) == PRETO)
                {
                    mover_direita(raiz);
                }

                if (strcmp(palavra, (*raiz)->info->palavra_portugues) == 0)
                {
                    encontrado = 1;
                    Rubronegra *min = procurar_menor(&(*raiz)->direita); // aqui
                    (*raiz)->info = min->info;
                    remover_elemento_min(&((*raiz)->direita));
                }
                else
                {
                    encontrado = remover_no_rubro(&((*raiz)->direita), palavra);
                }
            }
        }

        if (*raiz)
        {
            conferindo_regras(raiz);
        }
    }

    return encontrado;
}

int remover_na_arvore(Rubronegra **raiz, char *palavra)
{
    int resultado = remover_no_rubro(raiz, palavra);
    if (*raiz)
    {
        (*raiz)->cor = PRETO;
    }
    return resultado;
}

// mostrar informações tanto da rubro como da binaria de uma unidade especifica
void mostrar_binaria_em_rubro(Rubronegra *raiz, int unidade)
{
    if (raiz != NULL)
    {
        // Exibe a subárvore esquerda
        mostrar_binaria_em_rubro(raiz->esquerda, unidade);

        // Se a unidade do nó corresponder à unidade fornecida, imprime a palavra
        if (raiz->info->unidade == unidade)
        {
            mostrar_arvore_binaria(raiz->info->palavras_ingles, raiz->info->unidade);
            printf("\n");
        }

        // Exibe a subárvore direita
        mostrar_binaria_em_rubro(raiz->direita, unidade);
    }
}

void mostrar_rubronegra(Rubronegra *raiz)
{
    if (raiz)
    {
        mostrar_rubronegra(raiz->esquerda);
        printf("Palavra: %s, Cor: %s\n", raiz->info->palavra_portugues, raiz->cor == PRETO ? "PRETO" : "VERMELHO");
        printf("Unidade: %d\n", raiz->info->unidade);
        printf("Arvore binaria da palavra(palavras em ingles): \n");
        printf("\n");
        mostrar_arvore_binaria_completa(raiz->info->palavras_ingles);
        mostrar_rubronegra(raiz->direita);
    }
}

Informacao_VP *criar_info_vp(char *palavra_portugues, char *palavra_ingles, int unidade)
{
    Informacao_VP *info = malloc(sizeof(Informacao_VP));
    if (info == NULL)
    {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para a palavra em português e copia a string
    info->palavra_portugues = malloc(strlen(palavra_portugues) + 1);
    if (info->palavra_portugues == NULL)
    {
        perror("Erro ao alocar memória para palavra_portugues");
        exit(EXIT_FAILURE);
    }
    strcpy(info->palavra_portugues, palavra_portugues);

    info->unidade = unidade;
    info->palavras_ingles = NULL; // Inicializa a árvore binária como vazia

    // Insere a palavra em inglês na árvore binária
    insere_arvore_binaria(&info->palavras_ingles, palavra_ingles, unidade);

    return info;
}

// informar uma unidade e então imprima todas as palavras da unidade em português seguida das
// equivalentes em inglês;
void mostrar_palavras_em_portugues_de_uma_unidade(Rubronegra *raiz, int unidade)
{
    if (raiz != NULL)
    {
        mostrar_palavras_em_portugues_de_uma_unidade(raiz->esquerda, unidade);
        if (raiz->info->unidade == unidade)
        {
            printf("Plavra em portugues: %s\n", raiz->info->palavra_portugues);
            printf("Palavras em ingles: \n");
            mostrar_arvore_binaria_completa(raiz->info->palavras_ingles);
            printf("\n");
        }
        mostrar_palavras_em_portugues_de_uma_unidade(raiz->direita, unidade);
    }
}

// informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em
// português dada, independente da unidade;
void Imprimir_toda_palavras(Rubronegra *raiz, char *palavra_portugues)
{
    if (raiz != NULL)
    {

        int comparacao = strcmp(palavra_portugues, raiz->info->palavra_portugues);

        if (comparacao < 0)
        {
            // ela ta subárvore a esquerda
            Imprimir_toda_palavras(raiz->esquerda, palavra_portugues);
        }
        else if (comparacao > 0)
        {
            Imprimir_toda_palavras(raiz->direita, palavra_portugues);
        }
        else
        {
            // Palavra encontrada, exibe as palavras em inglês da árvore binária
            printf("Palavra em português: %s\n", raiz->info->palavra_portugues);
            printf("Palavras em inglês equivalentes:\n");
            mostrar_arvore_binaria_completa(raiz->info->palavras_ingles);
            printf("\n");
        }
    }
}

Rubronegra *buscar_palavra_rubro_negra(Rubronegra *raiz, char *palavra_portugues)
{
    Rubronegra *resultado = NULL;

    if (raiz != NULL)
    {
        int comparacao = strcmp(palavra_portugues, raiz->info->palavra_portugues);

        if (comparacao == 0)
        {
            resultado = raiz;
        }
        else if (comparacao < 0)
        {
            resultado = buscar_palavra_rubro_negra(raiz->esquerda, palavra_portugues);
        }
        else
        {
            resultado = buscar_palavra_rubro_negra(raiz->direita, palavra_portugues);
        }
    }

    return resultado;
}

// informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto
//  deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
//  unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da rubro negra
int remover_palavra_completa(Rubronegra **raiz, char *palavra_portugues, int unidade)
{
    int confere = 0; // Indicador de sucesso

    Rubronegra *no = buscar_palavra_rubro_negra(*raiz, palavra_portugues);

    if (no != NULL)
    {

        remover_todas_palavras_por_unidade(&(no->info->palavras_ingles), unidade);

        if (no->info->palavras_ingles == NULL)
        {

            remover_na_arvore(raiz, palavra_portugues);

            printf("A palavra '%s' foi removida da árvore rubro-negra e da árvore binária.\n", palavra_portugues);
        }
        else
        {
            printf("As palavras em inglês foram removidas, mas a palavra em português permanece.\n");
        }

        confere = 1; // Indica que a remoção foi bem-sucedida
    }
    else
    {
        printf("A palavra '%s' não foi encontrada ou a unidade não corresponde.\n", palavra_portugues);
    }

    return confere; // Retorna 1 se a remoção foi bem-sucedida, 0 caso contrário
}

// rpz custoso melhora emilly do futuro
void liberar_rubronegra_binaria(Informacao_VP *info)
{

    if (info)
    {
        if (info->palavras_ingles)
        {
            //  liberar_binaria(&(*raiz)->info->palavras_ingles);
            info->palavras_ingles = NULL;
        }
        free(info);
    }
}

void liberar_rubronegra(Rubronegra **raiz)
{
    if (*raiz)
    {
        liberar_rubronegra(&(*raiz)->esquerda);
        liberar_rubronegra(&(*raiz)->direita);
        // liberar_rubronegra_binaria((*raiz)->info);
    }
    free(*raiz);
    *raiz = NULL;
}

// informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias
// das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da 
// rubro negra
void remover_palavra_ingles_e_unidade(Rubronegra **raiz, char *palavra_ingles, int unidade)
{
    if (*raiz == NULL)
    {
        return; // Árvore vazia, nada a remover
    }

    // Travessia em profundidade
    remover_palavra_ingles_e_unidade(&((*raiz)->esquerda), palavra_ingles, unidade);
    remover_palavra_ingles_e_unidade(&((*raiz)->direita), palavra_ingles, unidade);

    // Verifica se o nó atual tem palavras e unidade correspondente
    if ((*raiz)->info && (*raiz)->info->unidade == unidade)
    {
        // Remove a palavra da árvore binária associada
        remover_palavra_por_unidade(&((*raiz)->info->palavras_ingles), palavra_ingles, unidade);

        // Verifica se a árvore binária ficou vazia após a remoção
        if ((*raiz)->info->palavras_ingles == NULL)
        {
            // Captura a palavra em português antes de remover
            char palavra_portugues[100];
            strcpy(palavra_portugues, (*raiz)->info->palavra_portugues);

            // Remove o nó da árvore Rubro-Negra
            int sucesso = remover_na_arvore(raiz, palavra_portugues);
            if (sucesso)
            {

                printf("Palavra '%s' foi removida da árvore Rubro-Negra e da árvore binária.\n", palavra_portugues);
            }
        }
        else
        {
            printf("Palavra '%s' em inglês foi removida, mas a palavra em português permanece.\n", palavra_ingles);
        }
    }
}
