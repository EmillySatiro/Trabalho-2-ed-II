#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H
#include "Arvores/Binaria/ARV_BINARIA.h"

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



// alocar nó 
<<<<<<< HEAD:Arvore2_3/Vermelho_preta.h
// Rubronegra *alocar_no(Informacao_VP info);
// void liberar_rubronegra_binaria(Rubronegra **raiz);
// void liberar_rubronegra( Rubronegra **raiz);
// int Qual_a_cor(Rubronegra *no);
// void troca_cor(Rubronegra *no);
// void girar_esquerda(Rubronegra **raiz);
// void move_esquerda(Rubronegra **no);
// void girar_direita(Rubronegra **raiz);
// void mover_direita(Rubronegra **no);
// Rubronegra *procurar_menor(Rubronegra *raiz);
// void conferindo_regras(Rubronegra **raiz);
// void remover_elemento_min(Rubronegra **raiz);
// Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP info);
// Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP info);
// void mostrar_rubronegra(Rubronegra *raiz);

=======
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
>>>>>>> origin/main:Arvores/Rubro_negra/Rubro_negra.h
#endif 