#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef struct {
    TIPOCHAVE chave;
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
    int altura;     // Altura do No, sendo que um No folha tem altura 0

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
// os apontadores para o pai e para os filhos contendo NULL.
// A altura e inicializada com 0.
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
    (*arvore)->altura = 0;
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


/*
 * Objetivo: Cria um filho no NO apontado por Arvore na direcao informada. 
 *           Retorna um apontador para o NO criado ou NULL caso nao consiga.
 */ 
ARVORE_BINARIA* adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore) || (direcao == NoPai) || (direcao == NoRaiz) || existeNo(direcao, arvore))
     return false;  // Criacao ilegal de um filho

   if (direcao == NoEsquerdo)
   {
       criarNo(item, &(arvore->esq));
       arvore->esq->pai = arvore;
       return arvore->esq;
   }
   else
   {
       criarNo(item, &(arvore->dir));
       arvore->dir->pai = arvore;
       return arvore->dir;
   }
   return NULL;
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



/*
 Objetivos: Partindo do nivel passado como parametro, calcula o numero de nos (numNos),
            a altura da arvore e a soma dos niveis de cada.
*/
void inOrdCarac(int nivel, int *numNos, int *altura, float *soma, ARVORE_BINARIA *arvore)
{
   if (!vazia(arvore))
   {
      inOrdCarac(nivel + 1, numNos, altura, soma, arvore->esq);
      *numNos = *numNos + 1;
      *soma = *soma + nivel;
      if (nivel > *altura)
         *altura = nivel;
      inOrdCarac(nivel + 1, numNos, altura, soma, arvore->dir);
   }
}


/*
| Objetivos: Determinar as caracteristicas de uma arvore, tal como, o numero
|            de Nos, Altura, e o seu comprimento medio.
*/
void caracteristicas(int *numNos, int *altura, float *compMedio,
                     ARVORE_BINARIA *arvore)
{

   *numNos = 0;
   *altura = 0;
   float soma = 0;
   inOrdCarac(0, numNos, altura, &soma, arvore);
   *compMedio = soma / *numNos;
}


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
  Objetivos: Procura um No que contenha uma chave igual a passada. Caso
             encontre, copia o dado do No em item e retorna true. Se
             nao encontrar, retorna false e item nao e modificado
*/
bool obter(TIPOCHAVE chave, ITEM *item, ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *p;
   if (encontrarChave(chave, &p, arvore))
   {
      *item = p->item;
      return true;
   }
   else
      return false;
}


/*
  Objetivos: Procura um No que contenha uma chave igual a passada. Caso
             encontre, copia item sobre o item do No e retorna true. Se
             nao encontrar, retorna false
*/
bool alterar(ITEM item, ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *p;
   if (encontrarChave(item.chave, &p, arvore))
   {
      p->item = item;
      return true;
   }
   else
      return false;
}


bool encadeamentoComNoPaiCorreto(ARVORE_BINARIA *pai, ARVORE_BINARIA *filhoEsq, 
                                                      ARVORE_BINARIA *filhoDir)
{
   bool ok = true;
   if (!vazia(pai))
   {
      // Checa se o filho esquerdo esta ligado ao no atual corretamente via apontador pai
      // Faz o mesmo para as subarvores deste filho
      if (!vazia(filhoEsq))
         ok = (pai == filhoEsq->pai) &&
              encadeamentoComNoPaiCorreto(filhoEsq, filhoEsq->esq, filhoEsq->dir);
      // Checa se o filho direito esta ligado ao no atual corretamente via apontador pai
      // Faz o mesmo para as subarvores deste filho
      if (!vazia(filhoDir) && ok)
         ok = (pai == filhoDir->pai) &&
              encadeamentoComNoPaiCorreto(filhoDir, filhoDir->esq, filhoDir->dir);
   }
   return ok;
}

void checarEncadeamento(ARVORE_BINARIA *arvore)
{
   if (encadeamentoComNoPaiCorreto(arvore, arvore->esq, arvore->dir))
      printf("\nOk: Encadeamento dos filhos com o no pai correto");
   else
      printf("\nErro: Encadeamento dos filhos com o no pai incorreto");
}


void mostrarCaracteristicas(ARVORE_BINARIA *arv)
{
   // Obtendo as caracteristicas da arvore
   int numNos, altura;
   float compMedio;
   caracteristicas(&numNos, &altura, &compMedio, arv);
   printf("\nNumero de Nos: %d - Altura: %d - Comprimento Medio: %.2f", numNos, altura, compMedio);
}


