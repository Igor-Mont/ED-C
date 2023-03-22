#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
	char valor[100];
} ITEM;

typedef struct{
	ITEM itens[MAX];
	int tamanho;
} LISTA;


void inicializar(LISTA *l) {
	l->tamanho = 0;
}

// Insere o item passado como parametro na lista passada.
bool inserir(ITEM item, LISTA *l) {
	if (l->tamanho == MAX) 
		return false; // lista cheia
    else
	   l->itens[l->tamanho++] = item;
	return true;
}


// Remove o item cuja chave coincide com o parametro chave.
bool remover(TIPOCHAVE chave, LISTA *l) {
	int i, j;
	for (i = 0; i < l->tamanho; i++)
		if (chave == l->itens[i].chave) 
		{
	        for (j = i; j < l-> tamanho - 1; j++)
               l->itens[j] = l->itens[j + 1];

			l->tamanho--;
			return true;
		}	
	return false;
}


// Altera os dados de um item existente na lista.
bool alterar(ITEM item, LISTA *l) {
	for (int i = 0; i < l->tamanho; i++)
		if (item.chave == l->itens[i].chave) 
		{
			l->itens[i] = item;
			return true; 
		}	
	return false;
}

// Procura na lista usando a chave passada.
bool obter(TIPOCHAVE ch, ITEM * item, LISTA l) {
	int i;
	for (i = 0; i < l.tamanho; i++)
		if (ch == l.itens[i].chave) 
		{
			*item = l.itens[i];
			return true;
		}	
	item = NULL;
	return false;
}


// Retorna o tamanho da lista sequencial
int tamanho(LISTA l) {
	return l.tamanho;
}


// Retorna true se a lista esta cheia (Tamanho = MAX)
bool cheia(LISTA l) {
	return tamanho(l) == MAX;
}


// Retorna true se a lista esta vazia (Tamanho = 0)
bool vazia(LISTA l) {
	return tamanho(l) == 0;
}

// Retorna o n-esimo elemento da lista sequencial
ITEM enesimo(int n, LISTA l) {
    if (n >= 0 && n < l.tamanho) 
        return (l.itens[n]);
    else 
        exit(EXIT_FAILURE);
}


// Insere o item passado como parametro na posicao i da lista.
bool inserirNaPos(ITEM item, int i, LISTA *l) {
	int j;
	// A posicao tem que estar entre 0 e MAX-1 e ate o tamanho atual
	if ((tamanho(*l) >= MAX) || (i < 0) || (i > tamanho(*l)))
		return false; // lista cheia ou indice invalido
	// Se for inserido no meio, e necessario abrir espaco para o item
	if ((tamanho(*l) > 0) && (i < tamanho(*l)))
		for (j = l->tamanho; j >= (i+1); j--)
			l->itens[j] = l->itens[j-1];
	l->itens[i] = item;
	l->tamanho++;
	return true;
}


// Exibção da lista sequencial
void exibirLista(LISTA l) {
  int i;
	for (i = 0; i < l.tamanho; i++)
		printf("(%d,%s)", l.itens[i].chave, l.itens[i].valor);
}


// Destruição da lista sequencial
void destruir(LISTA *l) {
	l->tamanho = 0;
}


void lerItens(LISTA *l) {
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

// Inverte a lista.
void inverter(LISTA *l) {
	if(vazia(*l)) return;

	LISTA aux;
	inicializar(&aux);

	int tam = tamanho(*l);
	int j = 0;

	for(int i = tam - 1; i >= 0; i--) {
		aux.itens[j] = l->itens[i];
		aux.tamanho++;
		j++;
	}

	*l = aux;
}

int main(){
	LISTA l;
	
	inicializar(&l);	
    lerItens(&l);
	printf("Tamanho l = %d\n", tamanho(l));
    exibirLista(l);
	printf("\n");

    inverter(&l);

    printf("Tamanho l = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");

    // Lendo mais itens para vefificar se a lista esta correta
    lerItens(&l);
    printf("Tamanho l = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");
    
	return 0;
}