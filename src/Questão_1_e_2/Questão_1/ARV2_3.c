#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARV2_3.h"
#include "../Binaria/ARV_BINARIA.h"

/**
 * @brief Cria um novo nó para a árvore 2-3.
 *
 * Esta função aloca memória para um novo nó da árvore 2-3 e inicializa
 * seus campos com as informações fornecidas.
 *
 * @param info Informação a ser armazenada no nó.
 * @param filho_esquerda Ponteiro para o filho à esquerda do nó.
 * @param filho_centro Ponteiro para o filho do centro do nó.
 * @return Ponteiro para o novo nó criado, ou NULL se a alocação falhar.
 */
ARV2_3 *criar_no(Informacao info, ARV2_3 *filho_esquerda, ARV2_3 *filho_centro)
{
    ARV2_3 *no = (ARV2_3 *)malloc(sizeof(ARV2_3));

    if (no != NULL)
    {
        no->info1 = info;
        no->esquerda = filho_esquerda;
        no->centro = filho_centro;
        no->quant_infos = 1;
        no->direita = NULL;
    }
    else
    {
        printf("Não foi possivel criar no \n ");
    }
    return no;
}

/**
 * @brief Função para quebrar um nó em uma árvore 2-3.
 *
 * Esta função quebra um nó da árvore 2-3 em dois nós, ajustando as informações
 * e os ponteiros de acordo com a nova informação inserida.
 *
 * @param no Ponteiro duplo para o nó a ser quebrado.
 * @param info Informação a ser inserida na árvore.
 * @param sobe Ponteiro para a informação que irá subir para o nó pai.
 * @param filho Ponteiro para o filho que será ajustado na quebra do nó.
 * @return ARV2_3* Retorna o novo nó criado com a maior informação.
 *
 * @note A função considera três casos:
 *       1. A nova informação é maior que a info2 do nó.
 *       2. A nova informação está entre info1 e info2 do nó.
 *       3. A nova informação é menor que a info1 do nó.
 */
ARV2_3 *quebra_No(ARV2_3 **no, Informacao info, Informacao *sobe, ARV2_3 **filho)
{
    ARV2_3 *maior_info;

    // Caso 1: O novo elemento (info) é maior que info2.
    if (strcmp(info.palavra_portugues, (*no)->info2.palavra_portugues) > 0)
    {
        *sobe = (*no)->info2; // info2 sobe, pois é o do meio

        // Cria um novo nó com o maior valor e o ponteiro do filho.
        maior_info = criar_no(info, (*no)->direita, filho ? *filho : NULL);
        
        // Atualiza o nó atual para manter apenas info1
        (*no)->quant_infos = 1;
        (*no)->direita = NULL;
    }
    // Caso 2: O novo elemento está entre info1 e info2.
    else if (strcmp(info.palavra_portugues, (*no)->info1.palavra_portugues) > 0)
    {
        *sobe = info; // O novo elemento sobe

        // Cria um novo nó com info2 e o ponteiro do filho direito.
        maior_info = criar_no((*no)->info2, (*no)->centro, (*no)->direita);
        
        // Atualiza o nó atual para manter info1
        (*no)->quant_infos = 1;
        (*no)->centro = (*no)->direita;
        (*no)->direita = NULL;
    }
    // Caso 3: O novo elemento é menor que info1.
    else
    {
        *sobe = (*no)->info1; // info1 sobe

        // Cria um novo nó com info2 e os ponteiros de centro e direita
        maior_info = criar_no((*no)->info2, (*no)->centro, (*no)->direita);

        // Atualiza o nó atual para manter apenas o novo valor (info)
        (*no)->quant_infos = 1;
        (*no)->info1 = info;
        (*no)->centro = (filho ? *filho : NULL);
        (*no)->direita = NULL;
    }

    return maior_info;
}

/**
 * @brief Adiciona um elemento a um nó da árvore 2-3.
 *
 * Esta função adiciona um novo elemento (Info) a um nó (no) da árvore 2-3,
 * ajustando os ponteiros dos filhos conforme necessário.
 *
 * @param no Ponteiro para o nó da árvore 2-3 onde o elemento será adicionado.
 * @param Info Estrutura contendo a informação a ser adicionada ao nó.
 * @param filho Ponteiro para o filho que será ajustado após a adição do elemento.
 */
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

/**
 * @brief Insere um elemento na árvore 2-3.
 *
 * Esta função insere um novo elemento na árvore 2-3, mantendo suas propriedades.
 * Se o nó for uma folha, a função adiciona a nova informação diretamente ou quebra o nó se necessário.
 * Se o nó não for uma folha, a função procura o local apropriado para inserir a nova informação.
 *
 * @param no Ponteiro para o nó atual da árvore.
 * @param info Informação a ser inserida na árvore.
 * @param sobe Ponteiro para a informação que pode subir para o nó pai em caso de quebra.
 * @param pai Ponteiro para o nó pai do nó atual.
 * @return Ponteiro para o maior nó resultante da quebra, ou NULL se não houver quebra.
 */
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

/**
 * @brief Insere uma nova informação na árvore 2-3.
 *
 * Esta função insere um novo elemento na árvore 2-3. Se a inserção causar um 
 * estouro no nó raiz, um novo nó raiz é criado.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore 2-3.
 * @param info Informação a ser inserida na árvore.
 */
void insere(ARV2_3 **raiz, Informacao info)
{
   
    Informacao sobe;
    ARV2_3 *novo_no = inserir_Elemento_ARV_2_3(raiz, info, &sobe, NULL);
    if (novo_no)
    {
        *raiz = criar_no(sobe, *raiz, novo_no);
    }
}

/**
 * @brief Cria uma estrutura de informação contendo uma palavra em português, 
 *        uma árvore binária com a palavra em inglês e uma unidade.
 *
 * @param palavra_portugues A palavra em português a ser armazenada.
 * @param palavra_ingles A palavra em inglês a ser inserida na árvore binária.
 * @param unidade Um valor inteiro representando a unidade associada.
 * @return Uma estrutura Informacao contendo a palavra em português, 
 *         a árvore binária com a palavra em inglês e a unidade.
 */
