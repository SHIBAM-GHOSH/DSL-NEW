#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Node {
public:
    string word;   // Word to store in dictionary
    string meaning; // Meaning of the word
    Node* next;     // Pointer to next node (for chaining in case of collision)
    
    // Constructor to initialize a node with word and meaning
    Node(string word, string meaning) {
        this->word = word;
        this->meaning = meaning;
        this->next = nullptr; // Initially, next is set to nullptr
    }
};

// Hash function to map the string (word) to an integer index for the table
int hash_func(string s) {
    int hash_value = 0;
    
    // Calculate the hash value by iterating through the string and summing up
    // the ASCII values of characters weighted by powers of 10
    for (int i = 0; i < s.length(); i++) {
        int ascii = s[i];            // ASCII value of the character
        hash_value += ascii * pow(10, i);  // Calculate hash value
    }

    // Return hash value modulo table size (to fit within array size)
    return hash_value % 10;
}

class Dictionary {
private:
    Node** dict; // Array of pointers to Nodes (for the dictionary)
    
public:
    // Constructor: Initialize the dictionary table with 10 slots (hash table)
    Dictionary() {
        dict = new Node*[10];
        for (int i = 0; i < 10; i++) {
            dict[i] = nullptr; // Set each slot to nullptr (empty)
        }
    }

    // Method to insert a new word and its meaning into the dictionary
    void put(string word, string meaning, int index) {
        // Create a new node for the word and its meaning
        Node* newNode = new Node(word, meaning);
        
        // If the slot at the index is empty, directly place the word there
        if (dict[index] == nullptr) {
            dict[index] = newNode;
        }
        else {
            // If the slot is occupied, chain the new node at the beginning
            // of the existing list (linked list)
            newNode->next = dict[index];
            dict[index] = newNode;
        }
    }

    // Method to insert a word and its meaning after taking input from the user
    void insert() {
        string word, meaning;
        
        // Take word and its meaning as input from the user
        cout << "Enter the word you want to insert: ";
        cin >> word;
        cout << "Enter the meaning of the word '" << word << "': ";
        cin >> meaning;

        // Compute the hash index for the word
        int index = hash_func(word);
        
        // Insert the word and meaning at the computed index
        put(word, meaning, index);
        
        cout << "Word successfully inserted at index " << index << ".\n";
    }

    // Method to search for a word in the dictionary
    void search() {
        string word;
        
        // Take word as input to search its meaning
        cout << "Enter the word whose meaning you want to search: ";
        cin >> word;
        
        // Compute hash index for the word
        int index = hash_func(word);
        
        // Traverse the linked list at the computed index
        Node* temp = dict[index];
        while (temp != nullptr) {
            // If the word is found, display its meaning
            if (temp->word == word) {
                cout << "The meaning of '" << word << "' is: " << temp->meaning << endl;
                return; // Exit the function once the word is found
            }
            temp = temp->next; // Move to the next node in the chain
        }
        
        // If the word is not found, print a message
        cout << "Word not found in the dictionary.\n";
    }

    // Method to display the contents of the dictionary (all words and their meanings)
    void display() {
        cout << "Dictionary is: \n";
        cout << "Word -> Meaning\n";

        // Traverse the table and print the words at each index
        for (int i = 0; i < 10; i++) {
            Node* temp = dict[i];
            cout << "Words with hash value " << i << ":\n";

            // Traverse the chain (linked list) at each slot
            while (temp != nullptr) {
                cout << temp->word << " -> " << temp->meaning << endl;
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    // Create an object of the Dictionary class
    Dictionary d;
    
    int choice;
    
    // Menu to choose operations
    while (true) {
        cout << "Enter your choice:\n1. Insert word\n2. Search Meaning\n3. Display Dictionary\n4. Exit\n";
        cin >> choice;
        
        if (choice == 1) {
            d.insert();  // Call insert method to add a new word
        }
        else if (choice == 2) {
            d.search();  // Call search method to find a word's meaning
        }
        else if (choice == 3) {
            d.display();  // Display the entire dictionary
        }
        else {
            return 0;  // Exit the program
        }
    }
    return 0;
}
