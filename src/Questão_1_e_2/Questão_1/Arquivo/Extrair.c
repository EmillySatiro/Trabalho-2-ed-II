#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../Binaria/ARV_BINARIA.h"
#include "../../Questão_1/ARV2_3.h"

#define Tamanho_linha 1024

/**
 * @brief Remove espaços em branco e tabulações do início e do fim de uma string.
 *
 * Esta função recebe uma string e remove todos os espaços em branco e tabulações
 * do início e do fim da string. Se a string for nula, ela retorna a própria string.
 *
 * @param str A string a ser processada. Pode ser nula.
 * @return A string processada com espaços e tabulações removidos do início e do fim.
 */
char *trim_23(char *str) {
    if (str == NULL) return str;  // Garantir que o ponteiro não seja nulo

    
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
 * @brief Extrai dados de um arquivo e insere em uma árvore 2-3.
 *
 * Esta função abre o arquivo "Dicionario.txt" para leitura e extrai as informações
 * contidas nele, inserindo-as em uma árvore 2-3. O arquivo deve conter linhas no
 * formato "Unidade X" para indicar a unidade e linhas no formato "palavra:tradução"
 * para indicar as palavras e suas traduções.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3 onde os dados serão inseridos.
 * @return ARV2_3* Ponteiro para a raiz da árvore 2-3 após a inserção dos dados.
 *
 * @note A função espera que o arquivo "Dicionario.txt" esteja no mesmo diretório
 *       de execução do programa.
 * @note A função utiliza a função trim_23 para remover espaços em branco das palavras.
 * @note A função utiliza a função criar_info para criar a estrutura de informação a ser inserida.
 * @note A função utiliza a função insere para inserir a informação na árvore 2-3.
 * @note Em caso de erro ao abrir o arquivo, a função imprime uma mensagem de erro e encerra o programa.
 */
ARV2_3 *Pegar_dados_arquivo_23(ARV2_3 **raiz) {
    FILE *arquivo = fopen("Dicionario.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[100];
    int unidade = 0;
    char palavra_ingles[100]; 
    while (fgets(linha, sizeof(linha), arquivo)) 
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strstr(linha, "Unidade")) {
            unidade += 1;
        } else 
        {
            char *pt = strtok(linha, ":,;");
            pt = trim_23(pt);
            if (pt) {
                strcpy(palavra_ingles, pt);
                
                while ((pt = strtok(NULL, ":,;")) != NULL) 
                {
                    pt = trim_23(pt);
                    Informacao info = criar_info(pt,palavra_ingles, unidade);
                    if (&info != NULL) {
                       Informacao sobe; 
                       inserir_Elemento_ARV_2_3(NULL,raiz, info, &sobe);
                    } else {
                        fprintf(stderr, "Erro ao criar Informacao_VP\n");
                    }

                }
            }
        }
    }

    printf("Palavras extraídas do arquivo com sucesso!!\n");

    fclose(arquivo);
    return *raiz;
}

