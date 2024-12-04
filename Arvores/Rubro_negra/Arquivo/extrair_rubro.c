#include <stdio.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra.h"
#include "./extrair_rubro.h"

void pegar_dados_arquirvo(Rubronegra *arvore)
{
    printf("Entrou\n");

    FILE *arquivo;
    arquivo = fopen("Dicionario", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char palavra_ingles[100];
    int unidade;

    while (fscanf(arquivo, "% Unidade %d", &unidade) != EOF)
    {
        while (fscanf(arquivo, "%s", palavra_ingles) != EOF)
        {
            insere_arvore_binaria(arvore->info->palavras_ingles, palavra_ingles, unidade);
        }
        printf("Arquivo lido com sucesso\n");

        mostrar_arvore_binaria(arvore->info->palavras_ingles, unidade);
    }

    fclose(arquivo);
}