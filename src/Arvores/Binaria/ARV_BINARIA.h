#ifndef ARV_BINARIA_H
#define ARV_BINARIA_H

typedef struct ARV_BINARIA{
    char palavra_ingles[100];
    int unidade; 
    struct ARV_BINARIA *esquerda; 
    struct ARV_BINARIA *direita; 
}ARV_BINARIA;

ARV_BINARIA *cria_arvore_binaria(char *palavra_ingles, int unidade);
void insere_arvore_binaria(ARV_BINARIA **arvore, char *palavra_ingles, int unidade);
void libera_arvore_binaria(ARV_BINARIA **arvore);
void mostrar_arvore_binaria(ARV_BINARIA *arvore,int unidade);
void mostrar_arvore_binaria_completa(ARV_BINARIA *arvore);
int remover_no_binaria(ARV_BINARIA **arvore, char *palavra_ingles);
int eh_folha_binaria(ARV_BINARIA *no);
int tem_apenas_um_filho(ARV_BINARIA *no);
int tem_dois_filhos(ARV_BINARIA *no);
ARV_BINARIA *buscar_palavra(ARV_BINARIA *arvore, char *palavra_ingles);
void remover_todas_palavras_por_unidade(ARV_BINARIA **arvore, int unidade);
void remover_palavra_por_unidade(ARV_BINARIA **arvore, char *palavra_ingles, int unidade);

#endif