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
    if (arvore != NULL)
    {
        strncpy(arvore->palavra_ingles, palavra_ingles, sizeof(arvore->palavra_ingles) - 1);
        arvore->palavra_ingles[sizeof(arvore->palavra_ingles) - 1] = '\0';

        arvore->unidade = NULL;
        inserir_lista_unidade(&(arvore->unidade), unidade);
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
void insere_arvore_binaria(ARV_BINARIA **arvore, char *palavra_ingles, int unidade)
{

    if (*arvore == NULL)
    {
        *arvore = cria_arvore_binaria(palavra_ingles, unidade);
    }
    else
    {
        if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0)
        {
            insere_arvore_binaria(&(*arvore)->esquerda, palavra_ingles, unidade);
        }
        else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0)
        {
            insere_arvore_binaria(&(*arvore)->direita, palavra_ingles, unidade);
        }
        else
        {

            inserir_lista_unidade(&(*arvore)->unidade, unidade);
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
    if (arvore != NULL)
    {

        lista_unidade *temp = arvore->unidade;
        while (temp != NULL)
        {
            if (temp->unidade == unidade)
            {
                printf("%s \n", arvore->palavra_ingles);
            }
            temp = temp->proximo;
        }
        if (arvore->esquerda != NULL || arvore->direita != NULL)
        {
            if (arvore->esquerda != NULL)
            {
                mostrar_arvore_binaria(arvore->esquerda, unidade);
            }
            if (arvore->direita != NULL)
            {
                mostrar_arvore_binaria(arvore->direita, unidade);
            }
        }
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
    if (arvore != NULL)
    {
        printf("%s\nUnidades: ", arvore->palavra_ingles);

        lista_unidade *temp = arvore->unidade;
        while (temp != NULL)
        {
            printf("%d| ", temp->unidade);
            temp = temp->proximo;
        }
        printf("\n");

        if (arvore->esquerda != NULL || arvore->direita != NULL)
        {
            if (arvore->esquerda != NULL)
            {
                mostrar_arvore_binaria_completa(arvore->esquerda);
            }
            if (arvore->direita != NULL)
            {
                mostrar_arvore_binaria_completa(arvore->direita);
            }
        }
    }
}

/**
 * @brief Libera a memória alocada para uma árvore binária e suas listas de unidades.
 *
 * Esta função percorre a árvore binária de forma recursiva, liberando a memória alocada
 * para cada nó, bem como a memória das listas de unidades associadas a cada nó.
 *
 * @param arvore Ponteiro duplo para a árvore binária a ser liberada.
 */
void libera_arvore_binaria(ARV_BINARIA **arvore) {
    if (*arvore) {
        
        libera_lista_unidade(&(*arvore)->unidade);
        
       
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
ARV_BINARIA *buscar_palavra(ARV_BINARIA *arvore, char *palavra_ingles)
{
    ARV_BINARIA *resultado = NULL;

    if (arvore != NULL)
    {
        if (strcmp(palavra_ingles, arvore->palavra_ingles) == 0)
        {
            resultado = arvore;
        }
        else if (strcmp(palavra_ingles, arvore->palavra_ingles) < 0)
        {
            resultado = buscar_palavra(arvore->esquerda, palavra_ingles);
        }
        else
        {
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
int eh_folha__binaria(ARV_BINARIA *no)
{
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
int tem_apenas_um_filho(ARV_BINARIA *no)
{
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
int tem_dois_filhos(ARV_BINARIA *no)
{
    return (no->esquerda != NULL && no->direita != NULL);
}

/**
 * @brief Remove um nó da árvore binária que contém a palavra em inglês especificada.
 *
 * Esta função remove um nó da árvore binária que contém a palavra em inglês fornecida.
 * Se a palavra não for encontrada, a função não faz nenhuma alteração na árvore.
 * A função também lida com a remoção de nós que têm zero, um ou dois filhos.
 *
 * @param arvore Ponteiro duplo para a árvore binária.
 * @param palavra_ingles Palavra em inglês a ser removida da árvore.
 * @return int Retorna 1 se a remoção for bem-sucedida, 0 caso contrário.
 */
int remover_no_binaria(ARV_BINARIA **arvore, char *palavra_ingles)
{
    int resultado = 0;

    if (*arvore != NULL)
    {
        if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) < 0)
        {

            resultado = remover_no_binaria(&(*arvore)->esquerda, palavra_ingles);
        }
        else if (strcmp(palavra_ingles, (*arvore)->palavra_ingles) > 0)
        {

            resultado = remover_no_binaria(&(*arvore)->direita, palavra_ingles);
        }
        else
        {
            remover_lista_unidade(&(*arvore)->unidade, (*arvore)->unidade->unidade);

            if ((*arvore)->unidade == NULL)
            {
                if (eh_folha__binaria(*arvore))
                {
                    free(*arvore);
                    *arvore = NULL;
                    resultado = 1;
                }
                else if (tem_apenas_um_filho(*arvore))
                {
                    ARV_BINARIA *temp = *arvore;
                    *arvore = (*arvore)->esquerda != NULL ? (*arvore)->esquerda : (*arvore)->direita;
                    free(temp);
                    resultado = 1;
                }
                else
                {
                    ARV_BINARIA *temp = (*arvore)->esquerda;
                    while (temp->direita != NULL)
                    {
                        temp = temp->direita;
                    }
                    strncpy((*arvore)->palavra_ingles, temp->palavra_ingles, sizeof((*arvore)->palavra_ingles) - 1);
                    (*arvore)->palavra_ingles[sizeof((*arvore)->palavra_ingles) - 1] = '\0';
                    resultado = remover_no_binaria(&(*arvore)->esquerda, temp->palavra_ingles);
                }
            }
            else
            {

                printf("A lista de unidades nao esta vazia\n");
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
void remover_todas_palavras_por_unidade(ARV_BINARIA **arvore, int unidade)
{
    if (*arvore != NULL)
    {
        if ((*arvore)->unidade->unidade == unidade)
        {
            remover_no_binaria(arvore, (*arvore)->palavra_ingles);
        }
        remover_todas_palavras_por_unidade(&(*arvore)->esquerda, unidade);
        remover_todas_palavras_por_unidade(&(*arvore)->direita, unidade);
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
int remover_palavra_por_unidade(ARV_BINARIA **arvore, char *palavra_ingles, int unidade) {
    int resultado = 0;

    if (*arvore != NULL) {
       
        if ((*arvore)->unidade != NULL) {
            lista_unidade *unidade_atual = (*arvore)->unidade;
            
            while (unidade_atual != NULL) {
                if (unidade_atual->unidade == unidade) {
                    resultado = remover_no_binaria(arvore, palavra_ingles);
                    if (resultado) {
                        break;
                    }
                }
                unidade_atual = unidade_atual->proximo;
            }
        }

        if (resultado == 0) {
            resultado = remover_palavra_por_unidade(&((*arvore)->esquerda), palavra_ingles, unidade);
        }
        
        if (resultado == 0) {
            resultado = remover_palavra_por_unidade(&((*arvore)->direita), palavra_ingles, unidade);
        }
    }

    return resultado;
}

/**
 * @brief Insere uma unidade na lista de unidades.
 *
 * Esta função insere uma nova unidade na lista de unidades, caso ela ainda não exista na lista.
 * Se a lista estiver vazia, a função aloca memória para a nova unidade e a insere como o primeiro
 * elemento da lista. Se a lista já contiver elementos, a função verifica se a unidade já existe
 * na lista. Se a unidade não existir, a função a insere no final da lista. Caso contrário, uma
 * mensagem informando que a unidade já existe é exibida.
 *
 * @param lista Ponteiro duplo para a lista de unidades.
 * @param unidade Unidade a ser inserida na lista.
 */
void inserir_lista_unidade(lista_unidade **lista, int unidade)
{
    if (*lista == NULL)
    {
        *lista = (lista_unidade *)malloc(sizeof(lista_unidade));
        if (*lista == NULL)
        {
            printf("Erro ao alocar memória para nova unidade.\n");
        }
        else
        {
            (*lista)->unidade = unidade;
            (*lista)->proximo = NULL;
        }
    }
    else
    {
        lista_unidade *temp = *lista;
        int unidade_existe = 0;

        while (temp != NULL)
        {
            if (temp->unidade == unidade)
            {
                unidade_existe = 1;
            }
            temp = temp->proximo;
        }

        if (!unidade_existe)
        {

            temp = *lista;
            while (temp->proximo != NULL)
            {
                temp = temp->proximo;
            }

            temp->proximo = (lista_unidade *)malloc(sizeof(lista_unidade));
            if (temp->proximo == NULL)
            {
                printf("Erro ao alocar memória para nova unidade.\n");
            }
            else
            {
                temp = temp->proximo;
                temp->unidade = unidade;
                temp->proximo = NULL;
            }
        }
        else
        {
            printf("Unidade já existente na lista.\n");
        }
    }
}

/**
 * @brief Remove uma unidade da lista.
 *
 * Esta função remove a primeira ocorrência de uma unidade específica da lista.
 * Se a lista estiver vazia, uma mensagem será exibida. Se a unidade não for
 * encontrada na lista, uma mensagem será exibida.
 *
 * @param lista Ponteiro para o ponteiro da lista de unidades.
 * @param unidade Unidade a ser removida da lista.
 */
void remover_lista_unidade(lista_unidade **lista, int unidade)
{
    if (*lista == NULL)
    {
        printf("A lista está vazia.\n");
    }
    else
    {
        lista_unidade *temp = *lista;
        lista_unidade *anterior = NULL;

        if (temp != NULL && temp->unidade == unidade)
        {
            *lista = temp->proximo;
            free(temp);
        }
        else
        {
            while (temp != NULL && temp->unidade != unidade)
            {
                anterior = temp;
                temp = temp->proximo;
            }

            if (temp == NULL)
            {
                printf("Unidade %d não encontrada na lista.\n", unidade);
            }
            else
            {
                anterior->proximo = temp->proximo;
                free(temp);
            }
        }
    }
}

/**
 * @brief Libera a memória da lista de unidades.
 *
 * Esta função percorre a lista de unidades de um nó e libera cada nó da lista.
 *
 * @param unidade Ponteiro para o ponteiro da lista de unidades a ser liberada.
 */
void libera_lista_unidade(lista_unidade **unidade) {
    lista_unidade *temp;
    
    while (*unidade != NULL) {
        temp = *unidade;
        *unidade = (*unidade)->proximo;
        free(temp);  
    }
}

/**
 * @brief Limpa o buffer de entrada.
 *
 * Esta função descarta todos os caracteres no buffer de entrada até encontrar
 * um caractere de nova linha ('\n') e, em seguida, lê e descarta esse caractere
 * de nova linha. É útil para evitar problemas com entradas residuais ao usar
 * funções de entrada como scanf.
 */
void limparBuffer(){
    scanf("%*[^\n]"); 
    getchar();        
}
