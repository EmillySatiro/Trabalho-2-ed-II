#include <stdio.h>
#include <stdlib.h> 
#include "ARV2_3.h"



int main(){
  
    Informacao info1 = {"ola", NULL};
    Informacao info2 = {"zebra", NULL};
    Informacao info3 = {"casa", NULL};
    Informacao info4 = {"abobora", NULL};
    Informacao info5 = {"pera", NULL};
    Informacao info6 = {"uva", NULL};
    ARV_BINARIA palavra;
    ARV2_3 *raiz = NULL; // Inicializa a árvore como vazia

    // Insere os elementos na árvore
    insere(&raiz, info1);
    insere(&raiz, info2);
    insere(&raiz, info6);
    insere(&raiz, info3);
    insere(&raiz, info4);
    insere(&raiz, info5);

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    mostrar(raiz);

    // insere_arvore_binaria(&palavra, "hello", 1);
    // insere_arvore_binaria(&palavra, "world", 2);
    // insere_arvore_binaria(&palavra, "apple", 3);
    // printf("\nArvore binaria em ordem:\n");
    // mostrar_arvore_binaria(&palavra, 1);


    return 0;
}
