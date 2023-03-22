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
| Objetivos: Analisa se a arvore passada pode ser considerada uma arvore binaria
|            de busca. Para isso, percorre a arvore e analisa se os nos estao 
|            dispostos na ordem crescente das chaves, seguindo o caminhamento 
|            central (LNR).
*/
bool eBinariaBusca(ARVORE_BINARIA *arvore)
{
  if(vazia(arvore)) return true;

  if(!vazia(arvore->esq) && arvore->esq->item.chave >= arvore->item.chave) return false;
  if(!vazia(arvore->dir) && arvore->dir->item.chave <= arvore->item.chave) return false;
  if(!eBinariaBusca(arvore->esq) || !eBinariaBusca(arvore->dir)) return false;

  return true;
}


/////////////////////////////////////////////////////

/* 
  Objetivo: Mostra na tela uma linha informando se a arvore passada e uma
            arvore binaria de busca.
*/
void imprimirSeEArvBinBusca(ARVORE_BINARIA *arv) {
   if (eBinariaBusca(arv))
      printf("E binaria de busca\n");
   else
      printf("Nao e binaria de busca\n");
}

/////////////////////////////////////////////////////

int main()
{
   ARVORE_BINARIA *arv1 = NULL;
   inicializar(arv1);
   imprimirSeEArvBinBusca(arv1);

   ITEM item;
   item.chave = 4;
   criarNo(item, &arv1); // cria o no Raiz
   imprimirSeEArvBinBusca(arv1);

   item.chave = 2;
   adicionarFilho(item, NoEsquerdo, arv1);
   imprimirSeEArvBinBusca(arv1);

   item.chave = 7;
   adicionarFilho(item, NoDireito, arv1);
   imprimirSeEArvBinBusca(arv1);
   /*
                 4
              2     7
   */

   item.chave = 1;
   adicionarFilho(item, NoEsquerdo, arv1->esq);
   imprimirSeEArvBinBusca(arv1);

   item.chave = 3;
   adicionarFilho(item, NoDireito, arv1->esq);
   imprimirSeEArvBinBusca(arv1);

   item.chave = 5;
   adicionarFilho(item, NoEsquerdo, arv1->dir);
   imprimirSeEArvBinBusca(arv1);

   item.chave = 6;
   adicionarFilho(item, NoDireito, arv1->dir->esq);
   imprimirSeEArvBinBusca(arv1);   
/*
                                4
                             2     7
                            1 3   5
                                   6
*/

   item.chave = 1;
   adicionarFilho(item, NoEsquerdo, arv1->esq->esq);
   imprimirSeEArvBinBusca(arv1);
/*
                                 4
                            2        7
                          1   3    5
                        1           6
*/

   item.chave = 7;
   adicionarFilho(item, NoDireito, arv1->dir);
   imprimirSeEArvBinBusca(arv1);

/*
                                 4
                            2        7
                          1   3    5   7
                        1           6
*/

   disposeArvore(arv1);
   return 0;
}
