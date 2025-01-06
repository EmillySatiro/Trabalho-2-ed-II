#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H
#include "../Binaria/ARV_BINARIA.h"

#define VERMELHO 1 
#define PRETO 0

typedef struct Informacao_VP{
    char *palavra_portugues;
    int unidade; 
    ARV_BINARIA *palavras_ingles; 
}Informacao_VP;

typedef struct Rubronegra{
    Informacao_VP *info;
    int cor; 
    struct Rubronegra *direita; 
    struct Rubronegra *esquerda; 
}Rubronegra;

/*Funções de inserir*/
Rubronegra *alocar_no(Informacao_VP *info);
Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP *info);
Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP *info);
Informacao_VP *criar_info_vp(char *palavra_portugues, char *palavra_ingles, int unidade);

/*Funções de suporte*/
void conferindo_regras(Rubronegra **raiz);
int Qual_a_cor(Rubronegra *no);
void troca_cor(Rubronegra **no);
void girar_esquerda(Rubronegra **raiz);
void move_esquerda(Rubronegra **no);
void girar_direita(Rubronegra **raiz);
void mover_direita(Rubronegra **no);
Rubronegra *procurar_menor(Rubronegra **raiz);
Rubronegra *buscar_palavra_rubro_negra(Rubronegra *raiz, char *palavra_portugues);

/*Funções de remover */
void remover_elemento_min(Rubronegra **raiz);
int remover_no_rubro(Rubronegra **raiz, char *palavra);
int remover_na_arvore(Rubronegra **raiz, char *palavra);
int remover_palavra_completa(Rubronegra **raiz, char *palavra_portugues, int unidade);
void remover_palavra_ingles_e_unidade(Rubronegra **raiz, char *palavra_ingles, int unidade);

/*Funções de listagem*/
void mostrar_binaria_em_rubro(Rubronegra *raiz, int unidade);
void mostrar_rubronegra(Rubronegra *raiz);
void mostrar_palavras_em_portugues_de_uma_unidade(Rubronegra *raiz, int unidade);
void Imprimir_toda_palavras(Rubronegra *raiz, char *palavra_portugues);

/*Funções de liberar*/
void liberar_rubronegra_binaria(Informacao_VP *info);
void liberar_rubronegra(Rubronegra **raiz);

#endif 