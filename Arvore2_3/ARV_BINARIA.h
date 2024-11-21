#ifndef ARV_BINARIA_H
#define ARV_BINARIA_H

typedef struct ARV_BINARIA{
    char palavra_ingles[25];
    int unidade; 
    struct ARV_BINARIA *esquerda; 
    struct ARV_BINARIA *direita; 
}ARV_BINARIA;

#endif