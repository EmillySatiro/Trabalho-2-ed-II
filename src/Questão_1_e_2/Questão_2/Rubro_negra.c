#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Rubro_negra.h"
#include "../Binaria/ARV_BINARIA.h"
#include "time.h"

/**
 * @brief Aloca um novo nó para a árvore rubro-negra.
 *
 * Esta função aloca memória para um novo nó da árvore rubro-negra e inicializa
 * seus campos com os valores fornecidos. Se a alocação de memória falhar em
 * qualquer etapa, a função imprime uma mensagem de erro apropriada e retorna NULL.
 *
 * @param info Ponteiro para a estrutura Informacao_VP que contém os dados a serem
 * copiados para o novo nó.
 * @return Ponteiro para o novo nó alocado, ou NULL se a alocação de memória falhar.
 */
Rubronegra *alocar_no(Informacao_VP *info){
    Rubronegra *no = (Rubronegra *)malloc(sizeof(Rubronegra)); 

    if (no != NULL){

        no->info = (Informacao_VP *)malloc(sizeof(Informacao_VP));

        if (no->info != NULL){

            no->info->palavra_portugues = malloc(strlen(info->palavra_portugues) + 1);
            if (no->info->palavra_portugues != NULL){
                strcpy(no->info->palavra_portugues, info->palavra_portugues);
            }else{
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
        }else{
            printf("Erro ao alocar memória para 'info'!\n");
        }
    }else{
        printf("erro ao alocar memoria para nó !!\n");
        exit(1);
    }
    return no;
}

/**
 * @brief Insere um novo nó na árvore rubro-negra.
 *
 * Esta função insere um novo nó na árvore rubro-negra com a informação fornecida.
 * Se a árvore estiver vazia, o novo nó se torna a raiz. Caso contrário, a função
 * insere o nó na posição correta de acordo com a ordem alfabética da palavra em português.
 * Se a palavra já existir na árvore, a função insere a palavra em inglês na árvore binária
 * associada à palavra em português existente.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore rubro-negra.
 * @param info Ponteiro para a estrutura de informação a ser inserida.
 * @return Ponteiro para a raiz da árvore rubro-negra após a inserção.
 */
Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP *info){
    Rubronegra *inserido = NULL;
    if (*raiz == NULL){
        *raiz = alocar_no(info);
        inserido = *raiz;
    }
    else{
        if (strcmp(info->palavra_portugues, (*raiz)->info->palavra_portugues) < 0){
         
            inserido = inserir_rubro(&((*raiz)->esquerda), info);
        }
        else if (strcmp(info->palavra_portugues, (*raiz)->info->palavra_portugues) > 0){
         
            inserido = inserir_rubro(&((*raiz)->direita), info);
        }
        else{
            insere_arvore_binaria(&((*raiz)->info->palavras_ingles), info->palavras_ingles->palavra_ingles, info->unidade);
            inserido = NULL;
        }
    }

    if (inserido != NULL){
        conferindo_regras(raiz);
    }

    return *raiz;
}

/**
 * @brief Função que insere um novo nó na árvore rubro-negra e ajusta a cor da raiz.
 *
 * Esta função insere um novo nó na árvore rubro-negra utilizando a função `inserir_rubro`.
 * Após a inserção, se a raiz não for nula, a cor da raiz é ajustada para preto.
 *
 * @param raiz Ponteiro para a raiz da árvore rubro-negra.
 * @param info Ponteiro para a informação a ser inserida na árvore.
 * @return Ponteiro para a nova raiz da árvore rubro-negra.
 */
Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP *info){
    raiz = inserir_rubro(&raiz, info); 
    if(raiz != NULL){
       raiz->cor = PRETO;
    } 
    return raiz;
}

/**
 * @brief Verifica e ajusta as regras da árvore rubro-negra.
 *
 * Esta função verifica e ajusta a árvore rubro-negra para garantir que as regras
 * da árvore sejam mantidas. As regras verificadas incluem:
 * 
 * 1. Se o filho à esquerda é preto e o filho à direita é vermelho, realiza uma rotação à esquerda.
 * 2. Se o filho à esquerda e o neto à esquerda são vermelhos, realiza uma rotação à direita.
 * 3. Se ambos os filhos são vermelhos, troca as cores dos nós.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore rubro-negra.
 */
