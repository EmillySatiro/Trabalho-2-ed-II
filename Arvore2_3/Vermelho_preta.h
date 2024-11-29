#ifndef VERMELHO_PRETA_H
#define VERMELHO_PRETA_H
#include "ARV_BINARIA.h"

#define VERMELHO 1 
#define PRETO 0
//informação do nó
typedef struct Informacao_VP{
    char palavra_portugues[25];
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
#include "Vermelho_preta.h"

// alocar nó 
Rubronegra *alocar_no(Informacao_VP info);
Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP info);
Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP info);
void conferindo_regras(Rubronegra **raiz);
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
int remover_no(Rubronegra **raiz, char *palavra);
int remover_na_arvore(Rubronegra **raiz, char *palavra);
void mostrar_rubronegra(Rubronegra *raiz);
#endif 