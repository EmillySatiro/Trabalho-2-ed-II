#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV_BINARIA.h"


/**
 * @brief Cria uma nova árvore binária.
 *
 * Esta função aloca memória para uma nova árvore binária e inicializa seus campos
 * com os valores fornecidos.
 *
 * @param palavra_ingles A palavra em inglês a ser armazenada na árvore.
 * @param unidade O valor da unidade a ser armazenado na árvore.
 * @return Um ponteiro para a nova árvore binária criada.
 *
 * @note A função imprime uma mensagem de erro e termina o programa se a alocação de memória falhar.
 */
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



/**
 * @brief Insere uma nova palavra na árvore binária.
 *
 * Esta função insere uma nova palavra na árvore binária de acordo com a ordem alfabética.
 * Se a árvore estiver vazia, um novo nó é criado. Caso contrário, a função compara a palavra
 * a ser inserida com a palavra do nó atual e decide se deve inserir na subárvore esquerda ou direita.
 *
 * @param arvore Ponteiro duplo para a árvore binária.
 * @param palavra_ingles Palavra em inglês a ser inserida na árvore.
 * @param unidade Unidade associada à palavra a ser inserida.
 */
void insere_arvore_binaria(ARV_BINARIA **arvore, char *palavra_ingles, int unidade){
    // Se a árvore estiver vazia, cria um novo nó
    if (*arvore == NULL){
        *arvore = cria_arvore_binaria(palavra_ingles, unidade);
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

ARV_BINARIA *buscar_palavra(ARV_BINARIA *arvore, char *palavra_ingles) {
    ARV_BINARIA *resultado = NULL; // Variável para armazenar o resultado da busca

    if (arvore != NULL) {
        if (strcmp(palavra_ingles, arvore->palavra_ingles) == 0) {
            resultado = arvore; // Palavra encontrada
        } else if (strcmp(palavra_ingles, arvore->palavra_ingles) < 0) {
            resultado = buscar_palavra(arvore->esquerda, palavra_ingles); // Busca na subárvore esquerda
        } else {
            resultado = buscar_palavra(arvore->direita, palavra_ingles); // Busca na subárvore direita
        }
    }

    return resultado; // Retorna o resultado armazenado
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



int remover_no_binaria(ARV_BINARIA **arvore, char *palavra_ingles) {
    int resultado = 0; // Variável para armazenar o status da remoção

    if (*arvore == NULL) {
        return resultado; // Árvore vazia, nada a remover
    }

    if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0) {
        resultado = remover_no_binaria(&(*arvore)->esquerda, palavra_ingles); // Busca na subárvore esquerda
    } else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0) {
        resultado = remover_no_binaria(&(*arvore)->direita, palavra_ingles); // Busca na subárvore direita
    } else {
        // Caso em que o nó foi encontrado
        if (eh_folha__binaria(*arvore)) {
            free(*arvore);
            *arvore = NULL;
            resultado = 1; // Remoção bem-sucedida
        } else if (tem_apenas_um_filho(*arvore)) {
            ARV_BINARIA *temp = *arvore;
            *arvore = (*arvore)->esquerda != NULL ? (*arvore)->esquerda : (*arvore)->direita;
            free(temp);
            resultado = 1; // Remoção bem-sucedida
        } else {
            // Encontra o maior valor na subárvore esquerda
            ARV_BINARIA *temp = (*arvore)->esquerda;
            while (temp->direita != NULL) {
                temp = temp->direita;
            }
            // Copia o valor do nó substituto
            strncpy((*arvore)->palavra_ingles, temp->palavra_ingles, sizeof((*arvore)->palavra_ingles) - 1);
            (*arvore)->palavra_ingles[sizeof((*arvore)->palavra_ingles) - 1] = '\0';
            resultado = remover_no_binaria(&(*arvore)->esquerda, temp->palavra_ingles); // Remove o nó substituto
        }
    }

    return resultado; // Retorna o resultado da remoção
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

