#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Rubro_negra.h"

// alocar nó 
Rubronegra *alocar_no(Informacao_VP info){
    Rubronegra *no = (Rubronegra *)malloc(sizeof(Rubronegra)); 
    if (no != NULL) {
        no->info = (Informacao_VP *)malloc(sizeof(Informacao_VP));
            if (no->info != NULL){
                strcpy(no->info->palavra_portugues, info.palavra_portugues);
                no->info->unidade=info.unidade;
                no->info->palavras_ingles = NULL;
                no->cor = VERMELHO; 
                no->direita = NULL; 
                no->esquerda = NULL;
            }else{
                printf("Erro ao alocar memória para 'info'!\n");
                
            }
        
    }else{
        printf("erro ao alocar memoria para nó !!\n");
        exit(1);

    }
    return no;
    
}

Rubronegra *inserir_rubro(Rubronegra **raiz, Informacao_VP info){
    Rubronegra *inserido = NULL;
    if (*raiz == NULL){
       *raiz = alocar_no(info);
       inserido = *raiz;
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
    }
     
    if (inserido != NULL){
       conferindo_regras(raiz);
    }
    
    return *raiz ; 
}

Rubronegra *conferindo_raiz(Rubronegra *raiz, Informacao_VP info){
    raiz = inserir_rubro(&raiz, info); 
    if(raiz != NULL){
       raiz->cor = PRETO;
    } 
    return raiz;
}

void conferindo_regras(Rubronegra **raiz){
    if(*raiz != NULL){

        // balencear se o filho da  e as esquerda preto direita for vermelho 
        if( Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->direita) == VERMELHO){
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
   
     
}

// rpz custoso melhora emilly do futuro 
void liberar_rubronegra_binaria(Informacao_VP *info){

   if (info){
       if (info->palavras_ingles){
        //  liberar_binaria(&(*raiz)->info->palavras_ingles); 
        info->palavras_ingles = NULL;
       }
       free(info);
   } 
    
}

void liberar_rubronegra( Rubronegra **raiz){
    if(*raiz){
        liberar_rubronegra(&(*raiz)->esquerda); 
        liberar_rubronegra(&(*raiz)->direita); 
        //liberar_rubronegra_binaria((*raiz)->info);
    }
    free(*raiz);
    *raiz = NULL; 
}

int Qual_a_cor(Rubronegra *no) {
    if (no == NULL) {
        return PRETO; 
    }
    return no->cor;  
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
        troca_cor(no); 
        if ((*no)->direita->esquerda && Qual_a_cor((*no)->direita->esquerda) == VERMELHO){
            girar_direita(&(*no)->direita);
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
        troca_cor(no); 
        if ((*no)->esquerda->esquerda && Qual_a_cor((*no)->esquerda->esquerda)== VERMELHO){
            girar_direita(no); 
            troca_cor(no);
        
        }
    }
}
Rubronegra *procurar_menor(Rubronegra **raiz){
    Rubronegra *no1 = *raiz;
    Rubronegra *no2 = (*raiz)->esquerda;
    if (*raiz){
        while (no2 !=NULL){
            no1 = no2; 
            no2 = no2->esquerda;
        }
        
        
    }
    printf("%s\n",no1->info->palavra_portugues);
    return no1;
}
void remover_elemento_min(Rubronegra **raiz){
    if(*raiz != NULL){
        if ((*raiz)->esquerda == NULL){
            free(*raiz);
            *raiz = NULL;
        }else{
            if (Qual_a_cor((*raiz)->esquerda)  == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO){
                move_esquerda(raiz);
            }
            
            remover_elemento_min(&((*raiz)->esquerda));

        }
        
        if(*raiz)
            conferindo_regras(raiz);
              
    }
   

}

int remover_no(Rubronegra **raiz, char *palavra){
    int encontrado = 0; // não encontrado 

    if(*raiz){
        if(strcmp(palavra, (*raiz)->info->palavra_portugues)< 0){
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == PRETO && Qual_a_cor((*raiz)->esquerda->esquerda) == PRETO){
                move_esquerda(raiz);
            }

            encontrado = remover_no(&((*raiz)->esquerda), palavra);
            
        }else {
            if ((*raiz)->esquerda && Qual_a_cor((*raiz)->esquerda) == VERMELHO){
                girar_direita(raiz);
            }
            
            if (strcmp(palavra,(*raiz)->info->palavra_portugues) == 0 && (*raiz)->direita == NULL){
                free(*raiz);
                *raiz = NULL;
            }else{
                if((*raiz)->direita && Qual_a_cor((*raiz)->direita) == PRETO && Qual_a_cor((*raiz)->direita->esquerda) == PRETO){
                    mover_direita(raiz);
                }

                if (strcmp(palavra,(*raiz)->info->palavra_portugues) == 0){
                    encontrado = 1;
                    Rubronegra *min = procurar_menor(&(*raiz)->direita); // aqui 
                    (*raiz)->info = min->info;
                    remover_elemento_min(&((*raiz)->direita)); 
                }else{
                encontrado = remover_no(&((*raiz)->direita), palavra);
               }
            }
            
           
                
        }

        if (*raiz){
            conferindo_regras(raiz);
        }
    }

    return encontrado;
}

int remover_na_arvore(Rubronegra **raiz, char *palavra){
    int resultado = remover_no(raiz,palavra);
    if (*raiz){
        (*raiz)->cor = PRETO;
    }
    return resultado;
}
void mostrar_rubronegra(Rubronegra *raiz){
    if(raiz){
    
    // mostrar a arvore binaria dela chama sua 
    mostrar_rubronegra(raiz->esquerda);
    printf("Palavra: %s, Cor: %s\n", raiz->info->palavra_portugues, raiz->cor == PRETO ? "PRETO" : "VERMELHO");
    mostrar_rubronegra(raiz->direita);
    }
}

