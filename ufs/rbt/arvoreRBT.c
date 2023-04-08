/** C implementation for
	Red-Black Tree insert
	This code is provided by
	costheta_z **/
#include <stdio.h>
#include <stdlib.h>

// Structure to represent each
// node in a red-black tree
typedef struct node {
	int data; // data
	int color; // 1-red, 0-black
	struct node* parent; // parent
	struct node* right; // right-child
	struct node* left; // left child
} RBTree;

// Raíz global para toda a árvore.
RBTree* globalRoot = NULL;

// Function performing right rotation
// of the passed node
void rightrotate(RBTree* newNode)
{
	RBTree* left = newNode->left;
	newNode->left = left->right;
	if (newNode->left)
		newNode->left->parent = newNode;

	left->parent = newNode->parent;

	if (!newNode->parent)
		globalRoot = left;
	else if (newNode == newNode->parent->left)
		newNode->parent->left = left;
	else
		newNode->parent->right = left;

	left->right = newNode;
	newNode->parent = left;
}

// Function performing left rotation
// of the passed node
void leftrotate(RBTree* newNode)
{
	RBTree* right = newNode->right;
	newNode->right = right->left;
	if (newNode->right)
		newNode->right->parent = newNode;
	right->parent = newNode->parent;
	if (!newNode->parent)
		globalRoot = right;
	else if (newNode == newNode->parent->left)
		newNode->parent->left = right;
	else
		newNode->parent->right = right;
	right->left = newNode;
	newNode->parent = right;
}

// Função para corrigir as violações causadas pela inserção.
void fixup(RBTree* root, RBTree* newNode)
{
	RBTree* parent_newNode = NULL;
	RBTree* grand_parent_newNode = NULL;

	// NO diferente da raiz && cor do no for vermelha && cor do pai for vermelha
	while ((newNode != root) && (newNode->color != 0)
		&& (newNode->parent->color == 1))
	{
		parent_newNode = newNode->parent;
		grand_parent_newNode = newNode->parent->parent;

		/* Case : A
			Parent of newNode is left child
			of Grand-parent of
		newNode */
		if (parent_newNode == grand_parent_newNode->left)
		{

			RBTree* uncle_newNode = grand_parent_newNode->right;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (uncle_newNode != NULL && uncle_newNode->color == 1)
			{
				grand_parent_newNode->color = 1;
				parent_newNode->color = 0;
				uncle_newNode->color = 0;
				newNode = grand_parent_newNode;
			}

			else {

				/* Case : 2
					newNode is right child of its parent
					Left-rotation required */
				if (newNode == parent_newNode->right) {
					leftrotate(parent_newNode);
					newNode = parent_newNode;
					parent_newNode = newNode->parent;
				}

				/* Case : 3
					pt is left child of its parent
					Right-rotation required */
				rightrotate(grand_parent_newNode);
				int t = parent_newNode->color;
				parent_newNode->color = grand_parent_newNode->color;
				grand_parent_newNode->color = t;
				newNode = parent_newNode;
			}
		}

		/* Case : B
			Parent of newNode is right
			child of Grand-parent of
		newNode */
		else {
			RBTree* uncle_newNode = grand_parent_newNode->left;

			/* Case : 1
				The uncle of newNode is also red
				Only Recoloring required */
			if ((uncle_newNode != NULL) && (uncle_newNode->color == 1))
			{
				grand_parent_newNode->color = 1;
				parent_newNode->color = 0;
				uncle_newNode->color = 0;
				newNode = grand_parent_newNode;
			}
			else {
				/* Case : 2
				newNode is left child of its parent
				Right-rotation required */
				if (newNode == parent_newNode->left) {
					rightrotate(parent_newNode);
					newNode = parent_newNode;
					parent_newNode = newNode->parent;
				}

				/* Case : 3
					newNode is right child of its parent
					Left-rotation required */
				leftrotate(grand_parent_newNode);
				int t = parent_newNode->color;
				parent_newNode->color = grand_parent_newNode->color;
				grand_parent_newNode->color = t;
				newNode = parent_newNode;
			}
		}
	}
	root->color = 0;
}

// Função para executar a inserção de um NÓ em uma BST.
RBTree* insertBST(RBTree* root, RBTree* newNode)
{
	if (root == NULL) return newNode;

	if (newNode->data < root->data)
	{
		root->left = insertBST(root->left, newNode);
		root->left->parent = root;
	}
	else if (newNode->data > root->data)
	{
		root->right = insertBST(root->right, newNode);
		root->right->parent = root;
	};

	return root;
}

void insertRBT(RBTree* root, RBTree* newNode)
{	
	globalRoot = insertBST(root, newNode);
	fixup(globalRoot, newNode);
	return;
}

RBTree* search(RBTree* root, int value) {
    // Percorre a árvore a partir da raiz
    while (root != NULL && root->data != value) {
        if (value < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    // Verifica se o valor foi encontrado ou não
    if (root == NULL) {
        printf("Valor nao encontrado na arvore.\n");
        return NULL;
    } else {
        printf("Valor encontrado na arvore.\n");
        return root;
    }
}
// Function to print inorder traversal
// of the fixated tree
void inorder(RBTree* trav)
{
	if (trav == NULL)
		return;
	inorder(trav->left);
	printf("%d ", trav->data);
	inorder(trav->right);
}

// driver code
int main()
{
	int n = 7;
	int a[7] = { 7, 6, 5, 4, 3, 2, 1};

	for (int i = 0; i < n; i++) {

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array
		RBTree* temp = (RBTree*) malloc(sizeof(RBTree));
		temp->right = NULL;
		temp->left = NULL;
		temp->parent = NULL;
		temp->data = a[i];
		temp->color = 1;

		// calling function that performs insert insert of
		// this newly created node
		// globalRoot = insertBST(globalRoot, temp);
		// fixup(globalRoot, temp);
		insertRBT(globalRoot, temp);



		// calling function to preserve properties of rb
		// tree
	}

	// search(globalRoot, 5);

	printf("Inorder Traversal of Created Tree\n");
	inorder(globalRoot);

	return 0;
}
