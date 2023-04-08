#include <stdio.h>
#include <stdlib.h>

enum COR
{
    Vermelho,
    Preto
};

typedef struct estrutura
{
    int valor;
    struct estrutura *dir;
    struct estrutura *esq;
    struct estrutura *pai;
    enum COR cor;
} No;

typedef struct arvore
{
    No *raiz;
    No *NIL;
} ARVORE_RUBRO_NEGRA;

No *criarNoARB(int valor)
{
    No *n = malloc(sizeof(No));
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->valor = valor;
    n->cor = Vermelho;

    return n;
}

ARVORE_RUBRO_NEGRA *criaARB()
{
    ARVORE_RUBRO_NEGRA *t = malloc(sizeof(ARVORE_RUBRO_NEGRA));
    No *nil_no = malloc(sizeof(No));
    nil_no->esq = NULL;
    nil_no->dir = NULL;
    nil_no->pai = NULL;
    nil_no->cor = Preto;
    nil_no->valor = 0;
    t->NIL = nil_no;
    t->raiz = t->NIL;

    return t;
}

No* buscaARB(ARVORE_RUBRO_NEGRA* arv, int valor) {
    // Percorre a árvore a partir da raiz.
    while (arv->raiz != arv->NIL && arv->raiz->valor != valor) {
        if (valor < arv->raiz->valor)
            arv->raiz = arv->raiz->esq;
        else
            arv->raiz = arv->raiz->dir;
    }
    
    // Verifica se o valor foi encontrado ou não.
    if (arv->raiz == arv->NIL) {
        printf("Valor nao encontrado na arvore.\n");
        return NULL;
    } else {
        printf("Valor encontrado na arvore.\n");
        return arv->raiz;
    }
}

void rotacaoEsquerda(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    No *dir = no->dir;
    no->dir = dir->esq;
    if (dir->esq != arv->NIL) {
        dir->esq->pai = no;
    }
    dir->pai = no->pai;
    if (no->pai == arv->NIL)
    { // no is raiz
        arv->raiz = dir;
    }
    else if (no == no->pai->esq)
    { // no is esq child
        no->pai->esq = dir;
    }
    else
    { // no is dir child
        no->pai->dir = dir;
    }
    dir->esq = no;
    no->pai = dir;
}

void rotacaoDireita(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    No *esq = no->esq;
    no->esq = esq->dir;
    if (esq->dir != arv->NIL)
    {
        esq->dir->pai = no;
    }
    esq->pai = no->pai;
    if (no->pai == arv->NIL)
    { // no is raiz
        arv->raiz = esq;
    }
    else if (no == no->pai->dir)
    { // no is esq child
        no->pai->dir = esq;
    }
    else
    { // no is dir child
        no->pai->esq = esq;
    }
    esq->dir = no;
    no->pai = esq;
}

void balancearInsercao(ARVORE_RUBRO_NEGRA *arv, No *no) {
    while (no->pai->cor == Vermelho) {   
        No * pai = no->pai;
        No * grandpai = no->pai->pai;
        //  pai            .esq
        if (pai == grandpai->esq) // o nó pai é filho esquerdo de um avó
        {

            No *uncle = grandpai->dir; // tio de no
            //tio vermelho
            if (uncle->cor == Vermelho)
            { // caso 1
                pai->cor = Preto;
                uncle->cor = Preto;
                grandpai->cor = Vermelho;
                no = grandpai;
                //proxima iteração...
            }
            else { //tio preto
                // case2
                if (no == pai->dir) { 
                    no = no->pai; // marked no.pai as new no
                    rotacaoEsquerda(arv, no);
                }
                // case3
                no->pai->cor = Preto;       
                no->pai->pai->cor = Vermelho;
                rotacaoDireita(arv, no->pai->pai);
            }
        }
        else
        {                                           // no.pai is the dir child
            No *uncle = no->pai->pai->esq; // uncle of no

            if (uncle->cor == Vermelho)
            {
                no->pai->cor = Preto;
                uncle->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            }
            else
            {
                if (no == no->pai->esq)
                {
                    no = no->pai; // marked no.pai as new no
                    rotacaoDireita(arv, no);
                }
                no->pai->cor = Preto;       // made pai black
                no->pai->pai->cor = Vermelho; // made pai red
                rotacaoEsquerda(arv, no->pai->pai);
            }
        }
    }
    arv->raiz->cor = Preto;
}

void insercao(ARVORE_RUBRO_NEGRA *arv, No *newNode) 
{
    No *paiOfNewNode = arv->NIL;
    No *current = arv->raiz;

    /* encontra o pai do novo newNode */
    while (current != arv->NIL) {
        paiOfNewNode = current;
        if (newNode->valor < current->valor)
            current = current->esq;
        else
            current = current->dir;
    }

    newNode->pai = paiOfNewNode;

    //se arvore vazia, o newNode é raiz, se for menor que seu pai adiciona a esquerda, senao a direita
    if (paiOfNewNode == arv->NIL)  {
        arv->raiz = newNode;
    }
    else if (newNode->valor < paiOfNewNode->valor)
        paiOfNewNode->esq = newNode;
    else
        paiOfNewNode->dir = newNode;

    newNode->dir = arv->NIL;
    newNode->esq = arv->NIL;

    balancearInsercao(arv, newNode);
}

