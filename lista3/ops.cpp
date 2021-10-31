#include <bits/stdc++.h>
using namespace std;


/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct node
{
	int data;
	struct node *left;
	struct node *right;
};

// A utility function to create a node
struct node* newNode (int data)
{
	struct node* temp = (struct node *) malloc( sizeof(struct node) );

	temp->data = data;
	temp->left = temp->right = NULL;

	return temp;
}

// A recursive function to construct Full from pre[]. preIndex is used
// to keep track of index in pre[].
struct node* constructTreeUtil (int pre[], int* preIndex,
								int low, int high, int size)
{
	// Base case
	if (*preIndex >= size || low > high)
		return NULL;

	// The first node in preorder traversal is root. So take the node at
	// preIndex from pre[] and make it root, and increment preIndex
	struct node* root = newNode ( pre[*preIndex] );
	*preIndex = *preIndex + 1;

	// If the current subarry has only one element, no need to recur
	if (low == high)
		return root;

	// Search for the first element greater than root
	int i;
	for ( i = low; i <= high; ++i )
		if ( pre[ i ] > root->data )
			break;

	// Use the index of element found in preorder to divide preorder array in
	// two parts. Left subtree and right subtree
	root->left = constructTreeUtil ( pre, preIndex, *preIndex, i - 1, size );
	root->right = constructTreeUtil ( pre, preIndex, i, high, size );

	return root;
}

// The main function to construct BST from given preorder traversal.
// This function mainly uses constructTreeUtil()
struct node *constructTree (int pre[], int size)
{
	int preIndex = 0;
	return constructTreeUtil (pre, &preIndex, 0, size - 1, size);
}

// A utility function to print inorder traversal of a Binary Tree
void printInorder (struct node* node)
{
	if (node == NULL)
		return;
	printInorder(node->left);
	cout<<node->data<<" ";
	printInorder(node->right);
}

// Driver program to test above functions
int main ()
{
	int pre[] = {3, 1, 0, 2, 4, 8, 6, 5, 7};
	int size = sizeof( pre ) / sizeof( pre[0] );

	struct node *root = constructTree(pre, size);

	cout<< "Inorder traversal of the constructed tree: "<<endl;
	printInorder(root);

	return 0;
}