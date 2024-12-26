#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Binaria/ARV_BINARIA.h"
#include "../Arvore_2_3/ARV2_3.h"
#include "../Arvore_2_3/Arquivo/Extrair.h"

int main() {
    ARV2_3 *arvore2_3 = NULL;
    int opcao; 
    int unidade = 0;
    char palavra[100];
    char palavra_removida[100];

    do {
        
        printf("========= MENU PRINCIPAL =========\n");
        printf("1.Passar as palavras do arquivo para a Arvore\n");
        printf("2.Informe uma unidade e então veja todas as palavras da unidade em português seguida das equivalentes em inglês\n");
        printf("3.Informe uma palavra em português e então veja  todas as palavras em inglês equivalente a palavra em português dada, independente da unidade\n");
        printf("4.Remover uma palavra em inglês de todas as arvores que a mesma pertence\n");
        printf("5.Remover uma palavra em português e a unidade a qual a mesma pertence\n");
        printf("6.Mostrar todas as palavras em portugues e suas traduções para o inglês\n");
        printf("0. Sair\n");
        printf("==================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

    

        switch (opcao) {
            case 1:
                printf("Você escolheu a Opção 1!\n");
                Pegar_dados_arquivo_23(&arvore2_3);
                break;
            case 2:
                printf("Você escolheu a Opção 2!\n");
                printf("Infome a unidade: \n");
                scanf("%d", &unidade);
                imprimir_palavras_unidade(arvore2_3, unidade);
                limparBuffer();
                break;
            case 3:
                printf("Você escolheu a Opção 3!\n");
                printf("Digite a palavra: ");
                fgets(palavra, sizeof(palavra), stdin); 
                palavra[strcspn(palavra, "\n")] = '\0'; 
                imprimir_palavras_ingles(arvore2_3, palavra);
                break;
            case 4:
                printf("Você escolheu a Opção 4!\n");
                printf("Informações importantes: \n Caso ela seja a única palavra em uma das árvores binárias, ela também será removida da arvore Rubro_negra\n");
                printf("Infome a unidade: \n");
                scanf("%d", &unidade);
                limparBuffer();
                printf("Digite a palavra em ingles: ");
                fgets(palavra_removida, sizeof(palavra_removida), stdin); 
                palavra_removida[strcspn(palavra_removida, "\n")] = '\0'; 
                remover_palavra_ingles_e_unidade_2_3(&arvore2_3, palavra_removida, unidade) ;
                printf("saindo aqui ");
                break;
            case 5:
                printf("Você escolheu a Opção 5!\n");
                printf("Informações importantes:\n Para remover  a palavra em portugues, deve ser removida a palavra em inglês da árvore binária correspondente a palavra em português da mesma unidade.\n Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da árvore Rubro- negra!\n");
                printf("Infome a unidade: \n");
                scanf("%d", &unidade);
                limparBuffer();
                printf("Digite a palavra em portugues: ");
                fgets(palavra_removida, sizeof(palavra_removida), stdin); 
                palavra_removida[strcspn(palavra_removida, "\n")] = '\0'; 
                remover_palavra_completa_2_3(&arvore2_3, palavra_removida, unidade);
                break;
            case 6:
                printf("Você escolheu a Opção 6!\n");
                mostrar(arvore2_3);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n"); 
    } while (opcao != 0); 

    

    return 0;

}

