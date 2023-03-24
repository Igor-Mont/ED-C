#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
    int tamanho;
} LISTA;


// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
    l->cabeca = NULL;
    l->tamanho = 0;
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
    return l->tamanho;
}


// Retorna true se a lista esta vazia (Cabeca = NULL)
bool vazia(LISTA *l)
{
    return l->cabeca == NULL;
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


/*
 Objetivo: Inserir em uma lista ordenada o item passado e garantir
           que nao havera duplicacao.
*/
bool inserirNaOrdem(ITEM item, LISTA *l)
{
   if (vazia(l)) // quando vazia, apenas cria o NO e coloca na cabeca
   {
      l->cabeca = criarNo(item, l->cabeca);
      l->tamanho++;
      return true;
   }

   if (item.chave == l->cabeca->item.chave)   // Chave duplicada, nao insere 
      return false;

   if (item.chave < l->cabeca->item.chave)   // quando vazia ou menor que a cabeca
   {
      l->cabeca = criarNo(item, l->cabeca);
      l->tamanho++;
      return true;
   }

   NO* pAnterior = l->cabeca;

   // p nao e NULL e nao chegou na posicao
   while ( (pAnterior->prox != NULL) && (item.chave > pAnterior->prox->item.chave) )
      pAnterior = pAnterior->prox;
    
   // Laco parou porque foi encontrado um valor igual, logo nao pode inserir
   if (pAnterior->prox != NULL && (item.chave == pAnterior->prox->item.chave))
      return false;

   // Cria um novo No no meio ou no final da lista
   pAnterior->prox = criarNo(item, pAnterior->prox);
   l->tamanho++;

   return true; // conseguiu inserir com sucesso
}


// Exibicao da lista
void exibirLista(LISTA *l)
{
   NO *p = l->cabeca;
   while (p)
   {
      printf("(%d)", p->item.chave);
      p = p->prox;
   }
}


void imprimirLista(LISTA *l)
{
   printf("Tamanho = %d\n", tamanho(l));
   exibirLista(l);
   printf("\n");
}


void lerItens(LISTA *l)
{
   int n;
   scanf("%d", &n);

   // insere os valores n pares chave
   ITEM item;
   for (int i = 0; i < n; i++)
   {
      scanf("%d", &item.chave);
      inserirNaOrdem(item, l);
   }
}


//////////////////////////////////////////////////////////////

/*
 Objetivo: Inverte a lista encadeada ajustando apenas os apontadores,
           ou seja, evitando copiar os dados para uma nova lista.
*/
void inverter(LISTA *l)
{
  if(l->cabeca == NULL || l->tamanho <= 1) return;

  NO * NOAtual = l->cabeca;
  NO * NOAnterior = NULL; 

  NO * NOProximo = NULL;

  while(NOAtual != NULL) {
    NOProximo = NOAtual->prox;
    NOAtual->prox = NOAnterior;
    NOAnterior = NOAtual;
    NOAtual = NOProximo;
  }

  l->cabeca = NOAnterior;
}

//////////////////////////////////////////////////////////////


int main()
{
  LISTA l;
  ITEM item;

  inicializar(&l);

  lerItens(&l);
  imprimirLista(&l);

  inverter(&l);
  imprimirLista(&l);

  inverter(&l);
  imprimirLista(&l);

  destruir(&l);
  return 0;
}