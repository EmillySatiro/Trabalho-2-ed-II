#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "ARV2_3.h"
#include "Vermelho_preta.h"



// int main(){
  
//     Informacao info1 = {"ola", NULL};
//     Informacao info2 = {"zebra", NULL};
//     Informacao info3 = {"casa", NULL};
//     Informacao info4 = {"abobora", NULL};
//     Informacao info5 = {"pera", NULL};
//     Informacao info6 = {"uva", NULL};
//     ARV2_3 *raiz = NULL; // Inicializa a árvore como vazia

//     // Insere os elementos na árvore
//     insere(&raiz, info1);
//     insere(&raiz, info2);
//     insere(&raiz, info6);
//     insere(&raiz, info3);
//     insere(&raiz, info4);
//     insere(&raiz, info5);

//     // Exibe a árvore em ordem
//     printf("\nArvore em ordem:\n");
//     mostrar(raiz);

//     return 0;
//     liberar_2_3(raiz); 
// }

int main() {
    // Criando a raiz da árvore rubro-negra
    Rubronegra *raiz = NULL;

    // Criando alguns dados para inserção
    Informacao_VP info1;
    strcpy(info1.palavra_portugues, "maçã");
    info1.unidade = 10;

    Informacao_VP info2;
    strcpy(info2.palavra_portugues, "banana");
    info2.unidade = 20;

    Informacao_VP info3;
    strcpy(info3.palavra_portugues, "laranja");
    info3.unidade = 15;

    Informacao_VP info4;
    strcpy(info4.palavra_portugues, "kiwi");
    info4.unidade = 5;

    // Inserindo elementos na árvore
    raiz = conferindo_raiz(raiz, info1);
    raiz = conferindo_raiz(raiz, info2);
    raiz = conferindo_raiz(raiz, info3);
    raiz = conferindo_raiz(raiz, info4);

    // Mostrando a árvore rubro-negra
    printf("Árvore Rubro-Negra:\n");
    mostrar_rubronegra(raiz);

    // Liberando a memória alocada para a árvore
    liberar_rubronegra(&raiz);

    return 0;
}




