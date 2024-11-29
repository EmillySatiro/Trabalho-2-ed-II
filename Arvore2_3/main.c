#include <stdio.h>
#include <stdlib.h>
#include "ARV2_3.h"
#include "ARV_BINARIA.h"

int main()
{

    ARV_BINARIA *palavra = NULL; // Inicializa a árvore binária como vazia
    ARV2_3 *raiz = NULL;         // Inicializa a árvore 2-3 como vazia

    Informacao info1 = {"ola", NULL};

    //     // Insere os elementos na árvore
       insere(&raiz, info1);
    //
    //     // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    mostrar(raiz);

    //     return 0;
    liberar_2_3(raiz);

    insere_arvore_binaria(info1.palavra_ingles, "apple", 10);
    insere_arvore_binaria(info1.palavra_ingles, "maçã", 10);
    insere_arvore_binaria(info1.palavra_ingles, "manzana", 10);

    mostrar_arvore_binaria(raiz->info1.palavra_ingles, 10);

    // Libera a árvore binária
    libera_arvore_binaria(&palavra);
}

// int main()
// {
//     // // Criando a raiz da árvore rubro-negra
// Rubronegra *raiz = NULL;

// // Criando alguns dados para inserção
// Informacao_VP info1;
// strcpy(info1.palavra_portugues, "maçã");
// info1.unidade = 10;

// Informacao_VP info2;
// strcpy(info2.palavra_portugues, "banana");
// info2.unidade = 20;

// Informacao_VP info3;
// strcpy(info3.palavra_portugues, "laranja");
// info3.unidade = 15;

// Informacao_VP info4;
// strcpy(info4.palavra_portugues, "kiwi");
// info4.unidade = 5;

// // Inserindo elementos na árvore
// raiz = conferindo_raiz(raiz, info1);
// raiz = conferindo_raiz(raiz, info2);
// raiz = conferindo_raiz(raiz, info3);
// raiz = conferindo_raiz(raiz, info4);

// // Mostrando a árvore rubro-negra
// printf("Árvore Rubro-Negra:\n");
// mostrar_rubronegra(raiz);

// // Liberando a memória alocada para a árvore
// liberar_rubronegra(&raiz);

//     return 0;
// }
