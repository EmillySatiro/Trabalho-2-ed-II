#include <stdio.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra.h"
#include "./extrair_rubro.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pegar_dados_arquivo(Rubronegra **arvore)
{
    printf("Entrou\n");

    FILE *arquivo;
    arquivo = fopen("Dicionario.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[200];  // Para armazenar cada linha do arquivo
    int unidade;
    char palavra_ingles[100];
    char *pt, *result;

    // Loop para ler as linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        result = linha;  // A linha lida será processada

        // Verificar se a linha contém a palavra "Unidade"
        if (strstr(result, "Unidade"))
        {
            // Extrair a unidade da linha
            pt = strtok(result, "%% Unidade ");  // Separar por "%% Unidade "
            unidade = atoi(pt);  // Converter a unidade para inteiro
            printf("Unidade: %d\n", unidade);
        }
        else
        {
            // Processar as palavras caso contrário
            pt = strtok(result, ":;,");

            if (pt)
            {
                // Copiar a palavra em inglês
                strcpy(palavra_ingles, pt);
                printf("Palavra em inglês: %s\n", palavra_ingles);

                // Agora processar as traduções
                while ((pt = strtok(NULL, ":;,")) != NULL)
                {
                    char pt_br[100];
                    // Copiar a tradução em português
                    strncpy(pt_br, pt + 1, strlen(pt) - 1);
                    printf("Tradução em português: %s\n", pt_br);
                }
            }
        }
    }

    fclose(arquivo);
}
