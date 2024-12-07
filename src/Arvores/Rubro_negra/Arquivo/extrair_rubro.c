#include <stdio.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra.h"
#include "./extrair_rubro.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *trim(char *str) {
    char *end;
    // Remove espaços do início
    while (isspace((unsigned char)*str)) str++;
    if (*str == '\0') return str; // String vazia

    // Remove espaços do final
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

Rubronegra *pegar_dados_arquivo(Rubronegra **arvore)
{
    printf("Entrou\n");

    FILE *arquivo = fopen("Dicionario.txt", "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
            exit(EXIT_FAILURE);
    }

    char linha[200];
    int unidade;
    char palavra_ingles[100];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strstr(linha, "Unidade"))
        {
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1)
            {
                 printf("Unidade: %d\n", unidade);
            }
        }
        else
        {
            char *pt = strtok(linha, ":");
            if (pt)
            {
                strcpy(palavra_ingles, pt);
         

                while ((pt = strtok(NULL, ",;")) != NULL)
                {
                
                    pt = trim(pt);
                    Informacao_VP *info = criar_info_vp(pt, palavra_ingles, unidade);
                    if (info != NULL) {
                        inserir_rubro(arvore, info);
                    } else {
                        fprintf(stderr, "Erro ao criar Informacao_VP\n");
                    }
                }
                printf("\n");
            }
        }
    }

    return *arvore;

    fclose(arquivo);
}
