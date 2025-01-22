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
        // int num;
        // cout << "Enter the number to insert: ";
        // cin >> num;
        int key = num % 10;

        if (arr[key][0] == -1) {
            // Case 1: Slot is empty
            arr[key][0] = num;
            cout << "Inserted " << num << " at slot " << key << endl;
            return;
        }

        if (arr[key][0] % 10 == key) 
        {
            // Case 2 and 3: Handle chaining
            int prevKey = key;
            while (arr[key][1] != -1) {
                key = arr[key][1];
            }
            int newKey = findNextEmptySlot(key);
            if (newKey != -1) {
                arr[newKey][0] = num;
                arr[key][1] = newKey;
                cout << "Inserted " << num << " at slot " << newKey << endl;
            } else {
                cout << "Hash table is full!" << endl;
            }
            return;
        }

        // Case 4: Replacement
        int displaced = arr[key][0];
        arr[key][0] = num;
        int newKey = findNextEmptySlot(key);
        if (newKey != -1) 
        {
            arr[newKey][0] = displaced;
            cout << "Replaced " << displaced << " with " << num << ". Moved " << displaced << " to slot " << newKey << endl;
        } else {
            cout << "Hash table is full!" << endl;
        }
    }

    void display() {
        cout << "Slot  Value   Next\n";
        for (int i = 0; i < 10; i++) {
            if(arr[i][0] == -1) //slot val empty
            {
                cout << i << "  " << "NULL"<< -1;
            }
            
            else{
                //not empty
                cout<< i<<" "<<arr[i][0]<<"  "<<arr[i][1];
            }   
        }
    }

private:
    int findNextEmptySlot(int start) {
        for (int i = (start + 1) % 10; i != start; i = (i + 1) % 10) {
            if (arr[i][0] == -1) return i;
        }
        return -1; // No empty slot found
    }
};

int main() {
    HashTable h;
    int choice;
    // while (true) {
    //     cout << "Menu:\n1. Insert\n2. Display\n3. Exit\nEnter your choice: ";
    //     cin >> choice;

    //     if (choice == 1) {
    //         h.insert();
    //     } else if (choice == 2) {
    //         h.display();
    //     } else {
    //         break;
    //     }
    // }
    int arr[] ={22, 33,52,72,44,55,45,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0 ; i<n; i++)
    {
        h.insert(arr[i]);
    }
    h.display();
    return 0;
}
