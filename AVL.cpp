#include <bits/stdc++.h>
using namespace std;

// Node structure
class Node
{
    public:
      int data, height;
      Node* left, *right;
      Node(int val){
          data=val;height=1;
          left=right=NULL;
    
      }
};

// Get height of a node
int getHeight(Node* root) {
       if(root==NULL) return 0;
        return root->height;
}

// Get balance factor of a node
int getBalance(Node* node) {
    return  getHeight(node->left) - getHeight(node->right) ;
}

// Update height of a node
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Left rotation
Node* leftRotate(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;
    x->left = y;
    y->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Insert key into AVL tree
Node* insert(Node* root, int key) {
    if (!root) {
        Node* newNode = new Node(key);
        return newNode;
    }

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root; // Duplicate keys not allowed
     //update root height after insertion  
        // root is the node to which new node is inserted  
    updateHeight(root);
    int balance = getBalance(root);
     //fix unbalance
    // here root 
    // LL Case
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);
 
    // LR Case,     ,key inserted in right of left node of root
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Get height of the tree
int getTreeHeight(Node* root) {
    return getHeight(root);
}

// Driver code to test the program
int main() {
    Node *root=NULL;
    vector<int>v = {10,20,30,50,70,5,100,95};
    for(int i: v)
        {  root=insert(root, i);}
 
    cout<<endl;
    inorder(root);

}