void conferindo_regras(Rubronegra **raiz){
    if(*raiz != NULL){

        if (Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->direita) == VERMELHO){
            girar_esquerda(raiz);
        }

        if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->esquerda->esquerda) == VERMELHO){
            girar_direita(raiz);
        }
    
        if (Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->direita) == VERMELHO){
            troca_cor(raiz);
        }
    }
}

/**
 * @brief Retorna a cor de um nó na árvore rubro-negra.
 *
 * Esta função verifica a cor de um nó na árvore rubro-negra. Se o nó for NULL,
 * a função retorna PRETO, indicando que nós nulos são considerados pretos.
 * Caso contrário, a função retorna a cor do nó.
 *
 * @param no Ponteiro para o nó da árvore rubro-negra.
 * @return A cor do nó. Se o nó for NULL, retorna PRETO.
 */
int Qual_a_cor(Rubronegra *no) {
    if (no == NULL) {
        return PRETO; 
    }
    return no->cor;
}

/**
 * @brief Inverte a cor do nó e de seus filhos.
 *
 * Esta função troca a cor do nó Rubronegra e de seus filhos, se existirem.
 * A cor é invertida, ou seja, se for vermelho, torna-se preto e vice-versa.
 *
 * @param no Ponteiro duplo para o nó Rubronegra cuja cor será invertida.
 *
 * @note A função não faz nada se o ponteiro fornecido for NULL.
 */
void troca_cor(Rubronegra **no){
    if(no != NULL){
        (*no)->cor = !(*no)->cor; 
        if ((*no)->esquerda){
            (*no)->esquerda->cor= !(*no)->esquerda->cor; }

        if ((*no)->direita)
        {
            (*no)->direita->cor = !(*no)->direita->cor;
        }
    }
}

/**
 * @brief Realiza uma rotação à esquerda em uma árvore rubro-negra.
 *
 * Esta função realiza uma rotação à esquerda na árvore rubro-negra apontada por `raiz`.
 * A rotação à esquerda é uma operação fundamental para manter o balanceamento da árvore
 * rubro-negra após inserções e remoções.
 *
 * @param raiz Um ponteiro duplo para o nó raiz da árvore rubro-negra.
 *
 * @note A função assume que a árvore não é nula e que o nó à direita da raiz não é nulo.
 *       A cor do novo nó raiz é ajustada para a cor do nó raiz original, e a cor do nó
 *       raiz original é ajustada para vermelho.
 */
void girar_esquerda(Rubronegra **raiz){
    if(*raiz != NULL && (*raiz)->direita != NULL){
        Rubronegra *novo_no = (*raiz)->direita; 
        
        (*raiz)->direita = novo_no->esquerda; 
        novo_no->esquerda = *raiz;

     
        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;

        *raiz = novo_no;
    }
}

/**
 * @brief Move o nó para a esquerda em uma árvore rubro-negra.
 *
 * Esta função realiza uma rotação à esquerda em um nó de uma árvore rubro-negra,
 * ajustando as cores dos nós conforme necessário para manter as propriedades da árvore.
 *
 * @param no Ponteiro duplo para o nó que será movido para a esquerda.
 *
 * A função verifica se o nó e seu filho direito não são nulos. Se o filho direito
 * tiver um filho esquerdo vermelho, a função realiza uma rotação à direita no filho
 * direito, seguida de uma rotação à esquerda no nó atual, e ajusta as cores dos nós.
 */
void move_esquerda(Rubronegra **no){
    if (*no != NULL){
        troca_cor(no); 
        if ((*no)->direita != NULL && (*no)->direita->esquerda != NULL && Qual_a_cor((*no)->direita->esquerda) == VERMELHO) {
            girar_direita(&(*no)->direita);
            girar_esquerda(no);
            troca_cor(no);
        }
    }
}

