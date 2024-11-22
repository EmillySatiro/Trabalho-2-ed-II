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
    strcpy(arvore->palavra_ingles, palavra_ingles);
    arvore->unidade = unidade;
    arvore->esquerda = NULL;
    arvore->direita = NULL;
    return arvore;
}

ARV_BINARIA *insere_arvore_binaria(ARV_BINARIA *arvore, char *palavra_ingles, int unidade)
{
    if (arvore == NULL)
    {
        return cria_arvore_binaria(palavra_ingles, unidade);
    }
    if (strcmp(palavra_ingles, arvore->palavra_ingles) < 0)
    {
        arvore->esquerda = insere_arvore_binaria(arvore->esquerda, palavra_ingles, unidade);
    }
    else
    {
        arvore->direita = insere_arvore_binaria(arvore->direita, palavra_ingles, unidade);
    }
    return arvore;
}

void mostrar_arvore_binaria(ARV_BINARIA *arvore,int unidade){
    if(arvore == NULL){
        return 0;
    }

    printf("%s",arvore->palavra_ingles);
    mostrar_arvore_binaria(arvore->esquerda,unidade); 
    mostrar_arvore_binaria(arvore->direita,unidade);
}

ARV_BINARIA *libera_arvore_binaria(ARV_BINARIA *arvore)
{
    if (arvore != NULL)
    {
        libera_arvore_binaria(arvore->esquerda);
        libera_arvore_binaria(arvore->direita);
        free(arvore);
    }
    return NULL;
}



// funções da binaria aqui