Informacao criar_info(char *palavra_portugues, char *palavra_ingles, int unidade)
{
    ARV_BINARIA *arvore = NULL;  // A árvore binária será criada localmente
    Informacao info;

    strcpy(info.palavra_portugues, palavra_portugues);
    insere_arvore_binaria(&arvore, palavra_ingles, unidade);
    info.palavra_ingles = arvore;
    info.unidade = unidade;
    return info;
}

/**
 * @brief Insere um elemento binário em uma árvore 2-3.
 *
 * Esta função insere uma nova informação na árvore 2-3. A informação é composta por uma palavra em português,
 * uma palavra em inglês e uma unidade. Se a inserção resultar na necessidade de um novo nó raiz, a árvore é ajustada
 * adequadamente.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore 2-3.
 * @param palavra_portugues Palavra em português a ser inserida.
 * @param unidade Unidade associada à palavra.
 * @param palavra_ingles Palavra em inglês a ser inserida.
 */
void inserir_binaria_em_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade, char *palavra_ingles){
    Informacao info_2_3 = criar_info(palavra_portugues, palavra_ingles, unidade); 

    Informacao sobe;
    ARV2_3 *novo_no = inserir_Elemento_ARV_2_3(raiz, info_2_3, &sobe, NULL);
    if (novo_no)
        *raiz = criar_no(sobe, *raiz, novo_no);
    
}

/**
 * @brief Exibe a estrutura da árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 e exibe as informações contidas em cada nó,
 * incluindo a quantidade de informações, as palavras em português, suas unidades
 * e as árvores binárias associadas a cada palavra.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 */
void mostrar(ARV2_3 *raiz){
   
    if (raiz)
    {
        mostrar(raiz->esquerda);
        printf("\n+--- Nó Atual ---+\n");
        printf("| Quantidade de Informações: %d\n", raiz->quant_infos);

        printf("| Palavra 1 (PT): %s\n", raiz->info1.palavra_portugues);
        printf("| Unidade : %d\n", raiz->info1.unidade);
        printf("| Árvore Binária Associada à Palavra 1:\n");
        mostrar_arvore_binaria_completa(raiz->info1.palavra_ingles);
        printf("+----------------+\n");
        mostrar(raiz->centro);

        if (raiz->quant_infos == 2)
        {
            printf("| Palavra 2 (PT): %s\n", raiz->info2.palavra_portugues);
            printf("| Unidade : %d\n", raiz->info2.unidade);
            printf("| Árvore Binária Associada à Palavra 2:\n");
            mostrar_arvore_binaria_completa(raiz->info2.palavra_ingles);
            printf("+----------------+\n");
            mostrar(raiz->direita);
        }

        
        
    }
}

/**
 * imprimir_palavras_unidade - Imprime as palavras em português e suas traduções em inglês para uma unidade específica.
 * @raiz: Ponteiro para a raiz da árvore 2-3.
 * @unidade: Unidade que será usada para filtrar as palavras a serem impressas.
 * 
 * Esta função percorre recursivamente a árvore 2-3 e verifica se a unidade da palavra em português corresponde à unidade
 * fornecida. Quando encontra uma palavra com a unidade correspondente, a função imprime a palavra em português, seguida
 * pela tradução em inglês, que é exibida utilizando a função `mostrar_arvore_binaria_completa`.
 * A função trata tanto a primeira quanto a segunda informação de cada nó e imprime as informações de todas as palavras
 * da unidade especificada.
 */
void imprimir_palavras_unidade(ARV2_3 *raiz, int unidade) {
    if (raiz != NULL) {

         imprimir_palavras_unidade(raiz->esquerda, unidade);

        if (raiz->info1.unidade == unidade) {
            printf("\n=====================================\n");
            printf("Palavra em Português: %s\n", raiz->info1.palavra_portugues);
            printf("Tradução para o Inglês:\n");
            mostrar_arvore_binaria_completa(raiz->info1.palavra_ingles);
            printf("=====================================\n");
           
        }
        imprimir_palavras_unidade(raiz->centro, unidade);
        if (raiz->quant_infos == 2 && raiz->info2.unidade == unidade) {
            printf("\n=====================================\n");
            printf("Palavra em Português: %s\n", raiz->info2.palavra_portugues);
            printf("Tradução para o Inglês:\n");
            mostrar_arvore_binaria_completa(raiz->info2.palavra_ingles);
            printf("=====================================\n");
            imprimir_palavras_unidade(raiz->direita, unidade);

        }

       
    }
  
}

/**
 * imprimir_palavras_ingles - Imprime as palavras em inglês associadas a uma palavra em português em uma árvore 2-3.
 * @raiz: Ponteiro para a raiz da árvore 2-3.
 * @palavra_portugues: Palavra em português cuja tradução em inglês será impressa.
 * 
 * Esta função percorre recursivamente a árvore 2-3 em busca da palavra em português especificada e, quando a encontra,
 * imprime a tradução correspondente em inglês. A função examina tanto a primeira quanto a segunda informação de cada nó,
 * imprimindo a tradução para o inglês quando a palavra em português correspondente for encontrada.
 * A função também utiliza a função `mostrar_arvore_binaria_completa` para exibir a tradução.
 */
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

/**
 * no_2_3_juntar - Junta informações de um nó em uma árvore 2-3.
 * @filho1: Ponteiro para o nó filho que receberá a informação.
 * @info: Informação a ser adicionada ao nó.
 * @maior: Ponteiro para o maior nó da árvore.
 * @raiz: Ponteiro duplo para a raiz da árvore.
 *
 * Esta função verifica se o nó filho possui duas informações e, caso possua, reduz a quantidade de informações para uma.
 * Em seguida, a nova informação é adicionada ao nó filho. Após a operação, a quantidade de informações da raiz é decrementada.
 * Se a raiz ficar sem informações, o nó raiz é desacoplado.
 *
 * Retorno:
 * Retorna o ponteiro para o nó filho após a operação de junção.
 */
