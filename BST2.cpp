#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        val = value;
        left = right = NULL;
    }
};

//----------------- BST INSERTION --------------------
TreeNode* insertBST(TreeNode* root, int value) {
    if (!root) return new TreeNode(value);
    if (value < root->val)
        root->left = insertBST(root->left, value);
    else
        root->right = insertBST(root->right, value);
    return root;
}

//----------------- USER INPUT -----------------------
void inputTree(TreeNode*& root) {
    int value;
    cout << "Enter BST elements (-1 to stop): ";
    cin >> value;
    while (value != -1) {
        root = insertBST(root, value);
        cin >> value;
    }
}

//------------------ LEVEL ORDER ---------------------
void printLevelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* node = q.front(); q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

//------------------ RECURSIVE TRAVERSALS ---------------------
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(TreeNode* root) {
    if (!root) return;
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->val << " ";
}

//------------------ ITERATIVE TRAVERSALS ---------------------
void iterativeInorder(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top(); s.pop();
        cout << curr->val << " ";
        curr = curr->right;
    }
}

void iterativePreorder(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top(); s.pop();
        cout << node->val << " ";
        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
}

void iterativePostorder(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        TreeNode* node = s1.top(); s1.pop();
        s2.push(node);
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
    }
}

//------------------ HEIGHT OF TREE ---------------------
int treeHeight(TreeNode* root) {
    if (!root) return 0;
    return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}

//------------------ CLONE A TREE ---------------------
TreeNode* cloneTree(TreeNode* root) {
    if (!root) return nullptr;
    TreeNode* newNode = new TreeNode(root->val);
    newNode->left = cloneTree(root->left);
    newNode->right = cloneTree(root->right);
    return newNode;
}

//------------------ DELETE ENTIRE TREE ---------------------
void deleteTree(TreeNode*& root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

//------------------ MIRROR TREE ---------------------
TreeNode* mirrorTree(TreeNode* root) {
    if (!root) return nullptr;
    TreeNode* mirrored = new TreeNode(root->val);
    mirrored->left = mirrorTree(root->right);
    mirrored->right = mirrorTree(root->left);
    return mirrored;
}

//------------------ CONSTRUCT FROM INORDER + PREORDER ---------------------
TreeNode* build(vector<int>& preorder, int prelo, int prehi, vector<int>& inorder, int inlo, int inhi) {
    if (prelo > prehi) return NULL;
    TreeNode* root = new TreeNode(preorder[prelo]);
    if (prelo == prehi) return root;

    int i = inlo;
    while (i <= inhi && inorder[i] != preorder[prelo]) i++;

    int leftcount = i - inlo;
    root->left = build(preorder, prelo + 1, prelo + leftcount, inorder, inlo, i - 1);
    root->right = build(preorder, prelo + leftcount + 1, prehi, inorder, i + 1, inhi);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int n = preorder.size();
    return build(preorder, 0, n - 1, inorder, 0, n - 1);
}

//------------------ CHECK EQUALITY ---------------------
bool areTreesEqual(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;  // both null
    if (!a || !b) return false; // one of them null
    return (a->val == b->val) &&
           areTreesEqual(a->left, b->left) &&
           areTreesEqual(a->right, b->right);
}

//------------------ SEARCH ---------------------
bool searchInBST(TreeNode* root, int value) {
    if (root==NULL) return false;
    if (root->val == value) return true;
    return (value < root->val) ? searchInBST(root->left, value) : searchInBST(root->right, value);
}

//------------------ DELETE A NODE USING INORDER PREDECESSOR ---------------------
TreeNode* iop(TreeNode* root) {
    TreeNode* pred = root->left;
    while (pred->right)
        pred = pred->right;
    return pred;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return NULL;

    if (root->val == key) {
        // Case 1: No child
        if (!root->left && !root->right)
            return NULL;
        // Case 2: One child
        if (!root->left || !root->right)
            return root->left ? root->left : root->right;
        // Case 3: Two children
        TreeNode* pred = iop(root);
        root->val = pred->val;
        root->left = deleteNode(root->left, pred->val);
    }
    else if (key < root->val)
        root->left = deleteNode(root->left, key);
    else
        root->right = deleteNode(root->right, key);

    return root;
}   

//------------------ MAIN FUNCTION ---------------------
int main() {
    TreeNode* root = nullptr;
    inputTree(root);

    cout << "\nLevel-order traversal:\n";
    printLevelOrder(root);

    cout << "\nInorder (recursive): "; printInorder(root);
    cout << "\nPreorder (recursive): "; printPreorder(root);
    cout << "\nPostorder (recursive): "; printPostorder(root);

    cout << "\nInorder (iterative): "; iterativeInorder(root);
    cout << "\nPreorder (iterative): "; iterativePreorder(root);
    cout << "\nPostorder (iterative): "; iterativePostorder(root);

    cout << "\n\nHeight of tree: " << treeHeight(root) << endl;

    TreeNode* clone = cloneTree(root);
    deleteTree(root);
    cout << "\nOriginal tree deleted. Clone's inorder: ";
    printInorder(clone);

    TreeNode* mirror = mirrorTree(clone);
    cout << "\nMirror of cloned tree (inorder): ";
    printInorder(mirror);

    vector<int> inorder = {20, 30, 40, 50, 60, 70};
    vector<int> preorder = {50, 30, 20, 40, 70, 60};
    TreeNode* constructed = buildTree(preorder, inorder);
    cout << "\n\nConstructed tree from inorder & preorder (inorder): ";
    printInorder(constructed);

    cout << "\n\nAre clone and constructed tree equal? " << (areTreesEqual(clone, constructed) ? "Yes" : "No") << endl;

    return 0;
}
