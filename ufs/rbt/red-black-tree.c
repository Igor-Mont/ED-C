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
    No *nil_node = malloc(sizeof(No));
    nil_node->esq = NULL;
    nil_node->dir = NULL;
    nil_node->pai = NULL;
    nil_node->cor = Preto;
    nil_node->valor = 0;
    t->NIL = nil_node;
    t->raiz = t->NIL;

    return t;
}

No* buscaARB(ARVORE_RUBRO_NEGRA* t, int value) {
    // Percorre a árvore a partir da raiz 
    while (t->raiz != t->NIL && t->raiz->valor != value) {
        if (value < t->raiz->valor) {
            t->raiz = t->raiz->esq;
        } else {
            t->raiz = t->raiz->dir;
        }
    }
    
    // Verifica se o valor foi encontrado ou não
    if (t->raiz == t->NIL) {
        printf("Valor nao encontrado na arvore.\n");
        return NULL;
    } else {
        printf("Valor encontrado na arvore.\n");
        return t->raiz;
    }
}

void rotacaoEsquerda(ARVORE_RUBRO_NEGRA *tree,No *node)
{
    No *dir = node->dir;
    node->dir = dir->esq;
    if (dir->esq != tree->NIL) {
        dir->esq->pai = node;
    }
    dir->pai = node->pai;
    if (node->pai == tree->NIL)
    { // node is raiz
        tree->raiz = dir;
    }
    else if (node == node->pai->esq)
    { // node is esq child
        node->pai->esq = dir;
    }
    else
    { // node is dir child
        node->pai->dir = dir;
    }
    dir->esq = node;
    node->pai = dir;
}

void rotacaoDireita(ARVORE_RUBRO_NEGRA *tree, No *node)
{
    No *esq = node->esq;
    node->esq = esq->dir;
    if (esq->dir != tree->NIL)
    {
        esq->dir->pai = node;
    }
    esq->pai = node->pai;
    if (node->pai == tree->NIL)
    { // node is raiz
        tree->raiz = esq;
    }
    else if (node == node->pai->dir)
    { // node is esq child
        node->pai->dir = esq;
    }
    else
    { // node is dir child
        node->pai->esq = esq;
    }
    esq->dir = node;
    node->pai = esq;
}

void insertion_fixup(ARVORE_RUBRO_NEGRA *tree, No *node) {
    while (node->pai->cor == Vermelho) {   
        No * pai = node->pai;
        No * grandpai = node->pai->pai;
        //  pai            .esq
        if (pai == grandpai->esq) // o nó pai é filho esquerdo de um avó
        {

            No *uncle = grandpai->dir; // tio de node
            //tio vermelho
            if (uncle->cor == Vermelho)
            { // caso 1
                pai->cor = Preto;
                uncle->cor = Preto;
                grandpai->cor = Vermelho;
                node = grandpai;
                //proxima iteração...
            }
            else { //tio preto
                // case2
                if (node == pai->dir) { 
                    node = node->pai; // marked node.pai as new node
                    rotacaoEsquerda(tree, node);
                }
                // case3
                node->pai->cor = Preto;       
                node->pai->pai->cor = Vermelho;
                rotacaoDireita(tree, node->pai->pai);
            }
        }
        else
        {                                           // node.pai is the dir child
            No *uncle = node->pai->pai->esq; // uncle of node

            if (uncle->cor == Vermelho)
            {
                node->pai->cor = Preto;
                uncle->cor = Preto;
                node->pai->pai->cor = Vermelho;
                node = node->pai->pai;
            }
            else
            {
                if (node == node->pai->esq)
                {
                    node = node->pai; // marked node.pai as new node
                    rotacaoDireita(tree, node);
                }
                node->pai->cor = Preto;       // made pai black
                node->pai->pai->cor = Vermelho; // made pai red
                rotacaoEsquerda(tree, node->pai->pai);
            }
        }
    }
    tree->raiz->cor = Preto;
}

void insert(ARVORE_RUBRO_NEGRA *tree, No *newNode) 
{
    No *paiOfNewNode = tree->NIL;
    No *current = tree->raiz;

    /* encontra o pai do novo newNode */
    while (current != tree->NIL) {
        paiOfNewNode = current;
        if (newNode->valor < current->valor)
            current = current->esq;
        else
            current = current->dir;
    }

    newNode->pai = paiOfNewNode;

    //se arvore vazia, o newNode é raiz, se for menor que seu pai adiciona a esquerda, senao a direita
    if (paiOfNewNode == tree->NIL)  {
        tree->raiz = newNode;
    }
    else if (newNode->valor < paiOfNewNode->valor)
        paiOfNewNode->esq = newNode;
    else
        paiOfNewNode->dir = newNode;

    newNode->dir = tree->NIL;
    newNode->esq = tree->NIL;

    insertion_fixup(tree, newNode);
}

