#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef struct {
    TIPOCHAVE chave;
//    char valor[100];
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
} ARVORE_BINARIA;


// Inicializa a arvore binaria deixando-a pronta para ser utilizada.
void inicializar(ARVORE_BINARIA *arvore)
{
    arvore = NULL;
}


// Retorna true se a arvore esta vazia (igual a NULL)
bool vazia(ARVORE_BINARIA *arvore)
{
    return arvore == NULL;
}


// Cria um novo no usando o apontador arvore passado contendo o item,
// os apontadores para o pai e para os filhos contendo NULL
void criarNo(ITEM item, ARVORE_BINARIA **arvore)
{
    if (!vazia(*arvore))
    {
       printf("ERRO: O no deve estar vazio para ser criado.");
       exit(EXIT_FAILURE);
    }

    *arvore = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));
    (*arvore)->item = item;
    (*arvore)->pai = NULL;
    (*arvore)->esq = NULL;
    (*arvore)->dir = NULL;
}


// Testa se o No indicado por Direcao a partir de arv existe
bool existeNo(DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;

   if (direcao == NoRaiz)
      return true;
   
   if (direcao == NoPai)
      return !vazia(arvore->pai);

   if (direcao == NoEsquerdo)
      return !vazia(arvore->esq);

   if (direcao == NoDireito)
      return !vazia(arvore->dir);

   return false;
}


// Deslocar o apontador Arvore para o No indicado por Direcao
void deslocar(DIRECAO direcao, ARVORE_BINARIA **arvore)
{
   if (direcao == NoRaiz)
      while (existeNo(NoPai, *arvore))
         *arvore = (*arvore)->pai;

   if (direcao == NoPai)
      *arvore = (*arvore)->pai;

   if (direcao == NoEsquerdo)
      *arvore = (*arvore)->esq;

   if (direcao == NoDireito)
      *arvore = (*arvore)->dir;
}


/*
  Objetivo: O parametro item recebe o item contido no No apontado por Arvore.
            Caso tenha sucesso, retorna true. Caso contrário, false.
*/
bool obterItem(ITEM *item, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;
  
   *item = arvore->item;
   return true;
}


/*
  Objetivo: Altera o valor do item armazenado no No da Arvore.
            Caso tenha sucesso, retorna true. Caso contrário, false.
*/
bool alterarItem(ITEM item, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;
  
   arvore->item = item;
   return true;
}



// Cria um filho no NO apontado por Arvore na direcao informada
bool adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore) || (direcao == NoPai) || (direcao == NoRaiz) || existeNo(direcao, arvore))
     return false;  // Criacao ilegal de um filho

   if (direcao == NoEsquerdo)
   {
       criarNo(item, &(arvore->esq));
       arvore->esq->pai = arvore;
   }
   else
   {
       criarNo(item, &(arvore->dir));
       arvore->dir->pai = arvore;
   }
   return true;
}



// Desaloca da memoria toda a arvore
void disposeArvore(ARVORE_BINARIA *arvore)
{
   if (!vazia(arvore))
   {
      disposeArvore(arvore->esq);
      disposeArvore(arvore->dir);
      free(arvore);
   }
}


/*
| Objetivos: Desaloca da memoria arvore e seus descendentes, atualizando, se
|            necessario, o apontador do pai dessa arvore ou atribuindo o valor
|            NULL a arvore, quando for a raiz.
*/
void deltree(ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pTemp = *arvore;

   /* 
     Testa se Arvore tem pai. Caso tenha, arvore se desloca para ele e pTemp
     continua apontando para o inicio da arvore a ser deletada, depois a
     arvore e apagada e o apontador do pai e atualizado com NULL. Caso Arvore
     nao tenha pai, a arvore e eliminada usando pTemp e arvore recebe NULL */
   if (existeNo(NoPai, *arvore))
   {
      deslocar(NoPai, arvore);
      disposeArvore(pTemp);
      if ((*arvore)->esq == pTemp)
         (*arvore)->esq = NULL;
      else
         (*arvore)->dir = NULL;
   }
   else
   {
      disposeArvore(pTemp);
      arvore = NULL;
   }
}


