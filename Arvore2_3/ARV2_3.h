#ifndef ARV2_3_H 
#define ARV2_3_H 
#include "ARV_BINARIA.h"

typedef struct Informacao{
   
    char palavra_portugues[25];
    ARV_BINARIA *palavra_ingles;
    int unidade; 

}Informacao;


typedef struct ARV2_3{
    Informacao info1; 
    Informacao info2; 
    int quant_infos; 
    struct ARV2_3 *esquerda; 
    struct ARV2_3 *centro; 
    struct ARV2_3 *direita; 
} ARV2_3;



ARV2_3 *criar_no(Informacao info, ARV2_3 *filho_esquerda, ARV2_3*filho_centro);
ARV2_3 *quebra_No(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **filho);
int eh_folha(ARV2_3 *no);
void add_elementos(ARV2_3 *no, Informacao Info, ARV2_3 *filho);
ARV2_3 *inserir_Elemento_ARV_2_3(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **pai);
void insere(ARV2_3 **raiz, Informacao info);
void mostrar(ARV2_3 *raiz);
void liberar_2_3(ARV2_3 *raiz);


#endif 