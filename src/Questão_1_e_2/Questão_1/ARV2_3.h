#ifndef ARV2_3_H 
#define ARV2_3_H 
#include "../Binaria/ARV_BINARIA.h"

typedef double tempo_tipo;

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


/*Funções referentes a inserir  2_3*/
ARV2_3 *criar_no(Informacao info, ARV2_3 *filho_esquerda, ARV2_3 *filho_centro, ARV2_3 *direita);
ARV2_3 *quebra_No(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 *filho);
void add_elementos(ARV2_3 *no, Informacao Info, ARV2_3 *filho);
ARV2_3 *inserir_Elemento_ARV_2_3(ARV2_3 *pai,ARV2_3 **no, Informacao info, Informacao *sobe);
void insere(ARV2_3 **raiz, Informacao info);
Informacao criar_info(char *palavra_portugues, char *palavra_ingles, int unidade);
void inserir_binaria_em_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade, char *palavra_ingles);

/*Funções listagem 2_3*/
void mostrar(ARV2_3 *raiz);
void imprimir_palavras_unidade(ARV2_3 *raiz, int unidade);
void imprimir_palavras_ingles(ARV2_3 *raiz, char *palavra_portugues);

/*Funções de apoio */
ARV2_3 *no_2_3_juntar(ARV2_3 *filho1, Informacao info, ARV2_3 *maior, ARV2_3 **raiz);
void no_2_3_adicionar_info(ARV2_3 *no, Informacao info, ARV2_3 *filho_maior);
int eh_folha(ARV2_3 *no);
int eh_info1(ARV2_3 no, char *info);
int eh_info2(ARV2_3 no, char *info);
ARV2_3 *no_2_3_alocar();
void no_2_3_desacolar(ARV2_3 **no);
Informacao maior_info(ARV2_3 *raiz);
int arvore_2_3_rebalancear(ARV2_3 **raiz, char  *info, ARV2_3 **maior);
int balanceamento(ARV2_3 **raiz, ARV2_3 *filho1, ARV2_3 **filho2, Informacao info, ARV2_3 **maior);
int calcular_altura(ARV2_3 *no);

/*Funções de busca*/
ARV2_3 *buscar_menor_filho(ARV2_3 *raiz, ARV2_3 **pai);
ARV2_3 *buscar_maior_filho(ARV2_3 *raiz, ARV2_3 **pai, Informacao *maior_valor);
ARV2_3 *buscar_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_maior_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_menor_pai(ARV2_3 *raiz, char *info);
ARV2_3 *buscar_menor_pai_2_info(ARV2_3 *raiz, char *info);
void arvore_2_3_desalocar(ARV2_3 **raiz);
ARV2_3 *buscar_palavra_2_3(ARV2_3 *raiz, char *palavra_portugues);

/*Funções de remoção*/
int possivel_remover(ARV2_3 *raiz);
int ondinha_1(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior, int (*funcao_remover)(ARV2_3 **, char *, ARV2_3 *, ARV2_3 **, ARV2_3 **));
int arvore23_remover_nao_folha1(ARV2_3 **origem, ARV2_3* raiz, Informacao *info, ARV2_3 *filho1, ARV2_3 *filho2, ARV2_3 **maior);
int arvore23_remover_nao_folha2(ARV2_3 **origem, ARV2_3* raiz, Informacao *info, ARV2_3 *filho1, ARV2_3 *filho2, ARV2_3 **maior);
int _1_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior);// arrumar
int _2_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3  *pai, ARV2_3  **origem, ARV2_3  **maior);
void remover_palavra_ingles_e_unidade_2_3(ARV2_3 **raiz, char *palavra_ingles, int unidade);
int remover_palavra_completa_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade);

/*funções de pegar tempo de busca*/
tempo_tipo calcula_tempo(clock_t inicio, clock_t fim);
tempo_tipo calcular_tempo_medio(ARV2_3 **arvore, char *info, int repeticoes);
ARV2_3 *arvore23_buscar_caminho(ARV2_3 *raiz, char *info);

/*Funções de liberação 2_3*/
void liberar_arvore_2_3_binaria(Informacao *info);
void liberar_arvore_2_3(ARV2_3 **raiz);

#endif 















   