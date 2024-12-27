#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Questao3/src/ARVORE2_3.h"
#include <stdio.h>

// Declarações de funções fictícias (você deve definir essas funções)
void cadastrarNos(ARVORE2_3 **raiz, int ultimo_endereco);
void exibirNos(ARVORE2_3 *raiz);
void alocarNos(ARVORE2_3 **raiz, int quantidade_blocos);
void liberarBlocos(ARVORE2_3 **raiz, int quantidade_blocos);
void liberarNos(ARVORE2_3 *raiz);

int main() {
    ARVORE2_3 *raiz = NULL;
    int opcao;
    int ultimo_endereco, quantidade_blocos;

    // Solicitar o último endereço de memória
    printf("Informe o último endereço de memória: ");
    if (scanf("%d", &ultimo_endereco) != 1 || ultimo_endereco <= 0) {
        printf("Endereço inválido.\n");
        return 1;
    }

    // Menu de opções
    while (1) {
        // Exibição do menu
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
                // Cadastrar um novo nó
                cadastrarNos(&raiz, ultimo_endereco);
                break;
            case 2:
                // Exibir os nós cadastrados
                exibirNos(raiz);
                break;
            case 3:
                // Solicitar quantidade de blocos a serem alocados
                printf("\nInforme a quantidade de blocos a serem alocados: ");
                if (scanf("%d", &quantidade_blocos) != 1 || quantidade_blocos <= 0) {
                    printf("Quantidade inválida.\n");
                    break;
                }
                alocarNos(&raiz, quantidade_blocos);
                printf("\n=============== Nós após a alocação ==================\n");
                exibirNos(raiz);
                break;
            case 4:
                // Solicitar quantidade de blocos a serem liberados
                printf("\nInforme a quantidade de blocos a serem liberados: ");
                if (scanf("%d", &quantidade_blocos) != 1 || quantidade_blocos <= 0) {
                    printf("Quantidade inválida.\n");
                    break;
                }
                liberarBlocos(&raiz, quantidade_blocos);
                printf("\n=============== Nós após a liberação ==================\n");
                exibirNos(raiz);
                break;
            case 5:
                // Liberar memória e sair
                liberarNos(raiz);
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}

