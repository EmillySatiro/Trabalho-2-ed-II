#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV2_3.h"
#include "../Binaria/ARV_BINARIA.h"
#include "../Rubro_negra/Rubro_negra.h"


ARV2_3 *criar_no(Informacao info, ARV2_3 *filho_esquerda, ARV2_3 *filho_centro)
{
    ARV2_3 *no = (ARV2_3 *)malloc(sizeof(ARV2_3));

    if (no != NULL)
    {
        no->info1 = info;
        no->esquerda = filho_esquerda;
        no->centro = filho_centro;
        no->quant_infos = 1;
    }
    else
    {
        printf("Não foi possivel criar no \n ");
    }
    return no;
}

ARV2_3 *quebra_No(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **filho)
{
    ARV2_3 *maior_info;

    // caso 1 : O novo elemento (info) é maior que minha info2.
    if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) > 0)
    {
        *sobe = (*no)->info2; // o info dois sobe pq ele é o do meio

        maior_info = criar_no(info, (*no)->direita, filho ? *filho : NULL);
        // criando um no para o maior que no caso é meu novo elemento( esse filho ? * filho: null é se o filho não for nulo ele executa e manda(*filho)  para o criar e se não for manda null)

        // cado 2: o novo elemento é oq sobe pois ele esta entre info 1 e info 2
    }
    else if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) > 0)
    {
        *sobe = info; // novo elemento sobe

        maior_info = criar_no((*no)->info2, filho ? *filho : NULL, (*no)->direita);
        // msm coisa do outro só que quem sobe é info 2
    }
    else
    {                         // caso 3 info menor info 1
        *sobe = (*no)->info1; // quem vai subir é info 1

        maior_info = criar_no((*no)->info2, (*no)->centro, (*no)->direita);

        // ajustar o no atual para nova info ser info 1
        (*no)->info1 = info;
        (*no)->centro = (filho ? *filho : NULL);
    }

    (*no)->quant_infos = 1;

    return maior_info;
}

int eh_folha(ARV2_3 *no)
{
    return (no->esquerda == NULL);
}

void add_elementos(ARV2_3 *no, Informacao Info, ARV2_3 *filho)
{

    if (strcmp(Info.palavra_portugues, no->info1.palavra_portugues) > 0)
    {
        no->info2 = Info;
        no->direita = filho;
    }
    else
    {
        no->info2 = no->info1;
        no->direita = no->centro;
        no->info1 = Info;
        no->centro = filho;
    }
    no->quant_infos = 2;
}

ARV2_3 *inserir_Elemento_ARV_2_3(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **pai)
{
    Informacao sobe_sup;
    ARV2_3 *maior = NULL;

    // se é nullo cria né
    if (*no == NULL)
    {
        *no = criar_no(info, NULL, NULL);
    }
    else
    {
        // caso seja folha
        if (eh_folha(*no))
        {
            if ((*no)->quant_infos == 1)
            {
                add_elementos(*no, info, NULL);
            }
            else
            {
                maior = quebra_No(no, info, sobe, NULL);
                // se não houver pai, cria um novo só superior
                if (pai && !(*pai))
                {
                    *no = criar_no(*sobe, *no, maior);
                    maior = NULL; // só pra limpar o maior
                }
            }
        }
        else
        { // caso não seja uma folha procrura onde vamos inserir né
            if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) < 0)
            {
                maior = inserir_Elemento_ARV_2_3(&((*no)->esquerda), info, sobe, no);
            }
            else if (((*no)->quant_infos == 1) || (strcmp((info.palavra_portugues), (*no)->info2.palavra_portugues)) < 0)
            {
                maior = inserir_Elemento_ARV_2_3(&((*no)->centro), info, sobe, no);
            }
            else
            {
               maior = inserir_Elemento_ARV_2_3(&((*no)->direita), info, sobe, no);
            }

            // se maior foi retornado, o nó pode precisar ser atualizado ou quebrado
            if (maior)
            {
                if ((*no)->quant_infos == 1)
                {
                    add_elementos(*no, *sobe, maior);
                    maior = NULL; // limpa maior após adicionar
                }
                else
                {
                    maior = quebra_No(no, *sobe, &sobe_sup, &maior);
                    if (pai)
                    {
                        *no = criar_no(sobe_sup, *no, maior);
                        maior = NULL; // limpar maior após criar o nó
                    }
                }
            }
        }
    }
    return maior;
}

void insere(ARV2_3 **raiz, Informacao info)
{
    Informacao sobe;
    ARV2_3 *novo_no = inserir_Elemento_ARV_2_3(raiz, info, &sobe, NULL);
    if (novo_no)
    {
        *raiz = criar_no(sobe, *raiz, novo_no);
    }
}

void mostrar(ARV2_3 *raiz)
{
    if (raiz)
    {
        mostrar(raiz->esquerda);
        printf("\n%d\n", raiz->info1.unidade);
        printf("%s\n", raiz->info1.palavra_portugues);
        printf(":");
        mostrar_arvore_binaria(raiz->info1.palavra_ingles, raiz->info1.unidade);
        mostrar(raiz->centro);

        if (raiz->quant_infos == 2)
        {
            printf("\n%d\n", raiz->info2.unidade);
            printf("%s\n", raiz->info2.palavra_portugues);
            printf(":");
            mostrar_arvore_binaria(raiz->info2.palavra_ingles, raiz->info2.unidade);
            mostrar(raiz->direita);
        }
    }
}

void liberar_2_3_binaria(Informacao *info)
{
    // liberar binaria
    free(info->palavra_portugues);
}

// void liberar_2_3(ARV2_3 *raiz)
// {
//     if (raiz)
//     {
//         liberar_2_3(raiz->esquerda);
//         liberar_2_3(raiz->centro);
//         if (raiz->quant_infos == 2)
//         {
//             liberar_2_3(raiz->direita);
//             liberar_2_3_binaria(&raiz->info2);
//         }
//         liberar_2_3_binaria(&raiz->info1);
//         free(raiz);
//     }
// }

void liberar_arv2_3(ARV2_3 *raiz) {
    if (raiz == NULL) return;
    // Liberar as subárvores binárias associadas a cada palavra
     libera_arvore_binaria(&raiz->info1.palavra_ingles);
     libera_arvore_binaria(&raiz->info2.palavra_ingles);


    // Liberar as subárvores 2-3
    liberar_arv2_3(raiz->esquerda);
    liberar_arv2_3(raiz->centro);
    liberar_arv2_3(raiz->direita);

    free(raiz);  // Liberar o próprio nó da árvore 2-3
}

Informacao criar_info(char *palavra_portugues, char *palavra_ingles, int unidade)
{
    ARV_BINARIA *arvore = NULL;  // A árvore binária será criada localmente
    Informacao info;

    strcpy(info.palavra_portugues, palavra_portugues);
    // Insere a palavra na árvore binária, que é criada fora da função
    insere_arvore_binaria(&arvore, palavra_ingles, unidade);
    // Atribuindo a árvore binária à estrutura de informação
    info.palavra_ingles = arvore;
    info.unidade = unidade;
    
    return info;
}

void inserir_binaria_em_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade, char *palavra_ingles)
{
    Informacao info_2_3 = criar_info(palavra_portugues, palavra_ingles, unidade);  // Agora a árvore binária é associada corretamente
    criar_no(info_2_3, NULL, NULL);  // O nó de ARV2_3 é criado com as informações corretas
    insere(raiz, info_2_3);  // A inserção é feita com os dados da informação criada
}

