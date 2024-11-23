#ifndef Ver_preta_h 
#define Ver_preta_h 
#include "ARV_BINARIA.h"

#define VERMELHO 1 
#define PRETO 0
//informação do nó
typedef struct Informacao_VP{
    ARV_BINARIA *palavras_ingles; 
    char *palavra_portugues[25];
}Informacao_VP;

typedef struct Rubronegra{
    Informacao_VP *info;
    int color; 
    struct Rubronegra *direita; 
    struct Rubronegra *esquerda; 

    
}Rubronegra;


#endif 