ARV2_3 *no_2_3_juntar(ARV2_3 *filho1, Informacao info, ARV2_3 *maior, ARV2_3 **raiz)
{
    no_2_3_adicionar_info(filho1, info, maior);

    (*raiz)->quant_infos--;

    if((*raiz)->quant_infos== 0)
        no_2_3_desacolar(raiz);

    return filho1;
}

/**
 * no_2_3_adicionar_info - Adiciona uma nova informação a um nó em uma árvore 2-3.
 * @no: Ponteiro para o nó onde a informação será adicionada.
 * @info: A informação a ser adicionada ao nó.
 * @filho_maior: Ponteiro para o nó filho maior, que será associado ao nó em caso de redistribuição.
 * 
 * Esta função adiciona uma nova informação a um nó de uma árvore 2-3, ajustando os ponteiros dos filhos conforme necessário.
 * Se a nova informação for maior que a primeira informação do nó, ela será colocada na segunda posição, e o nó filho maior será associado à direita.
 * Caso contrário, a primeira informação será deslocada para a segunda posição e o nó filho maior será colocado no lugar do centro, enquanto a nova informação ocupará a primeira posição.
 * Após a adição, o nó passa a ter duas informações.
 */
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

/**
 * eh_folha - Verifica se um nó é uma folha em uma árvore 2-3.
 * @no: Ponteiro para o nó que será verificado.
 * 
 * Retorno: 1 se o nó for uma folha (não possui filhos), 0 caso contrário.
 * 
 * Esta função verifica se o nó é uma folha, ou seja, se ele não possui filhos à esquerda (o ponteiro 'esquerda' é NULL).
 * Se o nó for uma folha, a função retorna 1, caso contrário, retorna 0.
 */
int eh_folha(ARV2_3 *no){
    return no->esquerda == NULL;
}

/**
 * eh_info1 - Verifica se uma informação corresponde ao primeiro item de um nó em uma árvore 2-3.
 * @no: Nó da árvore 2-3 que contém as informações a serem verificadas.
 * @info: A informação (palavra em português) a ser comparada.
 * 
 * Retorno: 1 se a informação corresponde ao primeiro item do nó, 0 caso contrário.
 * 
 * Esta função compara a informação fornecida com o primeiro item de um nó. 
 * Se a informação fornecida for igual ao primeiro item do nó, a função retorna 1, indicando que a condição foi satisfeita.
 * Caso contrário, retorna 0.
 */
int eh_info1(ARV2_3 no, char *info){
    return strcmp(info,no.info1.palavra_portugues )  == 0;
}

/**
 * eh_info2 - Verifica se uma informação corresponde ao segundo item de um nó em uma árvore 2-3.
 * @no: Nó da árvore 2-3 que contém as informações a serem verificadas.
 * @info: A informação (palavra em português) a ser comparada.
 * 
 * Retorno: 1 se a informação corresponde ao segundo item do nó, 0 caso contrário.
 * 
 * Esta função compara a informação fornecida com o segundo item de um nó que contém duas informações (caso o nó tenha duas informações). 
 * Se a informação fornecida for igual ao segundo item do nó, a função retorna 1, indicando que a condição foi satisfeita.
 * Caso contrário, retorna 0.
 */
int eh_info2(ARV2_3 no, char *info) {
    return (no.quant_infos == 2 && strcmp(info, no.info2.palavra_portugues) == 0);
}

/**
 * no_2_3_alocar - Aloca dinamicamente um nó de uma árvore 2-3.
 * 
 * Retorna: Um ponteiro para o nó recém-alocado da árvore 2-3.
 *
 * Esta função aloca dinamicamente um nó do tipo `ARV2_3` utilizando a função `malloc`. Se a alocação falhar, a função imprime uma mensagem de erro e finaliza o programa.
 * O nó alocado é inicializado com valores padrão para ser utilizado na árvore.
 */
ARV2_3 *no_2_3_alocar(){
    ARV2_3 *no; 
    no = (ARV2_3 *)malloc(sizeof(ARV2_3)); 

    if (!no){
        
        printf("erro ao alocar nó da arvore");
        exit(EXIT_FAILURE);
    }
    
    return no; 

}

/**
 * no_2_3_desacolar - Desacopla (libera a memória) de um nó em uma árvore 2-3.
 * @no: Ponteiro duplo para o nó a ser desacoplado.
 *
 * Esta função libera a memória alocada para o nó passado como argumento e define o ponteiro do nó como NULL,
 * efetivamente removendo-o da árvore e garantindo que não haja referência a um nó de memória já liberada.
 */
void no_2_3_desacolar(ARV2_3 **no){
    if(*no != NULL){
        free(*no);
        *no = NULL;
    }
}

/**
 * maior_info - Retorna a maior informação de um nó em uma árvore 2-3.
 * @raiz: Ponteiro para o nó da árvore de onde a maior informação será extraída.
 *
 * Esta função verifica o número de informações presentes no nó. Se o nó contiver duas informações,
 * retorna a segunda informação (a maior). Caso contrário, retorna a primeira informação.
 *
 * Retorno:
 * Retorna a maior informação presente no nó, que pode ser a `info1` ou `info2` dependendo da quantidade de informações.
 */
Informacao maior_info(ARV2_3 *raiz){ 
    return raiz->quant_infos == 2 ? raiz->info2 : raiz->info1;
}

/**
 * buscar_menor_filho - Busca o menor filho de um nó em uma árvore 2-3.
 * @raiz: Ponteiro para o nó da árvore onde a busca será iniciada.
 * @pai: Ponteiro duplo para armazenar o pai do nó encontrado.
 *
 * Esta função percorre a árvore em direção à esquerda até encontrar o nó folha com o menor valor.
 * Durante o percurso, o nó pai é atualizado para o nó atual.
 *
 * Retorno:
 * Retorna o ponteiro para o nó folha com o menor valor encontrado.
 */