void transplantarSubArvore(ARVORE_RUBRO_NEGRA *arv, No *no, No *filho) 
{
    if (no->pai == arv->NIL)
        arv->raiz = filho;
    else if (no == no->pai->esq)
        no->pai->esq = filho;
    else
        no->pai->dir = filho;
    filho->pai = no->pai;
}

No *obterSucessor(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    while (no->esq != arv->NIL)
        no = no->esq;
    return no;
}

void rb_delete_fixup(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    while (no != arv->raiz && no->cor == Preto)
    { /* se o no é filho esquerdo do pai */
        if (no == no->pai->esq)
        {
            No *sibling = no->pai->dir;
            /* CASO 1; se o irmao for vermelho, recore o irmao e pai,
            para fazer a rotação
              */
            if (sibling->cor == Vermelho)
            {
                //recorTorotacaoEsquerda()
                sibling->cor = Preto;
                no->pai->cor = Vermelho;
                rotacaoEsquerda(arv, no->pai);
                //updateSibling()
                sibling = no->pai->dir;
            }
            /* CASO 2; irmao preto entao recore e passa para o pai */
            if (sibling->esq->cor == Preto && sibling->dir->cor == Preto)
            {
                sibling->cor = Vermelho; //recor sibling
                no = no->pai;
            }
            else
            {   /* CASO 3: filho esquedo vermelho e direito preto */
                if (sibling->dir->cor == Preto)
                {
                    //recorir
                    sibling->cor = Vermelho;
                    sibling->esq->cor = Preto;
                    rotacaoDireita(arv, sibling);
                    //atualizando irmao
                    sibling = no->pai->dir;
                }
                /* CASO 4: filho direito vermelho */
                sibling->cor = no->pai->cor;
                no->pai->cor = Preto;
                sibling->dir->cor = Preto;
                rotacaoEsquerda(arv, no->pai);
                no = arv->raiz;
            }
        }
        else /* mesma coisa só que para o caso de ser o filho direito de um pai */
        {
            No *sibling = no->pai->esq;
            if (sibling->cor == Vermelho)
            {
                sibling->cor = Preto;
                no->pai->cor = Vermelho;
                rotacaoDireita(arv, no->pai);
                sibling = no->pai->esq;
            }
            if (sibling->dir->cor == Preto && sibling->esq->cor == Preto)
            {
                sibling->cor = Vermelho;
                no = no->pai;
            }
            else
            {
                if (sibling->esq->cor == Preto)
                {
                    sibling->dir->cor = Preto;
                    sibling->cor = Vermelho;
                    rotacaoEsquerda(arv, sibling);
                    sibling = no->pai->esq;
                }
                sibling->cor = no->pai->cor;
                no->pai->cor = Preto;
                sibling->esq->cor = Preto;
                rotacaoDireita(arv, no->pai);
                no = arv->raiz;
            }
        }
    }
    no->cor = Preto;
}

void rb_delete(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    No *successor = no;
    No *children;
    enum COR successor_orignal_cor = successor->cor;
    /* caso um dos lados estiver NULL entao basta transplantar o lado
    não nulo para o nó que deseja remover
     */
    if (no->esq == arv->NIL) {
        children = no->dir;
        transplantarSubArvore(arv, no, no->dir);
    }
    else if (no->dir == arv->NIL) {
        children = no->esq;
        transplantarSubArvore(arv, no, no->esq);
    }
    /* caso nenhum os 2 lados tenham filhos */
    else {
        successor = obterSucessor(arv, no->dir);
        children = successor->dir;
        successor_orignal_cor = successor->cor; /* preciso guardar a cor para colocar no no que vai ser removido */
        /* caso o sucessor seja filho imediato de no 
        eu tenho que ter certeza que ele esta apontando
        para no pois se children for nulo entao teremos 
        problemas na hora de balancear
         */
        if (successor->pai == no) {
            children->pai = successor;
        }
        else {
            transplantarSubArvore(arv, successor, successor->dir);
            successor->dir = no->dir;
            successor->dir->pai = successor;
        }
        transplantarSubArvore(arv, no, successor);
        successor->esq = no->esq;
        successor->esq->pai = successor;
        successor->cor = no->cor;
    }
    /* se o no sucessor  */
    if (successor_orignal_cor == Preto)
        rb_delete_fixup(arv, children);
}

void inorder(ARVORE_RUBRO_NEGRA *t, No *n)
{
    if (n != t->NIL)
    {
        inorder(t, n->esq);
        printf("%d\n", n->valor);
        inorder(t, n->dir);
    }
}

int main()
{
    ARVORE_RUBRO_NEGRA *t = criaARB();

    No *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = criarNoARB(10);
    b = criarNoARB(20);
    c = criarNoARB(30);
    d = criarNoARB(100);
    e = criarNoARB(90);
    f = criarNoARB(40);
    g = criarNoARB(50);
    h = criarNoARB(60);
    i = criarNoARB(70);
    j = criarNoARB(80);
    k = criarNoARB(150);
    l = criarNoARB(110);
    m = criarNoARB(120);

    insercao(t, a);
    insercao(t, b);
    insercao(t, c);
    insercao(t, d);
    insercao(t, e);
    insercao(t, f);
    insercao(t, g);
    insercao(t, h);
    insercao(t, i);
    insercao(t, j);
    insercao(t, k);
    insercao(t, l);
    insercao(t, m);

    rb_delete(t, a);
    rb_delete(t, m);
    rb_delete(t, g);
    rb_delete(t, b);

    inorder(t, t->raiz);

    buscaARB(t, 11);

    return 0;
}