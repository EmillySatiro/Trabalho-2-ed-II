#ifndef ARV2_3_H 
#define ARV2_3_H 
#include "../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra/Rubro_negra.h"


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
void liberar_2_3_binaria(Informacao *info);
//void liberar_2_3(ARV2_3 *raiz);
void liberar_arv2_3(ARV2_3 *raiz);
Informacao criar_info(char *palavra_portugues, char *palavra_ingles, int unidade);
void inserir_binaria_em_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade, char *palavra_ingles);
void imprimir_palavras_ingles(ARV2_3 *raiz, char *palavra_portugues);
void imprimir_palavras_unidade(ARV2_3 *raiz, int unidade);




void no_2_3_adicionar_info(ARV2_3 *no, Informacao info, ARV2_3 *filho_maior);
int eh_folha(ARV2_3 *no);
int eh_info1(ARV2_3 no, char *info);
int eh_info2(ARV2_3 no , char *info);
ARV2_3 *no_2_3_alocar();
void troca_infos(Informacao *info1, Informacao *info2);
void no_2_3_desacolar(ARV2_3 **no);
ARV2_3 *no_2_3_juntar(ARV2_3 *filho1, Informacao info, ARV2_3 *maior, ARV2_3 **raiz);
ARV2_3 *buscar_menor_filho(ARV2_3 *raiz, ARV2_3 **pai);
Informacao maior_info(ARV2_3 *raiz);
ARV2_3 *buscar_maior_filho(ARV2_3 *raiz, ARV2_3 **pai, Informacao *maior_valor);
ARV2_3 *buscar_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_maior_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_menor_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_menor_pai_2_info(ARV2_3 *raiz, char *info);
int ondinha_1(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior);
int ondinha_esq2dir(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior);
void arvore_2_3_desalocar(ARV2_3 **raiz);
int _1_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior);
int _2_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior);
int arvore_2_3_rebalancear(ARV2_3 **raiz, char *info, ARV2_3 **maior);

static int balanceamento(ARV2_3 **raiz, ARV2_3 *filho1, ARV2_3 **filho2, Informacao info, ARV2_3 **maior);
#endif 