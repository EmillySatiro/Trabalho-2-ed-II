#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra.h"
#include "./extrair_rubro.h"


/**
 * @brief Remove espaços em branco e tabulações do início e do fim de uma string.
 *
 * Esta função recebe uma string e remove todos os espaços em branco e tabulações
 * do início e do fim da string. Se a string for NULL, ela retorna NULL. Se a string
 * contiver apenas espaços em branco e/ou tabulações, ela retorna uma string vazia.
 *
 * @param str A string a ser processada.
 * @return A string processada com espaços em branco e tabulações removidos do início e do fim.
 */
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

/**
 * @brief Função para extrair dados de um arquivo e inserir em uma árvore rubro-negra.
 *
 * Esta função abre um arquivo chamado "Dicionario.txt" para leitura e extrai dados
 * dele para inserir em uma árvore rubro-negra. O arquivo deve conter linhas com
 * informações de unidades e palavras em inglês, que serão processadas e inseridas
 * na árvore.
 *
 * @param arvore Ponteiro duplo para a árvore rubro-negra onde os dados serão inseridos.
 * @return Retorna a árvore rubro-negra com os dados inseridos.
 *
 * @note A função espera que o arquivo "Dicionario.txt" esteja no mesmo diretório de execução.
 *       Em caso de erro ao abrir o arquivo, a função exibirá uma mensagem de erro e encerrará o programa.
 *       A função também assume que as linhas do arquivo estão formatadas corretamente.
 */
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
            }
        }
        else
        {
            char *pt = strtok(linha, ":,;");
            pt = trim(pt);

            if (pt)
            {
                strcpy(palavra_ingles, pt);
                while ((pt = strtok(NULL, ":,;")) != NULL)
                {
                    pt = trim(pt);
                    Informacao_VP *info = criar_info_vp(pt, palavra_ingles, unidade);
                    if (info != NULL) {
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
