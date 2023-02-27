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


/*
  Objetivo: Procura na lista usando a chave passada. Caso encontre,
            a funcao returna um apontador para o NO na lista.
            Caso contrario, a funcao retorna NULL.

*/
NO* obterNo(TIPOCHAVE ch, LISTA *l)
{
    NO* p = l->cabeca;
    while (p)  // p != NULL
    {
        if (p->item.chave == ch)
            return p;
        p = p->prox;
    }
    return NULL; // Nao achou
}


// Retornar o tamanho da lista
int tamanho(LISTA *l)
{
    return l->tamanho;
}


// Nunca estara cheia pois o limite e a memoria disponivel
bool cheia(LISTA *l)
{
    return false;
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


/*
  Objetivo: Remove o item cuja chave coincide com o parametro chave
            passado. Caso nao haja um item com essa chave, retorna
            false. Se o item foi removido, retorna true.
*/
bool remover(TIPOCHAVE chave, LISTA *l)
{
   NO* pAtual = obterNo(chave, l);
   if (pAtual != NULL)
   {
      if (pAtual == l->cabeca)  // ajuda a cabeca para o próximo do nó removido
         l->cabeca = pAtual->prox;

      if (pAtual == l->cauda)  // ajusta a cauda para o anterior do nó removido
         l->cauda = pAtual->ant;

      if (pAtual->prox != NULL)  // ajusta o apontador ant do próximo nó
         pAtual->prox->ant = pAtual->ant;

      if (pAtual->ant != NULL)  // ajusta o apontador prox do nó anterior
         pAtual->ant->prox = pAtual->prox;

      free(pAtual);
      l->tamanho--;
      return true;        
   }

   return false;  // nao removeu
}


/*
  Objetivo: Procura na lista usando a chave passada. Caso encontre,
            a funcao returna true e Item contem o Item obtido.
            Caso contrario, a funcao retorna false e Item contem NULL.

*/
bool obter(TIPOCHAVE ch, ITEM *item, LISTA *l)
{
   NO* pAtual = obterNo(ch, l);
   if (pAtual != NULL)
   {
      *item = pAtual->item;
      return true;
   }
   return false;  // nao achou
}


/*
  Objetivo: Altera os dados de um item existente na lista passada
            de forma que fique igual ao do item passado como parametro.
            Se o item for encontrado e alterado, retorna true. Caso
            contrario, retorna false.
*/
bool alterar(ITEM item, LISTA *l)
{
   NO* pAtual = obterNo(item.chave, l);
   if (pAtual != NULL)
   {
      pAtual->item = item;
      return true;
   }
   return false;  // nao achou
}


// Retornar o n-esimo elemento da lista
// Pre-condicao: 0 <= n < tamanho 
ITEM enesimo(int n, LISTA *l)
{
    NO* p = l->cabeca;
    int i = 0;
    while (p && (i < n))   // p != NULL e nao chegou a posicao n
    {
        p = p->prox;
        i++;
    }

    if (p && (i == n))
       return p->item;  // existe um n-esimo e p aponta para ele
    else
       exit(EXIT_FAILURE); // nao existe um n-esimo
}


// Exibicao da lista
void exibirLista(LISTA *l)
{
    NO* p = l->cabeca;
    while (p)
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
    l->cabeca = NULL; // ajusta a cabeca da lista (vazia)
    l->cauda = NULL; // ajusta a cauda da lista (vazia)
}


/////////////////////////////////////////////////////

int main(){
    
	LISTA l;
	
	inicializar(&l);
	
	// insere os valores de 0 a 4 na lista
	ITEM item;
	for (int i = 0; i < 5; i++)
    {
		item.chave = i;
        printf("Digite o valor para a chave [%d]: ", i);
        scanf("%s", item.valor);
        inserir(item, &l);
	}
	printf("Tamanho = %d\n", tamanho(&l));
	exibirLista(&l);
	printf("\n");

	// Testa a busca por uma chave existente
	TIPOCHAVE chave = 2;
	if (obter(chave, &item, &l))
	   printf("Achou chave: %d\n", chave);

	//Testa a busca por uma chave inexistente
    chave = 10;
    if (!obter(chave, &item, &l))
       printf("Nao achou chave: %d\n", chave);
	
	// Altera o valor guardado em um item com chave existente
    item.chave = 3;
    printf("Digite o novo valor associado a chave [%d]: ", item.chave);
    scanf("%s", item.valor);

    // Altera o valor e verifica se teve sucesso
    if (alterar(item, &l))
    	printf("Item %d alterado com sucesso.\n", item.chave);
    else
    	printf("Erro ao alterar o item com chave %d.\n", item.chave);

    printf("O novo valor armazenado foi: %s\n", enesimo(1,&l).valor);

    // Testa a remocao de uma chave inexistente
    chave = 10;
    if (remover(chave, &l))
        printf("Erro: Item com chave %d nao removido, mesmo nao estando na lista.\n", chave);
    else
        printf("Item %d nao foi removido pois nao esta na lista.\n", chave);

    // Testa a remocao de uma chave na cabeca da lista
    chave = 4;
    if (remover(chave, &l))
        printf("Item com chave %d removido com sucesso.\n", chave);
    else
        printf("Erro: item com chave %d nao foi removido da lista.\n", chave);

    // Testa a remocao de uma chave na cauda da lista
    chave = 0;
    if (remover(chave, &l))
        printf("Item com chave %d removido com sucesso.\n", chave);
    else
        printf("Erro: item com chave %d nao foi removido da lista.\n", chave);

    // Testa a remocao de uma chave no meio da lista
    chave = 2;
    if (remover(chave, &l))
        printf("Item com chave %d removido com sucesso.\n", chave);
    else
        printf("Erro: item com chave %d nao foi removido da lista.\n", chave);

 	exibirLista(&l);
	printf("\n");

  destruir(&l);
	getchar();
	return 0;
}