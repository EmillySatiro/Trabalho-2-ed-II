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
ARV_BINARIA *cria_arvore_binaria(char *palavra_ingles, int unidade){

    ARV_BINARIA *arvore = (ARV_BINARIA *)malloc(sizeof(ARV_BINARIA));
    if (arvore != NULL){
        strncpy(arvore->palavra_ingles, palavra_ingles, sizeof(arvore->palavra_ingles) -1);
        arvore->palavra_ingles[sizeof(arvore->palavra_ingles) - 1] = '\0';

        arvore->unidade = unidade;
        arvore->esquerda = NULL;
        arvore->direita = NULL;
       
    }
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
   
    if (*arvore == NULL){
        *arvore = cria_arvore_binaria(palavra_ingles, unidade);
    } else {
        if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0){
            insere_arvore_binaria(&(*arvore)->esquerda, palavra_ingles, unidade);
        }
        else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0){
            insere_arvore_binaria(&(*arvore)->direita, palavra_ingles, unidade);
        }
    }
}

/**
 * @brief Mostra as palavras em inglês da árvore binária que correspondem à unidade fornecida.
 *
 * Esta função percorre a árvore binária em ordem (in-order traversal) e imprime as palavras em inglês
 * dos nós cuja unidade corresponde à unidade fornecida.
 *
 * @param arvore Ponteiro para a árvore binária (ARV_BINARIA) a ser exibida.
 * @param unidade Unidade a ser comparada com a unidade dos nós da árvore.
 */
void mostrar_arvore_binaria(ARV_BINARIA *arvore, int unidade)
{
    if (arvore != NULL){
        mostrar_arvore_binaria(arvore->esquerda, unidade);
        if (arvore->unidade == unidade){
            printf("%s \n ", arvore->palavra_ingles);
        }
        mostrar_arvore_binaria(arvore->direita, unidade);
    }

}

/**
 * @brief Exibe a árvore binária completa em ordem.
 *
 * Esta função percorre a árvore binária em ordem (in-order traversal) e imprime
 * a palavra em inglês e a unidade de cada nó.
 *
 * @param arvore Ponteiro para a raiz da árvore binária.
 */
void mostrar_arvore_binaria_completa(ARV_BINARIA *arvore)
{
    if (arvore != NULL){

        mostrar_arvore_binaria_completa(arvore->esquerda);

        printf("%s ", arvore->palavra_ingles);
        printf("%d ", arvore->unidade);
        printf("\n");
    
        mostrar_arvore_binaria_completa(arvore->direita);
    }

}

/**
 * @brief Libera a memória alocada para uma árvore binária.
 *
 * Esta função percorre a árvore binária de forma recursiva e libera a memória
 * alocada para cada nó, garantindo que o ponteiro para o nó liberado seja
 * definido como NULL.
 *
 * @param arvore Ponteiro duplo para a árvore binária a ser liberada.
 */
void libera_arvore_binaria(ARV_BINARIA **arvore){
    if (*arvore){
        libera_arvore_binaria(&(*arvore)->esquerda);
        libera_arvore_binaria(&(*arvore)->direita);
        free(*arvore);
        *arvore = NULL; 
    }
}

/**
 * @brief Busca uma palavra em uma árvore binária.
 *
 * Esta função realiza a busca de uma palavra em inglês em uma árvore binária.
 * Se a palavra for encontrada, retorna o nó correspondente. Caso contrário,
 * retorna NULL.
 *
 * @param arvore Ponteiro para a raiz da árvore binária.
 * @param palavra_ingles Palavra em inglês a ser buscada na árvore.
 * @return ARV_BINARIA* Ponteiro para o nó que contém a palavra buscada, ou NULL se a palavra não for encontrada.
 */
ARV_BINARIA *buscar_palavra(ARV_BINARIA *arvore, char *palavra_ingles) {
    ARV_BINARIA *resultado = NULL; 

    if (arvore != NULL) {
        if (strcmp(palavra_ingles, arvore->palavra_ingles) == 0) {
            resultado = arvore; 
        } else if (strcmp(palavra_ingles, arvore->palavra_ingles) < 0) {
            resultado = buscar_palavra(arvore->esquerda, palavra_ingles); 
        } else {
            resultado = buscar_palavra(arvore->direita, palavra_ingles); 
        }
    }

    return resultado;
}

/**
 * @brief Verifies if a given node in a binary tree is a leaf node.
 *
 * This function checks if the specified node in a binary tree has no children.
 * A node is considered a leaf node if both its left and right child pointers are NULL.
 *
 * @param no Pointer to the node in the binary tree to be checked.
 * @return int Returns 1 if the node is a leaf node, otherwise returns 0.
 */
int eh_folha__binaria(ARV_BINARIA *no){
    return (no->esquerda == NULL && no->direita == NULL);
}

