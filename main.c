#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"
#include "Arvores/Arvore_2_3/Arquivo/Extrair.h"


int main() {
    ARV2_3 *raiz = NULL;

    // Ler o arquivo e inserir na árvore 2-3
    ler_arquivo_e_inserir("Dicionario.txt", &raiz);

    mostrar(raiz);

    // Liberar memória alocada
    liberar_arv2_3(raiz);

    return 0;
}





