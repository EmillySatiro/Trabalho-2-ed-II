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
    }else if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) > 0)
    {
        *sobe = info; // novo elemento sobe

        maior_info = criar_no((*no)->info2, filho ? *filho : NULL, (*no)->direita);
        // msm coisa do outro só que quem sobe é info 2
    }else
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

void add_elementos(ARV2_3 *no, Informacao Info, ARV2_3 *filho)
{

    if (strcmp(Info.palavra_portugues, no->info1.palavra_portugues) > 0){
        no->info2 = Info;
        no->direita = filho;
    }else{
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

    // Se o nó for NULL, cria um novo nó com a informação
    if (*no == NULL){
        *no = criar_no(info, NULL, NULL);
    }
    else {
        // Caso seja uma folha
        if (eh_folha(*no)) {
            // Se o nó tiver apenas um elemento, adiciona a nova informação
            if ((*no)->quant_infos == 1) {
                // Verifica se a palavra já existe antes de adicionar
                if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) != 0) {
                    add_elementos(*no, info, NULL);
                }else {
                    insere_arvore_binaria((&(*no)->info1.palavra_ingles), info.palavra_ingles->palavra_ingles, info.unidade);
                }
            } else if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) != 0){ // Caso o nó tenha 2 informações
                maior = quebra_No(no, info, sobe, NULL);
                // Se não houver pai, cria um novo nó superior
                if (pai == NULL) {
                    *no = criar_no(*sobe, *no, maior);
                    maior = NULL; // Limpa o maior
                }
            }else{
                insere_arvore_binaria((&(*no)->info2.palavra_ingles), info.palavra_ingles->palavra_ingles, info.unidade);
            }
        }
        else { // Caso não seja folha, procura o local para inserir
            if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) < 0) {
                    maior = inserir_Elemento_ARV_2_3(&((*no)->esquerda), info, sobe, no);
                }else if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) == 0) {
                    insere_arvore_binaria(&((*no)->info1.palavra_ingles), info.palavra_ingles->palavra_ingles, info.unidade);
                    maior = NULL;  
                }else if ((*no)->quant_infos == 1 || strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) < 0) {
                    maior = inserir_Elemento_ARV_2_3(&((*no)->centro), info, sobe, no);
                }else if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) == 0) {
                    insere_arvore_binaria(&((*no)->info2.palavra_ingles), info.palavra_ingles->palavra_ingles, info.unidade);
                    maior = NULL;  
                }
                else {
                    maior = inserir_Elemento_ARV_2_3(&((*no)->direita), info, sobe, no);
                }

            // Se maior foi retornado, o nó pode precisar ser atualizado ou quebrado
            if (maior) {
                // Se o nó tem apenas 1 informação, adiciona a informação
                if ((*no)->quant_infos == 1) {
                    add_elementos(*no, *sobe, maior);
                    maior = NULL; // Limpa maior após adicionar
                } else { // Caso o nó tenha 2 informações
                    maior = quebra_No(no, *sobe, &sobe_sup, &maior);

                    if (pai) {
                        *no = criar_no(sobe_sup, *no, maior);
                        maior = NULL; // Limpa maior após criar o nó
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

void inserir_binaria_em_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade, char *palavra_ingles){
    Informacao info_2_3 = criar_info(palavra_portugues, palavra_ingles, unidade); 

    Informacao sobe;
    ARV2_3 *novo_no = inserir_Elemento_ARV_2_3(raiz, info_2_3, &sobe, NULL);
    if (novo_no)
        *raiz = criar_no(sobe, *raiz, novo_no);
    
}


void mostrar(ARV2_3 *raiz){
   
    if (raiz)
    {
    
        printf("\n+--- Nó Atual ---+\n");
        printf("| Quantidade de Informações: %d\n", raiz->quant_infos);

    
       
        printf("| Palavra 1 (PT): %s\n", raiz->info1.palavra_portugues);
        printf("| Unidade : %d\n", raiz->info1.unidade);
        printf("| Árvore Binária Associada à Palavra 1:\n");
        mostrar_arvore_binaria_completa(raiz->info1.palavra_ingles);

   
        if (raiz->quant_infos == 2)
        {
            printf("| Palavra 2 (PT): %s\n", raiz->info2.palavra_portugues);
            printf("\n| Unidade : %d\n", raiz->info2.unidade);
            printf("| Árvore Binária Associada à Palavra 2:\n");
            mostrar_arvore_binaria_completa(raiz->info2.palavra_ingles);
        }

        printf("+----------------+\n");

        mostrar(raiz->esquerda);
        mostrar(raiz->centro);

        if (raiz->quant_infos == 2)
            mostrar(raiz->direita);
    }
}

void imprimir_palavras_unidade(ARV2_3 *raiz, int unidade) {
    if (raiz == NULL) {
        return;
    }

    imprimir_palavras_unidade(raiz->esquerda, unidade);

    if (raiz->info1.unidade == unidade) {
        printf("Português: %s\n", raiz->info1.palavra_portugues);
        printf("Inglês: ");
        mostrar_arvore_binaria_completa(raiz->info1.palavra_ingles);
    }
    if (raiz->quant_infos == 2 && raiz->info2.unidade == unidade) {
        printf("Português: %s\n", raiz->info2.palavra_portugues);
        printf("Inglês:");
        mostrar_arvore_binaria_completa(raiz->info2.palavra_ingles);

    }

    imprimir_palavras_unidade(raiz->centro, unidade);
    imprimir_palavras_unidade(raiz->direita, unidade);
}

void imprimir_palavras_ingles(ARV2_3 *raiz, char *palavra_portugues) {
    if (raiz == NULL) {
        return;
    }

    imprimir_palavras_ingles(raiz->esquerda, palavra_portugues);

    if (strcmp(raiz->info1.palavra_portugues, palavra_portugues) == 0) {
        printf("Inglês: ");
        mostrar_arvore_binaria_completa(raiz->info1.palavra_ingles);
    }
    if (raiz->quant_infos == 2 && strcmp(raiz->info2.palavra_portugues, palavra_portugues) == 0) {
        printf("Inglês: ");
        mostrar_arvore_binaria_completa(raiz->info2.palavra_ingles);
    }

    imprimir_palavras_ingles(raiz->centro, palavra_portugues);
    imprimir_palavras_ingles(raiz->direita, palavra_portugues);
}

void no_2_3_adicionar_info(ARV2_3 *no, Informacao info, ARV2_3 *filho_maior)
{
    if((strcmp( info.palavra_portugues, no->info1.palavra_portugues) > 0 )){
        no->info2 = info;
        no->direita = filho_maior;
    }
    else{
        no->info2 = no->info1;
        no->direita = no->centro;
        no->centro = filho_maior;
        no->info1 = info;
    }
    no->quant_infos = 2;
}

int eh_folha(ARV2_3 *no){
    return no->esquerda == NULL;
}

int eh_info1(ARV2_3 no, char *info){
    return strcmp(info,no.info1.palavra_portugues )  == 0;
}

int eh_info2(ARV2_3 no, char *info) {
    return (no.quant_infos == 2 && strcmp(info, no.info2.palavra_portugues) == 0);
}


ARV2_3 *no_2_3_alocar(){
    ARV2_3 *no; 
    no = (ARV2_3 *)malloc(sizeof(ARV2_3)); 

    if (!no){
        
        printf("erro ao alocar nó da arvore");
        exit(EXIT_FAILURE);
    }
    
    return no; 

}

void troca_infos(Informacao *info1, Informacao *info2){
    Informacao aux = *info1; 
    *info1 = *info2; 
    *info2 = aux;
}

void no_2_3_desacolar(ARV2_3 **no){
    free(*no);
    *no = NULL;
}

ARV2_3 *no_2_3_juntar(ARV2_3 *filho1, Informacao info, ARV2_3 *maior, ARV2_3 **raiz)
{
    if(filho1->quant_infos == 2)
        filho1->quant_infos = 1;
        
    no_2_3_adicionar_info(filho1, info, maior);

    (*raiz)->quant_infos--;

    if((*raiz)->quant_infos == 0)
        no_2_3_desacolar(raiz);

    return filho1;
}

ARV2_3 *buscar_menor_filho(ARV2_3 *raiz, ARV2_3 **pai){ 
    ARV2_3 *filho;
    filho = raiz; 

    while (!eh_folha(filho)) {
        *pai = filho; 
        filho = filho->esquerda;
    }
    
    return filho; 
}

Informacao maior_info(ARV2_3 *raiz){ 
    return raiz->quant_infos == 2 ? raiz->info2 : raiz->info1;
}

ARV2_3 *buscar_maior_filho(ARV2_3 *raiz, ARV2_3 **pai, Informacao *maior_valor)
{
    ARV2_3 *filho;
    filho = raiz;

    while(!eh_folha(filho))
    {
        *pai = filho;
        if(filho->quant_infos == 1)
            filho = filho->centro;
        else
            filho = filho->direita;
    }

    if(filho != NULL)
        *maior_valor = maior_info(filho);

    return filho;
}

ARV2_3 *buscar_pai(ARV2_3 *raiz, char *info){
    ARV2_3 *pai; 
    pai = NULL; 

    if (raiz != NULL){
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info)){
            if (strcmp(info, raiz->info1.palavra_portugues)< 0){
                pai = buscar_pai(raiz->esquerda, info); 

            }else if (raiz->quant_infos == 1 || (strcmp(info, raiz->info2.palavra_portugues) < 0) ){
                pai = buscar_pai(raiz->centro, info);
            }else{
                pai = buscar_pai(raiz->direita, info);
            }
            
            if(pai == NULL){
                pai = raiz; 
            }
        }
        
    }

    return pai; 
}

