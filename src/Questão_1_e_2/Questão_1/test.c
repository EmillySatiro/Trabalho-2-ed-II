#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV2_3.h"
#include "../Binaria/ARV_BINARIA.h"

ARV2_3 *arvore23_buscar_caminho(ARV2_3 *raiz, char *info);


typedef double tempo_tipo;


tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo) (fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}

Informacao preencher_info(char *palavra)
{
    Informacao info;
    unsigned long long valor = rand() % 100000000000ULL;
    info.palavra_ingles = cria_arvore_binaria(palavra, valor);

    strcpy(info.palavra_portugues, palavra);
    info.unidade = rand() % 100;  // Exemplo de dado aleatório, como quantidade de unidades

    return info;
}

ARV2_3 *montar_arvore_23(int quant, int tam)
{
    ARV2_3 *arvore = NULL;
    int atual = 0;
    char *palavra = (char *) malloc(tam + 1);

    for (int i = 0; i < tam; i++) {
        palavra[i] = 'a';
    }
    palavra[tam] = '\0';

    while (atual < quant) {
        for (int i = tam - 1; i >= 0; i--) {
            for (int j = 'a'; j <= 'z' && atual < quant; j++) {
                palavra[i] = j;
                Informacao info = preencher_info(palavra);
                insere(&arvore, info);
                atual++;
            }
        }
    }

    free(palavra);
    return arvore;
}
tempo_tipo calcular_tempo_medio(ARV2_3 **arvore, char *info, int repeticoes)
{
    tempo_tipo media = 0;

    for (int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        ARV2_3 *no_encontrado;
        

        tempo_tipo tempo_gasto;

        inicio = clock();

        // Função para buscar na árvore
        no_encontrado = buscar_palavra_2_3(*arvore, info);

        fim = clock();
        
        tempo_gasto = calcula_tempo(inicio, fim);
        media += tempo_gasto;
    }
    
    media /= repeticoes;
    return media;
}

ARV2_3 *arvore23_buscar_caminho(ARV2_3 *raiz, char *info)
{
    ARV2_3 *no = NULL;

    if (raiz != NULL)
    {
        printf("[1º] %s ", raiz->info1.palavra_portugues);

        if (raiz->quant_infos == 2)
            printf("| [2º] %s ", raiz->info2.palavra_portugues);

        printf("-> ");
   
        if (strcmp(info, raiz->info1.palavra_portugues) == 0 || 
            (raiz->quant_infos == 2 && strcmp(info, raiz->info2.palavra_portugues) == 0)) {
            no = raiz;
        } else if (strcmp(info, raiz->info1.palavra_portugues) < 0) {
            no = arvore23_buscar_caminho(raiz->esquerda, info);
        } else if (raiz->quant_infos == 1 || (strcmp(info, raiz->info2.palavra_portugues) < 0)) {
            no = arvore23_buscar_caminho(raiz->centro, info);
        } else {
            no = arvore23_buscar_caminho(raiz->direita, info);
        }
    }

    return no;
}

int main(){
    
srand(time(NULL));
int tamanho = 5, repeticoes = 30;
    int quant_nos = 1000;  // Quantidade de palavras no conjunto

    char palavras[][50] = {"amor", "biscoito", "carro", "dado", "elefante", 
                            "futebol", "gato", "homem", "igreja", "jacaré", 
                            "kiwi", "laranja", "montanha", "navio", "ovo", 
                            "pato", "queijo", "rato", "sapato", "tigre", 
                            "uva", "vento", "wesley", "xadrez", "yasmin", 
                            "zebra", "porta", "jardim", "livro", "telefone"};

    int quant_palavras = sizeof(palavras) / sizeof(char [50]);

    // Montar árvore 2-3 com palavras aleatórias
    ARV2_3 *arvore = montar_arvore_23(quant_nos, tamanho);

    for (int i = 0; i < quant_palavras; i++) {
        Informacao info = preencher_info(palavras[i]);
        insere(&arvore, info);
    }

    // Calcular o tempo médio de execução para as buscas
    for (int i = 0; i < quant_palavras; i++) {
        arvore23_buscar_caminho(arvore, palavras[i]);
        printf("\n");
        tempo_tipo media = calcular_tempo_medio(&arvore, palavras[i], repeticoes);
        printf("[%dº] [%s] Tempo médio de execução: %lf microssegundos\n\n", i + 1, palavras[i], media);
    }

    printf("\n[Árvore de %d elementos]\n", quant_nos + quant_palavras);


    return 0;
}
