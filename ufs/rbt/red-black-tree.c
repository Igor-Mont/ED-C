#include <stdio.h>
#include <stdlib.h>

enum COR
{
    Vermelho,
    Preto
};

typedef struct tree_node
{
    int valor;
    struct tree_node *dir;
    struct tree_node *esq;
    struct tree_node *pai;
    enum COR cor;
} tree_node;

typedef struct red_black_tree
{
    tree_node *root;
    tree_node *NIL;
} red_black_tree;

tree_node* globalRoot = NULL;

tree_node *new_RBTree(int valor)
{
    tree_node *n = malloc(sizeof(tree_node));
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->valor = valor;
    n->cor = Vermelho;

    return n;
}

red_black_tree *new_red_black_tree()
{
    red_black_tree *t = malloc(sizeof(red_black_tree));
    tree_node *nil_node = malloc(sizeof(tree_node));
    nil_node->esq = NULL;
    nil_node->dir = NULL;
    nil_node->pai = NULL;
    nil_node->cor = Preto;
    nil_node->valor = 0;
    t->NIL = nil_node;
    t->root = t->NIL;

    return t;
}

tree_node* search(red_black_tree* t, int value) {
    // Percorre a árvore a partir da raiz
    while (t->root != t->NIL && t->root->valor != value) {
        if (value < t->root->valor) {
            t->root = t->root->esq;
        } else {
            t->root = t->root->dir;
        }
    }
    
    // Verifica se o valor foi encontrado ou não
    if (t->root == t->NIL) {
        printf("Valor nao encontrado na arvore.\n");
        return NULL;
    } else {
        printf("Valor encontrado na arvore.\n");
        return t->root;
    }
}

void rotacaoEsquerda(red_black_tree *tree,tree_node *node)
{
    tree_node *dir = node->dir;
    node->dir = dir->esq;
    if (dir->esq != tree->NIL) {
        dir->esq->pai = node;
    }
    dir->pai = node->pai;
    if (node->pai == tree->NIL)
    { // node is root
        tree->root = dir;
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

void rotacaoDireita(red_black_tree *tree, tree_node *node)
{
    tree_node *esq = node->esq;
    node->esq = esq->dir;
    if (esq->dir != tree->NIL)
    {
        esq->dir->pai = node;
    }
    esq->pai = node->pai;
    if (node->pai == tree->NIL)
    { // node is root
        tree->root = esq;
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

void insertion_fixup(red_black_tree *tree, tree_node *node) {
    while (node->pai->cor == Vermelho) {   
        tree_node * pai = node->pai;
        tree_node * grandpai = node->pai->pai;
        //  pai            .esq
        if (pai == grandpai->esq) // o nó pai é filho esquerdo de um avó
        {

            tree_node *uncle = grandpai->dir; // tio de node
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
            tree_node *uncle = node->pai->pai->esq; // uncle of node

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
    tree->root->cor = Preto;
}

void insert(red_black_tree *tree, tree_node *newNode) 
{
    tree_node *paiOfNewNode = tree->NIL;
    tree_node *current = tree->root;

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
        tree->root = newNode;
    }
    else if (newNode->valor < paiOfNewNode->valor)
        paiOfNewNode->esq = newNode;
    else
        paiOfNewNode->dir = newNode;

    newNode->dir = tree->NIL;
    newNode->esq = tree->NIL;

    insertion_fixup(tree, newNode);
}

void rb_transplant(red_black_tree *tree, tree_node *node, tree_node *children) 
{
    if (node->pai == tree->NIL)
        tree->root = children;
    else if (node == node->pai->esq)
        node->pai->esq = children;
    else
        node->pai->dir = children;
    children->pai = node->pai;
}

tree_node *minimum(red_black_tree *tree, tree_node *node)
{
    while (node->esq != tree->NIL)
        node = node->esq;
    return node;
}

void rb_delete_fixup(red_black_tree *tree, tree_node *node)
{
    while (node != tree->root && node->cor == Preto)
    { /* se o no é filho esquerdo do pai */
        if (node == node->pai->esq)
        {
            tree_node *sibling = node->pai->dir;
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
                node = tree->root;
            }
        }
        else /* mesma coisa só que para o caso de ser o filho direito de um pai */
        {
            tree_node *sibling = node->pai->esq;
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
                node = tree->root;
            }
        }
    }
    node->cor = Preto;
}

void rb_delete(red_black_tree *tree, tree_node *node)
{
    tree_node *successor = node;
    tree_node *children;
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

void inorder(red_black_tree *t, tree_node *n)
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
    red_black_tree *t = new_red_black_tree();

    tree_node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = new_RBTree(10);
    b = new_RBTree(20);
    c = new_RBTree(30);
    d = new_RBTree(100);
    e = new_RBTree(90);
    f = new_RBTree(40);
    g = new_RBTree(50);
    h = new_RBTree(60);
    i = new_RBTree(70);
    j = new_RBTree(80);
    k = new_RBTree(150);
    l = new_RBTree(110);
    m = new_RBTree(120);

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

    inorder(t, t->root);

    search(t, 11);

    return 0;
}