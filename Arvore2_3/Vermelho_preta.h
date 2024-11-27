#ifndef VERMELHO_PRETA_H
#define VERMELHO_PRETA_H
#include "ARV_BINARIA.h"

#define VERMELHO 1 
#define PRETO 0
//informação do nó
typedef struct Informacao_VP{
    ARV_BINARIA *palavras_ingles; 
    char palavra_portugues[25];
    int unidade; 
}Informacao_VP;

typedef struct Rubronegra{
    Informacao_VP *info;
    int cor; 
    struct Rubronegra *direita; 
    struct Rubronegra *esquerda; 

    
}Rubronegra;


// alocar nó 
Rubronegra *alocar_no(Informacao_VP info);
void liberar_rubronegra_binaria(Rubronegra **raiz);
void liberar_rubronegra( Rubronegra **raiz);
int Qual_a_cor(Rubronegra *no);
void troca_cor(Rubronegra *no);
void girar_esquerda(Rubronegra **raiz);
void move_esquerda(Rubronegra **no);
void girar_direita(Rubronegra **raiz);
void mover_direita(Rubronegra **no);
Rubronegra *procurar_menor(Rubronegra *raiz);
void conferindo_regras(Rubronegra **raiz);
void remover_elemento_min(Rubronegra **raiz);
Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP info);
Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP info);
void mostrar_rubronegra(Rubronegra *raiz);
#endif 