void rb_transplant(ARVORE_RUBRO_NEGRA *tree, No *node, No *children) 
{
    if (node->pai == tree->NIL)
        tree->raiz = children;
    else if (node == node->pai->esq)
        node->pai->esq = children;
    else
        node->pai->dir = children;
    children->pai = node->pai;
}

No *minimum(ARVORE_RUBRO_NEGRA *tree, No *node)
{
    while (node->esq != tree->NIL)
        node = node->esq;
    return node;
}

void rb_delete_fixup(ARVORE_RUBRO_NEGRA *tree, No *node)
{
    while (node != tree->raiz && node->cor == Preto)
    { /* se o no é filho esquerdo do pai */
        if (node == node->pai->esq)
        {
            No *sibling = node->pai->dir;
            /* CASO 1; se o irmao for vermelho, recore o irmao e pai,
            para fazer a rotação
              */
            if (sibling->cor == Vermelho)
            {
                //recorTorotacaoEsquerda()
                sibling->cor = Preto;
                node->pai->cor = Vermelho;
                rotacaoEsquerda(tree, node->pai);
                //updateSibling()
                sibling = node->pai->dir;
            }
            /* CASO 2; irmao preto entao recore e passa para o pai */
            if (sibling->esq->cor == Preto && sibling->dir->cor == Preto)
            {
                sibling->cor = Vermelho; //recor sibling
                node = node->pai;
            }
            else
            {   /* CASO 3: filho esquedo vermelho e direito preto */
                if (sibling->dir->cor == Preto)
                {
                    //recorir
                    sibling->cor = Vermelho;
                    sibling->esq->cor = Preto;
                    rotacaoDireita(tree, sibling);
                    //atualizando irmao
                    sibling = node->pai->dir;
                }
                /* CASO 4: filho direito vermelho */
                sibling->cor = node->pai->cor;
                node->pai->cor = Preto;
                sibling->dir->cor = Preto;
                rotacaoEsquerda(tree, node->pai);
                node = tree->raiz;
            }
        }
        else /* mesma coisa só que para o caso de ser o filho direito de um pai */
        {
            No *sibling = node->pai->esq;
            if (sibling->cor == Vermelho)
            {
                sibling->cor = Preto;
                node->pai->cor = Vermelho;
                rotacaoDireita(tree, node->pai);
                sibling = node->pai->esq;
            }
            if (sibling->dir->cor == Preto && sibling->esq->cor == Preto)
            {
                sibling->cor = Vermelho;
                node = node->pai;
            }
            else
            {
                if (sibling->esq->cor == Preto)
                {
                    sibling->dir->cor = Preto;
                    sibling->cor = Vermelho;
                    rotacaoEsquerda(tree, sibling);
                    sibling = node->pai->esq;
                }
                sibling->cor = node->pai->cor;
                node->pai->cor = Preto;
                sibling->esq->cor = Preto;
                rotacaoDireita(tree, node->pai);
                node = tree->raiz;
            }
        }
    }
    node->cor = Preto;
}

void rb_delete(ARVORE_RUBRO_NEGRA *tree, No *node)
{
    No *successor = node;
    No *children;
    enum COR successor_orignal_cor = successor->cor;
    /* caso um dos lados estiver NULL entao basta transplantar o lado
    não nulo para o nó que deseja remover
     */
    if (node->esq == tree->NIL) {
        children = node->dir;
        rb_transplant(tree, node, node->dir);
    }
    else if (node->dir == tree->NIL) {
        children = node->esq;
        rb_transplant(tree, node, node->esq);
    }
    /* caso nenhum os 2 lados tenham filhos */
    else {
        successor = minimum(tree, node->dir);
        children = successor->dir;
        successor_orignal_cor = successor->cor; /* preciso guardar a cor para colocar no node que vai ser removido */
        /* caso o sucessor seja filho imediato de node 
        eu tenho que ter certeza que ele esta apontando
        para node pois se children for nulo entao teremos 
        problemas na hora de balancear
         */
        if (successor->pai == node) {
            children->pai = successor;
        }
        else {
            rb_transplant(tree, successor, successor->dir);
            successor->dir = node->dir;
            successor->dir->pai = successor;
        }
        rb_transplant(tree, node, successor);
        successor->esq = node->esq;
        successor->esq->pai = successor;
        successor->cor = node->cor;
    }
    /* se o no sucessor  */
    if (successor_orignal_cor == Preto)
        rb_delete_fixup(tree, children);
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

    insert(t, a);
    insert(t, b);
    insert(t, c);
    insert(t, d);
    insert(t, e);
    insert(t, f);
    insert(t, g);
    insert(t, h);
    insert(t, i);
    insert(t, j);
    insert(t, k);
    insert(t, l);
    insert(t, m);

    rb_delete(t, a);
    rb_delete(t, m);
    rb_delete(t, g);
    rb_delete(t, b);

    inorder(t, t->raiz);

    buscaARB(t, 11);

    return 0;
}