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
ARVORE2_3* criar_no_Q3(Informacao_memoria info, ARVORE2_3* esq, ARVORE2_3* centro, ARVORE2_3* dir);
void cadastrarNos(ARVORE2_3** raiz, int ultimo_endereco);
void alocarNos(ARVORE2_3** raiz, int quantidade_blocos);//conferir se realmente precisa do balancear 
void no_2_3_adicionar_info_Q3(ARVORE2_3 *no, Informacao_memoria info, ARVORE2_3 *filho_maior);
ARVORE2_3* inserir_Elemento_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 **pai);
void add_elementos_Q3(ARVORE2_3 *no, Informacao_memoria Info, ARVORE2_3 *filho);
ARVORE2_3 *quebra_No_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 **filho);
void insere_Q3(ARVORE2_3 **raiz, Informacao_memoria info);
Informacao_memoria criar_info(int state, int block_inicio, int block_fim);
void atualizar_no_Q3(ARVORE2_3 *no, Informacao_memoria info);
Informacao_memoria maior_info(ARVORE2_3 *raiz);
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