/**
 * @brief Realiza uma rotação à direita em uma árvore rubro-negra.
 *
 * Esta função realiza uma rotação à direita na árvore rubro-negra apontada por `raiz`.
 * A rotação à direita é uma operação que mantém a propriedade de árvore binária de busca
 * e é utilizada para balancear a árvore após inserções ou remoções.
 *
 * @param raiz Um ponteiro para o ponteiro da raiz da árvore rubro-negra.
 *
 * @note A função assume que a árvore não é nula e que o nó à esquerda da raiz não é nulo.
 */
void girar_direita(Rubronegra **raiz){
    if(*raiz != NULL && (*raiz)->esquerda != NULL){
        Rubronegra *novo_no = (*raiz)->esquerda; 

        (*raiz)->esquerda = novo_no->direita;
        novo_no->direita = *raiz;

        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;

       
        *raiz = novo_no;
    }
}

/**
 * @brief Move o nó para a direita em uma árvore rubro-negra.
 *
 * Esta função realiza uma rotação à direita em um nó de uma árvore rubro-negra,
 * ajustando as cores dos nós conforme necessário para manter as propriedades
 * da árvore rubro-negra.
 *
 * @param no Um ponteiro duplo para o nó a ser movido para a direita.
 *
 * @note A função verifica se o nó e seu filho esquerdo não são nulos antes de
 *       realizar a rotação. Se o filho esquerdo do nó também tiver um filho
 *       esquerdo vermelho, a rotação é realizada e as cores dos nós são ajustadas.
 */
void mover_direita(Rubronegra **no){
    if(*no !=NULL){
        troca_cor(no); 
        if ( (*no)->esquerda != NULL &&  (*no)->esquerda->esquerda != NULL && Qual_a_cor((*no)->esquerda->esquerda)== VERMELHO){
            girar_direita(no); 
            troca_cor(no);
        }
    }
}

/**
 * @brief Procura o menor nó na árvore rubro-negra.
 *
 * Esta função percorre a árvore rubro-negra a partir da raiz fornecida
 * e encontra o nó com o menor valor (mais à esquerda).
 *
 * @param raiz Ponteiro para a raiz da árvore rubro-negra.
 * @return Ponteiro para o nó com o menor valor na árvore.
 */
Rubronegra *procurar_menor(Rubronegra **raiz){
    Rubronegra *no1 = *raiz;
    Rubronegra *no2 = (*raiz)->esquerda;
    if (*raiz){
        while (no2 !=NULL){
            no1 = no2; 
            no2 = no2->esquerda;
        }
    }

    return no1;
}

/**
 * @brief Remove o menor elemento de uma árvore Rubro-Negra.
 *
 * Esta função remove o menor elemento da árvore Rubro-Negra apontada por `raiz`.
 * Se a árvore não estiver vazia, ela verifica se o nó esquerdo é nulo. Se for,
 * libera a memória do nó atual e define o ponteiro `raiz` como nulo. Caso contrário,
 * verifica a cor do nó esquerdo e do filho esquerdo do nó esquerdo. Se ambos forem pretos,
 * chama a função `move_esquerda` para ajustar a árvore.
 * Em seguida, chama recursivamente `remover_elemento_min` no nó esquerdo.
 * Após a remoção, se a raiz não for nula, chama a função `conferindo_regras` para garantir
 * que as propriedades da árvore Rubro-Negra sejam mantidas.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore Rubro-Negra.
 */
void remover_elemento_min(Rubronegra **raiz){
    if(*raiz != NULL){
        if ((*raiz)->esquerda == NULL){
            free(*raiz);
            *raiz = NULL;
        }else{
            if (Qual_a_cor((*raiz)->esquerda)  == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO){
                move_esquerda(raiz);
            }

            remover_elemento_min(&((*raiz)->esquerda));

        }
        
        if(*raiz)
            conferindo_regras(raiz);
              
    }

}

/**
 * @brief Remove um nó de uma árvore rubro-negra.
 *
 * Esta função remove um nó contendo a palavra especificada de uma árvore rubro-negra.
 * A função ajusta a árvore conforme necessário para manter as propriedades da árvore rubro-negra.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore rubro-negra.
 * @param palavra Palavra a ser removida da árvore.
 * @return int Retorna 1 se a palavra foi encontrada e removida, 0 caso contrário.
 */
