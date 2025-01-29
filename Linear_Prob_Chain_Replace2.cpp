#include <iostream>
using namespace std;

class HashTable {
    int arr[10][2]; // [value, next index]

public:
    HashTable() {
        for (int i = 0; i < 10; i++) {
            arr[i][0] = -1; // Initialize all slots as empty
            arr[i][1] = -1; // No chaining initially
        }
    }

    void insert(int num) {
        int key = num % 10;

        // Case 1: Slot is empty
        if (arr[key][0] == -1) {
            arr[key][0] = num;
            arr[key][1] = -1; // No chaining needed for now
            cout << "Inserted " << num << " at slot " << key << endl;
            return;
        }

        // Handle collisions with chaining (linear probing)
        int currentKey = key;
        while (arr[currentKey][1] != -1) {
            currentKey = arr[currentKey][1]; // Move to the next slot in chain
        }
        
        // Try to find the next available empty slot to insert
        int newKey = findNextEmptySlot(currentKey);
        if (newKey != -1) {
            arr[newKey][0] = num;
            arr[currentKey][1] = newKey;  // Update the "next" pointer for the chain
            arr[newKey][1] = -1; // End of chain
            cout << "Inserted " << num << " at slot " << newKey << endl;
        } else {
            cout << "Hash table is full!" << endl;
        }
    }

    void display() {
        cout << "Slot  Value   Next\n";
        for (int i = 0; i < 10; i++) {
            if (arr[i][0] == -1) {
                cout << i << "  NULL -1\n"; // Empty slot
            } else {
                cout << i << "  " << arr[i][0] << "   " << arr[i][1] << endl;
            }
        }
    }

private:
    int findNextEmptySlot(int start) {
        for (int i = (start + 1) % 10; i != start; i = (i + 1) % 10) {
            if (arr[i][0] == -1) return i;  // Found empty slot
        }
        return -1; // No empty slot found
    }
};

int main() {
    HashTable h;
    int arr[] = {22, 33, 44, 55, 52, 72, 45, 35}; // Test case array
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        h.insert(arr[i]);
    }

    h.display();  // Display the hash table content after insertion

    return 0;
}
