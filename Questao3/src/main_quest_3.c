#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Questao3/src/ARVORE2_3.h"
//oi
int main() {
    ARVORE2_3 *raiz = NULL;
    int opcao;
    int ultimo_endereco, quantidade_blocos;

    printf("Informe o último endereço de memória: ");
    if (scanf("%d", &ultimo_endereco) != 1 || ultimo_endereco <= 0) {
        printf("Endereço inválido.\n");
        return 1;
    }

    do {
        printf("\n=================== Menu ===================\n");
        printf("1. Cadastrar nó\n");
        printf("2. Exibir nós\n");
        printf("3. Alocar nós\n");
        printf("4. Liberar blocos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarNos(&raiz, ultimo_endereco);
                break;
            case 2:
                exibirNos(raiz);
                break;
            case 3:
                printf("\nInforme a quantidade de blocos a serem alocados: ");
                if (scanf("%d", &quantidade_blocos) != 1 || quantidade_blocos <= 0) {
                    printf("Quantidade inválida.\n");
                    break;
                }
                alocarBloco(&raiz, quantidade_blocos);
                printf("\n=============== Nós após a alocação ==================\n");
                exibirNos(raiz);
                break;
            case 4:
                printf("\nInforme a quantidade de blocos a serem liberados: ");
                if (scanf("%d", &quantidade_blocos) != 1 || quantidade_blocos <= 0) {
                    printf("Quantidade inválida.\n");
                    break;
                }
                liberarBlocos(&raiz, quantidade_blocos, ultimo_endereco);
                printf("\n=============== Nós após a liberação ==================\n");
                exibirNos(raiz);
                break;
            case 5:
                printf("Saindo do programa...\n");
                liberarNos(raiz);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
