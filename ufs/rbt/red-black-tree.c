#include <stdio.h>
#include <stdlib.h>

enum COLOR
{
    Red,
    Black
};

typedef struct tree_node
{
    int data;
    struct tree_node *right;
    struct tree_node *left;
    struct tree_node *parent;
    enum COLOR color;
} tree_node;

typedef struct red_black_tree
{
    tree_node *root;
    tree_node *NIL;
} red_black_tree;

tree_node* globalRoot = NULL;

tree_node *new_RBTree(int data)
{
    tree_node *n = malloc(sizeof(tree_node));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->data = data;
    n->color = Red;

    return n;
}

red_black_tree *new_red_black_tree()
{
    red_black_tree *t = malloc(sizeof(red_black_tree));
    tree_node *nil_node = malloc(sizeof(tree_node));
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->parent = NULL;
    nil_node->color = Black;
    nil_node->data = 0;
    t->NIL = nil_node;
    t->root = t->NIL;

    return t;
}

void leftRotate(red_black_tree *tree,tree_node *node)
{
    tree_node *right = node->right;
    node->right = right->left;
    if (right->left != tree->NIL) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == tree->NIL)
    { // node is root
        tree->root = right;
    }
    else if (node == node->parent->left)
    { // node is left child
        node->parent->left = right;
    }
    else
    { // node is right child
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void rightRotate(red_black_tree *tree, tree_node *node)
{
    tree_node *left = node->left;
    node->left = left->right;
    if (left->right != tree->NIL)
    {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == tree->NIL)
    { // node is root
        tree->root = left;
    }
    else if (node == node->parent->right)
    { // node is left child
        node->parent->right = left;
    }
    else
    { // node is right child
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

void insertion_fixup(red_black_tree *tree, tree_node *node) {
    while (node->parent->color == Red) {   
        tree_node * parent = node->parent;
        tree_node * grandparent = node->parent->parent;
        //  parent            .left
        if (parent == grandparent->left) // o nó pai é filho esquerdo de um avó
        {

            tree_node *uncle = grandparent->right; // tio de node
            //tio vermelho
            if (uncle->color == Red)
            { // caso 1
                parent->color = Black;
                uncle->color = Black;
                grandparent->color = Red;
                node = grandparent;
                //proxima iteração...
            }
            else { //tio preto
                // case2
                if (node == parent->right) { 
                    node = node->parent; // marked node.parent as new node
                    leftRotate(tree, node);
                }
                // case3
                node->parent->color = Black;       
                node->parent->parent->color = Red;
                rightRotate(tree, node->parent->parent);
            }
        }
        else
        {                                           // node.parent is the right child
            tree_node *uncle = node->parent->parent->left; // uncle of node

            if (uncle->color == Red)
            {
                node->parent->color = Black;
                uncle->color = Black;
                node->parent->parent->color = Red;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent; // marked node.parent as new node
                    rightRotate(tree, node);
                }
                node->parent->color = Black;       // made parent black
                node->parent->parent->color = Red; // made parent red
                leftRotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = Black;
}

void insert(red_black_tree *tree, tree_node *newNode) 
{
    tree_node *parentOfNewNode = tree->NIL;
    tree_node *current = tree->root;

    /* encontra o pai do novo newNode */
    while (current != tree->NIL) {
        parentOfNewNode = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parentOfNewNode;

    //se arvore vazia, o newNode é raiz, se for menor que seu pai adiciona a esquerda, senao a direita
    if (parentOfNewNode == tree->NIL)  {
        tree->root = newNode;
    }
    else if (newNode->data < parentOfNewNode->data)
        parentOfNewNode->left = newNode;
    else
        parentOfNewNode->right = newNode;

    newNode->right = tree->NIL;
    newNode->left = tree->NIL;

    insertion_fixup(tree, newNode);
}

void rb_transplant(red_black_tree *tree, tree_node *node, tree_node *children) 
{
    if (node->parent == tree->NIL)
        tree->root = children;
    else if (node == node->parent->left)
        node->parent->left = children;
    else
        node->parent->right = children;
    children->parent = node->parent;
}

tree_node *minimum(red_black_tree *tree, tree_node *node)
{
    while (node->left != tree->NIL)
        node = node->left;
    return node;
}

void rb_delete_fixup(red_black_tree *tree, tree_node *node)
{
    while (node != tree->root && node->color == Black)
    { /* se o no é filho esquerdo do pai */
        if (node == node->parent->left)
        {
            tree_node *sibling = node->parent->right;
            /* CASO 1; se o irmao for vermelho, recolore o irmao e pai,
            para fazer a rotação
              */
            if (sibling->color == Red)
            {
                //recolorToLeftRotate()
                sibling->color = Black;
                node->parent->color = Red;
                leftRotate(tree, node->parent);
                //updateSibling()
                sibling = node->parent->right;
            }
            /* CASO 2; irmao preto entao recolore e passa para o pai */
            if (sibling->left->color == Black && sibling->right->color == Black)
            {
                sibling->color = Red; //recolor sibling
                node = node->parent;
            }
            else
            {   /* CASO 3: filho esquedo vermelho e direito preto */
                if (sibling->right->color == Black)
                {
                    //recolorir
                    sibling->color = Red;
                    sibling->left->color = Black;
                    rightRotate(tree, sibling);
                    //atualizando irmao
                    sibling = node->parent->right;
                }
                /* CASO 4: filho direito vermelho */
                sibling->color = node->parent->color;
                node->parent->color = Black;
                sibling->right->color = Black;
                leftRotate(tree, node->parent);
                node = tree->root;
            }
        }
        else /* mesma coisa só que para o caso de ser o filho direito de um pai */
        {
            tree_node *sibling = node->parent->left;
            if (sibling->color == Red)
            {
                sibling->color = Black;
                node->parent->color = Red;
                rightRotate(tree, node->parent);
                sibling = node->parent->left;
            }
            if (sibling->right->color == Black && sibling->left->color == Black)
            {
                sibling->color = Red;
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == Black)
                {
                    sibling->right->color = Black;
                    sibling->color = Red;
                    leftRotate(tree, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = Black;
                sibling->left->color = Black;
                rightRotate(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = Black;
}

void rb_delete(red_black_tree *tree, tree_node *node)
{
    tree_node *successor = node;
    tree_node *children;
    enum COLOR successor_orignal_color = successor->color;
    /* caso um dos lados estiver NULL entao basta transplantar o lado
    não nulo para o nó que deseja remover
     */
    if (node->left == tree->NIL) {
        children = node->right;
        rb_transplant(tree, node, node->right);
    }
    else if (node->right == tree->NIL) {
        children = node->left;
        rb_transplant(tree, node, node->left);
    }
    /* caso nenhum os 2 lados tenham filhos */
    else {
        successor = minimum(tree, node->right);
        children = successor->right;
        successor_orignal_color = successor->color; /* preciso guardar a cor para colocar no node que vai ser removido */
        /* caso o sucessor seja filho imediato de node 
        eu tenho que ter certeza que ele esta apontando
        para node pois se children for nulo entao teremos 
        problemas na hora de balancear
         */
        if (successor->parent == node) {
            children->parent = successor;
        }
        else {
            rb_transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        rb_transplant(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }
    /* se o no sucessor  */
    if (successor_orignal_color == Black)
        rb_delete_fixup(tree, children);
}

void inorder(red_black_tree *t, tree_node *n)
{
    if (n != t->NIL)
    {
        inorder(t, n->left);
        printf("%d\n", n->data);
        inorder(t, n->right);
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

    return 0;
}