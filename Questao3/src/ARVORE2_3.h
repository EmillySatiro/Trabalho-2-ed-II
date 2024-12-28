#ifndef ARVORE2_3_H
#define ARVORE2_3_H

#define LIVRE 0  
#define OCUPADO 1 

typedef struct Informacao_memoria{
    int state; 
    int block_inicio; 
    int block_fim;   
} Informacao_memoria;

typedef struct ARVORE2_3 {
    Informacao_memoria info1;   
    Informacao_memoria info2;  
    int quant_infos;   
    struct ARVORE2_3 *esquerda; 
    struct ARVORE2_3 *centro;   
    struct ARVORE2_3 *direita;  
} ARVORE2_3;


/*Funções de inserir */
ARVORE2_3 *criarNo(Informacao_memoria info);
void cadastrarNos(ARVORE2_3** raiz, int ultimo_endereco);
void alocarNos(ARVORE2_3** raiz, int quantidade_blocos);//conferir se realmente precisa do balancear 
void no_2_3_adicionar_info_Q3(ARVORE2_3 *no, Informacao_memoria info, ARVORE2_3 *filho_maior);
void inserir_Elemento_ARV_2_3(ARVORE2_3 **no, Informacao info, Informacao *sobe, ARVORE2_3 *pai);
/*Funções de liberar*/
void liberarBlocos(ARVORE2_3 **raiz, int quantidade_blocos);
void liberarNos(ARVORE2_3* raiz);

/*Funções de listagem*/
void exibirNos(ARVORE2_3* raiz);

/*Funções suporte */
void intercalarNos(ARVORE2_3 **raiz);
int eh_folha_Q3(ARVORE2_3 *no);
void no_2_3_desacolar_Q3(ARVORE2_3 **no);
ARVORE2_3 *no_2_3_juntar_Q3(ARVORE2_3 *filho1, Informacao_memoria info, ARVORE2_3 *maior, ARVORE2_3 **raiz);
int arvore_2_3_rebalancear_Q3(ARVORE2_3 **raiz, int info, ARVORE2_3 **maior);
static int balanceamento_Q3(ARVORE2_3 **raiz, ARVORE2_3 *filho1, ARVORE2_3 **filho2, Informacao_memoria info, ARVORE2_3 **maior);




#endif 