#include <stdio.h>
#include <stdlib.h>
#include "ARV2_3.h"
#include "ARV_BINARIA.h"

int main()
{


    ARV_BINARIA *palavra = NULL; // Inicializa a árvore binária como vazia

    // Insere os elementos na árvore 2-3


    // Exibe a árvore 2-3 em ordem


    // Insere os elementos na árvore binária
    insere_arvore_binaria(&palavra, "hello", 1);
    insere_arvore_binaria(&palavra, "world", 1);
    insere_arvore_binaria(&palavra, "goodbye", 1);
    insere_arvore_binaria(&palavra, "cruel", 1);
    insere_arvore_binaria(&palavra, "world", 1);
    

    mostrar_arvore_binaria(palavra, 1);

    ARV_BINARIA *resposta = buscar_palavra(palavra, "world");
    if (resposta)
    {
        printf("Palavra encontrada: %s\n", resposta->palavra_ingles);
    }
    else
    {
        printf("Palavra não encontrada\n");
    }
    remover_no(&palavra, "hello");
    printf("Após remover 'hello'=========:\n");
    mostrar_arvore_binaria(palavra, 1);
    remover_no(&palavra, "world");
    printf("Após remover 'world'=========:\n");
    mostrar_arvore_binaria(palavra, 1);

    // Libera a árvore binária
    libera_arvore_binaria(&palavra);


    return 0;
}
