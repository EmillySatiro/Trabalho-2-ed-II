#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"
#include "Arvores/Rubro_negra/Rubro_negra.h"
#include "Arvores/Rubro_negra/Arquivo/extrair_rubro.h"

int main()
{


    Rubronegra *raiz = NULL;

 

    raiz = pegar_dados_arquivo(&raiz);

    // printf("=============Palavras em portugues=============\n");

    // mostrar_rubronegra(raiz);

    printf("=============Palavras em ingles =============\n");
    // printf("=============Palavras em ingles =============\n");

    // mostrar_binaria_em_rubro(raiz, 1);

    printf("=============Palavras em portugues de uma unidade =============\n");

    mostrar_palavras_em_portugues_de_uma_unidade(raiz, 1);
    //buscar_palavra_portugues(raiz, "barramento");

    
    if (raiz->info && raiz->info->palavras_ingles)
    {
        libera_arvore_binaria(&raiz->info->palavras_ingles);
    }
    liberar_rubronegra(&raiz);
    // if (raiz->info && raiz->info->palavras_ingles){
    //     libera_arvore_binaria(&raiz->info->palavras_ingles);
    // }
    // liberar_rubronegra(&raiz);

    buscar_palavra_portugues(raiz, "barramento");

    return 0;
}
