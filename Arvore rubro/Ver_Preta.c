#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Ver_preta.h"

// alocar nó 
Rubronegra *alocar_no(Informacao_VP info){
    Rubronegra *no = (Rubronegra *)malloc(sizeof(Rubronegra)); 
    if (no != NULL) {
       strcpy(no->info->palavra_portugues, info.palavra_portugues);
       no->info->unidade=info.unidade;
       no->cor = VERMELHO; 
       no->direita = NULL; 
       no->esquerda = NULL; 
    }else{
        printf("erro ao alocar memoria !!\n");

    }
    return no;
    
}

int Qual_a_cor(Rubronegra *no){
    return (no == NULL) ? PRETO : no->cor;
}

void troca_cor(Rubronegra *no){
    if(no != NULL){
        no->cor = !no->cor; // inverte a cor 
        if (no->esquerda){
            no->esquerda->cor= !no->esquerda->cor; }

        if (no->direita){
            no->direita->cor= !no->direita->cor; }
        
    }
}
void girar_esquerda(Rubronegra **raiz){
    if(raiz && *raiz && (*raiz)->direita){
        Rubronegra *novo_no = (*raiz)->direita; 
        
        // fiz a rotação aqui lek 
        (*raiz)->direita = novo_no->esquerda; 
        novo_no->esquerda = *raiz;
        
        // ajustar cor 
        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO; 

        //atualiza a raiz
        *raiz = novo_no;

    }
}
void move_esquerda(Rubronegra **no){
    if (no && *no){
        troca_cor(*no); 
        Rubronegra *filho_direita = (*no)->direita; 

        if (filho_direita && Qual_a_cor(filho_direita->esquerda) == VERMELHO){
            girar_direita(&(filho_direita));
            girar_esquerda(no); 
            troca_cor(*no);
        }
    }
}

void girar_direita(Rubronegra **raiz){
    if(raiz && *raiz && (*raiz)->esquerda){
        Rubronegra *novo_no = (*raiz)->esquerda; 

        // roda
        (*raiz)->esquerda = novo_no->direita; 
        novo_no->direita = *raiz;

        // troca cor
        novo_no->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO; 

        //att raiz
        *raiz = novo_no; 
        
    }
}

void mover_direita(Rubronegra **no){
    if(no && *no){
        troca_cor(*no); 
        Rubronegra *filho_esquerda = (*no)->esquerda; 

        if (filho_esquerda && Qual_a_cor(filho_esquerda->esquerda)== VERMELHO){
            girar_direita(no); 
            troca_cor(*no);
        
        }
    }
}


