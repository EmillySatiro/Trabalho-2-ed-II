#ifndef ARV_BINARIA_H
#define ARV_BINARIA_H

typedef struct ARV_BINARIA{
    char palavra_ingles[25];
    int unidade; 
    struct ARV_BINARIA *esquerda; 
    struct ARV_BINARIA *direita; 
}ARV_BINARIA;

ARV_BINARIA *cria_arvore_binaria(char *palavra_ingles, int unidade);
ARV_BINARIA *insere_arvore_binaria(ARV_BINARIA *arvore, char *palavra_ingles, int unidade);
ARV_BINARIA *libera_arvore_binaria(ARV_BINARIA *arvore);
void mostrar_arvore_binaria(ARV_BINARIA *arvore);

#endif