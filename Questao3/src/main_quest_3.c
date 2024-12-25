#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/walison/Trabalho-2-ed-II/Questao3/src/ARVORE2_3.h"

int main() {
    ARVORE2_3* raiz = NULL;
    int quantidade_blocos, ultimo_endereco;

    printf("Informe o último endereço de memória: ");
    if (scanf("%d", &ultimo_endereco) != 1 || ultimo_endereco <= 0) {
        printf("Endereço inválido.\n");
        return 1; 
    }

    cadastrarNos(&raiz, ultimo_endereco);

    printf("\nNós cadastrados na árvore:\n");
    exibirNos(raiz);

    printf("\nInforme a quantidade de blocos a serem alocados: ");
    if (scanf("%d", &quantidade_blocos) != 1 || quantidade_blocos <= 0) {
        printf("Quantidade inválida.\n");
        return 1; 
    }
    
    alocarNos(&raiz, quantidade_blocos);

    printf("\nNós após a alocação ==================\n");
    exibirNos(raiz);

    liberarNos(raiz);

    return 0;
}