int remover_no_rubro(Rubronegra **raiz, char *palavra){
    int encontrado = 0; // não encontrado 

    if(*raiz){
        if(strcmp(palavra, (*raiz)->info->palavra_portugues)< 0){
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO){
                move_esquerda(raiz);
            }
            encontrado = remover_no_rubro(&((*raiz)->esquerda), palavra);
        }else{
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO){
                girar_direita(raiz);
            }

            if (strcmp(palavra, (*raiz)->info->palavra_portugues) == 0 && (*raiz)->direita == NULL){
                free(*raiz);
                *raiz = NULL;
            }else{
                if ((*raiz)->direita && Qual_a_cor((*raiz)->direita) == PRETO && Qual_a_cor((*raiz)->direita->esquerda) == PRETO){
                    mover_direita(raiz);
                }

                if (strcmp(palavra, (*raiz)->info->palavra_portugues) == 0){
                    encontrado = 1;
                    Rubronegra *min = procurar_menor(&(*raiz)->direita); 
                    (*raiz)->info = min->info;
                    remover_elemento_min(&((*raiz)->direita));
                }else{
                    encontrado = remover_no_rubro(&((*raiz)->direita), palavra);
                }
            }
        }
        if (*raiz){
            conferindo_regras(raiz);
        }
    }

    return encontrado;
}

/**
 * @brief Remove um nó da árvore rubro-negra.
 *
 * Esta função remove um nó da árvore rubro-negra que contém a palavra especificada.
 * Após a remoção, se a árvore não estiver vazia, a raiz é colorida de preto.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore rubro-negra.
 * @param palavra Palavra a ser removida da árvore.
 * @return int Resultado da remoção (0 se bem-sucedido, outro valor se houver erro).
 */
int remover_na_arvore(Rubronegra **raiz, char *palavra){
    int resultado = remover_no_rubro(raiz,palavra);
    if (*raiz){
        (*raiz)->cor = PRETO;
    }
    return resultado;
}

/**
 * @brief Mostra informações tanto da árvore rubro-negra quanto da árvore binária de uma unidade específica.
 *
 * Esta função percorre a árvore rubro-negra em ordem simétrica (in-order) e, para cada nó cuja unidade corresponde à unidade fornecida,
 * exibe as informações da árvore binária associada a esse nó.
 *
 * @param raiz Ponteiro para o nó raiz da árvore rubro-negra.
 * @param unidade Unidade específica cujas informações devem ser exibidas.
 */
void mostrar_binaria_em_rubro(Rubronegra *raiz, int unidade){
    if (raiz  != NULL){
        if (raiz->info->unidade == unidade){
            mostrar_arvore_binaria(raiz->info->palavras_ingles,unidade);
            printf("\n");
        }
    }
}

/**
 * @brief Exibe a árvore rubro-negra em ordem simétrica (in-order).
 *
 * Esta função percorre a árvore rubro-negra a partir da raiz e exibe as informações
 * de cada nó, incluindo a palavra em português, a cor do nó (PRETO ou VERMELHO),
 * a unidade e a árvore binária associada contendo palavras em inglês.
 *
 * @param raiz Ponteiro para o nó raiz da árvore rubro-negra.
 */
void mostrar_rubronegra(Rubronegra *raiz){
    if (raiz) {
      
        mostrar_rubronegra(raiz->esquerda);

       
        printf("\n=====================================\n");
        printf("| Palavra em Português: %s\n", raiz->info->palavra_portugues);
        printf("| Cor do nó: %s\n", raiz->cor == PRETO ? "PRETO" : "VERMELHO");
        printf("| Unidade: %d\n", raiz->info->unidade);
        printf("| Árvore binária das palavras em Inglês:\n");
        mostrar_arvore_binaria_completa(raiz->info->palavras_ingles);
        printf("=====================================\n");
        mostrar_rubronegra(raiz->direita);

        
    }

}

/**
 * @brief Cria uma nova estrutura de informação para a árvore rubro-negra.
 *
 * Esta função aloca memória para uma nova estrutura Informacao_VP, inicializa
 * seus campos com os valores fornecidos e insere a palavra em inglês na árvore
 * binária associada.
 *
 * @param palavra_portugues A palavra em português a ser armazenada.
 * @param palavra_ingles A palavra em inglês a ser inserida na árvore binária.
 * @param unidade O valor da unidade associado à palavra.
 * @return Um ponteiro para a nova estrutura Informacao_VP criada.
 *
 * @note A função termina o programa com um erro se a alocação de memória falhar.
 */
