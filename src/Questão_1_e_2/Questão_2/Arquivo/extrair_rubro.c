#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra.h"
#include "./extrair_rubro.h"



char *trim(char *str) {
    if (str == NULL) return str; 

   
    while (*str && (isspace((unsigned char)*str) || *str == '\t')) {
        str++;
    }

   
    if (*str == '\0') {
        return str;
    }

    
    char *end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char)*end) || *end == '\t')) {
        end--;
    }
    *(end + 1) = '\0';  
    return str;
}


Rubronegra *pegar_dados_arquivo(Rubronegra **arvore){

    FILE *arquivo = fopen("Dicionario.txt", "r");
    if (!arquivo){
        perror("Erro ao abrir o arquivo");
            exit(EXIT_FAILURE);
    }

    char linha[100];
    int unidade;
    char palavra_ingles[100];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strstr(linha, "Unidade"))
        {
            if (sscanf(linha, "%% Unidade %d", &unidade) == 1){
                //printf("Unidade: %d\n", unidade);
            }
        }
        else
        {
            char *pt = strtok(linha, ":,;");
            pt = trim(pt);

            if (pt)
            {
                strcpy(palavra_ingles, pt);
                //printf("Palavra em ingles: %s\n", palavra_ingles);
                while ((pt = strtok(NULL, ":,;")) != NULL)
                {
                    pt = trim(pt);
                    Informacao_VP *info = criar_info_vp(pt, palavra_ingles, unidade);
                    if (info != NULL) {
                        //printf("Palavra em portugues: %s\n", info->palavra_portugues);
                        inserir_rubro(arvore, info);
                    } else {
                        fprintf(stderr, "Erro ao criar Informacao_VP\n");
                    }
                }
            }
        }
    } printf("Palavras extraidas do arquivo com sucesso!!\n");

    return *arvore;
   
    fclose(arquivo);
}
