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
    NO* topo;
    int tamanho;
} PILHA;


// Inicializa a pilha deixando-a pronta para ser utilizada.
void inicializar(PILHA *p)
{
    p->topo = NULL;
    p->tamanho = 0;
}


// Cria um novo no com o item passado e tendo NULL como prox
NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


// Retornar o tamanho da pilha
int tamanho(PILHA *p)
{
    return p->tamanho;
}


// Nunca estara cheia pois o limite e a memoria disponivel
bool cheia(PILHA *p)
{
    return false;
}


// Retorna true se a pilha esta vazia (Topo = NULL)
bool vazia(PILHA *p)
{
    return p->topo == NULL;
}


/* 
  Objetivo: Empilha um No no topo da pilha.
            Coloca na cabeca de uma lista encadeada.
*/
bool empilhar(ITEM item, PILHA *p)
{
    p->topo = criarNo(item, p->topo);
    p->tamanho++;
    return true;
}


/*
  Objetivo: Retira o No do Topo da Pilha e atribui ao parametro item.
            Retorna true quando algum item foi retornado.
*/
bool desempilhar(ITEM *item, PILHA *p)
{
   if (vazia(p))
      return false; // Nao desempilhou

   NO* pDesempilhado = p->topo;
   *item = pDesempilhado->item;

   // Muda o topo da lista para ser o NO abaixo do Topo atual  
   p->topo = pDesempilhado->prox;
   p->tamanho--;
   free(pDesempilhado);
   return true;
}



/*
  Objetivo: Acessa o topo da Pilha e atribui ao parâmetro item, sem afetar
            o estado da Pilha. Retorna true quando algum item foi obtido.
*/
bool topo(ITEM *item, PILHA *p)
{
   if (vazia(p))
      return false; // Nao achou

   *item = p->topo->item;
   return true;
}


// Exibicao da pilha
void exibir(PILHA *p)
{
    NO* pAtual = p->topo;
    while (pAtual)  // pAtual != NULL
    {
        printf("(%d,%s)", pAtual->item.chave, pAtual->item.valor);
        pAtual = pAtual->prox;
    }
}


// Liberacao das variaveis dinamicas dos nos da lista, iniciando da cabeca
void destruir(PILHA *p)
{
    NO* atual = p->topo;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    p->topo = NULL; // ajusta inicio da lista (vazia)
    p->tamanho = 0; // zera o tamanho
}


/////////////////////////////////////////////////////

int main(){
    
	PILHA p;
	
	inicializar(&p);
	
	// insere os valores com chaves de 1 a 5
	ITEM item;
	for (int i = 1; i <= 5; i++)
  {
		 item.chave = i;
     printf("Digite o valor para a chave [%d]: ", i);
     scanf("%s", item.valor);
     empilhar(item, &p);
	}
	printf("Tamanho = %d\n", tamanho(&p));
	exibir(&p);
	printf("\n");

  for (int i = 1; i < 4; i++)
     if (desempilhar(&item, &p))
        printf("Desempilhado (%d,%s)\n", item.chave, item.valor);
     else
        printf("Nao desempilhou\n");

  printf("Tamanho = %d\n", tamanho(&p));
 	exibir(&p);
	printf("\n");

  if (topo(&item, &p))
      printf("Topo (%d,%s)\n", item.chave, item.valor);
  else
      printf("Nao tem topo\n");

  for (int i = 1; i < 4; i++)
     if (desempilhar(&item, &p))
        printf("Desempilhado (%d,%s)\n", item.chave, item.valor);
     else
        printf("Nao desempilhou\n");

  printf("Tamanho = %d\n", tamanho(&p));
  exibir(&p);
  printf("\n");

  destruir(&p);
	getchar();
	return 0;
}