Informacao_VP *criar_info_vp(char *palavra_portugues, char *palavra_ingles, int unidade) {
    Informacao_VP *info = malloc(sizeof(Informacao_VP));

    if (info != NULL){
       
        info->palavra_portugues = malloc(strlen(palavra_portugues) + 1);
        if (info->palavra_portugues == NULL){
            perror("Erro ao alocar memória para palavra_portugues");
            exit(EXIT_FAILURE);
        }
        strcpy(info->palavra_portugues, palavra_portugues);

        info->unidade = unidade;
        info->palavras_ingles = NULL; 

        
        insere_arvore_binaria(&info->palavras_ingles, palavra_ingles, unidade);

        
    }
    return info;    
}

/**
 * @brief Mostra as palavras em português de uma unidade específica na árvore rubro-negra.
 *
 * Esta função percorre a árvore rubro-negra em ordem e exibe as palavras em português
 * que pertencem à unidade especificada. Para cada palavra em português encontrada,
 * também são exibidas suas traduções em inglês.
 *
 * @param raiz Ponteiro para a raiz da árvore rubro-negra.
 * @param unidade Unidade específica cujas palavras em português devem ser exibidas.
 */
void mostrar_palavras_em_portugues_de_uma_unidade(Rubronegra *raiz, int unidade){
    if (raiz != NULL){
        mostrar_palavras_em_portugues_de_uma_unidade(raiz->esquerda, unidade);
        mostrar_palavras_em_portugues_de_uma_unidade(raiz->direita, unidade);
         if (raiz->info->unidade == unidade) {
            printf("\n=====================================\n");
            printf("Palavra em Português: %s\n", raiz->info->palavra_portugues);
            printf("Palavras em Inglês:\n");
            mostrar_binaria_em_rubro(raiz, unidade);
            printf("=====================================\n");
    }
       
    }

}

/**
 * @brief Imprime todas as palavras equivalentes em inglês para uma palavra em português específica na árvore rubro-negra.
 * 
 * Esta função percorre a árvore rubro-negra para encontrar a palavra em português especificada.
 * Se a palavra for encontrada, ela exibe a palavra em português e todas as palavras equivalentes em inglês
 * armazenadas na árvore binária associada.
 * 
 * @param raiz Ponteiro para a raiz da árvore rubro-negra.
 * @param palavra_portugues Palavra em português a ser buscada na árvore.
 */
void Imprimir_toda_palavras(Rubronegra *raiz, char *palavra_portugues){
    if(raiz != NULL){
        int comparacao = strcmp(palavra_portugues, raiz->info->palavra_portugues); 
        if (comparacao < 0){
            Imprimir_toda_palavras(raiz->esquerda, palavra_portugues);
        }
        else if (comparacao > 0){
            Imprimir_toda_palavras(raiz->direita, palavra_portugues);
        }
        else{
            printf("\n=====================================\n");
            printf("Palavra em Português: %s\n", raiz->info->palavra_portugues);
            printf("=====================================\n");
            printf("Palavras em Inglês equivalentes:\n");
            mostrar_arvore_binaria_completa(raiz->info->palavras_ingles);
            printf("\n=====================================\n");

        }
    }
}

/**
 * @brief Busca uma palavra em uma árvore rubro-negra.
 *
 * Esta função realiza a busca de uma palavra em uma árvore rubro-negra,
 * comparando a palavra fornecida com as palavras armazenadas nos nós da árvore.
 *
 * @param raiz Ponteiro para o nó raiz da árvore rubro-negra.
 * @param palavra_portugues Ponteiro para a string contendo a palavra em português a ser buscada.
 * @return Retorna um ponteiro para o nó que contém a palavra buscada, ou NULL se a palavra não for encontrada.
 */
