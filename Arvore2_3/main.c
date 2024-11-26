#include <stdio.h>
#include <stdlib.h>
#include "ARV2_3.h"

int main() {

    Informacao info1 = {"ola", NULL};
    Informacao info2 = {"zebra", NULL};
    Informacao info3 = {"casa", NULL};
    Informacao info4 = {"abobora", NULL};
    Informacao info5 = {"pera", NULL};
    Informacao info6 = {"uva", NULL};
    ARV_BINARIA *palavra = NULL; // Inicializa a árvore binária como vazia
    ARV2_3 *raiz = NULL; // Inicializa a árvore 2-3 como vazia

    // Insere os elementos na árvore 2-3
    insere(&raiz, info1);
    insere(&raiz, info2);
    insere(&raiz, info6);
    insere(&raiz, info3);
    insere(&raiz, info4);
    insere(&raiz, info5);

    // Exibe a árvore 2-3 em ordem
    printf("\nArvore 2-3 em ordem:\n");
    mostrar(raiz);

    // Insere os elementos na árvore binária
    insere_arvore_binaria(&palavra, "hello", 1);  // Passando referência corretamente
    insere_arvore_binaria(&palavra, "world", 1);
    insere_arvore_binaria(&palavra, "apple", 1);
    insere_arvore_binaria(&palavra, "banana", 1);
    insere_arvore_binaria(&palavra, "orange", 1);

    // Exibe a árvore binária em ordem
    printf("\nArvore binaria em ordem:\n");
    mostrar_arvore_binaria(&palavra, 1); // Passando ponteiro corretamente

    // Libera a memória da árvore binária
    libera_arvore_binaria(&palavra);

    return 0;
}