/////////////////////////////////////////////////////////////////
//            FUNCOES ESPECIFICAS DE ARVORES AVL               //
/////////////////////////////////////////////////////////////////


// Retorna true se o no passado e o filho esquerdo
bool eFilhoEsquerdo(ARVORE_BINARIA *no)
{
   return existeNo(NoPai, no) && (no->pai->esq == no); 
}


// Retorna true se o no passado e o filho direito    
bool eFilhoDireito(ARVORE_BINARIA *no)
{
   return existeNo(NoPai, no) && (no->pai->dir == no);
}


// Calcula a altura de um No da arvore
int alturaNo(ARVORE_BINARIA *no)
{
   return no->altura;
}


// Retorna o balanceamento de um No da arvore
int balanceamento(ARVORE_BINARIA *no)
{
   return alturaNo(no->esq) - alturaNo(no->dir);
}


// Retorna o balanco de um No da Arvore AVL
int balanco(ARVORE_BINARIA *no)
{
   int bal = 0;
   if (existeNo(NoEsquerdo, no))
      bal += 1 + alturaNo(no->esq);
   if (existeNo(NoDireito, no))
      bal -= 1 + alturaNo(no->dir);
   return bal;
}


/*
 * Objetivo: Retorna true se o No corrente esta balanceado, ou seja,
 *           tem balanco igual a -1, 0 ou 1.
 */
bool balanceado(ARVORE_BINARIA *no)
{
   return (balanco(no) >= -1) && (balanco(no) <= 1);      
}


/*
 * Objetivo: Retorna true se o No corrente esta desbalanceado, ou seja,
 *           tem balanco fora da faixa -1 a 1.
 */
bool desbalanceado(ARVORE_BINARIA *no)
{
   return !balanceado(no);      
}    


// Retorna o maior valor entre a e b.
int maior(int a, int b)
{
   return a > b ? a : b;
}


/*
 * Objetivo: Retorna a altura do filho mais alto.
 */
int alturaFilhoMaisAlto(ARVORE_BINARIA *no) 
{
   int alturaFilhoEsq = existeNo(NoEsquerdo, no) ? alturaNo(no->esq) : -1;
   int alturaFilhoDir = existeNo(NoDireito, no) ? alturaNo(no->dir) : -1;
   return maior(alturaFilhoEsq, alturaFilhoDir);
 }


/*
 * Objetivo: Atualiza a altura do No com base na altura do filho mais alto.
 */
void atualizarAltura(ARVORE_BINARIA *no)
{
   no->altura = alturaFilhoMaisAlto(no) + 1;
}


/**
 * Objetivo: Faz com que o No apontado por outroNo passe a ter como 
 *           No pai o pai do No apontado por no. Ao mesmo tempo, faz
 *           com que o pai de no passe a enxergar outroNo como filho.
 */
void trocarPaiComNo(ARVORE_BINARIA *outroNo, ARVORE_BINARIA *no)
{
   outroNo->pai = no->pai;      
   if (eFilhoEsquerdo(no))
      outroNo->pai->esq = outroNo;
   else 
      if (eFilhoDireito(no))
         outroNo->pai->dir = outroNo;
   no->pai = outroNo;
}


/**
 * Objetivo: Efetua uma rotacao simples para a esquerda considerando o No
 * corrente como o pivo.

   Fazendo a rotacao em torno de A teriamos a situacao ao lado

              A  <-- no                       C
            /   \                           /   \
          B      C  <-- filhoDir  =>       A     G
         / \    / \                       / \
        D  E   F  G                      B   F
                                        / \
                                       D   E
*/
void rotacaoParaEsquerda(ARVORE_BINARIA *no) {      
   ARVORE_BINARIA *filhoDir = no->dir;
   ARVORE_BINARIA *temp = filhoDir->esq;

   filhoDir->esq = no;
   trocarPaiComNo(filhoDir, no);

   no->dir = temp;
   if (temp)      // temp != NULL
      temp->pai = no;

   atualizarAltura(no);
   atualizarAltura(filhoDir);
}