Rubronegra *buscar_palavra_rubro_negra(Rubronegra *raiz, char *palavra_portugues) {
    Rubronegra *resultado = NULL;

    if (raiz != NULL){
        int comparacao = strcmp(palavra_portugues, raiz->info->palavra_portugues);

        if (comparacao == 0){
            resultado = raiz;
        }
        else if (comparacao < 0){
            resultado = buscar_palavra_rubro_negra(raiz->esquerda, palavra_portugues);
        }
        else{
            resultado = buscar_palavra_rubro_negra(raiz->direita, palavra_portugues);
        }
    }

    return resultado;
}

/**
 * @brief Remove uma palavra completa da árvore rubro-negra.
 *
 * Esta função busca uma palavra em português na árvore rubro-negra e remove todas as suas traduções
 * em inglês associadas a uma unidade específica. Se todas as traduções em inglês forem removidas,
 * a palavra em português também é removida da árvore rubro-negra.
 *
 * @param raiz Ponteiro para a raiz da árvore rubro-negra.
 * @param palavra_portugues Palavra em português a ser removida.
 * @param unidade Unidade associada às traduções em inglês a serem removidas.
 * @return int Retorna 1 se a remoção foi bem-sucedida, 0 caso contrário.
 */
int remover_palavra_completa(Rubronegra **raiz, char *palavra_portugues, int unidade) {

    int confere = 0; 
    Rubronegra *no = buscar_palavra_rubro_negra(*raiz, palavra_portugues);

    if (no != NULL){

        remover_todas_palavras_por_unidade(&(no->info->palavras_ingles), unidade);

        if (no->info->palavras_ingles == NULL){
            remover_na_arvore(raiz, palavra_portugues);
            printf("A palavra '%s' foi removida da árvore rubro-negra e da árvore binária.\n", palavra_portugues);
        }else{
            printf("As palavras em inglês foram removidas, mas a palavra em português permanece.\n");
        }

        confere = 1; 
    }else{
        printf("A palavra '%s' não foi encontrada ou a unidade não corresponde.\n", palavra_portugues);
    }

    return confere; 
}

/**
 * @brief Remove uma palavra em inglês e sua unidade correspondente da árvore Rubro-Negra.
 *
 * Esta função percorre a árvore Rubro-Negra e remove a palavra em inglês especificada
 * e sua unidade correspondente. Se a palavra em inglês for removida com sucesso e não
 * houver mais palavras em inglês associadas à palavra em português, a palavra em português
 * também será removida da árvore Rubro-Negra.
 *
 * @param raiz Ponteiro para a raiz da árvore Rubro-Negra.
 * @param palavra_ingles Palavra em inglês a ser removida.
 * @param unidade Unidade associada à palavra em inglês a ser removida.
 */
void remover_palavra_ingles_e_unidade(Rubronegra **raiz, char *palavra_ingles, int unidade) {
    if (*raiz != NULL) { 
    
        if ((*raiz)->info != NULL) {
            int sucesso = remover_palavra_por_unidade(&((*raiz)->info->palavras_ingles), palavra_ingles, unidade);
            if (sucesso) {
                if ((*raiz)->info->palavras_ingles == NULL) {
                    char palavra_portugues[100];
                    strcpy(palavra_portugues, (*raiz)->info->palavra_portugues);
                    if (sucesso) {
                        remover_na_arvore(raiz, palavra_portugues);
                        printf("Palavra '%s' foi removida da árvore Rubro-Negra e da árvore binária.\n", palavra_portugues);
                    } else {
                        printf("Falha ao remover a palavra '%s' da árvore binária.\n", palavra_portugues);
                    }
                } else {
                    printf("Palavra '%s' em inglês foi removida, mas a palavra em português permanece.\n", palavra_ingles);
                }
            }
        }

   
        remover_palavra_ingles_e_unidade(&((*raiz)->esquerda), palavra_ingles, unidade);
        remover_palavra_ingles_e_unidade(&((*raiz)->direita), palavra_ingles, unidade);
    }
}

/**
 * @brief Libera a memória alocada para a estrutura Informacao_VP e sua árvore binária de palavras em inglês.
 *
 * Esta função verifica se a estrutura Informacao_VP passada como parâmetro é não-nula.
 * Se for, libera a memória alocada para a árvore binária de palavras em inglês,
 * define o ponteiro para NULL e, em seguida, libera a memória da própria estrutura Informacao_VP.
 *
 * @param info Ponteiro para a estrutura Informacao_VP a ser liberada.
 */
