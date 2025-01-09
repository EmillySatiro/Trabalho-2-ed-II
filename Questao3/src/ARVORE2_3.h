#ifndef ARVORE2_3_H
#define ARVORE2_3_H

#define LIVRE 0  
#define OCUPADO 1 

typedef struct Informacao_memoria{
    int state; 
    int block_inicio,block_fim;
    int inicio, fim;
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
void alocarBloco(ARVORE2_3 **raiz, int quantidade_blocos);
void no_2_3_adicionar_info_Q3(ARVORE2_3 *no, Informacao_memoria info, ARVORE2_3 *filho_maior);
ARVORE2_3 *inserir_Elemento_Q3(ARVORE2_3 *pai, ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe);
void add_elementos_Q3(ARVORE2_3 *no, Informacao_memoria Info, ARVORE2_3 *filho);
ARVORE2_3 *quebra_No_Q3(ARVORE2_3 **no, Informacao_memoria info, Informacao_memoria *sobe, ARVORE2_3 *filho);
void insere_Q3(ARVORE2_3 **raiz, Informacao_memoria info);
Informacao_memoria criar_info(int state, int block_inicio, int block_fim);
void atualizar_no_Q3(ARVORE2_3 *no, Informacao_memoria info);
Informacao_memoria maior_info(ARVORE2_3 **raiz);
void liberarBlocos(ARVORE2_3 **raiz, int *blocos_restantes, int ultimo_endereco);
void concatenarBlocos(ARVORE2_3 *atual, int *blocos_restantes);
int arvore23_remover_nao_folha2_q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info,ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior);

int _2_remover_2_3(ARVORE2_3 **raiz, int *info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior);
int _1_remover_2_3(ARVORE2_3 **raiz, int *info, ARVORE2_3 *pai, ARVORE2_3 **origem, ARVORE2_3 **maior);

int eh_info1(ARVORE2_3 no, int *info);
int eh_info2(ARVORE2_3 no, int *info);

ARVORE2_3 *buscar_maior_pai(ARVORE2_3 *raiz, int block_inicio);

ARVORE2_3* buscar_menor_filho(ARVORE2_3 *raiz, ARVORE2_3 **pai);
ARVORE2_3* buscar_maior_filho(ARVORE2_3 *raiz, ARVORE2_3 **pai, Informacao_memoria *info);
int calcular_altura(ARVORE2_3 *raiz);
ARVORE2_3 *buscar_maior_bloco(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_maior);
ARVORE2_3 *buscar_menor_bloco(ARVORE2_3 **raiz, ARVORE2_3 *no, Informacao_memoria *info, Informacao_memoria **valor_menor);

ARVORE2_3 *buscar_pai(ARVORE2_3 *raiz, int block_inicio);
ARVORE2_3 *buscar_menor_pai_2_info(ARVORE2_3 *raiz, int info);
ARVORE2_3* buscar_menor_pai(ARVORE2_3 *raiz, int block_inicio);
ARVORE2_3 *encontrarProximo(ARVORE2_3 *atual);
void no_2_3_desacolar(ARVORE2_3 **no);
void remover(ARVORE2_3 **raiz, int *info);
void concatenar_no(ARVORE2_3 **raiz, int *endereco_final, int limite, int valor_remover);

/*Funções de liberar*/
void liberarNos(ARVORE2_3* raiz);
void liberarInfo(ARVORE2_3 *raiz, Informacao_memoria info);

/*Funções de listagem*/
void exibirNos(ARVORE2_3* raiz);

int arvore23_remover_nao_folha1_q3(ARVORE2_3 **origem, ARVORE2_3 *raiz, Informacao_memoria *info,ARVORE2_3 *filho1, ARVORE2_3 *filho2, ARVORE2_3 **maior);

int ondinha_1(Informacao_memoria saindo, Informacao_memoria *entrada, ARVORE2_3 *pai,ARVORE2_3 **origem, ARVORE2_3 **raiz, ARVORE2_3 **maior,int (*funcao_remover)(ARVORE2_3 **, int *, ARVORE2_3 *, ARVORE2_3 **, ARVORE2_3 **));

/*Funções suporte */
void intercalarNos(ARVORE2_3 **raiz);
int eh_folha_Q3(ARVORE2_3 *no);
void no_2_3_desacolar_Q3(ARVORE2_3 **no);
ARVORE2_3 *no_2_3_juntar_Q3(ARVORE2_3 *filho1, Informacao_memoria info, ARVORE2_3 *maior, ARVORE2_3 **raiz);



#endif 