/**
 * Objetivo: Efetua uma rotacao simples para a direita considerando
 *           o No corrente como o pivo.

   Fazendo a rotacao em torno de A teriamos a situacao ao lado

         No -->   A                        B
                /   \                    /   \
filhoEsq -->  B      C      =>          D     A
             / \    / \                      / \
            D   E  F   G                    E   C
                                           / \
                                          F   G
*/ 
void rotacaoParaDireita(ARVORE_BINARIA *no) {
   ARVORE_BINARIA *filhoEsq = no->esq;
   ARVORE_BINARIA *temp = filhoEsq->dir;

   filhoEsq->dir = no;      
   trocarPaiComNo(filhoEsq, no);

   no->esq = temp;
   if (temp)      // temp != NULL
      temp->pai = no;

   atualizarAltura(no);
   atualizarAltura(filhoEsq);
}


/*
* Objetivo: Rotacao dupla esquerda direita. Rotaciona primeiro o filho
*           esquerdo para a esquerda e depois o proprio pivo (no atual)
*           como parametro para a direita.
*/
 void rotacaoDuplaEsquerdaDireita(ARVORE_BINARIA *no)
 {
     rotacaoParaEsquerda(no->esq);
     rotacaoParaDireita(no);
 }

 /*
 * Objetivo: Rotacao dupla direita esquerda. Rotaciona primeiro o filho
 *           direito para a direita e depois o proprio pivo (no atual)
 *           como parametro para a esquerda
 */
 void rotacaoDuplaDireitaEsquerda(ARVORE_BINARIA *no)
 {
     rotacaoParaDireita(no->dir);
     rotacaoParaEsquerda(no);
 }


/*
 * Objetivo: Verifica os balancos de um No e efetua a rotacao adequada
 *           para deixar o no com balanco entre -1 e 1.
 */
void rotacionar(ARVORE_BINARIA *no)
{
   if (balanco(no) < -1)
   {
      if (balanco(no->dir) <= 0)
      {
         printf("\nRotacao simples para Esquerda");
         rotacaoParaEsquerda(no);
      }
      else
      {
         printf("\nRotacao Direita e Esquerda");
         rotacaoDuplaDireitaEsquerda(no);
      }
   } 
   else
   { 
      if (balanco(no) > 1)
      {
         if (balanco(no->esq) >= 0)
         {
            printf("\nRotacao simples para Direita");
            rotacaoParaDireita(no);
         }
         else
         {
            printf("\nRotacao para Esquerda Direita");
            rotacaoDuplaEsquerdaDireita(no);
         }
      }              
   }
}


/**
 * Verifica o balanco e efetua rotacoes visando corrigir o
 * desbalanceamento provodado pela remocao.
 */
void balancearAscendentes(ARVORE_BINARIA *no)
{
   if (no != NULL) // Ainda nao chegou na Raiz
   {
      ARVORE_BINARIA *pai = no->pai;
      atualizarAltura(no);
      
      if (desbalanceado(no))
         rotacionar(no);

      balancearAscendentes(pai);       
   }
}


/*
| Objetivos: Tenta inserir um No na Arvore Binaria de Busca apontada por arvore.
|            Se conseguir, retorna o No inserido. Caso nao consiga, retorna NULL.
*/
ARVORE_BINARIA* inserirBinaria(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pPai;
   bool inseriu = true;

   // Se arvore estiver vazia entao so e necessario criar o No, mas se nao
   // estiver, entao sera feita a procura (pela chave) na arvore. Se for achada
   // alguma ocorrencia da chave na arvore (chave duplicada), entao retornara
   // false. Caso contrario item sera adicionado em uma das subarvores de Arvore.
   if (vazia(*arvore))
   {
      criarNo(item, arvore);
      return *arvore;
   }

   if (encontrarChave(item.chave, &pPai, *arvore))
      return NULL;    // chave duplicada

   if (item.chave < pPai->item.chave)
      return adicionarFilho(item, NoEsquerdo, pPai);   // Inseriu na esquerda
   else
      return adicionarFilho(item, NoDireito, pPai);    // Inseriu na direita
}


/*
| Objetivos: Tenta inserir um No na Arvore AVL apontada por arvore.
|            Se conseguir, retorna o No inserido. Caso nao consiga, retorna NULL.
*/
ARVORE_BINARIA* inserir(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *noInserido = inserirBinaria(item, arvore);
   balancearAscendentes(noInserido);
   deslocar(NoRaiz, arvore);  // Depois das rotacoes, a raiz pode mudar
   return noInserido;
}


