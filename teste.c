#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char situacao; // 'L' para Livre ou 'O' para Ocupado
    int bloco_inicial;
    int bloco_final;
    unsigned long endereco_inicial;
    unsigned long endereco_final;
    struct No *esquerda, *meio, *direita;
} No;

// Função para criar um novo nó
No* criar_no(char situacao, int bloco_inicial, int bloco_final, unsigned long endereco_inicial, unsigned long endereco_final) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->situacao = situacao;
    novo_no->bloco_inicial = bloco_inicial;
    novo_no->bloco_final = bloco_final;
    novo_no->endereco_inicial = endereco_inicial;
    novo_no->endereco_final = endereco_final;
    novo_no->esquerda = novo_no->meio = novo_no->direita = NULL;
    return novo_no;
}

// Função para inserir um nó na árvore
No* inserir_no(No* raiz, No* novo) {
    if (!raiz) return novo;

    // Verifica se deve ir para a esquerda, meio ou direita (simplificação da lógica 2-3)
    if (novo->bloco_final < raiz->bloco_inicial) {
        raiz->esquerda = inserir_no(raiz->esquerda, novo);
    } else if (novo->bloco_inicial > raiz->bloco_final) {
        raiz->direita = inserir_no(raiz->direita, novo);
    } else {
        raiz->meio = inserir_no(raiz->meio, novo);
    }
    return raiz;
}

// Função para exibir a árvore (para debug)
void exibir_arvore(No* raiz) {
    if (!raiz) return;
    printf("Nó [%c] Blocos: %d-%d, Endereços: %lu-%lu\n",
           raiz->situacao, raiz->bloco_inicial, raiz->bloco_final, raiz->endereco_inicial, raiz->endereco_final);
    exibir_arvore(raiz->esquerda);
    exibir_arvore(raiz->meio);
    exibir_arvore(raiz->direita);
}

// Função para alocar memória (Parte b)
No* alocar_memoria(No* raiz, int qtd_blocos) {
    if (!raiz) return NULL;

    // Verifica se o nó atual é Livre e possui blocos suficientes
    if (raiz->situacao == 'L' && (raiz->bloco_final - raiz->bloco_inicial + 1) >= qtd_blocos) {
        int novo_fim = raiz->bloco_inicial + qtd_blocos - 1;

        // Divide o nó se houver blocos restantes
        if (novo_fim < raiz->bloco_final) {
            No* novo_no = criar_no('L', novo_fim + 1, raiz->bloco_final, raiz->endereco_inicial + (novo_fim - raiz->bloco_inicial + 1) * 1024 * 1024, raiz->endereco_final);
            raiz->bloco_final = novo_fim;
            raiz->endereco_final = novo_no->endereco_inicial - 1;
            raiz->direita = inserir_no(raiz->direita, novo_no);
        }

        // Marca o nó como Ocupado
        raiz->situacao = 'O';
        return raiz;
    }

    // Continua buscando nos filhos
    No* encontrado = alocar_memoria(raiz->esquerda, qtd_blocos);
    if (encontrado) return encontrado;

    encontrado = alocar_memoria(raiz->meio, qtd_blocos);
    if (encontrado) return encontrado;

    return alocar_memoria(raiz->direita, qtd_blocos);
}

// Função para liberar memória (Parte c)
void liberar_memoria(No* raiz, int bloco_inicial, int bloco_final) {
    if (!raiz) return;

    // Verifica se o bloco a ser liberado está neste nó
    if (raiz->bloco_inicial <= bloco_inicial && raiz->bloco_final >= bloco_final && raiz->situacao == 'O') {
        raiz->situacao = 'L';
        // Realiza a concatenação de nós adjacentes, se necessário
        if (raiz->esquerda && raiz->esquerda->situacao == 'L') {
            raiz->bloco_inicial = raiz->esquerda->bloco_inicial;
            raiz->endereco_inicial = raiz->esquerda->endereco_inicial;
            free(raiz->esquerda);
            raiz->esquerda = NULL;
        }
        if (raiz->direita && raiz->direita->situacao == 'L') {
            raiz->bloco_final = raiz->direita->bloco_final;
            raiz->endereco_final = raiz->direita->endereco_final;
            free(raiz->direita);
            raiz->direita = NULL;
        }
        return;
    }

    // Continua buscando nos filhos
    liberar_memoria(raiz->esquerda, bloco_inicial, bloco_final);
    liberar_memoria(raiz->meio, bloco_inicial, bloco_final);
    liberar_memoria(raiz->direita, bloco_inicial, bloco_final);
}

int main() {
    No* raiz = NULL;
    unsigned long endereco_inicial, endereco_final;
    char situacao;
    int bloco_inicial = 0, bloco_final;

    printf("Cadastro de memória:\n");
    while (1) {
        printf("Situação do bloco (L/O): ");
        scanf(" %c", &situacao);
        if (bloco_inicial == 0) {
            printf("Endereço inicial: ");
            scanf("%lu", &endereco_inicial);
        }
        printf("Endereço final: ");
        scanf("%lu", &endereco_final);

        bloco_final = bloco_inicial + (endereco_final - (bloco_inicial ? endereco_inicial : 0)) / (1024 * 1024);
        No* novo = criar_no(situacao, bloco_inicial, bloco_final, endereco_inicial, endereco_final);
        raiz = inserir_no(raiz, novo);

        bloco_inicial = bloco_final + 1;
        if (endereco_final == (unsigned long)-1) break; // Indica o final da memória
    }

    printf("\nÁrvore de memória:\n");
    exibir_arvore(raiz);

    // Teste de alocação
    printf("\nAlocando memória:\n");
    int qtd_blocos;
    printf("Quantidade de blocos a alocar: ");
    scanf("%d", &qtd_blocos);
    No* alocado = alocar_memoria(raiz, qtd_blocos);
    if (alocado) {
        printf("Bloco alocado: %d-%d\n", alocado->bloco_inicial, alocado->bloco_final);
    } else {
        printf("Não foi possível alocar.\n");
    }

    printf("\nÁrvore de memória após alocação:\n");
    exibir_arvore(raiz);

    // Teste de liberação
    printf("\nLiberando memória:\n");
    int bloco_inicio, bloco_fim;
    printf("Bloco inicial e final a liberar: ");
    scanf("%d %d", &bloco_inicio, &bloco_fim);
    liberar_memoria(raiz, bloco_inicio, bloco_fim);

    printf("\nÁrvore de memória após liberação:\n");
    exibir_arvore(raiz);

    return 0;
}
