#ifndef ARVORE2_3_H
#define ARVORE2_3_H

#define LIVRE 0  
#define OCUPADO 1 
typedef struct Informacao_memoria{
    int state; // '0' para livre, '1' para ocupado
    int block_inicio; 
    int block_fim;   
} Informacao_memoria;

typedef struct ARVORE2_3 {
    Informacao_memoria info1;   // Primeira informação do nó
    Informacao_memoria info2;   // Segunda informação do nó (se houver)
    int quant_infos;    // Quantidade de informações no nó (1 ou 2)
    struct ARVORE2_3 *esquerda; // Ponteiro para o filho da esquerda
    struct ARVORE2_3 *centro;   // Ponteiro para o filho do centro
    struct ARVORE2_3 *direita;  // Ponteiro para o filho da direita (se houver)
} ARVORE2_3;


ARVORE2_3 *criarNo(Informacao_memoria info);
void cadastrarNos(ARVORE2_3** raiz, int ultimo_endereco);
void alocarNos(ARVORE2_3** raiz, int quantidade_blocos);
void exibirNos(ARVORE2_3* raiz);

void liberarNos(ARVORE2_3* raiz);
#endif 