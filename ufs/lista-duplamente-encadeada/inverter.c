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


/* 
  Objetivo: Insere o item passado como parametro na lista passada.
            A insercao ocorre no inicio da lista, ou seja, na cabeca.
            Nao veririca se o item existe na lista, ou seja, permite
            duplicacao.
*/
bool inserir(ITEM item, LISTA *l){
    NO* pNovo = criarNo(item, NULL, l->cabeca);
    l->tamanho++;

    if (l->cabeca) // cabeca != NULL
       l->cabeca->ant = pNovo;  // ajusta o apontador para o anterior na antiga cabeca
    
    l->cabeca = pNovo;
    
    if (l->cauda == NULL) // se nao tinha cauda, o novo no estara tambem na cauda 
       l->cauda = pNovo;

    return true;
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
 Objetivo: Inverte a lista encadeada ajustando apenas os apontadores,
           ou seja, evitando copiar os dados para uma nova lista.
*/
void inverter(LISTA *l)
{
    if (tamanho(l) <= 1) return;

    NO* NOatual = l->cabeca;
    NO* aux = NULL;

    while(NOatual) {
        aux = NOatual->ant; // 1
        NOatual->ant = NOatual->prox; // = 3
        NOatual->prox = aux; // 3 = 1
        NOatual = NOatual->ant; // 2 = 3
    }
    

    aux = l->cabeca;
    l->cabeca = l->cauda;
    l->cauda = aux;
}

/////////////////////////////////////////////////////

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


//////////////////////////////////////////////////////////////

int main(){
  LISTA l;
  ITEM item;

  inicializar(&l);

  lerItens(&l);
  imprimirLista(&l, true);   // cabeca => cauda
  
  inverter(&l);
  imprimirLista(&l, true);  // cabeca => cauda
  imprimirLista(&l, false); // cauda => cabeca

  destruir(&l);
  return 0;
}