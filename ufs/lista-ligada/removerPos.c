#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    char valor[100];
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
} LISTA;



// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
    l->cabeca = NULL;
}


// Cria um novo no com o item passado e tendo NULL como prox
NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


// Retornar o tamanho da lista
int tamanho(LISTA *l)
{
    NO* p = l->cabeca;
    int tam = 0;
    while (p)  // p != NULL
    {
        tam++;
        p = p->prox;
    }
    return tam;
}


// Retorna true se a lista esta vazia (Cabeca = NULL)
bool vazia(LISTA *l)
{
    return l->cabeca == NULL;
}


/* 
  Objetivo: Insere o item passado como parametro na lista passada.
            A insercao ocorre no inicio da lista, ou seja, na cabeca.
*/
bool inserir(ITEM item, LISTA *l){
    l->cabeca = criarNo(item, l->cabeca);
    return true;
}


// Exibicao da lista
void exibirLista(LISTA *l)
{
    NO* p = l->cabeca;
    while (p)  // p != NULL
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->prox;
    }
}


// Liberacao das variaveis dinamicas dos nos da lista, iniciando da cabeca
void destruir(LISTA *l)
{
    NO* atual = l->cabeca;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca = NULL; // ajusta inicio da lista (vazia)
}


void imprimirLista(LISTA *l)
{
    printf("Tamanho = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");
}


/////////////////////////////////////////////////////

/*
  Objetivo: Remover o item que se encontra na posicao pos da lista.
            Caso nao haja item nesta posicao, ou seja, a posicao nao esta
            no intervalo de (de 0 a tamanho - 1), nao havera remocao e a
            funcao retorna true.
            Caso contrario, a funcao retorna remove o item, portando mudando
            a posicao dos seguintes 1 unidade para baixo, e retorna true.

 */
bool removerDaPos(int posRemocao, LISTA *l)
{
    if(vazia(l) || !(posRemocao >= 0 && posRemocao < tamanho(l))) return false;

    NO * aux = l->cabeca;

    if(posRemocao == 0) {
        l->cabeca = l->cabeca->prox;
        free(aux);
        return true;
    }

    if(aux->prox == NULL) return false;

    for(int i = 0; i < posRemocao - 1; i++)
        aux = aux->prox;

    NO * no = aux->prox->prox;
    free(aux->prox);
    aux->prox = no;

    return true;
}


//////////////////////////////////////////////////////////////


void lerItens(LISTA *l)
{
    int n;
    scanf("%d", &n);

    // insere os valores n pares chave,valor
    ITEM item;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item.chave);
        scanf("%s", item.valor);
        inserir(item, l);
    }
}

void lerItensRemover(LISTA *l)
{
    int n;
    scanf("%d", &n);

    // insere as posicoes dos n itens que devem ser removidos
    for (int i = 0; i < n; i++)
    {
        int pos;
        scanf("%d", &pos);
        removerDaPos(pos, l);
    }
}


int main(){
  LISTA l;
  ITEM item;

  inicializar(&l);

  lerItens(&l);
  imprimirLista(&l);
    
  lerItensRemover(&l);
  imprimirLista(&l);

  destruir(&l);
  return 0;
}