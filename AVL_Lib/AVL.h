#ifndef AVL_TREE_H 
#define AVL_TREE_H

struct AVLNode{
    int key; 
    AVLNode*left; 
    AVLNode*right; 
    int height; 

    AVLNode(int key); 
};

class AVLTree{

private:
     AVLNode*root; 

    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, int key);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* deleteNode(AVLNode* root, int key); 

    void printInOrderHelper(AVLNode* node);

public: 
   AVLTree(); 

   void insert(int key); 
   void remove(int key); 
   bool search(int key); 
   void printInOrder(); 
};

#endif/* AVL_TREE_H */