ARV2_3 *buscar_menor_filho(ARV2_3 *raiz, ARV2_3 **pai){ 
    ARV2_3 *filho;
    filho = raiz; 

    while (!eh_folha(filho)) {
        *pai = filho; 
        filho = filho->esquerda;
    }
    
    return filho; 
}

/**
 * buscar_maior_filho - Busca o maior filho de um nó em uma árvore 2-3.
 * @raiz: Ponteiro para o nó raiz da subárvore onde a busca será realizada.
 * @pai: Ponteiro duplo para armazenar o nó pai do maior filho encontrado.
 * @maior_valor: Ponteiro para armazenar a maior informação encontrada no nó filho.
 *
 * Esta função percorre a árvore 2-3 a partir do nó raiz fornecido, indo para o filho da direita 
 * até encontrar um nó folha. Durante a travessia, o nó pai do maior filho encontrado é atualizado
 * e a maior informação armazenada no nó folha é copiada para o parâmetro `maior_valor`.
 *
 * Retorno:
 * Retorna o ponteiro para o maior filho encontrado na subárvore ou NULL se nenhum filho for encontrado.
 */
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

/**
 * buscar_pai - Busca o pai de um nó que contém a informação fornecida em uma árvore 2-3.
 * @raiz: Ponteiro para o nó raiz da subárvore onde a busca será realizada.
 * @info: Informação que está sendo buscada na árvore.
 *
 * Esta função percorre a árvore 2-3 de forma recursiva para encontrar o pai de um nó
 * que contém a informação fornecida. O algoritmo compara a informação fornecida com as palavras 
 * em português armazenadas nos nós e faz a busca no filho apropriado (esquerdo, centro ou direito).
 * Quando encontra o nó que contém a informação fornecida ou um nó próximo, ele retorna o nó pai.
 *
 * Retorno:
 * Retorna o ponteiro para o nó pai que contém a informação fornecida ou NULL caso o nó pai não seja encontrado.
 */
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

/**
 * buscar_maior_pai - Busca o pai de um nó que contém a maior informação menor que a fornecida em uma árvore 2-3.
 * @raiz: Ponteiro para o nó raiz da subárvore onde a busca será realizada.
 * @info: Informação que está sendo buscada na árvore.
 *
 * Esta função percorre a árvore 2-3 de forma recursiva para encontrar o pai de um nó
 * que contém a maior informação menor que a fornecida. O algoritmo compara a informação 
 * fornecida com as palavras em português armazenadas nos nós e faz a busca no filho apropriado 
 * (esquerdo, centro ou direito).
 *
 * Retorno:
 * Retorna o ponteiro para o nó pai que contém a maior informação menor que a fornecida, 
 * ou NULL caso não exista tal nó na árvore.
 */
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

/**
 * buscar_menor_pai - Busca o pai de um nó que contém a menor informação maior que a fornecida em uma árvore 2-3.
 * @raiz: Ponteiro para o nó raiz da subárvore onde a busca será realizada.
 * @info: Informação que está sendo buscada na árvore.
 *
 * Esta função percorre a árvore 2-3 de forma recursiva para encontrar o pai de um nó
 * que contém a menor informação maior que a fornecida. O algoritmo compara a informação 
 * fornecida com as palavras em português armazenadas nos nós e faz a busca no filho apropriado 
 * (esquerdo, centro ou direito).
 *
 * Retorno:
 * Retorna o ponteiro para o nó pai que contém a menor informação maior que a fornecida, 
 * ou NULL caso não exista tal nó na árvore.
 */
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

/**
 * buscar_menor_pai_2_info - Busca o pai de um nó que contém a menor informação em uma árvore 2-3.
 * @raiz: Ponteiro para o nó raiz da subárvore onde a busca será realizada.
 * @info: Informação que está sendo buscada na árvore.
 *
 * Esta função percorre a árvore 2-3 para localizar o nó pai que contém a menor informação
 * maior que a informação fornecida. A busca é feita recursivamente, comparando a informação
 * nos nós e direcionando a busca para o filho adequado (esquerdo, centro ou direito).
 *
 * Retorno: 
 * Retorna o ponteiro para o nó pai que contém a menor informação maior que a fornecida,
 * ou NULL caso a informação não seja encontrada.
 */
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

/**
 * @brief Verifica se é possível remover um nó da árvore 2-3.
 *
 * Esta função verifica se é possível remover um nó da árvore 2-3, 
 * verificando se o nó raiz possui duas informações ou se é possível 
 * remover um nó dos seus filhos.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @return int Retorna 1 se for possível remover o nó, caso contrário, retorna 0.
 */
int possivel_remover(ARV2_3 *raiz){
 int possivel = 0;

    if(raiz != NULL)
    {
        possivel = raiz->quant_infos == 2;

        if(!possivel)
        {
            possivel = possivel_remover(raiz->centro);

            if(!possivel)
                possivel = possivel_remover(raiz->esquerda);
        }
    }

    return possivel;
}

/**
 * ondinha_1 - Realiza o ajuste estrutural na árvore 2-3 durante a remoção de um nó.
 * @saindo: Informação que está sendo removida da árvore.
 * @entrada: Ponteiro para a nova informação que será ajustada na estrutura.
 * @pai: Ponteiro para o nó pai na árvore.
 * @origem: Ponteiro duplo para a raiz original da árvore.
 * @raiz: Ponteiro duplo para a raiz da subárvore atual.
 * @maior: Ponteiro duplo para o maior nó encontrado na estrutura.
 *
 * Esta função realiza a remoção de um nó em uma árvore 2-3 e ajusta sua estrutura
 * substituindo a informação do nó removido por uma nova entrada, caso necessário.
 * O ajuste é realizado por meio da função auxiliar `_1_remover_2_3`, e a entrada é atualizada 
 * com a informação que estava sendo removida.
 *
 * Retorno: 
 * 1 se a remoção foi bem-sucedida,
 * -1 se houve um problema durante a remoção,
 * 0 se a informação não foi encontrada na árvore.
 */
