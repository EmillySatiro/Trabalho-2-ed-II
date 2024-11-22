#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV2_3.h"
#include "ARV_BINARIA.h"



ARV2_3 *criar_no(Informacao info, ARV2_3 *filho_esquerda, ARV2_3*filho_centro){
    ARV2_3 *no = (ARV2_3 *)malloc(sizeof(ARV2_3)); 

    if (no != NULL){
        no->info1 = info;
        no->esquerda = filho_esquerda;
        no->centro = filho_centro; 
        no->quant_infos = 1;
    }else{
        printf("Não foi possivel criar no \n "); 

    }
    return no;
}

ARV2_3 *quebra_No(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **filho){
    ARV2_3 *maior_info; 

    // caso 1 : O novo elemento (info) é maior que minha info2. 
    if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues)> 0){
        *sobe = (*no)->info2;// o info dois sobe pq ele é o do meio 

        maior_info = criar_no(info,(*no)->direita, filho ? *filho: NULL); 
        // criando um no para o maior que no caso é meu novo elemento( esse filho ? * filho: null é se o filho não for nulo ele executa e manda(*filho)  para o criar e se não for manda null)
        
    }else if(strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) > 0){
        *sobe = info; 

        if (filho){

            maior_info = criar_no((*no)->info2, *filho, (*no)->direita);
        }else{
            maior_info = criar_no((*no)->info2, NULL, (*no)->direita);
        }
        
    }else{
        *sobe = (*no)->info1; 

        maior_info = criar_no((*no)->info2, (*no)->centro, (*no)->centro);
        (*no)->info1 = info; 
        (*no)->centro = (filho ? *filho : NULL); 
    }

    (*no)->quant_infos = 1; 
    
    return maior_info; 

}

int eh_folha(ARV2_3 *no){
    return (no->esquerda == NULL);
}

void add_elementos(ARV2_3 *no, Informacao Info, ARV2_3 *filho){

    if(strcmp(Info.palavra_portugues, no->info1.palavra_portugues)> 0){
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
ARV2_3 *inserir_Elemento_ARV_2_3(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **pai){
    Informacao sobe_sup; 
    ARV2_3 *maior = NULL; 

    if (*no == NULL){
        *no = criar_no(info, NULL, NULL); 
    }else{

        if(eh_folha(*no)){
            if((*no)->quant_infos == 1){
                add_elementos(*no, info,NULL);
            }else{
                maior = quebra_No(no, info, sobe, NULL);
                if (pai && !(*pai)){
                    *no = criar_no(*sobe, *no, maior);
                    maior = NULL; 
                }
                
            }
        }else{
            if(strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues)< 0 ){
                maior = inserir_Elemento_ARV_2_3(&((*no)->esquerda), info, sobe, no); 

            }else if(((*no)->quant_infos == 1)|| (strcmp((info.palavra_portugues), (*no)->info2.palavra_portugues))< 0){
                maior = inserir_Elemento_ARV_2_3(&((*no)->centro), info, sobe, no); 

            }else{
                maior = maior = inserir_Elemento_ARV_2_3(&((*no)->direita), info, sobe, no);
            }

            if(maior){
                if((*no)->quant_infos == 1){
                    add_elementos(*no,*sobe,maior);
                    maior = NULL;
                }else{
                    maior = quebra_No(no, *sobe, &sobe_sup, &maior); 
                    if(pai && !(*pai)){
                        *no = criar_no(sobe_sup, *no, maior);
                        maior= NULL; 
                    }
                }
            }
        }
       
    }
    return maior; 
}

void insere(ARV2_3 **raiz, Informacao info){
    Informacao sobe; 
    ARV2_3 *novo_no = inserir_Elemento_ARV_2_3(raiz, info, &sobe, NULL); 
    if (novo_no){
        *raiz = criar_no(sobe, *raiz, novo_no); 

    }
    
}

void mostrar(ARV2_3 *raiz){
    if(raiz){ 
        mostrar(raiz->esquerda); 
        printf("%s\n", raiz->info1.palavra_portugues); 
        mostrar(raiz->centro); 

        if (raiz->quant_infos == 2){
            printf("%s\n", raiz->info2.palavra_portugues);
            mostrar(raiz->direita); 
        }

    }
}

