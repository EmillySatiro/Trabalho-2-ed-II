
#ifndef ARVORE2_3_H
#define ARVORE2_3_H

typedef struct Informacao {
    char state; // 'L' para livre, 'O' para ocupado
    int block_inicio; // Bloco inicial
    int block_fim;   // Bloco final
} Informacao;

typedef struct ARVORE2_3 {
    Informacao info1;   // Primeira informação do nó
    Informacao info2;   // Segunda informação do nó (se houver)
    int quant_infos;    // Quantidade de informações no nó (1 ou 2)
    struct ARV2_3 *esquerda; // Ponteiro para o filho da esquerda
    struct ARV2_3 *centro;   // Ponteiro para o filho do centro
    struct ARV2_3 *direita;  // Ponteiro para o filho da direita (se houver)
} ARVORE2_3;


ARVORE2_3 *criarNo(Informacao info);
void cadastrarNos(ARVORE2_3** raiz, unsigned long ultimo_endereco);


#endif 