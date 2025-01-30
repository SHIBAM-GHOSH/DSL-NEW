#include <iostream>
#include <vector>
using namespace std;

class HashTable {
    vector<pair<int, int>> table;  // Stores (value, next)
    vector<int> lastIndex;  // Tracks last inserted index for each hash key

public:
    HashTable() {
        // Set table size to 10, initially all values are empty (-1)
        table = vector<pair<int, int>>(10, {-1, -1});

        // Set lastIndex size to 10, initially no values inserted (-1)
        lastIndex = vector<int>(10, -1);
    }

    void insert(int num) {
        int key = num % 10;
        cout << "\nInserting: " << num << " (Key: " << key << ")" << endl;

        int index = key;

        // Find the next available slot using linear probing
        while (table[index].first != -1) {
            index = (index + 1) % 10;
        }

        // Insert value at the found index
        table[index] = {num, -1};

        // If there was a previous value with the same hash key, update its next pointer
        if (lastIndex[key] != -1) {
            table[lastIndex[key]].second = index;
        }

        // Update last inserted index for this hash key
        lastIndex[key] = index;

        // Print placement message
        if (index == key) {
            cout << "Placed at slot " << index << " (No chaining needed)\n";
        } else {
            cout << "Placed at slot " << index << " (Chained from " << lastIndex[key] << ")\n";
        }
    }

    void display() {
        cout << "\nSlot | Value | Next\n";
        cout << "--------------------\n";
        for (int i = 0; i < 10; i++) {
            if (table[i].first == -1) {
                cout << "  " << i << "  | NULL  | -1\n";
            } else {
                cout << "  " << i << "  |  " << table[i].first << "   | " << table[i].second << endl;
            }
        }
    }
};

int main() {
    HashTable h;

    vector<int> testCases = {22, 32, 33, 44, 55, 52, 72, 45, 35};  // Test input

    cout << "--- Inserting Elements ---\n";
    for (int num : testCases) {
        h.insert(num);
    }

    h.display();  // Display the hash table

    return 0;
}
