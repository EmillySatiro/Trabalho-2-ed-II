#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Binaria/ARV_BINARIA.h"
#include "../Questão_1/ARV2_3.h"
#include "../../Questão_1_e_2/Questão_1/Arquivo/Extrair.h"


int main() {
    ARV2_3 *arvore2_3 = NULL;
    int opcao; 
    int unidade = 0;
    char palavra[100];
    char palavra_removida[100];
    srand(time(NULL));
    int tamanho = 5, repeticoes = 30;
    int quant_nos = 1000;  // Quantidade de palavras no conjunto
    char palavras[][50] = {"processamento", "algoritmo", "programação", "código", "linguagem", 
                                            "python", "java", "html", "css", "sql", 
                                            "banco de dados", "api", "endpoint", "rest", "json", 
                                            "xml", "tcp", "ssl", "vpn", "firewall", 
                                            "segurança", "automação", "robótica", "iot", "wearables", 
                                            "blockchain", "bitcoin", "ethereum", "criptomoeda", "smart contract", 
                                            "fintech", "startups", "investimento", "aceleração"};
    int quant_palavras = sizeof(palavras) / sizeof(char [50]);

    do {
        
        printf("========= MENU PRINCIPAL =========\n");
        printf("1.Passar as palavras do arquivo para a Arvore\n");
        printf("2.Informe uma unidade e então veja todas as palavras da unidade em português seguida das equivalentes em inglês\n");
        printf("3.Informe uma palavra em português e então veja  todas as palavras em inglês equivalente a palavra em português dada, independente da unidade\n");
        printf("4.Remover uma palavra em inglês de todas as arvores que a mesma pertence\n");
        printf("5.Remover uma palavra em português e a unidade a qual a mesma pertence\n");
        printf("6.Mostrar todas as palavras em portugues e suas traduções para o inglês\n");
        printf("7 Buscar caminho de 30 elementos predefinidos com visualização de tempo e quandidade de elesmentos na arvore\n");
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
                printf("Informações importantes: \n Caso ela seja a única palavra em uma das árvores binárias, ela também será removida da arvore 2_3\n");
                printf("Infome a unidade: \n");
                scanf("%d", &unidade);
                limparBuffer();
                printf("Digite a palavra em ingles: ");
                fgets(palavra_removida, sizeof(palavra_removida), stdin); 
                palavra_removida[strcspn(palavra_removida, "\n")] = '\0'; 
                remover_palavra_ingles_e_unidade_2_3(&arvore2_3, palavra_removida, unidade) ;
                break;
            case 5:
                printf("Você escolheu a Opção 5!\n");
                printf("Informações importantes:\n Para remover  a palavra em portugues, deve ser removida a palavra em inglês da árvore binária correspondente a palavra em português da mesma unidade.\n Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da árvore 2_3 !\n");
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
            case 7: 
                printf("Você escolheu opção 7!\n");
                    for (int i = 0; i < quant_palavras; i++) {
                        arvore23_buscar_caminho(arvore2_3, palavras[i]);
                        printf("\n");
                        tempo_tipo media = calcular_tempo_medio(&arvore2_3, palavras[i], repeticoes);
                        printf("[%dº] [%s] Tempo médio de execução: %lf microssegundos\n\n", i + 1, palavras[i], media);
                    }

                    printf("\n[Árvore de %d elementos]\n", quant_nos + quant_palavras);
            break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n"); 
    } while (opcao != 0); 
    liberar_arvore_2_3(&arvore2_3);
    return 0;


}
