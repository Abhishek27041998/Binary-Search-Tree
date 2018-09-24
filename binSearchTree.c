#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;

	struct Node *left;
	struct Node *right;
};

typedef struct Node Node;

Node* createNode(int data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;

	newNode->left  = NULL;
	newNode->right = NULL;

	return newNode;
}

Node* insert(Node *root, int data)
{
	Node *node = (Node*)malloc(sizeof(Node));

	node->data = data;
	
	node->left = node->right = NULL;

	if(root == NULL)
		return node;
	
	Node *par = NULL, *cur = root;

	while(cur != NULL)
	{
		par = cur;
		
		if(cur->data <= data)
			cur = cur->right;
		else
			cur = cur->left;
	}

	if(par->data <= data)
		par->right = node;
	else
		par->left = node;

	return root;
}

Node* insertRec(Node *root, int data)
{
	if(root == NULL)
	{
		Node *node = (Node*)malloc(sizeof(Node));

		node->data = data;
	
		node->left = node->right = NULL;
		
		return node;
		
	}

	if(root->data <= data)
		root->right = insertRec(root->right,data);
	else
		root->left  = insertRec(root->left,data);

	return root;
}

void inorder(Node *root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	
	printf("%d ",root->data);
	
	inorder(root->right);
}


Node* search(Node *root, int key)
{
	if(root == NULL)
		return NULL;

	if(root->data == key)
		return root;

	if(root->data < key)	
		return search(root->right,key);
	else
		return search(root->left,key);

}

int size(Node *root)
{
	if(!root)
		return 0;

	int leftTreeSize = size(root->left);
	int rightTreeSize = size(root->right);

	return 1+leftTreeSize + rightTreeSize;
}

int height(Node *root)
{
	if(!root)
		return 0;

	int leftTreeHeight = height(root->left);
	int rightTreeHeight = height(root->right);

	return 1 + ((leftTreeHeight > rightTreeHeight) ? leftTreeHeight : rightTreeHeight);
}


void levelOrderTra(Node *root)
{
	if(!root)
		return;

	Node *queue[50];
	int rear = 0, front = 0;

	queue[rear++] = root;

	while(front != rear)
	{	
		Node *dt = queue[front++];

		printf("%d ",dt->data);

		if(dt->left != NULL)
			queue[rear++] = dt->left;
		
		if(dt->right != NULL)
			queue[rear++] = dt->right;

	}
}

Node* lowestCommonAncestor(Node *root, int data1, int data2)
{
	if(root->data > (data1 > data2 ? data1 : data2))
		return lowestCommonAncestor(root->left,data1,data2);
	else if(root->data < (data1 < data2 ? data1 : data2))
		return lowestCommonAncestor(root->right,data1,data2);
	else
		return root;
			
}

int main()
{
	/*           5
		    / \
		   3   7
                  / \ / \
                 2  4 6  8
			  \
			   9
			    \
			    10
	*/


	Node *root = NULL;

	root = insert(root,5);
	root = insert(root,3);
	root = insert(root,7);
	root = insert(root,2);
	root = insertRec(root,4);
	root = insertRec(root,6);
	root = insertRec(root,8);
	root = insertRec(root,9);
	root = insertRec(root,10);
	
	inorder(root);

	Node *sea = search(root, 6);

	if(search)
		printf("\nFound %d\n",sea->data);
	else
		printf("Not Found\n");

	printf("Size : %d\n",size(root));

	printf("Height : %d\n",height(root));

	printf("Level Order Traversal : ");
	
	levelOrderTra(root);
	
	Node *lca = lowestCommonAncestor(root,6,9);

	printf("\nLCA of %d %d is %d\n",6,9,lca->data);

	return 0;
}