ARV2_3 *buscar_maior_pai(ARV2_3 *raiz, char *info)
{
    ARV2_3 *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if((strcmp( info,raiz->info1.palavra_portugues) < 0))
                pai = buscar_maior_pai(raiz->esquerda, info);
            else if(raiz->quant_infos == 1 || (strcmp( info,raiz->info2.palavra_portugues)< 0))
                pai = buscar_maior_pai(raiz->centro, info);
            else
                pai = buscar_maior_pai(raiz->direita, info);

            if(pai == NULL && ((raiz->quant_infos == 1 && (strcmp(raiz->info1.palavra_portugues,info)> 0) ) || (raiz->quant_infos == 2 && (strcmp(raiz->info2.palavra_portugues,info))> 0)))
                pai = raiz;
        }
    }

    return pai;
}

ARV2_3 *buscar_menor_pai(ARV2_3 *raiz, char *info)
{
    ARV2_3 *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if((strcmp(info, raiz->info1.palavra_portugues) < 0))
                pai = buscar_menor_pai(raiz->esquerda, info);
            else if(raiz->quant_infos == 1 || (strcmp(info, raiz->info2.palavra_portugues)< 0))
                pai = buscar_menor_pai(raiz->centro, info);
            else
                pai = buscar_menor_pai(raiz->direita, info);

            if(pai == NULL && (strcmp(raiz->info1.palavra_portugues,info)< 0 ))
                pai = raiz;
        }
    }

    return pai;
}

