#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H
#include "../Binaria/ARV_BINARIA.h"

#define VERMELHO 1 
#define PRETO 0
//informação do nó
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Rubro_negra.h"
#include "../Binaria/ARV_BINARIA.h"


Rubronegra *alocar_no(Informacao_VP *info);

Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP *info);

Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP *info);
void conferindo_regras(Rubronegra **raiz);

int Qual_a_cor(Rubronegra *no);

void troca_cor(Rubronegra **no);

void girar_esquerda(Rubronegra **raiz);

void move_esquerda(Rubronegra **no);

void girar_direita(Rubronegra **raiz);

void mover_direita(Rubronegra **no);

Rubronegra *procurar_menor(Rubronegra **raiz);

void remover_elemento_min(Rubronegra **raiz);

int remover_no_rubro(Rubronegra **raiz, char *palavra);

int remover_na_arvore(Rubronegra **raiz, char *palavra);

// não entendi o pq dela até agora 
void mostrar_binaria_em_rubro(Rubronegra *raiz, int unidade);

void mostrar_rubronegra(Rubronegra *raiz);

Informacao_VP *criar_info_vp(char *palavra_portugues, char *palavra_ingles, int unidade);

void mostrar_palavras_em_portugues_de_uma_unidade(Rubronegra *raiz, int unidade);

void Imprimir_toda_palavras(Rubronegra *raiz, char *palavra_portugues);

Rubronegra *buscar_palavra_rubro_negra(Rubronegra *raiz, char *palavra_portugues);

int remover_palavra_completa(Rubronegra **raiz, char *palavra_portugues, int unidade);

void remover_palavra_ingles_e_unidade(Rubronegra **raiz, char *palavra_ingles, int unidade);

// rpz custoso melhora emilly do futuro 
void liberar_rubronegra_binaria(Informacao_VP *info);

void liberar_rubronegra( Rubronegra **raiz);
int Qual_a_cor(Rubronegra *no);
void troca_cor(Rubronegra **no);
void girar_esquerda(Rubronegra **raiz);
void move_esquerda(Rubronegra **no);
void girar_direita(Rubronegra **raiz);
void mover_direita(Rubronegra **no);
Rubronegra *procurar_menor(Rubronegra **raiz);
void remover_elemento_min(Rubronegra **raiz);
int remover_no_rubro(Rubronegra **raiz, char *palavra);
int remover_na_arvore(Rubronegra **raiz, char *palavra);
void mostrar_rubronegra(Rubronegra *raiz);
void inserir_binaria_em_rubro(Rubronegra **raiz, Informacao_VP *info);
void mostrar_palavras_em_portugues_de_uma_unidade(Rubronegra *raiz, int unidade);
Informacao_VP *criar_info_vp(char *palavra_portugues, char *palavra_ingles, int unidade);
void mostrar_binaria_em_rubro(Rubronegra *raiz, int unidade);
void buscar_palavra_portugues(Rubronegra *raiz, char *palavra_portugues);
void remover_palavra_ingles_e_unidade(Rubronegra **raiz, char *palavra_ingles, int unidade);


#endif 