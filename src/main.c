#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"
#include "Arvores/Rubro_negra/Rubro_negra.h"
#include "Arvores/Rubro_negra/Arquivo/extrair_rubro.h"
#include "Arvores/Arvore_2_3/Arquivo/Extrair.h"

int main()
{

    ARV2_3 *raiz = NULL;

    raiz = Pegar_dados_arquivo_23(&raiz);
    mostrar(raiz);

    // printf("=============Palavras em portugues=============\n");

    // mostrar_palavras_em_portugues_de_uma_unidade(raiz, 1);
 
    return 0;
}