int ondinha_1(Informacao saindo, Informacao *entrada, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **raiz, ARV2_3 **maior, int (*funcao_remover)(ARV2_3 **, char *, ARV2_3 *, ARV2_3 **, ARV2_3 **)){
   int removeu = funcao_remover(raiz, saindo.palavra_portugues, pai, origem, maior);
    *entrada = saindo;
    return removeu;

}

/**
 * @brief Desaloca a árvore 2-3 a partir da raiz fornecida.
 *
 * Esta função percorre a árvore 2-3 de forma recursiva e desaloca todos os nós,
 * começando pela raiz fornecida. A função verifica se a raiz não é nula antes
 * de proceder com a desalocação. Ela chama recursivamente a si mesma para
 * desalocar os subárvores esquerda, centro e, se aplicável, direita. Após
 * desalocar os subárvores, a função desaloca o nó atual.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3 a ser desalocada.
 */
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

/**
 * @brief Calcula a altura de uma árvore binária.
 *
 * Esta função calcula a altura de uma árvore binária a partir de um nó dado.
 * A altura de uma árvore é definida como o número de arestas no caminho mais longo
 * da raiz até uma folha. Se a árvore estiver vazia, a altura é -1.
 *
 * @param no Ponteiro para o nó da árvore binária.
 * @return A altura da árvore binária. Retorna -1 se a árvore estiver vazia.
 */
int calcular_altura(ARV2_3 *no)
{
    int altura = -1;

    if(no != NULL)
        altura = 1 + calcular_altura(no->esquerda);

    return altura;
}

/**
 * @brief Remove um nó não-folha de uma árvore 2-3.
 *
 * Esta função remove um nó não-folha de uma árvore 2-3, ajustando os nós e informações conforme necessário.
 *
 * @param origem Ponteiro para a árvore original.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param info Ponteiro para a informação a ser removida.
 * @param filho1 Ponteiro para o primeiro filho do nó a ser removido.
 * @param filho2 Ponteiro para o segundo filho do nó a ser removido.
 * @param maior Ponteiro para o maior nó da subárvore.
 * @return int Retorna 1 se a remoção foi bem-sucedida, caso contrário, retorna 0.
 */
int arvore23_remover_nao_folha2(ARV2_3 **origem, ARV2_3* raiz, Informacao *info, ARV2_3 *filho1, ARV2_3 *filho2, ARV2_3 **maior)
{
    int removeu;
    ARV2_3 *filho, *pai;
    Informacao info_filho;

    pai = raiz;

    filho = buscar_menor_filho(filho1, &pai);

    if(filho->quant_infos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->quant_infos = 1;
    }
    else
    {
        filho = buscar_maior_filho(filho2, &pai, &info_filho);
        removeu = ondinha_1(info_filho, info, pai, origem, &filho, maior, _1_remover_2_3);
    }

    return removeu;
}

/**
 * @brief Remove um elemento de um nó não folha em uma árvore 2-3.
 *
 * @param origem Ponteiro duplo para a raiz da árvore.
 * @param raiz Ponteiro para o nó raiz.
 * @param info Ponteiro para a informação a ser substituída ou removida.
 * @param filho1 Ponteiro para o filho esquerdo do nó raiz.
 * @param filho2 Ponteiro para o filho direito do nó raiz.
 * @param maior Ponteiro para armazenar o maior nó, se necessário.
 *
 * @return 1 se a remoção foi bem-sucedida, 0 caso contrário.
 *
 * A função ajusta a estrutura da árvore para manter suas propriedades após a remoção, buscando o maior 
 * elemento do filho esquerdo ou o menor do filho direito, conforme necessário.
 */

int arvore23_remover_nao_folha1(ARV2_3 **origem, ARV2_3* raiz, Informacao *info, ARV2_3 *filho1, ARV2_3 *filho2, ARV2_3 **maior)
{
    int removeu;
    ARV2_3 *filho, *pai;
    Informacao info_filho;

    pai = raiz;

    filho = buscar_maior_filho(filho1, &pai, &info_filho);

    if(filho->quant_infos == 2)
    {
        *info = info_filho;
        filho->quant_infos = 1;
    }
    else
    {
        filho = buscar_menor_filho(filho2, &pai);
        removeu = ondinha_1(filho->info1, info, pai, origem, &filho, maior, _1_remover_2_3);
    }

    return removeu;
}


/**
 * _1_remover_2_3 - Remove um nó de uma árvore 2-3.
 * @raiz: Ponteiro duplo para a raiz da árvore.
 * @info: Informação a ser removida.
 * @pai: Ponteiro para o nó pai.
 * @origem: Ponteiro duplo para a raiz original da árvore.
 * @maior: Ponteiro duplo para o maior nó.
 *
 * Esta função remove um nó de uma árvore 2-3, ajustando a estrutura da árvore conforme necessário.
 * A função retorna 1 se a remoção foi bem-sucedida, -1 se houve um problema durante a remoção,
 * e 0 se a informação não foi encontrada na árvore.
 *
 * Retorno: 1 se a remoção foi bem-sucedida, -1 se houve um problema, 0 se a informação não foi encontrada.
 */
