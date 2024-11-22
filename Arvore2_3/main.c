#include <stdio.h>
<<<<<<< HEAD
#include <stdlib.h>
#include "Arvore_binaria/ARV_BINARIA.h"  
#include "ARV2_3.h"   
=======
#include <stdlib.h> 
#include "ARV2_3.h"

>>>>>>> 6c9427b442816ad84f9b906bc7289cd6a9579e25


int main(){
  
    Informacao info1 = {"ola", NULL};
    Informacao info2 = {"zebra", NULL};
    Informacao info3 = {"casa", NULL};
    Informacao info4 = {"abobora", NULL};
    Informacao info5 = {"pera", NULL};
    Informacao info6 = {"uva", NULL};
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
    // Libera memória alocada
    liberar(raiz);
    return 0;
}
