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
    struct estrutura *ant;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
    NO* cauda;
    int tamanho;
} LISTA;



// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}


// Cria um novo no com o item, os apontadores para o anterior e para o proximo
NO* criarNo(ITEM item,  NO *ant, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->ant = ant;
    pNovo->prox = prox;
    return pNovo;
}


// Retornar o tamanho da lista
int tamanho(LISTA *l)
{
    return l->tamanho;
}


// Retorna true se a lista esta vazia, ou seja, se tem tamanho = 0
bool vazia(LISTA *l)
{
    return tamanho(l) == 0;
}


// Exibicao da lista
void exibirListaCabecaCauda(LISTA *l)
{
    NO* p = l->cabeca;
    while (p)
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->prox;
    }
}

// Exibicao da lista comecando da cauda
void exibirListaCaudaCabeca(LISTA *l)
{
    NO* p = l->cauda;
    while (p)
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->ant;
    }
}


void imprimirLista(LISTA *l, bool crescente)
{
    printf("Tamanho = %d\n", tamanho(l));
    if (crescente)
        exibirListaCabecaCauda(l);
    else
        exibirListaCaudaCabeca(l);
    printf("\n");
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
    l->cabeca = NULL; // ajusta a cabeca da lista (vazia)
    l->cauda = NULL; // ajusta a cauda da lista (vazia)
}


/////////////////////////////////////////////////////

/*
 Objetivo: Inserir em uma lista ordenada o item passado e garantir
           que nao havera duplicacao.
*/
bool inserirNaOrdem(ITEM item, LISTA *l)
{
  NO* NOnovo = criarNo(item, NULL, NULL);

  if (l->tamanho == 0) {
    l->cabeca = NOnovo;
    l->cauda = NOnovo;
    l->tamanho++;
    return true;
  }

  NO* atual = l->cabeca;
  while (atual && atual->item.chave <= item.chave) {
    if(atual->item.chave == item.chave) {
      free(NOnovo);
      return false;
    }
    atual = atual->prox;
  }
  
  l->tamanho++;

  if (atual == NULL) { 
    NOnovo->ant = l->cauda;
    l->cauda->prox = NOnovo;
    l->cauda = NOnovo;
    return true;
  }

  if (atual == l->cabeca) {
    NOnovo->prox = l->cabeca;
    l->cabeca->ant = NOnovo;
    l->cabeca = NOnovo;
    return true;
  }

  NOnovo->ant = atual->ant;
  NOnovo->prox = atual;
  atual->ant->prox = NOnovo;
  atual->ant = NOnovo;

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
        inserirNaOrdem(item, l);
    }
}

//////////////////////////////////////////////////////////////

int main(){
  LISTA l;
  ITEM item;

  inicializar(&l);

  lerItens(&l);
  imprimirLista(&l, true);   // crescente
    
  lerItens(&l);
  imprimirLista(&l, false);  // decrescente

  destruir(&l);
  return 0;
}