/*
| Objetivos: Percorre a arvore, visitando primeiro a raiz, depois a subarvore
|            esquerda e por ultimo a subarvore direita.
*/
void preOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      visite(arvore);
      preOrdem(arvore->esq, visite);
      preOrdem(arvore->dir, visite);
   }
}


/*
| Objetivos: Percorre a arvore, visitando primeiro a subarvore esquerda,
|            depois a raiz e por ultimo a subarvore direita.
*/
void inOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      inOrdem(arvore->esq, visite);
      visite(arvore);
      inOrdem(arvore->dir, visite);
   }
}


/*
| Objetivos: Percorre a arvore, visitando primeiro a subarvore esquerda,
|            depois subarvore direita e por ultimo a a raiz.
*/
void posOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      posOrdem(arvore->esq, visite);
      posOrdem(arvore->dir, visite);
      visite(arvore);
   }
}


/////////////////////////////////////////////////////
// Visita um NO da arvore, imprimindo o valor da chave
// entre parenteses
void visite(ARVORE_BINARIA *arvore) {
    printf("(%d)", arvore->item.chave);
}


/////////////////////////////////////////////////////

/*
 Objetivo: Retorna true quando os itens sao iguais e false quando
           ha alguma diferenca.
*/
bool itensIguais(ITEM item1, ITEM item2)
{
   return item1.chave == item2.chave;
}


/*
 Objetivo: Dada duas arvores arv1 e arv2, retorna true quando as
           arvores sao exatamente iguais, em conteudo e disposicao.
*/
bool iguais(ARVORE_BINARIA *arv1, ARVORE_BINARIA *arv2)
{
  if(arv1 == NULL && arv2 == NULL) return true;
  if((arv1 == NULL || arv2 == NULL) || (arv1->item.chave != arv2->item.chave)) return false;

  return iguais(arv1->esq, arv2->esq) && iguais(arv1->dir, arv2->dir);
}

/////////////////////////////////////////////////////

// Mostra na tela uma linha informando se as Arvores sao iguais ou diferentes
void saoIguais(ARVORE_BINARIA *arv1, ARVORE_BINARIA *arv2) {
   if (iguais(arv1, arv2))
      printf("Arvores iguais\n");
   else
      printf("Arvores diferentes\n");
}


int main()
{
   ARVORE_BINARIA *arv1 = NULL;
   ARVORE_BINARIA *arv2 = NULL;
   inicializar(arv1);
   inicializar(arv2);
   saoIguais(arv1, arv2); // iguais

   ITEM item;
   item.chave = 1;
   criarNo(item, &arv1); // cria o no Raiz
   saoIguais(arv1, arv2); // diferentes
   criarNo(item, &arv2); // cria o no Raiz   
   saoIguais(arv1, arv2); // iguais

   item.chave = 2;
   adicionarFilho(item, NoEsquerdo, arv1);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoEsquerdo, arv2);
   saoIguais(arv1, arv2); // iguais

   item.chave = 5;
   adicionarFilho(item, NoDireito, arv1);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoDireito, arv2);
   saoIguais(arv1, arv2); // iguais
   /*
                 1
              2     5
   */

   item.chave = 3;
   adicionarFilho(item, NoEsquerdo, arv1->esq);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoEsquerdo, arv2->esq);
   saoIguais(arv1, arv2); // iguais

   item.chave = 4;
   adicionarFilho(item, NoDireito, arv1->esq);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoDireito, arv2->esq);
   saoIguais(arv1, arv2); // iguais

   item.chave = 6;
   adicionarFilho(item, NoEsquerdo, arv1->dir);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoEsquerdo, arv2->dir);
   saoIguais(arv1, arv2); // iguais

   item.chave = 7;
   adicionarFilho(item, NoDireito, arv1->dir->esq);
   saoIguais(arv1, arv2); // diferentes
   adicionarFilho(item, NoDireito, arv2->dir->esq);
   saoIguais(arv1, arv2); // iguais
   
/*
                                1
                             2     5
                            3 4   6
                                   7
*/

   disposeArvore(arv1);
   disposeArvore(arv2);
   return 0;
}