ARV2_3 *buscar_menor_pai_2_info(ARV2_3 *raiz, char *info)
{
    ARV2_3 *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if((strcmp(info, raiz->info1.palavra_portugues) < 0))
                pai = buscar_menor_pai_2_info(raiz->esquerda, info);
            else if(raiz->quant_infos == 1 || (strcmp(info, raiz->info2.palavra_portugues)< 0))
                pai = buscar_menor_pai_2_info(raiz->centro, info);
            else
                pai = buscar_menor_pai_2_info(raiz->direita, info);

            if(pai == NULL && (strcmp(raiz->info1.palavra_portugues,info)< 0 ))
                pai = raiz;
        }
    }

    return pai;
}

int ondinha_1(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior){
    int removeu =  _1_remover_2_3(raiz, saindo.palavra_portugues, pai, origem,maior); 
    *entrada = saindo; 
    return removeu; 
}

int ondinha_esq2dir(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior){
    int removeu = _2_remover_2_3(raiz, saindo.palavra_portugues, pai, origem, maior); 
    *entrada = saindo; 
    return removeu; 
}

void arvore_2_3_desalocar(ARV2_3 **raiz)
{
    if(*raiz != NULL)
    {
        arvore_2_3_desalocar(&((*raiz)->esquerda));
        arvore_2_3_desalocar(&((*raiz)->centro));

        if((*raiz)->quant_infos == 2)
            arvore_2_3_desalocar(&((*raiz)->direita));

        no_2_3_desacolar(raiz);
    }
}

