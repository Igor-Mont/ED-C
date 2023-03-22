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
    NO* inicio;
    NO* fim;
    int tamanho;
} FILA;



// Inicializa a fila deixando-a pronta para ser utilizada.
void inicializar(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}


// Cria um novo no com o item passado e tendo NULL como prox
NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


// Retornar o tamanho da fila
int tamanho(FILA *f)
{
    return f->tamanho;
}


// Nunca estara cheia pois o limite e a memoria disponivel
bool cheia(FILA *f)
{
    return false;
}


// Retorna true se a filha esta vazia (Tamanho = 0)
bool vazia(FILA *f)
{
    return tamanho(f) == 0;
}


/* 
  Objetivo: Insere um item no final da fila.
*/
bool inserir(ITEM item, FILA *f)
{
    NO* pNovo = criarNo(item, NULL);
    if (f->inicio == NULL)    //  inicio == NULL
       f->inicio = pNovo;  // A lista esta vazia
    else
       f->fim->prox = pNovo;
    f->fim = pNovo;
    f->tamanho++;
    return true;
}



/*
  Objetivo: Acessa a frente da Fila e atribui ao parâmetro item, sem afetar
            o estado da Fila. Retorna true quando algum item foi obtido.
*/
bool frente(ITEM *item, FILA *f)
{
   if (vazia(f))
      return false; // Nao achou

   *item = f->inicio->item;
   return true;
}



/*
  Objetivo: Retira o No do inicio da Fila (frente) e atribui
            ao parametro item.
            Retorna true quando algum item foi retornado.
*/
bool retirar(ITEM *item, FILA *f)
{
   if (frente(item, f))
   {
       NO* pFrente = f->inicio;    // Guarda o endereco do NO retirado
       f->inicio = pFrente->prox;  // Ajusta o inicio da fila

       if (f->inicio == NULL)
          f->fim = NULL;  // Fila esta vazia, logo fim deve ser NULL

       f->tamanho--;
       free(pFrente);
       return true;
   } 
   else
      return false;   // Nao retirou ja que esta nao tem nada na frente
}


// Exibicao da fila
void exibir(FILA *f)
{
    NO* pAtual = f->inicio;
    while (pAtual)  // pAtual != NULL
    {
        printf("(%d,%s)", pAtual->item.chave, pAtual->item.valor);
        pAtual = pAtual->prox;
    }
}


// Liberacao das variaveis dinamicas dos nos da lista, iniciando da cabeca
void destruir(FILA *f)
{
    NO* atual = f->inicio;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    f->inicio = NULL; // ajusta o inicio da lista (vazia)
    f->fim = NULL;    // ajusta o fim da lista (vazia)
    f->tamanho = 0;
}


/////////////////////////////////////////////////////

int main(){
    
	FILA f;
	
	inicializar(&f);
	
	// insere os valores com chaves de 1 a 5
	ITEM item;
	for (int i = 1; i <= 5; i++)
  {
		 item.chave = i;
     printf("Digite o valor para a chave [%d]: ", i);
     scanf("%s", item.valor);
     inserir(item, &f);
	}
	printf("Tamanho = %d\n", tamanho(&f));
	exibir(&f);
	printf("\n");

  for (int i = 1; i < 4; i++)
     if (retirar(&item, &f))
        printf("Retirou da Fila (%d,%s)\n", item.chave, item.valor);
     else
        printf("Nao retirou da Fila\n");

  printf("Tamanho = %d\n", tamanho(&f));
 	exibir(&f);
	printf("\n");

  if (frente(&item, &f))
      printf("Frente (%d,%s)\n", item.chave, item.valor);
  else
      printf("Nao tem frente\n");

  for (int i = 1; i < 4; i++)
     if (retirar(&item, &f))
        printf("Retirou da Fila (%d,%s)\n", item.chave, item.valor);
     else
        printf("Nao retirou da Fila\n");

  printf("Tamanho = %d\n", tamanho(&f));
  exibir(&f);
  printf("\n");

  destruir(&f);
	getchar();
	return 0;
}