/*
 * Objetivo: Retorna um apontador para o No sucessor do No apontado pelo
 *           parametro arvore.
 */ 
ARVORE_BINARIA* sucessor(ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA* suc = arvore->dir;

   // Desloca o sucessor pelas subarvores ate chegar em um No 
   // sem subarvore esquerda
   while (existeNo(NoEsquerdo, suc))
      deslocar(NoEsquerdo, &suc);

   return suc;
}


/*
  Objetivo: Substitui o ITEM contido No apontado pelo parametro arvore
            pelo valor contido em seu sucessor imediato.
*/
ARVORE_BINARIA* substituirPorSucessor(ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *suc = sucessor(arvore);
   ARVORE_BINARIA *pApagar = suc;
   arvore->item = suc->item;

   // Se existir, corrige o apontador pai do seu filho direito
   // de sucessor, fazendo-o apontar para o pai do sucessor
   if (existeNo(NoDireito, suc))
      suc->dir->pai = suc->pai;

   // Ajusta o apontador que o pai tem para o sucessor para apontar
   // para o filho direito do sucessor (que pode ser NULL)
   if (eFilhoDireito(suc))
      suc->pai->dir = suc->dir;
   else
      suc->pai->esq = suc->dir;

   return pApagar;
}


/*
| Objetivos: Retira o No contendo chave da arvore apontada por arvore. Retorna
|            o No removido ou NULL, caso contrario.
*/
ARVORE_BINARIA* removerBinaria(TIPOCHAVE chave, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pApagar;

   /* Se a arvore estiver vazia, o No nao sera retirado, pois nao existe. Mas
      se nao estiver vazia, sera feita a procura atraves de chamadas
      recursivas de remover, pegando a subarvore esquerda quando chave for
      menor que o valor da chave no No ou a subarvore direita quando for maior.
      Existem dois pontos de parada, o primeiro quando a subarvore onde esta
      sendo feita a busca esta vazia e o segundo quando a chave for encontrada.
      Nesse caso acontecera a remocao */
   if (vazia(*arvore))
      return NULL;

   if (chave < (*arvore)->item.chave)
      return removerBinaria(chave, &((*arvore)->esq));

   if (chave > (*arvore)->item.chave)
      return removerBinaria(chave, &((*arvore)->dir));

   /* Como nesse ponto item = arvore->item.chave, devemos verificar
     se o No possui duas, uma ou nenhuma subarvore. No primeiro caso
     deve ser procurado na subarvore direita o sucessor imediato do No
     e coloca-lo no lugar do No removido. Nos outros dois casos, so
     e necessario remover o No e ajustar os apontadores */

   if (vazia((*arvore)->esq))   // Arvore nao tem subarvores ou tem somente a direita
   {
      pApagar = *arvore;

      /* Se existir, corrige o apontador pai do filho direito do No a 
         ser removido, fazendo-o apontar para o pai do No a ser removido */
      if (!vazia((*arvore)->dir))
         (*arvore)->dir->pai = (*arvore)->pai;

      *arvore = (*arvore)->dir;
   }
   else
   {
      if (vazia((*arvore)->dir)) // Arvore tem somente o filho esquerdo
      {   
         pApagar = (*arvore);

         /* Corrige o apontador pai do filho esquerdo do No a ser removido,
            fazendo-o apontar para o pai do No a ser removido */
         (*arvore)->esq->pai = (*arvore)->pai;
         
         *arvore = (*arvore)->esq;
      }
      else
         pApagar = substituirPorSucessor(*arvore);
   }

   return pApagar;
}


/*
| Objetivos: Retira o No contendo chave da arvore apontada por arvore. 
|            Retorna true se conseguiu remover e false caso contrario.
*/
bool remover(TIPOCHAVE chave, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA* noRemovido = removerBinaria(chave, arvore);
   if (noRemovido == NULL)
      return false;

   balancearAscendentes(noRemovido->pai);

   if (!vazia(*arvore))
      deslocar(NoRaiz, arvore);  // Depois das rotacoes, a raiz pode mudar
   
   free(noRemovido);
   return true;
}


////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////


/////////////////////////////////////////////////////
// Visita um NO da arvore, imprimindo o valor da chave
// entre parenteses
void imprimir(ARVORE_BINARIA *arvore) {
    printf("(%d,%d)", arvore->item.chave, balanco(arvore));
}

