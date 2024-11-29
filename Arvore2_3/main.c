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
    // Criar a árvore vazia (inicializa a raiz como NULL)
    Rubronegra *raiz = NULL;
    
    // Exemplo de inserção de dados com palavras e unidades
    Informacao_VP info1 = {"abobora", 2,NULL};
    Informacao_VP info2 = {"cachorro", 15, NULL};
    Informacao_VP info3 = {"papagaio", 7, NULL};
    Informacao_VP info4 = {"ola", 2,NULL};
    Informacao_VP info5 = {"zebra",2, NULL};
    Informacao_VP info6 = {"casa",2, NULL};
    Informacao_VP info7 = {"abobora",2, NULL};
    Informacao_VP info8 = {"pera",2, NULL};
    Informacao_VP info9 = {"uva", 2,NULL};
    Informacao_VP info10 = {"gato", 10, NULL}; 
    
    // Inserir elementos na árvore
    raiz = conferindo_raiz(raiz, info1);
    raiz = conferindo_raiz(raiz, info2);
    raiz = conferindo_raiz(raiz, info3);
    raiz = conferindo_raiz(raiz, info4);
    raiz = conferindo_raiz(raiz, info5);
    raiz = conferindo_raiz(raiz, info6);
    raiz = conferindo_raiz(raiz, info7);
    raiz = conferindo_raiz(raiz, info8);
    raiz = conferindo_raiz(raiz, info9);
    raiz = conferindo_raiz(raiz, info10);
    
    // Mostrar a árvore
    printf("Exibindo a árvore Rubro-Negra:\n");
    mostrar_rubronegra(raiz);
    char palavra[] = "gato";
    int resul = remover_na_arvore(&raiz, palavra); 

    printf("Exibindo a árvore Rubro-Negra depois de remover:\n");
    mostrar_rubronegra(raiz);
    
    //Liberar memória (se necessário)
    liberar_rubronegra(&raiz);

    return 0;
}




