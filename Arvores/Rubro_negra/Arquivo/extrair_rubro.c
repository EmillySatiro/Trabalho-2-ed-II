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

    // Loop para ler as linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        // Remover o caractere de nova linha, se existir
        linha[strcspn(linha, "\n")] = '\0';

        // Verificar se a linha contém a palavra "Unidade"
        if (strstr(linha, "Unidade"))
        {
            // Extrair a unidade da linha
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1)
            {
                printf("Unidade: %d\n", unidade);
            }
        }
        else
        {
            // Processar as palavras caso contrário
            char *pt = strtok(linha, ":");
            if (pt)
            {
                // Copiar a palavra em inglês
                strcpy(palavra_ingles, pt);
                printf("Palavra em inglês: %s\n", palavra_ingles);

                // Agora processar as traduções
                while ((pt = strtok(NULL, ",;")) != NULL)
                {
                    // Remover espaços ou outros caracteres indesejados
                    while (*pt == ' ') pt++;  // Pular espaços iniciais

                    printf("Tradução em português: %s\n", pt);
                }
                printf("\n");
            }
        }
    }

    fclose(arquivo);
}