int _1_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior)
{
    int removeu = 0;

    if(*raiz != NULL){
        ARV2_3 *pai_aux;
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2){
            removeu = 1;
            if(eh_folha(*raiz))
            {
                if((*raiz)->quant_infos== 2)
                {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2 ;

                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if (pai == NULL)
                        no_2_3_desacolar(raiz);
                    else{
                        if(*raiz == pai->esquerda || (pai->quant_infos == 2 && *raiz == pai->centro)){
                            pai_aux = buscar_pai(*origem, pai->info1.palavra_portugues);
                            
                            if(*raiz == pai->esquerda)
                                removeu = ondinha_1(pai->info1, &((*raiz)->info1), pai_aux, origem, &pai, maior);
                            else 
                                removeu = ondinha_1(pai->info2, &((*raiz)->info1), pai_aux, origem, &pai, maior);
                        }else{// filho do centro(com pai de 1 info)ou da direita 

                            Informacao info_pai;
                            pai_aux = buscar_maior_pai(*origem,(*raiz)->info1.palavra_portugues);

                            ARV2_3 *menor_pai; 
                            menor_pai = buscar_menor_pai(*origem, (*raiz)->info1.palavra_portugues);

                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                *maior = pai;
                                (*raiz)->quant_infos = 0;
                                removeu = -1;
                            }
                            else{
                                if((strcmp(pai_aux->info1.palavra_portugues,(*raiz)->info1.palavra_portugues) > 0))
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;

                                ARV2_3 *avo;
                                avo = buscar_pai(*origem, info_pai.palavra_portugues);
                                removeu = ondinha_1(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior);
                            }
                        }
                }
            }
        }else{
                ARV2_3 *filho, *filho2;
                filho2 = NULL;
                Informacao info_filho;
                pai_aux = *raiz;

                if(info2)
                {
                    ARV2_3 *pai_aux2;
                    pai_aux2 = *raiz;

                    filho = buscar_menor_filho((*raiz)->direita, &pai_aux);

                    if(filho->quant_infos == 1)
                        filho2 = buscar_maior_filho((*raiz)->centro, &pai_aux2, &info_filho);
                    
                    if(filho2 != NULL && filho2->quant_infos == 2)
                    {
                        (*raiz)->info2 = filho2->info2;
                        filho2->quant_infos = 1;
                    }
                    else
                        removeu = ondinha_1(filho->info1, &((*raiz)->info2), pai_aux, origem, &filho, maior);
                }
                else if(info1)
                {
                    filho2 = buscar_maior_filho((*raiz)->esquerda, &pai_aux, &info_filho);

                    if(filho2->quant_infos == 2)
                    {
                        (*raiz)->info1 = info_filho;
                        filho2->quant_infos = 1;
                    }
                    else
                    {
                        filho = buscar_menor_filho((*raiz)->centro, &pai_aux);
                        removeu = ondinha_1(filho->info1, &((*raiz)->info1), pai_aux, origem, &filho, maior);
                    }
                }
            }
        }
        else{
            if((strcmp(info,(*raiz)->info1.palavra_portugues)< 0))
                removeu = _1_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if((*raiz)->quant_infos == 1 || (strcmp(info,(*raiz)->info2.palavra_portugues)< 0) )
                removeu = _1_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _1_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
           }
    
    return removeu;
  }

}

int _2_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior)
{
    int removeu = 0;

    if(*raiz != NULL)
    {
        ARV2_3 *pai_aux;
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(eh_folha(*raiz))
            {
                if((*raiz)->quant_infos == 2)
                {
                    if(info1)
                        troca_infos(&((*raiz)->info1), &((*raiz)->info2));

                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if(pai != NULL)
                    {
                        
                        if(*raiz == pai->centro || (pai->quant_infos == 2 && *raiz == pai->direita))
                        {
                            pai_aux = buscar_pai(*origem, pai->info1.palavra_portugues);
                            
                            if(*raiz == pai->centro)
                                removeu =ondinha_esq2dir(pai->info1, &((*raiz)->info1), pai_aux, origem, &pai, maior);
                            else 
                                removeu = ondinha_esq2dir(pai->info2, &((*raiz)->info1), pai_aux, origem, &pai, maior);
                        }
                        else
                        {
                            Informacao info_pai;
                            pai_aux = buscar_menor_pai(*origem,(*raiz)->info1.palavra_portugues);
                            if(pai_aux != NULL && pai->quant_infos == 1)
                            {
                                if(pai_aux->quant_infos == 2 && (strcmp(pai_aux->info2.palavra_portugues,(*raiz)->info1.palavra_portugues) < 0))
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                ARV2_3 *avo;
                                avo = buscar_pai(*origem, info_pai.palavra_portugues);
                                removeu = ondinha_esq2dir(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior);
                            }
                            else
                            {
                                // Revisar
                                ondinha_1(pai->info1, &((*raiz)->info1), pai_aux, origem, raiz, maior);
                            }
                        }
                    }
                    else
                        no_2_3_desacolar(raiz);
                }
            }
            else
            {
                ARV2_3 *filho;
                Informacao info_filho;
                pai_aux = *raiz;

                if(info2)
                {
                    filho = buscar_menor_filho((*raiz)->direita, &pai_aux);

                    // TODO revisar
                    if(filho->quant_infos == 2)
                    {
                        (*raiz)->info2 = filho->info1;
                        filho->info1 = filho->info2;
                        filho->quant_infos = 1;
                    }
                    else
                    {
                        filho = buscar_maior_filho((*raiz)->centro, &pai_aux, &info_filho);
                        removeu = ondinha_esq2dir(info_filho, &((*raiz)->info2), pai_aux, origem, &filho, maior);
                    }
                }
                else if(info1)
                {
                    filho = buscar_menor_filho((*raiz)->centro, &pai_aux);

                    if(filho->quant_infos == 2)
                    {
                        (*raiz)->info1 = filho->info1;
                        filho->info1 = filho->info2;
                        filho->quant_infos = 1;
                    }
                    else
                    {
                        filho = buscar_maior_filho((*raiz)->esquerda, &pai_aux, &info_filho);
                        removeu = ondinha_esq2dir(info_filho, &((*raiz)->info1), pai_aux, origem, &filho, maior);
                    }
                }
            }
        }
        else
        {
            if(info < (*raiz)->info1.palavra_portugues)
                removeu = _1_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if((*raiz)->quant_infos == 1 || info < (*raiz)->info2.palavra_portugues)
                removeu = _1_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _1_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }

    // TODO revisar
    if(*origem == NULL)
        *origem = *maior;

    return removeu;
}

