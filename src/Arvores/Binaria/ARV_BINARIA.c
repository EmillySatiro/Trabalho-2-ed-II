#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV_BINARIA.h"


ARV_BINARIA *cria_arvore_binaria(char *palavra_ingles, int unidade)
{
    ARV_BINARIA *arvore = (ARV_BINARIA *)malloc(sizeof(ARV_BINARIA));
    if (arvore == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
   
    strncpy(arvore->palavra_ingles, palavra_ingles, sizeof(arvore->palavra_ingles) -1);
    arvore->palavra_ingles[sizeof(arvore->palavra_ingles) - 1] = '\0'; // Garante que a string está terminada

    arvore->unidade = unidade;
    arvore->esquerda = NULL;
    arvore->direita = NULL;
    return arvore;
}


// arrumar retornos 
void insere_arvore_binaria(ARV_BINARIA **arvore, char *palavra_ingles, int unidade){
    // Se a árvore estiver vazia, cria um novo nó
    if (*arvore == NULL){
        *arvore = cria_arvore_binaria(palavra_ingles, unidade);
        return;
    }
    else
    {
        // Se a palavra a ser inserida for menor que a palavra do nó atual, insere na subárvore esquerda
        if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0){
            insere_arvore_binaria(&(*arvore)->esquerda, palavra_ingles, unidade);
        }
        // Se a palavra a ser inserida for maior que a palavra do nó atual, insere na subárvore direita
        else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0){
            insere_arvore_binaria(&(*arvore)->direita, palavra_ingles, unidade);
        }else{
          
        }
    }
}

void mostrar_arvore_binaria(ARV_BINARIA *arvore, int unidade)
{
    if (arvore != NULL){
      
    // Exibe a subárvore esquerda
    mostrar_arvore_binaria(arvore->esquerda, unidade);

    // Se a unidade do nó corresponder à unidade fornecida, imprime a palavra
    if (arvore->unidade == unidade){
        printf("%s \n ", arvore->palavra_ingles);
    }
    printf("\n");

    // Exibe a subárvore direita
    mostrar_arvore_binaria(arvore->direita, unidade);
    }

}

void mostrar_arvore_binaria_completa(ARV_BINARIA *arvore)
{
    if (arvore != NULL){
      
    // Exibe a subárvore esquerda
    mostrar_arvore_binaria_completa(arvore->esquerda);

    // Se a unidade do nó corresponder à unidade fornecida, imprime a palavra
    printf("%s ", arvore->palavra_ingles);
    printf("%d ", arvore->unidade);
    printf("\n");
    // Exibe a subárvore direita
    mostrar_arvore_binaria_completa(arvore->direita);
    }

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

// arrumar esses mil retornos 
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



int eh_folha__binaria(ARV_BINARIA *no){
    return (no->esquerda == NULL && no->direita == NULL);
}

int tem_apenas_um_filho(ARV_BINARIA *no){
    return (no->esquerda == NULL && no->direita != NULL) || (no->esquerda != NULL && no->direita == NULL);
}

int tem_dois_filhos(ARV_BINARIA *no){
    return (no->esquerda != NULL && no->direita != NULL);
}


//  arrumar esse tanto de retorno 
int remover_no_binaria(ARV_BINARIA **arvore, char *palavra_ingles){
    if (*arvore == NULL){
        return 0;
    }

    if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0){
        return remover_no_binaria(&(*arvore)->esquerda, palavra_ingles);
    }
    else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0){
        return remover_no_binaria(&(*arvore)->direita, palavra_ingles);
    }
    else{
        if (eh_folha__binaria(*arvore)){
            free(*arvore);
            *arvore = NULL;
            return 1;
        }
        else if (tem_apenas_um_filho(*arvore)){
        
            ARV_BINARIA *temp = *arvore;
            if ((*arvore)->esquerda != NULL){
                *arvore = (*arvore)->esquerda;
            }
            else{
                *arvore = (*arvore)->direita;
            }
            free(temp);
            return 1;
        }
        else{
            // Encontra o nó com o maior valor na subárvore esquerda
            ARV_BINARIA *temp = (*arvore)->esquerda;
            while (temp->direita != NULL){
                temp = temp->direita;
            }
            // Copia o valor do nó encontrado para o nó a ser removido
            strncpy((*arvore)->palavra_ingles, temp->palavra_ingles, sizeof((*arvore)->palavra_ingles) - 1);
            (*arvore)->palavra_ingles[sizeof((*arvore)->palavra_ingles) - 1] = '\0';
            return remover_no_binaria(&(*arvore)->esquerda, temp->palavra_ingles);
        
        }
    }
}

void remover_todas_palavras_por_unidade(ARV_BINARIA **arvore, int unidade) {
    if (*arvore != NULL) {
        
        remover_todas_palavras_por_unidade(&(*arvore)->esquerda, unidade);

        remover_todas_palavras_por_unidade(&(*arvore)->direita, unidade);
        if ((*arvore)->unidade == unidade) {
            remover_no_binaria(arvore, (*arvore)->palavra_ingles);
        }
    } 
}

void remover_palavra_por_unidade(ARV_BINARIA **arvore, char *palavra_ingles, int unidade) {
    if (*arvore == NULL) {
        return; // Árvore vazia, nada a remover
    }

    // Travessia em profundidade
    remover_palavra_por_unidade(&((*arvore)->esquerda), palavra_ingles, unidade);
    remover_palavra_por_unidade(&((*arvore)->direita), palavra_ingles, unidade);

    // Verifica se o nó atual tem palavras e unidade correspondente
    if ((*arvore)->unidade == unidade) {
        // Remove a palavra da árvore binária associada
        remover_no_binaria(arvore, palavra_ingles);
    }
}