int _1_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3 *pai, ARV2_3 **origem, ARV2_3 **maior) {
    int removeu = 0;

    if(*raiz != NULL){
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
                        ARV2_3 *pai_aux;
                        Informacao info_pai;
                        if(*raiz == pai->esquerda || (pai->quant_infos == 2 && *raiz == pai->centro)){
                            pai_aux = buscar_pai(*origem, pai->info1.palavra_portugues);
                            
                            if(*raiz == pai->esquerda)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;
                                removeu = ondinha_1(info_pai,&((*raiz)->info1),pai_aux,origem,&pai,maior,_1_remover_2_3);
                        }else{// filho do centro(com pai de 1 info)ou da direita 

                            pai_aux = buscar_maior_pai(*origem,(*raiz)->info1.palavra_portugues);

                            ARV2_3 *menor_pai; 
                            menor_pai = buscar_menor_pai(*origem, (*raiz)->info1.palavra_portugues);

                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                if (strcmp(pai_aux->info1.palavra_portugues, (*raiz)->info1.palavra_portugues) > 0){
                                    info_pai = pai_aux->info1;
                                }else{
                                    info_pai = pai_aux->info2;
                                }
                                
                            }
                            int alt_menor_pai = calcular_altura(menor_pai);
                            int alt_pai_aux = calcular_altura(pai_aux);
                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && alt_menor_pai <= alt_pai_aux && (strcmp(info_pai.palavra_portugues, menor_pai->info2.palavra_portugues) > 0))){  
                                *maior = pai; 
                                (*raiz)->quant_infos = 0; 
                                removeu = -1;   
                            }else{
                                ARV2_3 *avo;
                                avo = buscar_pai(*origem, info_pai.palavra_portugues);
                                removeu = ondinha_1(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, _1_remover_2_3);
                            }
                    }
                }
            }
        }
        else if (info2)
                removeu = arvore23_remover_nao_folha1(origem, *raiz,&((*raiz)->info2), (*raiz)->centro, (*raiz)->direita, maior); 
        else if(info1)
                removeu = arvore23_remover_nao_folha1(origem, *raiz,&((*raiz)->info1), (*raiz)->esquerda, (*raiz)->centro, maior); 
        }
        else{
            if((strcmp(info,(*raiz)->info1.palavra_portugues)< 0))
                removeu = _1_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if((*raiz)->quant_infos == 1 || (strcmp(info,(*raiz)->info2.palavra_portugues)< 0) )
                removeu = _1_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _1_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
           }
    
        }

 return removeu;
}

/**
 * @brief Remove um nó de uma árvore 2-3.
 * 
 * Esta função remove um nó de uma árvore 2-3 que contém a informação especificada.
 * 
 * @param raiz Ponteiro duplo para a raiz da árvore.
 * @param info Informação a ser removida.
 * @param pai Ponteiro para o nó pai.
 * @param origem Ponteiro duplo para a origem da árvore.
 * @param maior Ponteiro duplo para o maior nó da árvore.
 * @return int Retorna 1 se a remoção foi bem-sucedida, caso contrário, retorna 0.
 * 
 * A função percorre a árvore para encontrar o nó que contém a informação a ser removida.
 * Se o nó for uma folha, ele é removido diretamente. Caso contrário, a função realiza
 * uma série de operações para manter as propriedades da árvore 2-3.
 * 
 * A função também lida com casos especiais, como quando o nó a ser removido é a raiz
 * ou quando o nó pai tem apenas uma informação.
 */
