#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    char valor[100];
} ITEM;

typedef struct{
    ITEM itens[MAX];
    int tamanho;
} PILHA;


// Inicializa a pilha deixando-a pronta para ser utilizada.
void inicializar(PILHA *p)
{
    p->tamanho = 0;
}


// Retornar o tamanho da pilha
int tamanho(PILHA *p)
{
    return p->tamanho;
}


// Se o tamanho atual e igual a MAX, ja esta cheia
bool cheia(PILHA *p)
{
    return tamanho(p) == MAX;
}


// Retorna true se a pilha esta vazia (Tamanho = 0)
bool vazia(PILHA *p)
{
    return tamanho(p) == 0;
}


/*
  Objetivo: Acessa o topo da Pilha e atribui ao parâmetro item, sem afetar
            o estado da Pilha. Retorna true quando algum item foi obtido.
*/
bool topo(ITEM *item, PILHA *p)
{
  if(p->tamanho > 0) {
    *item = p->itens[p->tamanho - 1];
    return true;
  }

  return false;
}


/* 
  Objetivo: Empilha um Item no topo da pilha.
            Retorna true quando o item foi empilhado com sucesso.
*/
bool empilhar(ITEM item, PILHA *p)
{
  if(p->tamanho < MAX) {
    p->itens[p->tamanho++] = item;
    return true;
  }

  return false;
}


/*
  Objetivo: Retira o Item do Topo da Pilha e atribui ao parametro item.
            Retorna true quando algum item foi desempilhado com sucesso.
*/
bool desempilhar(ITEM *item, PILHA *p)
{
  if(p->tamanho > 0) {
    *item = p->itens[p->tamanho - 1];
    p->tamanho--;
    return true;
  }
  
  return false;
}


// Exibicao da pilha
void exibir(PILHA *p)
{
    int i;
    for (i = tamanho(p) - 1; i >= 0; i--)
        printf("(%d,%s)", p->itens[i].chave, p->itens[i].valor);

}


// Destruicao da pilha
void destruir(PILHA *p)
{
    p->tamanho = 0;
}

/////////////////////////////////////////////////////

void lerItens(PILHA *p)
{
    int n;
    scanf("%d", &n);

    // insere os valores n pares chave,valor
    ITEM item;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item.chave);
        scanf("%s", item.valor);
        empilhar(item, p);
    }
}

void retirar(PILHA *p, int n)
{
  ITEM item;
  for (int i = 0; i < n; i++)
     if (desempilhar(&item, p))
        printf("Desempilhado (%d,%s)\n", item.chave, item.valor);
     else
        printf("Nao desempilhou\n");
}


void imprimir(PILHA *p)
{
  printf("Tamanho = %d\n", tamanho(p));
  exibir(p);
  printf("\n");

}

/////////////////////////////////////////////////////

int main(){
    
	PILHA p;
	ITEM item;
  inicializar(&p);
  int n;
	
  // Obtem os itens iniciais e imprime a situacao
  lerItens(&p);
  imprimir(&p);

  // Le a quantidade de itens a serem desempilhados e desempilha 
  scanf("%d", &n);
  retirar(&p, n);
  imprimir(&p);

  // Mostra o topo da pilha, se existir 
  if (topo(&item, &p))
      printf("Topo (%d,%s)\n", item.chave, item.valor);
  else
      printf("Nao tem topo\n");

  // Obtem mais itens e imprime a situacao
  lerItens(&p);
  imprimir(&p);

  // Continua com a retirada de mais itens
  scanf("%d", &n);
  retirar(&p, n);
  imprimir(&p);

  destruir(&p);
	getchar();
	return 0;
}
