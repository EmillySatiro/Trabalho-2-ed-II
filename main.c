#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Arvores/Binaria/ARV_BINARIA.h"
#include "Arvores/Arvore_2_3/ARV2_3.h"
#include "Arvores/Rubro_negra/Rubro_negra.h"
#include "Arvores/Arvore_2_3/Arquivo/Extrair.h"



int main() {

    ARV2_3 *arvore_2_3 = NULL;
    arvore_2_3 = (ARV2_3 *)malloc(sizeof(ARV2_3));

    processar_arquivo("Dicionario.txt",&arvore_2_3);
    
    printf("\nArvore em ordem:\n");
    mostrar(arvore_2_3);

    liberar_2_3(arvore_2_3); 
    return 0;

}