/**
 * @brief Verifica se um nó da árvore binária tem apenas um filho.
 *
 * Esta função verifica se um nó da árvore binária possui exatamente um filho,
 * ou seja, se tem um filho à esquerda ou à direita, mas não ambos.
 *
 * @param no Ponteiro para o nó da árvore binária a ser verificado.
 * @return Retorna 1 se o nó tem exatamente um filho, caso contrário, retorna 0.
 */
int tem_apenas_um_filho(ARV_BINARIA *no){
    return (no->esquerda == NULL && no->direita != NULL) || (no->esquerda != NULL && no->direita == NULL);
}

/**
 * @brief Verifica se um nó da árvore binária tem dois filhos.
 *
 * Esta função verifica se o nó da árvore binária possui ambos os filhos, esquerdo e direito.
 *
 * @param no Ponteiro para o nó da árvore binária a ser verificado.
 * @return Retorna 1 se o nó tem ambos os filhos, caso contrário, retorna 0.
 */
int tem_dois_filhos(ARV_BINARIA *no){
    return (no->esquerda != NULL && no->direita != NULL);
}

/**
 * @brief Remove um nó de uma árvore binária de busca com base na palavra em inglês fornecida.
 *
 * Esta função remove um nó de uma árvore binária de busca que contém a palavra em inglês especificada.
 * A função lida com três casos principais:
 * 1. O nó a ser removido é uma folha.
 * 2. O nó a ser removido tem apenas um filho.
 * 3. O nó a ser removido tem dois filhos.
 *
 * @param arvore Um ponteiro duplo para a árvore binária de busca.
 * @param palavra_ingles A palavra em inglês a ser removida da árvore.
 * @return int Retorna 1 se a remoção for bem-sucedida, caso contrário, retorna 0.
 */
int remover_no_binaria(ARV_BINARIA **arvore, char *palavra_ingles) {
    int resultado = 0; 

    if (*arvore != NULL) {
         if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0) {

            resultado = remover_no_binaria(&(*arvore)->esquerda, palavra_ingles); 

        } else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0) {

            resultado = remover_no_binaria(&(*arvore)->direita, palavra_ingles); 

        } else {

            if (eh_folha__binaria(*arvore)){
                free(*arvore);
                *arvore = NULL;
                resultado = 1; 
            } else if (tem_apenas_um_filho(*arvore)) {
                ARV_BINARIA *temp = *arvore;
                *arvore = (*arvore)->esquerda != NULL ? (*arvore)->esquerda : (*arvore)->direita;
                free(temp);
                resultado = 1;
            } else {
                ARV_BINARIA *temp = (*arvore)->esquerda;
                while (temp->direita != NULL) {
                    temp = temp->direita;
                }
                strncpy((*arvore)->palavra_ingles, temp->palavra_ingles, sizeof((*arvore)->palavra_ingles) - 1);
                (*arvore)->palavra_ingles[sizeof((*arvore)->palavra_ingles) - 1] = '\0';
                resultado = remover_no_binaria(&(*arvore)->esquerda, temp->palavra_ingles);
            }
        }
        
    }
    return resultado;
    
}

/**
 * @brief Remove todas as palavras da árvore binária que correspondem à unidade fornecida.
 *
 * Esta função percorre a árvore binária e remove todos os nós onde a unidade
 * corresponde à unidade especificada. Ela realiza uma travessia pós-ordem para
 * garantir que todos os nós filhos sejam processados antes que o nó atual seja
 * potencialmente removido.
 *
 * @param arvore Um ponteiro duplo para a raiz da árvore binária.
 * @param unidade O valor da unidade a ser correspondido para remoção.
 */
void remover_todas_palavras_por_unidade(ARV_BINARIA **arvore, int unidade) {
    if (*arvore != NULL) {
        
        remover_todas_palavras_por_unidade(&(*arvore)->esquerda, unidade);
        remover_todas_palavras_por_unidade(&(*arvore)->direita, unidade);

        if ((*arvore)->unidade == unidade) {
            remover_no_binaria(arvore, (*arvore)->palavra_ingles);
        }
    } 
}

/**
 * @brief Remove uma palavra de um nó da árvore binária com base na unidade especificada.
 *
 * Esta função percorre a árvore binária em ordem de profundidade e remove a palavra especificada
 * dos nós que correspondem à unidade fornecida. Se a árvore estiver vazia, a função retorna imediatamente.
 *
 * @param arvore Um ponteiro duplo para a raiz da árvore binária.
 * @param palavra_ingles A palavra em inglês a ser removida da árvore.
 * @param unidade A unidade associada à palavra a ser removida.
 */
void remover_palavra_por_unidade(ARV_BINARIA **arvore, char *palavra_ingles, int unidade) {
    if (*arvore != NULL) {

        remover_palavra_por_unidade(&((*arvore)->esquerda), palavra_ingles, unidade);
        remover_palavra_por_unidade(&((*arvore)->direita), palavra_ingles, unidade);

        if ((*arvore)->unidade == unidade) {
        
            remover_no_binaria(arvore, palavra_ingles);
        }
    }
}

