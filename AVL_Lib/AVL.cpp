/*
MIT License

Copyright (c) [2024] [Ciro Santangelo]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include "AVL.h" // Including the header file where AVLTree and AVLNode classes are defined
#include <algorithm>

// Constructor for AVLNode class
AVLNode::AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(1) {}

// Constructor for AVLTree class
AVLTree::AVLTree() : root(nullptr) {}

// Function to calculate the height of a node
int AVLTree::height(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int AVLTree::balanceFactor(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to perform a right rotation
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Rotation process
    x->right = y;
    y->left = T2;

    // Update the heights of nodes
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Rotation process
    y->left = x;
    x->right = T2;

    // Update the heights of nodes
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// Function to insert a node with given key into the AVL tree
AVLNode* AVLTree::insertNode(AVLNode* node, int key) {
    if (node == nullptr)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the height of the current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Check the balance factor and perform rotations if necessary
    int balance = balanceFactor(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find the node with the minimum value in a subtree
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Function to delete a node with given key from the AVL tree
AVLNode* AVLTree::deleteNode(AVLNode* root, int key) {
    // Base case: If the tree is empty, return null
    if (root == nullptr)
        return root;

    // Recursively search for the node to be deleted
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node to be deleted found

        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;

            // Case with no child
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // Case with one child
                *root = *temp; // Copy the contents of the non-null child

            delete temp;
        } else {
            // Node with two children: find the inorder successor in the right subtree
            AVLNode* temp = minValueNode(root->right);

            // Copy the content of the inorder successor to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, return the tree
    if (root == nullptr)
        return root;

    // Update the height of the current node
    root->height = 1 + std::max(height(root->left), height(root->right));

    // Check the balance factor and perform rotations if necessary
    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a key in the AVL tree
bool AVLTree::search(int key) {
    AVLNode* current = root;
    while (current != nullptr) {
        if (key == current->key)
            return true;
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

// Function to print the AVL tree in order
void AVLTree::printInOrder() {
    printInOrderHelper(root);
}

// Helper function to print the AVL tree in order recursively
void AVLTree::printInOrderHelper(AVLNode* node) {
    if (node != nullptr) {
        printInOrderHelper(node->left);
        std::cout << node->key << " ";
        printInOrderHelper(node->right);
    }
}

// Function to insert a key into the AVL tree
void AVLTree::insert(int key) {
    root = insertNode(root, key);
}

// Function to remove a key from the AVL tree
void AVLTree::remove(int key) {
    root = deleteNode(root, key);
}

int main() {
    // Create an AVL tree object
    AVLTree tree;

    // Insert some values into the tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    // Print the tree in order
    std::cout << "AVL Tree in order: ";
    tree.printInOrder();
    std::cout << std::endl;

    // Search for a value in the tree
    int keyToSearch = 30;
    if (tree.search(keyToSearch)) {
        std::cout << "The value " << keyToSearch << " is present in the tree." << std::endl;
    } else {
        std::cout << "The value " << keyToSearch << " is not present in the tree." << std::endl;
    }

    // Remove a value from the tree
    int keyToRemove = 20;
    tree.remove(keyToRemove);
    std::cout << "Value " << keyToRemove << " removed from the tree." << std::endl;

    // Print the updated tree in order
    std::cout << "Updated AVL Tree in order: ";
    tree.printInOrder();
    std::cout << std::endl;

    return 0;
}