int arvore_2_3_remover(ARV2_3 **raiz, char *info)
{   
    ARV2_3 *maior, *posicao_juncao;
    maior = NULL;
    int removeu = _1_remover_2_3(raiz, info, NULL, raiz, &posicao_juncao);

    if(removeu == -1)
    {
        Informacao valor_juncao = maior_info(posicao_juncao);
        removeu = arvore_2_3_rebalancear(raiz, valor_juncao.palavra_portugues, &maior);
        
        if(removeu == -1)
        {
            ARV2_3 *pai, *posicao_juncao2;
            Informacao *entrada;
            pai = buscar_pai(*raiz, valor_juncao.palavra_portugues);

            if(eh_info1(*posicao_juncao, valor_juncao.palavra_portugues))
                entrada = &(posicao_juncao->centro->info1);
            else
                entrada = &(posicao_juncao->direita->info1);

            //removeu = ondinha_esq2dir(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2);
        }
            //removeu = _2_remover_2_3(raiz, posicao_juncao->info1.palavra_portugues, NULL, raiz, &posicao_juncao);

        if(*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

int arvore_2_3_rebalancear(ARV2_3 **raiz, char  *info, ARV2_3 **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!eh_folha(*raiz))
        {
            //if((*raiz)->quant_infos == 2 && !eh_info1(**raiz, info) && !eh_info2(**raiz, info))
            if((*raiz)->quant_infos == 2 && (*raiz)->centro->quant_infos == 2)
                balanceou = -1;
            else
            {
                if((strcmp (info, (*raiz)->info1.palavra_portugues) < 0))
                    balanceou = arvore_2_3_rebalancear(&((*raiz)->esquerda), info, maior);
                else if((*raiz)->quant_infos == 1 || info < (*raiz)->info2.palavra_portugues)
                    balanceou = arvore_2_3_rebalancear(&((*raiz)->centro), info, maior);
                else
                    balanceou = arvore_2_3_rebalancear(&((*raiz)->direita), info, maior);
                
                if((*raiz)->quant_infos == 1)
                    balanceou = balanceamento(raiz, (*raiz)->esquerda, &((*raiz)->centro), (*raiz)->info1, maior);
                else if((*raiz)->quant_infos == 2)
                    balanceou = balanceamento(raiz, (*raiz)->centro, &((*raiz)->direita), (*raiz)->info2, maior);
            }
        }
    }

    return balanceou;
}

static int balanceamento(ARV2_3 **raiz, ARV2_3 *filho1, ARV2_3 **filho2, Informacao info, ARV2_3 **maior)
{
    int balanceou = 0;
    if(*filho2 == NULL || (*filho2)->quant_infos == 0)
    {
        if(*filho2 != NULL)
            no_2_3_desacolar(filho2);

        *maior = no_2_3_juntar(filho1, info, *maior, raiz);
        balanceou = 1;
    }
    return balanceou;
}