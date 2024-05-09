#include <iostream>
using namespace std;

/* A Doubly Linked List node that
will also be used as a tree node */
class NodoUsuario
{
public:
	int index;
	int data;

	// For tree, next pointer can be
	// used as right subtree pointer 
	NodoUsuario* next;

	// For tree, prev pointer can be
	// used as left subtree pointer 
	NodoUsuario* prev;
};

// A utility function to count nodes in a Linked List 
int countNodes(NodoUsuario* head);

NodoUsuario* sortedListToBSTRecur(NodoUsuario** head_ref, int n);

/* This function counts the number of
nodes in Linked List and then calls
sortedListToBSTRecur() to construct BST */
NodoUsuario* sortedListToBST(NodoUsuario* head)
{
	/*Count the number of nodes in Linked List */
	int n = countNodes(head);

	/* Construct BST */
	return sortedListToBSTRecur(&head, n);
}

/* The main function that constructs
balanced BST and returns root of it.
head_ref --> Pointer to pointer to
head node of Doubly linked list
n --> No. of nodes in the Doubly Linked List */
NodoUsuario* sortedListToBSTRecur(NodoUsuario** head_ref, int n)
{
	/* Base Case */
	if (n <= 0)
		return NULL;

	/* Recursively construct the left subtree */
	NodoUsuario* prev = sortedListToBSTRecur(head_ref, n / 2);

	/* head_ref now refers to middle node,
	make middle node as root of BST*/
	NodoUsuario* root = *head_ref;

	// Set pointer to left subtree 
	root->prev = prev;

	/* Change head pointer of Linked List
	for parent recursive calls */
	*head_ref = (*head_ref)->next;

	/* Recursively construct the right
	subtree and link it with root
	The number of nodes in right subtree
	is total nodes - nodes in
	left subtree - 1 (for root) */
	root->next = sortedListToBSTRecur(head_ref, n - n / 2 - 1);

	return root;
}

/* UTILITY FUNCTIONS */
/* A utility function that returns
count of nodes in a given Linked List */
int countNodes(NodoUsuario* head)
{
	int count = 0;
	NodoUsuario* temp = head;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

/* Function to insert a node at
the beginning of the Doubly Linked List */
void push(NodoUsuario** head_ref, int index, int new_data)
{
	/* allocate node */
	NodoUsuario* new_node = new NodoUsuario();

	/* put in the data */
	new_node->data = new_data;
	new_node->index = index;

	/* since we are adding at the beginning,
	prev is always NULL */
	new_node->prev = NULL;

	/* link the old list of the new node */
	new_node->next = (*head_ref);

	/* change prev of head node to new node */
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Function to print nodes in a given linked list */
void printList(NodoUsuario* NodoUsuario)
{
	while (NodoUsuario != NULL)
	{
		cout << NodoUsuario->index << " " << NodoUsuario->data << "\n";
		NodoUsuario = NodoUsuario->next;
	}
}

/* A utility function to print
preorder traversal of BST */
void preOrder(NodoUsuario* NodoUsuario)
{
	if (NodoUsuario == NULL)
		return;
	cout << NodoUsuario->index << " " << NodoUsuario->data << "\n";
	preOrder(NodoUsuario->prev);
	preOrder(NodoUsuario->next);
}
// A C++ program for in-place conversion of Binary Tree to
// DLL
#include <iostream>
using namespace std;

// A simple recursive function to convert a given Binary
// tree to Doubly Linked List root --> Root of Binary Tree
// head --> Pointer to head node of created doubly linked
// list
void BinaryTree2DoubleLinkedList(NodoUsuario* root, NodoUsuario** head)
{
	// Base case
	if (root == NULL)
		return;

	// Initialize previously visited node as NULL. This is
	// static so that the same value is accessible in all
	// recursive calls
	static NodoUsuario* prev = NULL;

	// Recursively convert left subtree
	BinaryTree2DoubleLinkedList(root->prev, head);

	// Now convert this node
	if (prev == NULL)
		*head = root;
	else {
		root->prev = prev;
		prev->next = root;
	}
	prev = root;

	// Finally convert right subtree
	BinaryTree2DoubleLinkedList(root->next, head);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
NodoUsuario* newNode(int data)
{
	NodoUsuario* new_node = new NodoUsuario;
	new_node->data = data;
	new_node->prev = new_node->next = NULL;
	return (new_node);
}
/* Driver code*/
int main()
{
	/* Start with the empty list */
	NodoUsuario* head = NULL;

	/* Let us create a sorted linked list to test the functions
	Created linked list will be 7->6->5->4->3->2->1 */
	push(&head, 1, 7);
	push(&head, 2, 6);
	push(&head, 3, 5);
	push(&head, 4, 4);
	push(&head, 5, 3);
	push(&head, 6, 2);
	push(&head, 7, 1);

	cout << "Given Linked List\n";
	printList(head);

	/* Convert List to BST */
	NodoUsuario* root = sortedListToBST(head);
	cout << "\nPreOrder Traversal of constructed BST \n ";
	preOrder(root);

	
	// Convert to DLL
	BinaryTree2DoubleLinkedList(root, &head);
	cout << "\nDLL reconversion\n ";
	// Print the converted list
	printList(head);

	return 0;
}

// This code is contributed by rathbhupendra
