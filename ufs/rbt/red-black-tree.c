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

    if (dir->esq != arv->NIL)
        dir->esq->pai = no;
    dir->pai = no->pai;

    if (no->pai == arv->NIL) // Nó é raiz.
        arv->raiz = dir;
    else if (no == no->pai->esq) // Nó é filho esquerdo.
        no->pai->esq = dir;
    else // Nó é filho direito.
        no->pai->dir = dir;

    dir->esq = no;
    no->pai = dir;
}

void rotacaoDireita(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    No *esq = no->esq;
    no->esq = esq->dir;

    if (esq->dir != arv->NIL)
        esq->dir->pai = no;
    esq->pai = no->pai;

    if (no->pai == arv->NIL) // Nó é raiz.
        arv->raiz = esq;
    else if (no == no->pai->dir) // Nó é filho direito.
        no->pai->dir = esq;
    else // Nó é filho esquerdo.
        no->pai->esq = esq;

    esq->dir = no;
    no->pai = esq;
}

void balancearInsercao(ARVORE_RUBRO_NEGRA *arv, No *no) {
    while (no->pai->cor == Vermelho) {   
        No * pai = no->pai;
        No * avo = no->pai->pai;
        if (pai == avo->esq) // Nó pai é filho esquerdo do avô.
        {
            No *tio = avo->dir;
            if (tio->cor == Vermelho) // (Caso 1) Tio também é vermelho.
            {
                pai->cor = Preto;
                tio->cor = Preto;
                avo->cor = Vermelho;
                no = avo;
            }
            else { // (Caso 2) Tio é preto.
                if (no == pai->dir) // (Rotação dupla) Nó é filho direito do pai.
                { 
                    no = pai;
                    rotacaoEsquerda(arv, no);
                }
                pai = no->pai;
                // (Rotação Simples) Nó é filho esquerdo do pai.
                pai->cor = Preto;       
                avo->cor = Vermelho;
                rotacaoDireita(arv, avo);
            }
        }
        else // Nó pai é filho direito do avô.
        {
            No *tio = avo->esq;
            if (tio->cor == Vermelho) // (Caso 1) Tio também é vermelho.
            {
                pai->cor = Preto;
                tio->cor = Preto;
                avo->cor = Vermelho;
                no = avo;
            }
            else // (Caso 2) Tio é preto.
            {
                if (no == pai->esq) // (Rotação dupla) Nó é filho esquerdo do pai.
                {   
                    no = pai; // marked no.pai as new no
                    rotacaoDireita(arv, no);
                }
                pai = no->pai;
                // (Rotação Simples) Nó é filho direito do pai.
                pai->cor = Preto;
                avo->cor = Vermelho;
                rotacaoEsquerda(arv, avo);
            }
        }
    }
    arv->raiz->cor = Preto;
}

void inserir(ARVORE_RUBRO_NEGRA *arv, No *NoNovo) 
{
    No *paiNovoNo = arv->NIL;
    No *NoAtual = arv->raiz;

    // Encontra o pai do novo nó.
    while (NoAtual != arv->NIL) {
        paiNovoNo = NoAtual;
        if (NoNovo->valor < NoAtual->valor)
            NoAtual = NoAtual->esq;
        else
            NoAtual = NoAtual->dir;
    }

    NoNovo->pai = paiNovoNo;

    // Se árvore vazia, o novo nó é a raiz.
    if (paiNovoNo == arv->NIL)
        arv->raiz = NoNovo;
    else if (NoNovo->valor < paiNovoNo->valor) // Se for menor que seu pai adiciona a esquerda.
        paiNovoNo->esq = NoNovo;
    else // Se for maior que seu pai adiciona a direita.
        paiNovoNo->dir = NoNovo;

    NoNovo->dir = arv->NIL;
    NoNovo->esq = arv->NIL;

    balancearInsercao(arv, NoNovo);
}

void transplantarSubArvore(ARVORE_RUBRO_NEGRA *arv, No *no, No *filho) 
{
    if (no->pai == arv->NIL) // Se o pai do nó for nulo.
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

void balancearRemocao(ARVORE_RUBRO_NEGRA *arv, No *no)
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

void remover(ARVORE_RUBRO_NEGRA *arv, No *no)
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
        balancearRemocao(arv, children);
}

void inorder(ARVORE_RUBRO_NEGRA *arv, No *no)
{
    if (no != arv->NIL)
    {
        inorder(arv, no->esq);
        printf("%d\n", no->valor);
        inorder(arv, no->dir);
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

    inserir(t, a);
    inserir(t, b);
    inserir(t, c);
    inserir(t, d);
    inserir(t, e);
    inserir(t, f);
    inserir(t, g);
    inserir(t, h);
    inserir(t, i);
    inserir(t, j);
    inserir(t, k);
    inserir(t, l);
    inserir(t, m);

    remover(t, a);
    remover(t, m);
    remover(t, g);
    remover(t, b);

    inorder(t, t->raiz);

    buscaARB(t, 11);

    return 0;
}