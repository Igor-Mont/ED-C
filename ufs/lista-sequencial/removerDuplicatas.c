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


// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
	l->tamanho = 0;
}


/* 
  Objetivo: Insere o item passado como parametro na lista passada.
            Se o tamanho da lista ja for igual ao tamanho maximo,
            a funcao Inserir retorna false.
*/
bool inserir(ITEM item, LISTA *l){
	if (l->tamanho == MAX) 
		return false; // lista cheia
    else
	   l->itens[l->tamanho++] = item;
	return true;
}


/*
  Objetivo: Remove o item cuja chave coincide com o parametro chave
            passado. Caso nao haja um item com essa chave, retorna
            false. Se o item foi removido, retorna true.
*/
bool remover(TIPOCHAVE chave, LISTA *l)
{
	int i, j;
	for (i = 0; i < l->tamanho; i++)
		if (chave == l->itens[i].chave) 
		{
	        for (j = i; j < l-> tamanho - 1; j++)
               l->itens[j] = l->itens[j + 1];

			l->tamanho--;
			return true; // achou
		}	
	return false; // nao achou
}


/*
  Objetivo: Altera os dados de um item existente na lista passada
            de forma que fique igual ao do item passado como parametro.
            Se o item for encontrado e alterado, retorna true. Caso
            contrario, retorna false.
*/
bool alterar(ITEM item, LISTA *l)
{
	//int i;
	for (int i = 0; i < l->tamanho; i++)
		if (item.chave == l->itens[i].chave) 
		{
			l->itens[i] = item;
			return true; // achou
		}	
	return false; // nao achou
}


/*
  Objetivo: Procura na lista usando a chave passada. Caso encontre,
            a funcao returna true e Item contem o Item obtido.
            Caso contrario, a funcao retorna false e Item contem NULL.

*/
bool obter(TIPOCHAVE ch, ITEM * item, LISTA l)
{
	int i;
	for (i = 0; i < l.tamanho; i++)
		if (ch == l.itens[i].chave) 
		{
			*item = l.itens[i];
			return true; // achou
		}	
	item = NULL;
	return false; // nao achou
}


// Retornar o tamanho da lista sequencial
int tamanho(LISTA l)
{
	return l.tamanho;
}


// Retorna true se a lista esta cheia (Tamanho = MAX)
bool cheia(LISTA l)
{
	return tamanho(l) == MAX;
}


// Retorna true se a lista esta vazia (Tamanho = 0)
bool vazia(LISTA l)
{
	return tamanho(l) == 0;
}


// Retornar o n-esimo elemento da lista sequencial
// Pre-condicao: 0 <= n < tamanho 
ITEM enesimo(int n, LISTA l)
{
    if (n >= 0 && n < l.tamanho) 
        return (l.itens[n]);
    else 
        exit(EXIT_FAILURE);
}


/*
  Objetivo: Inserir o item passado como parametro na posicao i da lista.
            Caso a lista nao esteja cheia e a posicao seja valida, o item
            sera inserido e a funcao retorna true. Caso contrario, a funcao
            retorna false para indicar que o item nao foi inserido.
 */
bool inserirNaPos(ITEM item, int i, LISTA *l)
{
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


// Exibicao da lista sequencial
void exibirLista(LISTA l)
{
    int i;
	for (i = 0; i < l.tamanho; i++)
		printf("(%d,%s)", l.itens[i].chave, l.itens[i].valor);
}


// Destruicao da lista sequencial
void destruir(LISTA *l)
{
	l->tamanho = 0;
}


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



//////////////////////////////////////////////////////////

/*
  Objetivo: Remove itens (nos) com chaves duplicadas na lista. 
  Sera mantida a chave que tiver o menor indice no array de Itens.
  A funcao deve retornar quantos valores duplicados foram removidos.
 */
int removerDuplicados(LISTA *l)
{
  LISTA aux;
  inicializar(&aux);

  ITEM item;
  for(int i = 0; i < tamanho(*l); i++) {
    if(!obter(l->itens[i].chave, &item, aux)) {
      aux.itens[aux.tamanho++] = l->itens[i];
    }
  }
  int duplicados = l->tamanho - aux.tamanho;

  *l = aux;
  
  return duplicados;
}


/////////////////////////////////////////////////////////////////////

int main(){
   LISTA l;
	
   inicializar(&l);	
   lerItens(&l);

   printf("Tamanho l = %d\n", tamanho(l));
   exibirLista(l);
   printf("\n");

   int duplicados = removerDuplicados(&l);
   printf("Tamanho l = %d\n", tamanho(l));
   printf("Duplicados em l = %d\n", duplicados);

   exibirLista(l);
   printf("\n");
    
   return 0;
}