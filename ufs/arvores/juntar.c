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


/////////////////////////////////////////////////////
// Visita um NO da arvore, imprimindo o valor da chave
// entre parenteses
void imprimir(ARVORE_BINARIA *arvore) {
    printf("(%d)", arvore->item.chave);
}

/////////////////////////////////////////////////////


/*
| Objetivos: Retorna true se a chave for encontrada. Neste caso, p
|            aponta para o No. Se a chave nao for encontrada, retorna false
|            e p aponta para o No que seria o seu pai (caso existisse).
*/
bool encontrarChave(TIPOCHAVE chave, ARVORE_BINARIA **p, ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *pAnt = NULL;
   bool achou = false;
   *p = arvore;

   // Laco que fara o deslocamento de p ate que tenha chegado ao local onde
   // deveria estar o No ou tenha o encontrado
   while (!vazia(*p) && !achou)
   {
      pAnt = *p;
      if (chave == (*p)->item.chave)
         achou = true;
      else
      {
         if (chave < (*p)->item.chave)
            deslocar(NoEsquerdo, p);
         else
            deslocar(NoDireito, p);
      }
   }

   // Testa se nao achou a chave na arvore, pois nesse caso p devera estar
   //  apontando para o No que seria seu pai, ou seja, pAnt
   if (!achou)
      *p = pAnt;

   return achou;
}


/*
| Objetivos: Tenta inserir um No na Arvore Binaria de Busca apontada por arvore.
|            Se conseguir, retorna true.
*/
bool inserir(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pPai;
   bool inseriu = true;

   // Se arvore estiver vazia entao so e necessario criar o No, mas se nao
   // estiver, entao sera feita a procura (pela chave) na arvore. Se for achada
   // alguma ocorrencia da chave na arvore (chave duplicada), entao retornara
   // false. Caso contrario item sera adicionado em uma das subarvores de Arvore.
   if (vazia(*arvore))
      criarNo(item, arvore);
   else
   {
      if (encontrarChave(item.chave, &pPai, *arvore))
         inseriu = false;
      else
      {
         if (item.chave < pPai->item.chave)
            adicionarFilho(item, NoEsquerdo, pPai);
         else
            adicionarFilho(item, NoDireito, pPai);
      }
   }
   return inseriu;
}



///////////////////////////////////////////////////////////////////////
// Implemente aqui qualquer funcao adicional que precise


void capturaValores(ARVORE_BINARIA* arv, int* valores, int* posicao) {
    if(arv) {
      capturaValores(arv->esq, valores, posicao);
      valores[(*posicao)++] = arv->item.chave;
      capturaValores(arv->dir, valores, posicao);
    }
}

bool uniaoAux(ARVORE_BINARIA *arv, ARVORE_BINARIA **arvU) {
   if(arv == NULL) return true;
   if(!inserir(arv->item, arvU)) return false;
   return uniaoAux(arv->esq, arvU) && uniaoAux(arv->dir, arvU);
}

bool uniao(ARVORE_BINARIA *arv1, ARVORE_BINARIA *arv2, ARVORE_BINARIA **arvU)
{
  if(arv1 == NULL && arv2 == NULL) return true;
  return uniaoAux(arv1, arvU) && uniaoAux(arv2, arvU);
}


/////////////////////////////////////////////////////

void lerItens(ARVORE_BINARIA **a)
{
    //printf("Digite a quantidade de itens que deseja ler: ");
    int n;
    scanf("%d", &n);

    // insere os valores dos itens
    ITEM item;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item.chave);
        inserir(item, a);
    }
}


/////////////////////////////////////////////////////

int main()
{
   ITEM item;

   ARVORE_BINARIA *arv = NULL;
   inicializar(arv);
   lerItens(&arv);
   printf("inOrdem: ");
   inOrdem(arv, imprimir);
   printf("\n");


   ARVORE_BINARIA *arv2 = NULL;
   inicializar(arv2);
   lerItens(&arv2);
   printf("inOrdem: ");
   inOrdem(arv2, imprimir);
   printf("\n");

  
   ARVORE_BINARIA *arvU = NULL;
   if (uniao(arv, arv2, &arvU))
   {
      printf("inOrdem: ");
      inOrdem(arvU, imprimir);
      printf("\n");
      disposeArvore(arvU);
   }  
   else
      printf("Uniao nao realizada\n");


   disposeArvore(arv);
   disposeArvore(arv2);
   return 0;
}