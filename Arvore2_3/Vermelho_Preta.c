#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Vermelho_preta.h"

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

void liberar_rubronegra_binaria(Rubronegra **raiz){
   //  liberar_binaria(&(*raiz)->info->palavras_ingles); 
   if (*raiz){
    if ((*raiz)->info->palavra_portugues){
        free((*raiz)->info->palavra_portugues);
        
    }
    free(*raiz);
    *raiz = NULL;
   } 
    
}

void liberar_rubronegra( Rubronegra **raiz){
    if(*raiz){
        liberar_rubronegra(&(*raiz)->esquerda); 
        liberar_rubronegra(&(*raiz)->direita); 
        liberar_rubronegra_binaria(raiz);

    }
}

int Qual_a_cor(Rubronegra *no){
    return (no == NULL) ? PRETO : no->cor;
}

void troca_cor(Rubronegra **no){
    if(no != NULL){
        (*no)->cor = !(*no)->cor; // inverte a cor 
        if ((*no)->esquerda){
            (*no)->esquerda->cor= !(*no)->esquerda->cor; }

        if ((*no)->direita){
            (*no)->direita->cor= !(*no)->direita->cor; }
        
    }
}
void girar_esquerda(Rubronegra **raiz){
    if(*raiz != NULL && (*raiz)->direita != NULL){
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
    if (*no != NULL){
        troca_cor(*no); 
        Rubronegra *filho_direita = (*no)->direita; 

        if (filho_direita && Qual_a_cor(filho_direita->esquerda) == VERMELHO){
            girar_direita(&(filho_direita));
            girar_esquerda(no); 
            troca_cor(no);
        }
    }
}

void girar_direita(Rubronegra **raiz){
    if(*raiz != NULL && (*raiz)->esquerda != NULL){
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
    if(*no !=NULL){
        troca_cor(*no); 
        Rubronegra *filho_esquerda = (*no)->esquerda; 

        if (filho_esquerda && Qual_a_cor(filho_esquerda->esquerda)== VERMELHO){
            girar_direita(no); 
            troca_cor(no);
        
        }
    }
}

Rubronegra *procurar_menor(Rubronegra *raiz){
    Rubronegra *menor = raiz;
    if(raiz != NULL && raiz->esquerda != NULL ){
        menor = procurar_menor(raiz->esquerda);
    }
    return menor;
}

void conferindo_regras(Rubronegra **raiz){
    // balencear se o filho da  e as esquerda preto direita for vermelho 
    if( Qual_a_cor((*raiz)->esquerda) == PRETO && ((*raiz)->direita)== VERMELHO){
        girar_esquerda(raiz);
    }

    // balancear se o filho á esquerda e o neto são vermelhos 
    if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->esquerda->esquerda)==VERMELHO){
        girar_direita(raiz);
    }
    
    // ver se os dois filhos são vermelhos
    if (Qual_a_cor((*raiz)->esquerda) == VERMELHO && Qual_a_cor((*raiz)->direita)== VERMELHO){
        troca_cor(raiz);
    }
     
}

void remover_elemento_min(Rubronegra **raiz){
    if(*raiz != NULL){
        // se a esquerda é nula  achamos o minimo
        if ((*raiz)->esquerda == NULL){
            Rubronegra *aux = *raiz; 
            *raiz  = (*raiz)->direita; //substitui o no min pelo a direita
            free(aux);
            conferindo_regras(raiz);
        }else{
            // se a esquerda não é nula então chama ela dnv
            if(Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO){
                move_esquerda(raiz);

            }
            remover_elemento_min(&((*raiz)->esquerda));

            conferindo_regras(raiz);
        }
        
    }
}

Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP info){
    Rubronegra *inserido = NULL; 

    if (*raiz == NULL){
        Rubronegra *novo_elemento = alocar_no(info); 
        *raiz = novo_elemento;// atualiza a raiz
        inserido = novo_elemento; // atribui o nó inserido
    }else{
        if (strcmp(info.palavra_portugues, (*raiz)->info->palavra_portugues)< 0){
            // esquerda 
            inserido = inserir_rubro(&((*raiz)->esquerda), info);
        }else if (strcmp(info.palavra_portugues, (*raiz)->info->palavra_portugues)> 0){
            // direita
            inserido = inserir_rubro(&((*raiz)->direita), info);
        }else{
            // elemento ja existe 
            inserido = NULL; 
        }
        conferindo_regras(raiz); 
        
    }
    return inserido; 
}

Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP info){
    raiz = inserir_rubro(&raiz, info); 
    if(raiz != NULL){
       raiz->cor = PRETO;
    } 
    return raiz;
}

void mostrar_rubronegra(Rubronegra *raiz){
    if(raiz){
        mostrar_rubronegra(raiz->esquerda); 
        
        if(raiz->cor == VERMELHO){
            printf("Cor: Vermelho\n");
        }else{
            printf("cor : Preto\n"); 
        }

        printf("%s\n", raiz->info->palavra_portugues); 
        // chamar aqui a listagem da binaria 

        mostrar_rubronegra(raiz->direita);
    }
}