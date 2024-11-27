#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV_BINARIA.h"

ARV_BINARIA *cria_arvore_binaria(char *palavra_ingles, int unidade)
{
    ARV_BINARIA *arvore = (ARV_BINARIA *)malloc(sizeof(ARV_BINARIA));
    if (arvore == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    int TAMANHO_PALAVRA = strlen(palavra_ingles);
    // Verifica se o tamanho da palavra é adequado para o buffer
    strncpy(arvore->palavra_ingles, palavra_ingles, TAMANHO_PALAVRA - 1);
    arvore->palavra_ingles[TAMANHO_PALAVRA - 1] = '\0'; // Garante que a string está terminada

    arvore->unidade = unidade;
    arvore->esquerda = NULL;
    arvore->direita = NULL;
    return arvore;
}

void insere_arvore_binaria(ARV_BINARIA **arvore, char *palavra_ingles, int unidade)
{
    // Se a árvore estiver vazia, cria um novo nó
    if (*arvore == NULL)
    {
        *arvore = cria_arvore_binaria(palavra_ingles, unidade);
        return;
    }
    else
    {
        // Se a palavra a ser inserida for menor que a palavra do nó atual, insere na subárvore esquerda
        if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0)
        {
            insere_arvore_binaria(&(*arvore)->esquerda, palavra_ingles, unidade);
        }
        // Se a palavra a ser inserida for maior que a palavra do nó atual, insere na subárvore direita
        else
        {
            insere_arvore_binaria(&(*arvore)->direita, palavra_ingles, unidade);
        }
    }
}

void mostrar_arvore_binaria(ARV_BINARIA *arvore, int unidade)
{
    if (arvore == NULL)
    {
        return;
    }

    // Exibe a subárvore esquerda
    mostrar_arvore_binaria(arvore->esquerda, unidade);

    // Se a unidade do nó corresponder à unidade fornecida, imprime a palavra
    if (arvore->unidade == unidade)
    {
        printf("%s\n", arvore->palavra_ingles);
    }

    // Exibe a subárvore direita
    mostrar_arvore_binaria(arvore->direita, unidade);
}

void libera_arvore_binaria(ARV_BINARIA **arvore)
{
    if (*arvore != NULL)
    {
        libera_arvore_binaria(&(*arvore)->esquerda);
        libera_arvore_binaria(&(*arvore)->direita);
        free(*arvore);
        *arvore = NULL; // Garantir que o ponteiro se torne NULL após liberar
    }
}

ARV_BINARIA *buscar_palavra(ARV_BINARIA *arvore, char *palavra_ingles)
{
    if (arvore == NULL)
    {
        return NULL;
    }

    if (strcmp(palavra_ingles, arvore->palavra_ingles) == 0)
    {
        return arvore;
    }

    if (strcmp(palavra_ingles, arvore->palavra_ingles) < 0)
    {
        return buscar_palavra(arvore->esquerda, palavra_ingles);
    }
    else
    {
        return buscar_palavra(arvore->direita, palavra_ingles);
    }
}
