# AVL-Library
General Program Description
The program implements an AVL tree in C++ using two main classes: AVLNode and AVLTree. An AVL tree is a self-balancing binary search tree that maintains its height as logarithmic relative to the number of nodes, ensuring efficient operations for search, insertion, and deletion.

Program Structure
Header File (AVL.h):

Defines the structure of the AVLNode class, representing the nodes in the AVL tree.
Defines the AVLTree class, which manages the AVL tree.
Implementation File (main.cpp):

Implements the functions and methods declared in the header file.
Contains the main function to test the AVL tree operations.
AVLNode Class
Attributes:

int key: The key stored in the node.
AVLNode* left: Pointer to the left child.
AVLNode* right: Pointer to the right child.
int height: Height of the node.
Constructor:

Initializes the node's key, sets the children pointers to nullptr, and the height to 1.
AVLTree Class
Attributes:

AVLNode* root: Pointer to the root of the AVL tree.
Private Methods:

int height(AVLNode* node): Returns the height of a node.
int balanceFactor(AVLNode* node): Calculates the balance factor of a node.
AVLNode* rightRotate(AVLNode* y): Performs a right rotation on a node.
AVLNode* leftRotate(AVLNode* x): Performs a left rotation on a node.
AVLNode* insertNode(AVLNode* node, int key): Inserts a node into the AVL tree, maintaining balance.
AVLNode* minValueNode(AVLNode* node): Finds the node with the minimum value in a subtree.
AVLNode* deleteNode(AVLNode* root, int key): Deletes a node from the AVL tree, maintaining balance.
void printInOrderHelper(AVLNode* node): Recursively prints the nodes of the tree in order.
Public Methods:

AVLTree(): Constructor that initializes the root of the tree to nullptr.
void insert(int key): Inserts a key into the AVL tree.
void remove(int key): Removes a key from the AVL tree.
bool search(int key): Searches for a key in the AVL tree.
void printInOrder(): Prints the nodes of the tree in in-order traversal.
Program Operation
Creating the AVL Tree:

An AVLTree object is created in the main function.
Inserting Nodes:

Keys are inserted into the tree using the insert method.
Rotations (left and right) are used to maintain the balance of the tree after each insertion.
Searching for Nodes:

The search method checks if a key is present in the tree.
Deleting Nodes:

The remove method deletes a key from the tree, rebalancing the tree after each deletion.
Printing the Tree:

The printInOrder method prints the keys of the tree in ascending order, demonstrating the balanced structure of the AVL tree.
Example Usage
In the main function, the program performs the following operations:

Inserts the keys 10, 20, 30, 40, and 50 into the tree.
Prints the tree in ascending order.
Searches for the key 30 in the tree.
Removes the key 20 from the tree.
Prints the updated tree in ascending order to show the balanced structure after removal.
