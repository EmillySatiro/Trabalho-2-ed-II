#ifndef ARV_BINARIA_H
#define ARV_BINARIA_H

typedef struct lista_unidade{
   int unidade;
   struct lista_unidade *proximo;
}lista_unidade;

typedef struct ARV_BINARIA{
    char palavra_ingles[100];
    lista_unidade *unidade; 
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
int remover_palavra_por_unidade(ARV_BINARIA **arvore, char *palavra_ingles, int unidade);
void inserir_lista_unidade(lista_unidade **lista, int unidade);
void remover_lista_unidade(lista_unidade **lista, int unidade);
void libera_lista_unidade(lista_unidade **unidade);
void limparBuffer();
#endif