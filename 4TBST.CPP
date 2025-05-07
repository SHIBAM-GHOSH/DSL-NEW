#include <bits/stdc++.h>
using namespace std;

// Node structure for a Threaded Binary Search Tree (TBST)
class TreeNode {
public:
    int val;                  // Data value
    TreeNode* left, *right;   // Pointers to left and right children or threads
    bool lThread, rThread;    // Flags indicating if left/right is a thread (true) or a real child (false)

    TreeNode(int x) {
        val = x;
        left = right = nullptr;
        lThread = rThread = true;  // Initialize both as threads
    }
};

// Function to insert a new node into a regular (unthreaded) BST
TreeNode* insertBST(TreeNode* root, int val) {
    if (root == nullptr)
        return new TreeNode(val);

    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}

// Helper function to convert BST to TBST using inorder traversal
void createThreads(TreeNode* root, TreeNode*& prev) {
    if (root == nullptr)
        return;

    // Recurse into left subtree, left most node of subtree
    createThreads(root->left, prev);

    // Create left thread if left child is null
    if (root->left == nullptr) {
        root->left = prev;
        root->lThread = true;
    } else {
        root->lThread = false;
    }
    // Create right thread of prev if right child is null
    if (prev != nullptr && prev->right == nullptr) {
        prev->right = root;
        prev->rThread = true;
    }

    // Update previous node pointer to current node
    prev = root;

    // Recurse into right subtree
    createThreads(root->right, prev);
}

// Function to convert a BST to a Full Threaded Binary Search Tree (TBST)
TreeNode* convertToTBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    createThreads(root, prev);
    return root;
}

// Fixed insertTBST function
TreeNode* insertTBST(TreeNode* root, int key) {
    // If tree is empty
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode(key);
        return newNode;
    }
    
    TreeNode* ptr = root;
    TreeNode* parent = nullptr;
    
    // Find the position to insert
    while (true) {
        parent = ptr;
        
        // Duplicate keys not allowed
        if (key == ptr->val) {
            cout << "Duplicate keys not allowed\n";
            return root;
        }
        
        // Go to left subtree
        if (key < ptr->val) {
            if (ptr->lThread) {
                // Found position - left thread
                break;
            }
            ptr = ptr->left;
        }
        // Go to right subtree
        else {
            if (ptr->rThread) {
                // Found position - right thread
                break;
            }
            ptr = ptr->right;
        }
    }
    
    // Create new node
    TreeNode* newNode = new TreeNode(key);
    
    // Insert to the left
    if (key < parent->val) {
        // Set left and right pointers for new node
        newNode->left = parent->left;     // Left thread points to inorder predecessor
        newNode->right = parent;          // Right thread points to inorder successor
        
        // Update parent's left pointer and thread flag
        parent->lThread = false;          // No longer a thread
        parent->left = newNode;
    }
    // Insert to the right
    else {
        // Set left and right pointers for new node
        newNode->left = parent;           // Left thread points to inorder predecessor
        newNode->right = parent->right;   // Right thread points to inorder successor
        
        // Update parent's right pointer and thread flag
        parent->rThread = false;          // No longer a thread
        parent->right = newNode;
    }
    
    return root;
}

// Function to find the leftmost node in a tree (used to start inorder traversal)
TreeNode* leftmost(TreeNode* node) {
    if (node == nullptr)
        return nullptr;
        
    while (node != nullptr && !node->lThread)
        node = node->left;
    
    return node;
}

// Inorder traversal using threads (no recursion or stack)
void inorderThreadedTraversal(TreeNode* root) {
    TreeNode* curr = leftmost(root);  // Start from the leftmost node
    
    while (curr != nullptr) {
        cout << curr->val << " ";  // Visit current node
        
        // If right pointer is a thread, follow it directly to successor
        if (curr->rThread)
            curr = curr->right;
        else  // Otherwise, find leftmost in right subtree
            curr = leftmost(curr->right);
    }
}

// MAIN FUNCTION
int main() {
    TreeNode* root = nullptr;

    // Sample BST creation
    vector<int> v = {50, 30, 70, 20, 40, 60, 80};

    // Insert elements into the BST
    for (int val : v) {
        root = insertBST(root, val);
    }

    // Convert the BST to a Threaded BST (TBST)
    TreeNode* root1 = convertToTBST(root);

    // Perform inorder traversal using threads
    cout << "Inorder Traversal (Threaded BST): ";
    inorderThreadedTraversal(root1);
    cout << endl;

    // Insert another node (55) into the TBST
    root1 = insertTBST(root1, 55);

    // Perform inorder traversal after insertion of 55
    cout << "Inorder Traversal (Threaded BST) after inserting 55: ";
    inorderThreadedTraversal(root1);
    cout << endl;

    return 0;
}