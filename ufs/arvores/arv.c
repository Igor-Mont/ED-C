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

int main()
{
   ARVORE_BINARIA *arv = NULL;
   inicializar(arv);

   ITEM item;
   item.chave = 1;
   criarNo(item, &arv); // cria o no Raiz
   
   item.chave = 2;
   adicionarFilho(item, NoEsquerdo, arv);
   item.chave = 5;
   adicionarFilho(item, NoDireito, arv);
   /*
                 1
              2     5
   */

   printf("inOrdem: ");
   inOrdem(arv, visite);
   printf("\n");
   printf("inOrdem: ");
   inOrdem(arv, visite);
   printf("\n");
   printf("posOrdem: ");
   posOrdem(arv, visite);
   printf("\n");
   printf("preOrdem: ");
   preOrdem(arv, visite);
   printf("\n");

   item.chave = 3;
   adicionarFilho(item, NoEsquerdo, arv->esq);
   item.chave = 4;
   adicionarFilho(item, NoDireito, arv->esq);

   item.chave = 6;
   adicionarFilho(item, NoEsquerdo, arv->dir);
   item.chave = 7;
   adicionarFilho(item, NoDireito, arv->dir->esq);
  
/*
                                1
                             2     5
                            3 4   6
                                   7
*/

   printf("preOrdem: ");
   preOrdem(arv, visite); // Imprime: (1)(2)(3)(4)(5)(6)(7)
   printf("\n");

   deslocar(NoDireito, &arv);  // Vai para o No 5
   printf("Esperando 5, obtido %d\n", arv->item.chave);   
   printf("Existe no esquerdo = %s\n", existeNo(NoEsquerdo, arv) ? "sim" : "nao");  // Deve ser TRUE
   printf("Existe no direito  = %s\n", existeNo(NoDireito, arv) ? "sim" : "nao");   // Deve ser FALSE

   deslocar(NoEsquerdo, &arv);  // Vai para 6
   deslocar(NoDireito, &arv);   // Vai para 7
   printf("Esperando 7, obtido %d\n", arv->item.chave);

   deslocar(NoPai, &arv);  // Vai para 6
   printf("Esperando 6, obtido %d\n", arv->item.chave);

   deslocar(NoRaiz, &arv); // Vai para 1
   printf("Esperando 1, obtido %d\n", arv->item.chave);

   
   // Partindo da raiz, desce para o filho direito e executa um deltree
   deslocar(NoDireito, &arv);
   deltree(&arv);

/*
                              1
                             2
                            3 4
*/

   printf("preOrdem: ");
   preOrdem(arv, visite); // Imprime: (1)(2)(3)(4)
   printf("\n");

   disposeArvore(arv);
   return 0;
}