int _2_remover_2_3(ARV2_3 **raiz, char *info, ARV2_3  *pai, ARV2_3  **origem, ARV2_3  **maior){
    int removeu = 0;

    if(*raiz != NULL)
    {
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
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->quant_infos = 1;
                }
                else
                {
                    if(pai == NULL)
                        no_2_3_desacolar(raiz);
                    else
                    {
                        ARV2_3  *pai_aux;
                        Informacao info_pai;
                        if(*raiz == pai->centro || (pai->quant_infos == 2 && *raiz == pai->direita))
                        {
                            pai_aux = buscar_pai(*origem, pai->info1.palavra_portugues);
                            
                            if(*raiz == pai->centro)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = ondinha_1(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, _1_remover_2_3);
                        }
                        else // Filho da esquerda
                        {
                            pai_aux = buscar_menor_pai(*origem, (*raiz)->info1.palavra_portugues);

                            ARV2_3  *menor_pai;
                            menor_pai = buscar_menor_pai_2_info(*origem, (*raiz)->info1.palavra_portugues);

                            ARV2_3  *avo;
                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {  
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if(pai_aux->quant_infos == 2 && (strcmp(pai_aux->info2.palavra_portugues, (*raiz)->info1.palavra_portugues) < 0))
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = buscar_pai(*origem, info_pai.palavra_portugues);
                                removeu = ondinha_1(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, _2_remover_2_3);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info2), (*raiz)->direita, (*raiz)->centro, maior);
            else if(info1)
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info1), (*raiz)->centro, (*raiz)->esquerda, maior);
        }
        else
        {
            if((strcmp(info, (*raiz)->info1.palavra_portugues) < 0 ))
                removeu = _2_remover_2_3(&(*raiz)->esquerda, info, *raiz, origem, maior);
            else if((*raiz)->quant_infos == 1 || (strcmp(info,(*raiz)->info2.palavra_portugues)< 0))
                removeu = _2_remover_2_3(&(*raiz)->centro, info, *raiz, origem, maior);
            else
                removeu = _2_remover_2_3(&(*raiz)->direita, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

/**
 * @brief Remove um elemento de uma árvore 2-3 e mantém seu balanceamento.
 * 
 * Esta função remove um elemento identificado pela chave fornecida (`info`) 
 * de uma árvore 2-3. Durante o processo, verifica se a remoção causa 
 * desequilíbrio na árvore e tenta rebalanceá-la, realizando ajustes 
 * necessários, como redistribuição de chaves ou junção de nós.
 * 
 * A remoção é realizada em duas etapas principais:
 * 1. Tentativa de remoção direta do elemento com a função `_1_remover_2_3`.
 * 2. Caso haja necessidade de rebalanceamento, utiliza-se a função 
 * `arvore_2_3_rebalancear` e outras sub-rotinas para corrigir a estrutura 
 * da árvore.
 * 
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3. Pode ser atualizado 
 * caso a estrutura da árvore seja alterada.
 * @param info Chave que identifica o elemento a ser removido.
 * 
 * @return int Indica o status da operação:
 * - `0`: Remoção bem-sucedida sem necessidade de rebalanceamento.
 * - `-1`: Falha na remoção, possivelmente devido à ausência da chave ou 
 * necessidade de rebalanceamento que não foi resolvida.
 */
int arvore_2_3_remover(ARV2_3 **raiz, char *info)
{   
    ARV2_3 *maior, *posicao_juncao;
    int removeu = _1_remover_2_3(raiz, info, NULL, raiz, &posicao_juncao);

    if(removeu == -1)
    {
        removeu = 1;
        Informacao valor_juncao = maior_info(posicao_juncao);
        maior = NULL;
        int removeu_aux = arvore_2_3_rebalancear(raiz, valor_juncao.palavra_portugues, &maior);
        
        if(removeu_aux == -1)
        {
            ARV2_3 *pai, *posicao_juncao2;
            Informacao *entrada;
            pai = buscar_pai(*raiz, valor_juncao.palavra_portugues);

            if(eh_info1(*posicao_juncao, valor_juncao.palavra_portugues))
                entrada = &(posicao_juncao->centro->info1);
            else
                entrada = &(posicao_juncao->direita->info1);

            removeu_aux = ondinha_1(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, _1_remover_2_3);

            if(removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = buscar_pai(*raiz, valor_juncao.palavra_portugues);
                removeu_aux = ondinha_1(valor_juncao, &(posicao_juncao2->esquerda->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, _1_remover_2_3);

                valor_juncao = maior_info(posicao_juncao);
                maior = NULL;
                removeu_aux = arvore_2_3_rebalancear(raiz, valor_juncao.palavra_portugues, &maior);
            }
        }

        if(*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

/**
 * @brief Rebalanceia uma árvore 2-3.
 *
 * Esta função reequilibra uma árvore 2-3 a partir de um nó raiz fornecido.
 * 
 * @param raiz Ponteiro duplo para o nó raiz da árvore 2-3.
 * @param info Informação a ser utilizada no rebalanceamento.
 * @param maior Ponteiro duplo para armazenar o maior nó após o rebalanceamento.
 * @return Retorna 0 se o rebalanceamento foi bem-sucedido, -1 se não foi possível rebalancear.
 */
int arvore_2_3_rebalancear(ARV2_3 **raiz, char  *info, ARV2_3 **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!eh_folha(*raiz))
        {
            if((strcmp(info,(*raiz)->info1.palavra_portugues)< 0))
                balanceou = arvore_2_3_rebalancear(&((*raiz)->esquerda), info, maior);
            else if((*raiz)->quant_infos == 1 || info < (*raiz)->info2.palavra_portugues)
            {
                if((*raiz)->esquerda->quant_infos == 2 && !possivel_remover((*raiz)->centro))
                    balanceou = -1;
                else
                    balanceou = arvore_2_3_rebalancear(&((*raiz)->centro), info, maior);
            }
            else
            {
                if((*raiz)->centro->quant_infos == 2 && !possivel_remover((*raiz)->direita))
                    balanceou = -1;
                else
                    balanceou = arvore_2_3_rebalancear(&((*raiz)->direita), info, maior);
            }

            if(balanceou != -1)
            {
                if((*raiz)->quant_infos == 1)
                    balanceou = balanceamento(raiz, (*raiz)->esquerda, &((*raiz)->centro), (*raiz)->info1, maior);
                else if((*raiz)->quant_infos == 2)
                    balanceou = balanceamento(raiz, (*raiz)->centro, &((*raiz)->direita), (*raiz)->info2, maior);
            }
            
        }
    }

    return balanceou;
}

/**
 * @brief Realiza o balanceamento de uma árvore 2-3.
 *
 * Esta função verifica se o segundo filho é nulo ou se não possui informações.
 * Se for o caso, remove o nó do segundo filho e junta o primeiro filho com a informação
 * fornecida, ajustando a raiz e o maior nó conforme necessário.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore.
 * @param filho1 Ponteiro para o primeiro filho.
 * @param filho2 Ponteiro duplo para o segundo filho.
 * @param info Informação a ser inserida na árvore.
 * @param maior Ponteiro duplo para o maior nó.
 * @return Retorna 1 se o balanceamento foi realizado, caso contrário, retorna 0.
 */
int balanceamento(ARV2_3 **raiz, ARV2_3 *filho1, ARV2_3 **filho2, Informacao info, ARV2_3 **maior)
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

/**
 * @brief Remove uma palavra em inglês e sua unidade correspondente de uma árvore 2-3.
 * 
 * Esta função percorre uma árvore 2-3 e remove a palavra em inglês especificada, 
 * juntamente com sua unidade correspondente. Se a palavra em inglês for removida 
 * e a palavra em português correspondente estiver vazia, a entrada inteira é removida 
 * da árvore 2-3.
 * 
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3.
 * @param palavra_ingles Palavra em inglês a ser removida.
 * @param unidade Unidade correspondente à palavra em inglês a ser removida.
 */
void remover_palavra_ingles_e_unidade_2_3(ARV2_3 **raiz, char *palavra_ingles, int unidade) {
    if (*raiz != NULL) { 
        remover_palavra_ingles_e_unidade_2_3(&((*raiz)->esquerda), palavra_ingles, unidade);
        remover_palavra_ingles_e_unidade_2_3(&((*raiz)->direita), palavra_ingles, unidade);
        remover_palavra_ingles_e_unidade_2_3(&((*raiz)->centro), palavra_ingles, unidade);
        if (*raiz) {
            int sucesso = remover_palavra_por_unidade(&((*raiz)->info1.palavra_ingles), palavra_ingles, unidade);
            if (sucesso) {
                if ((*raiz)->info1.palavra_ingles == NULL) {
                    char palavra_portugues[100];
                    strcpy(palavra_portugues, (*raiz)->info1.palavra_portugues);
                    arvore_2_3_remover(raiz, palavra_portugues);
                    printf("Palavra '%s' foi removida da árvore 2-3 e da árvore binária.\n", palavra_portugues);
                } else {
                    printf("Palavra '%s' em inglês foi removida, mas a palavra em português permanece.\n", palavra_ingles);
                }
            }
        }
        if ( *raiz ) {
            int sucesso = remover_palavra_por_unidade(&((*raiz)->info2.palavra_ingles), palavra_ingles, unidade);
            if (sucesso) {
                if ((*raiz)->info2.palavra_ingles == NULL) {
                    char palavra_portugues[100];
                    strcpy(palavra_portugues, (*raiz)->info2.palavra_portugues);
                    arvore_2_3_remover(raiz, palavra_portugues);
                    printf("Palavra '%s' foi removida da árvore 2-3 e da árvore binária.\n", palavra_portugues);
                } else {
                    printf("Palavra '%s' em inglês foi removida, mas a palavra em português permanece.\n", palavra_ingles);
                }
            }
        }

      
      
    }
}

/**
 * @brief Busca uma palavra em uma árvore 2-3.
 *
 * Esta função realiza a busca de uma palavra em uma árvore 2-3, retornando o nó que contém a palavra, se encontrada.
 *
 * @param raiz Ponteiro para o nó raiz da árvore 2-3.
 * @param palavra_portugues Palavra em português a ser buscada na árvore.
 * @return Ponteiro para o nó que contém a palavra buscada, ou NULL se a palavra não for encontrada.
 */
ARV2_3 *buscar_palavra_2_3(ARV2_3 *raiz, char *palavra_portugues) {
    ARV2_3 *resultado = NULL;

    if (raiz != NULL) {
        int comparacao1 = strcmp(palavra_portugues, raiz->info1.palavra_portugues);
        int comparacao2 = (raiz->quant_infos == 2) ? strcmp(palavra_portugues, raiz->info2.palavra_portugues) : -1;

        if (comparacao1 == 0 || comparacao2 == 0) {
            resultado = raiz;
        } else if (comparacao1 < 0) {
            resultado = buscar_palavra_2_3(raiz->esquerda, palavra_portugues);
        } else if (comparacao2 > 0) {
            resultado = buscar_palavra_2_3(raiz->direita, palavra_portugues);
        } else {
            resultado = buscar_palavra_2_3(raiz->centro, palavra_portugues);
        }
    }

    return resultado;
}

/**
 * @brief Remove uma palavra completa da árvore 2-3.
 *
 * Esta função busca uma palavra em português na árvore 2-3 e remove todas as suas traduções em inglês
 * associadas a uma unidade específica. Se todas as traduções em inglês forem removidas, a palavra em português
 * também é removida da árvore 2-3.
 *
 * @param raiz Ponteiro para a raiz da árvore 2-3.
 * @param palavra_portugues Palavra em português a ser removida.
 * @param unidade Unidade associada às traduções em inglês a serem removidas.
 * @return Retorna 1 se a palavra foi removida com sucesso, caso contrário, retorna 0.
 */
int remover_palavra_completa_2_3(ARV2_3 **raiz, char *palavra_portugues, int unidade) {
    int confere = 0; 
    ARV2_3 *no = buscar_palavra_2_3(*raiz, palavra_portugues);

    if (no != NULL) {
        if (strcmp(no->info1.palavra_portugues, palavra_portugues) == 0) {
            remover_todas_palavras_por_unidade(&(no->info1.palavra_ingles), unidade);

            if (no->info1.palavra_ingles == NULL) {
                arvore_2_3_remover(raiz, palavra_portugues);
                printf("A palavra '%s' foi removida da árvore 2-3 e da árvore binária.\n", palavra_portugues);
            } else {
                printf("As palavras em inglês foram removidas, mas a palavra em português permanece.\n");
            }

            confere = 1;
        } else if (strcmp(no->info2.palavra_portugues, palavra_portugues) == 0) {
            remover_todas_palavras_por_unidade(&(no->info2.palavra_ingles), unidade);

            if (no->info2.palavra_ingles == NULL) {
                arvore_2_3_remover(raiz, palavra_portugues);
                printf("A palavra '%s' foi removida da árvore 2-3 e da árvore binária.\n", palavra_portugues);
            } else {
                printf("As palavras em inglês foram removidas, mas a palavra em português permanece.\n");
            }

            confere = 1;
        }
    } else {
        printf("A palavra '%s' não foi encontrada ou a unidade não corresponde.\n", palavra_portugues);
    }

    return confere; 
}

/**
 * @brief Libera a memória alocada para uma árvore 2-3 binária.
 *
 * Esta função libera a memória alocada para a estrutura de informação
 * associada a uma árvore 2-3 binária. Se a estrutura de informação contém
 * uma árvore binária de palavras em inglês, essa árvore também é liberada.
 *
 * @param info Ponteiro para a estrutura de informação a ser liberada.
 */
void liberar_arvore_2_3_binaria(Informacao *info) {

    if (info) {
        if (info->palavra_ingles) {
            libera_arvore_binaria(&info->palavra_ingles);
            info->palavra_ingles = NULL;
        }
    }
}

/**
 * @brief Libera a memória alocada para uma árvore 2-3.
 *
 * Esta função percorre a árvore 2-3 de forma recursiva, liberando a memória
 * alocada para cada nó e seus respectivos filhos (esquerda, centro e direita).
 * Além disso, também libera a memória alocada para as informações binárias
 * contidas nos nós (info1 e info2).
 *
 * @param raiz Ponteiro duplo para a raiz da árvore 2-3 a ser liberada.
 */
void liberar_arvore_2_3(ARV2_3 **raiz) {
    if (*raiz) {
        liberar_arvore_2_3(&(*raiz)->esquerda);
        liberar_arvore_2_3(&(*raiz)->centro);
        
        if ((*raiz)->quant_infos == 2) {
            liberar_arvore_2_3(&(*raiz)->direita);
        }

        liberar_arvore_2_3_binaria(&(*raiz)->info1); 
        if ((*raiz)->quant_infos == 2) {
            liberar_arvore_2_3_binaria(&(*raiz)->info2);  
        }

        free(*raiz);
        *raiz = NULL;  
    }
}

