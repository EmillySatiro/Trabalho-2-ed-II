#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Binaria/ARV_BINARIA.h"
#include "../Questão_2/Rubro_negra.h"
#include "../../Questão_1_e_2/Questão_2/Arquivo/extrair_rubro.h"

typedef double tempo_tipo;

tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo)(fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}

Informacao_VP* criar_info(char *palavra_portugues) {
    int unidade = rand() % 10000000 + 1; 
    return criar_info_vp(palavra_portugues, palavra_portugues, unidade);
}

Rubronegra* montar_arvore(int quant, int tam)
{
    Rubronegra *arvore = NULL;
    int atual = 0;
    char *palavra = (char *)malloc(tam + 1);  // +1 para o caractere null de string

    for(int i = 0; i < tam; i++) {
        palavra[i] = 'a';
    }
    palavra[tam] = '\0';  // Termina a string

    do
    {
        for(int i = tam - 1; i >= 0; i--)
        {
            for(int j = 'a'; j <= 'z' && atual < quant; j++)
            {
                palavra[i] = j;
                Informacao_VP *info = criar_info(palavra);
                inserir_rubro(&arvore, info);
                atual++;
            }
        }

    } while(atual < quant);

    free(palavra);
    return arvore;
}

Rubronegra *arvorevp_buscar_caminho(Rubronegra *raiz, char *palavra);

tempo_tipo calcular_tempo_medio(Rubronegra **arvore, char *info, int repeticoes)
{
    tempo_tipo media = 0;

    for(int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        Rubronegra *no_encontrado;
        tempo_tipo tempo_gasto;

        inicio = clock();

        // Substitua pela função de busca desejada
        no_encontrado = arvorevp_buscar_caminho(*arvore, info); 

        fim = clock();
        
        tempo_gasto = calcula_tempo(inicio, fim);
        media += tempo_gasto;
    }
    
    media /= repeticoes;
    return media;
}

Rubronegra *arvorevp_buscar_caminho(Rubronegra *raiz, char *palavra)
{
    Rubronegra *retorno = NULL;

    if(raiz != NULL)
    {
        printf("%d -> ", raiz->cor);

        int resultado = strcmp(palavra, raiz->info->palavra_portugues);

        if(resultado == 0)
            retorno = raiz;
        else if(resultado < 0)
            retorno = arvorevp_buscar_caminho(raiz->esquerda, palavra);
        else if(resultado > 0)
            retorno = arvorevp_buscar_caminho(raiz->direita, palavra);
    }

    return retorno;
}

int main()
{
    srand(1);
    srand(time(NULL));

    int tamanho = 5, repeticoes = 30;
    int quant_nos = 10000; // 26^5

    char palavras[][50] =  {"amor", "biscoito", "carro", "dado", "elefante", "futebol", "gato", "homem", "igreja", "jacaré", "kiwi", "laranja", "montanha", "navio", "ovo", "pato", "queijo", "rato", "sapato", "tigre", "uva", "vento", "wesley", "xadrez", "yasmin", "zebra", "porta", "jardim", "livro", "telefone"};

    int quant_palavras = sizeof(palavras) / sizeof(char [50]);

    Rubronegra *arvore;
    arvore = montar_arvore(quant_nos, tamanho);

    // Inserir palavras na árvore
    for(int i = 0; i < quant_palavras; i++)
    {
        Informacao_VP *info = criar_info(palavras[i]);
        inserir_rubro(&arvore, info);
    }

    // Calcular tempo médio
    for(int i = 0; i < quant_palavras; i++)
    {
        tempo_tipo media = calcular_tempo_medio(&arvore, palavras[i], repeticoes);
        printf("[%dº] [%s] Tempo médio de execução: %lf microssegundos\n\n", i+1, palavras[i], media);
    }

    printf("\n[Árvore de %d elementos]\n", quant_nos + quant_palavras);
    // Liberar memória da árvore
    liberar_rubronegra(&arvore);

    return 0;
}