void liberar_rubronegra_binaria(Informacao_VP *info) {
    if (info) {
        if (info->palavras_ingles) {
            libera_arvore_binaria(&info->palavras_ingles);
            info->palavras_ingles = NULL;
        }
        free(info);
    }
}

/**
 * @brief Libera a memória alocada para uma árvore rubro-negra.
 *
 * Esta função percorre a árvore rubro-negra de forma recursiva, liberando a memória
 * alocada para cada nó e seus respectivos filhos. Se o nó contém uma informação adicional,
 * a função `liberar_rubronegra_binaria` é chamada para liberar essa informação.
 *
 * @param raiz Ponteiro duplo para o nó raiz da árvore rubro-negra.
 */
void liberar_rubronegra(Rubronegra **raiz) {
    if (*raiz) {
       
        liberar_rubronegra(&(*raiz)->esquerda);
        liberar_rubronegra(&(*raiz)->direita);
        if ((*raiz)->info) {
            liberar_rubronegra_binaria((*raiz)->info);
        }

        free(*raiz);
        *raiz = NULL;
    }
}

/**
 * @brief Calcula o tempo decorrido entre dois instantes de tempo.
 *
 * Esta função calcula o tempo decorrido entre dois instantes de tempo 
 * fornecidos como parâmetros e retorna o valor em microssegundos.
 *
 * @param inicio O instante de tempo inicial.
 * @param fim O instante de tempo final.
 * @return O tempo decorrido em microssegundos.
 */
tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo)(fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}


/**
 * @brief Calcula o tempo médio de busca em uma árvore Rubro-Negra.
 *
 * Esta função realiza múltiplas buscas em uma árvore Rubro-Negra e calcula o tempo médio gasto nessas buscas.
 *
 * @param arvore Ponteiro para a árvore Rubro-Negra.
 * @param info Informação a ser buscada na árvore.
 * @param repeticoes Número de vezes que a busca será realizada para calcular a média.
 * @return O tempo médio gasto nas buscas.
 */
tempo_tipo calcular_tempo_medio(Rubronegra **arvore, char *info, int repeticoes)
{
    tempo_tipo media = 0;

    for(int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        Rubronegra *no_encontrado;
        tempo_tipo tempo_gasto;

        inicio = clock();

        // Substitua pela função de busca desejada
        no_encontrado = arvorevp_buscar_caminho(*arvore, info); 
        fim = clock();
        
        tempo_gasto = calcula_tempo(inicio, fim);
        media += tempo_gasto;
    }
    
    media /= repeticoes;
    return media;
}

/**
 * @brief Busca um nó na árvore rubro-negra que contém a palavra especificada e imprime o caminho percorrido.
 *
 * Esta função percorre a árvore rubro-negra a partir da raiz, comparando a palavra fornecida com as palavras
 * armazenadas nos nós da árvore. Durante a busca, a função imprime cada palavra encontrada no caminho até
 * encontrar a palavra desejada ou até chegar a um nó folha.
 *
 * @param raiz Ponteiro para o nó raiz da árvore rubro-negra.
 * @param palavra Ponteiro para a string que contém a palavra a ser buscada.
 * @return Ponteiro para o nó que contém a palavra buscada, ou NULL se a palavra não for encontrada.
 */
Rubronegra *arvorevp_buscar_caminho(Rubronegra *raiz, char *palavra)
{
    Rubronegra *retorno = NULL;

    if(raiz != NULL)
    {
       

        int resultado = strcmp(palavra, raiz->info->palavra_portugues);

        if(resultado == 0){
            printf("%s -> ", raiz->info->palavra_portugues);
            retorno = raiz;
        }else if(resultado < 0){
            printf("Esquerda->   ");
            retorno = arvorevp_buscar_caminho(raiz->esquerda, palavra);
        }else if(resultado > 0){
              printf("direita->   ");
            retorno = arvorevp_buscar_caminho(raiz->direita, palavra);
        }
    }   

    return retorno;
}



















