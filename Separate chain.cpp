#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

// Hash table size - a prime number is generally preferred to reduce collisions
const int TABLE_SIZE = 29;

// Hash function: Computes a simple hash by summing ASCII values of characters
int hashFunction(const string& word) {
    int hash = 0;
    for (char ch : word) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

// HashTable class with separate chaining
class HashTable {
private:
    // Each index holds a list of words to handle collisions (separate chaining)
    vector<list<string>> table;

public:
    HashTable() {
        table.resize(TABLE_SIZE); // Initialize vector of lists
    }

    // Insert a word into the hash table
    void insert(const string& word) {
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    // Search for a word in the hash table
    bool search(const string& word) {
        int index = hashFunction(word);
        for (auto w : table[index]) {
            if (w == word) {
                return true;
            }
        }
        return false;
    }

    // Display the contents of the hash table (optional for debugging)
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": ";
            for (auto word : table[i]) {
                cout << word << " -> ";
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable dictionary;

    // Sample list of 25 correctly spelled lowercase words
    vector<string> words = {
        "apple", "banana", "grape", "orange", "melon",
        "peach", "cherry", "lemon", "mango", "plum",
        "kiwi", "guava", "berry", "fig", "apricot",
        "pear", "date", "olive", "lime", "papaya",
        "coconut", "nectarine", "tamarind", "lychee", "blueberry"
    };

    // Insert words into the hash table
    for (auto word : words) {
        dictionary.insert(word);
    }

    cout << "Spell Checker Initialized with 25 words.\n";
    cout << "Enter words to check spelling (type 'exit' to quit):\n";

    string input;
    while (true) {
        cout << "Enter word: ";
        cin >> input;

        if (input == "exit") break;

        // Check if the word exists in the dictionary
        if (dictionary.search(input)) {
            cout << "'" << input << "' is spelled correctly.\n";
        } else {
            cout << "'" << input << "' is NOT spelled correctly.\n";
        }
    }

    return 0;
}
