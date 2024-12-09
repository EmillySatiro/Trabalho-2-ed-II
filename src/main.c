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

    // mostrar_palavras_em_portugues_de_uma_unidade(raiz, 1);
    mostrar_rubronegra(raiz);

    printf("============================================================\n");
    remover_palavra_ingles_e_unidade(&raiz,"Bug", 1);
    mostrar_rubronegra(raiz);

    // mostrar_palavras_em_portugues_de_uma_unidade(raiz, 1);
    // buscar_palavra_portugues(raiz, "barramento");

    // buscar_palavra_portugues(raiz, "barramento");


    // mostrar_palavras_em_portugues_de_uma_unidade(raiz, 1);
    //Imprimir_toda_palavras(raiz, "barramento");

    // liberar_rubronegra(&raiz);
    // if (raiz->info && raiz->info->palavras_ingles){
    //     libera_arvore_binaria(&raiz->info->palavras_ingles);
    // }
    return 0;
}