/////////////////////////////////////////////////////



int main()
{
   ARVORE_BINARIA *arv = NULL;
   inicializar(arv);
   ITEM item;

   item.chave = 7;
   inserir(item, &arv);
   item.chave = 6;
   inserir(item, &arv);
/*
             7
           6
*/
   printf("inOrdem: ");
   inOrdem(arv, imprimir);

   item.chave = 5;
   inserir(item, &arv);
/*
Antes da rotacao para direita:
             7
           6
         5   

Apos rotacao para direita:
           6
         5   7
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);

   item.chave = 11;
   inserir(item, &arv);
   item.chave = 9;
   inserir(item, &arv);
/*
Antes da rotacao dupla direita esquerda:
           6
         5   7
               11
             9

Passo 1: rotacao para direita sobre filho direito (11) do pivo (7)
           6
         5   7
               9
                 11

Passo 2: rotacao para esquerda sobre pivo (7)

           6
         5   9
            7 11
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);

   item.chave = 8;
   inserir(item, &arv);
/*
Antes da rotacao dupla direita esquerda:
            6
         5     9
            7    11
              8
Passo 1: rotacao para direita sobre filho direito (9) do pivo (6)
            6
         5     7
                 9
               8   11

Passo 2: rotacao para esquerda sobre pivo (6)
            7
         6     9
      5      8   11
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   item.chave = 10;
   inserir(item, &arv);
   item.chave = 12;
   inserir(item, &arv);
/*
              7
         6        9
      5        8     11
                   10  12
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);

  
   item.chave = 15;
   inserir(item, &arv);

/*
Antes da rotacao para esquerda sobre pivo (9):
              7
         6        9
      5        8     11
                   10  12
                         15

Apos rotacao para esquerda:
              7
         6         11
      5         9      12
             8   10       15

*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   mostrarCaracteristicas(arv);


//////////////////////////////////////////////////////////
// REMOCOES
//////////////////////////////////////////////////////////


   printf("\nRemovendo 100 (No nao existe)");
   if (remover(100, &arv))
      printf("\nERRO: Nao deveria conseguir remover 100");
   else
      printf("\nOK: Nao removeu 100 porque nao existe na arvore");


   printf("\nRemovendo 15 (No folha sem desbalancear)");
   remover(15, &arv);
/*
              7
         6         11
      5        9      12
             8   10
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 5 (No Folha desbalanceado)");
   remover(5, &arv);
/*
Antes da rotacao dupla direita esquerda:
              7
         6         11
               9      12
             8   10
Passo 1: rotacao para direita sobre filho direito (11) do pivo (7)
              7
         6         9
                8     11
                    10  12

Passo 2: rotacao para esquerda sobre pivo (7)
                   9
              7         11
           6     8   10    12
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 9 (No com 2 filhos sem desbalancear)");
   remover(9, &arv);
/*
                   10
              7         11
           6     8         12
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 11 (No com 1 filho sem desbalancear)");
   remover(11, &arv);
/*
                   10
              7         12
           6     8         
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 12 (No folha desbalanceado)");
   remover(12, &arv);
/*
Antes da rotacao para direita sobre pivo (10):
                   10
              7     
           6     8         

Apos rotacao para direita:
              7
         6         10
                8
*/

   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   // Checa o encadeamento dos nos, inclusive com seus pais
   checarEncadeamento(arv);


   printf("\nRemovendo 6 (No Folha desbalanceado)");
   remover(6, &arv);
/*
Antes da rotacao dupla direita esquerda:
              7
                   10
                8
Passo 1: rotacao para direita sobre filho direito (10) do pivo (7)
              7
                  8
                     10
Passo 2: rotacao para esquerda sobre pivo (7)
                  8
              7       10
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 8 (No com 2 filhos balanceado)");
   remover(8, &arv);
/*
                  10
              7
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 7 (No folha balanceado)");
   remover(7, &arv);
/*
                  10
*/
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);


   printf("\nRemovendo 10 (No raiz e arvore vazia)");
   remover(10, &arv);
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);

/*  
   for (int i = 1; i <= 100; i++)
   {
      item.chave = i;
      inserir(item, &arv);
   }
   printf("\ninOrdem: ");
   inOrdem(arv, imprimir);
   mostrarCaracteristicas(arv);
*/
   disposeArvore(arv);
   return 0;
}
