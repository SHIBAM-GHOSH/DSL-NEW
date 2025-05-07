#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Structure of a Huffman Tree Node
class Node {
  public:  
    char ch;              // Character
    int freq;             // Frequency of character
   Node *left;    // Left child
   Node *right;   // Right child

   Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Comparison object for min-heap priority queue
struct Compare {
    bool operator()( Node* a,Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to generate Huffman codes from the tree
void generateHuffmanCodes(Node* root, string code, 
                    unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    // If it's a leaf node (has a character)
    if (root->left==NULL && root->right==NULL) { // if its a bottom node 
        huffmanCode[root->ch] = code;      // store the code
    }
    // Traverse left with '0' added to code
    generateHuffmanCodes(root->left, code + "0", huffmanCode);
    // Traverse right with '1' added to code
    generateHuffmanCodes(root->right, code + "1", huffmanCode);
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(const unordered_map<char, int> &freqMap) {
    priority_queue< Node*, vector< Node*>, Compare> pq;

    // Create a leaf node for each character and push into min-heap
    for (auto pair : freqMap) {
        pq.push( new Node(pair.first, pair.second));
    }

    // Iterate until the heap has only one node
    while (pq.size() > 1) {
       Node* left = pq.top(); pq.pop(); //1st smallest
       Node* right = pq.top(); pq.pop();  // 2nd smallest

        // Merge the two nodes
       Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();  // Root of the Huffman Tree
}

// Function to encode the input string using Huffman codes
string encodeString(const string &input,  unordered_map<char, string> &huffmanCode) {
    string encoded;
    for (char ch : input) {
         encoded += huffmanCode[ch];
    }
    return encoded;
}

int main() {
    unordered_map<char, int> freqMap;
    int n;

    // --- Input Section ---
    cout << "Enter number of characters: ";
    cin >> n;
    cout << "Enter characters and their frequencies:\n";
    for (int i = 0; i < n; ++i) {
        char ch;
        int freq;
        cin >> ch >> freq;
        freqMap[ch] = freq;
    }

    // --- Build Huffman Tree ---
   Node* root = buildHuffmanTree(freqMap);

    // --- Generate Huffman Codes ---
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    // --- Print Huffman Codes ---
    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // --- Encode a String ---
    string inputStr;
    cout << "\nEnter string to encode using Huffman coding: ";
    cin >> inputStr;

    string encodedStr = encodeString(inputStr, huffmanCode);
    cout << "Encoded String: " << encodedStr << endl;

    return 0;
}
