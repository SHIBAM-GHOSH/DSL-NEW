#include<iostream>
using namespace std;

// Definition of node structure for the linked list
class node {
public:
    int data;  // Holds the data of the node
    node *next;  // Pointer to the next node in the list

    node(int data) {
        this->data = data;
        this->next = nullptr;  // Initially, next is nullptr as it's the last node
    }
};

// Definition of hash_table class
class hash_table {
    node **arr; 

public:
    // Constructor to initialize the hash table with 10 empty slots (size 10)
    hash_table() {
        arr = new node*[10];  // Create an array of 10 node pointers
        for (int i = 0; i < 10; i++) {
            arr[i] = nullptr;  // Initialize each slot to nullptr (empty)
        }
    }

    // Function to insert a number in the hash table using the given key
    void put(int num, int key) {
        node *n = new node(num); 
        if (arr[key] == nullptr) {  
            arr[key] = n;
            return;
        }
        else {
            // Traverse to the end of the linked list and insert the node
            node *temp = arr[key];
            while (temp->next != nullptr) {  // Move to the last node
                temp = temp->next;   
            }
            temp->next = n;  // Insert the new node at the end
        }
    }

    // Function to insert a number through user input
    void insert() {
        int num;
        cout << "Enter the number you want to insert: ";
        cin >> num;

        int key = num % 10;  // The key is the remainder of the number divided by 10
        put(num, key);  
        cout << "Number inserted successfully." << endl;
    }

    // Function to display the hash table
    void display() {
        for (int i = 0; i < 10; i++) {  // Loop through each slot in the hash table
            node *temp = arr[i];
            if (temp == nullptr) { 
                cout << -1;
            }
            else {
                // Traverse the linked list and print each node's data
                while (temp != nullptr) {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
            }
            cout << endl;  // Print a new line after each slot
        }
    }

    // Destructor to free the memory allocated for the hash table
    ~hash_table() {
        for (int i = 0; i < 10; i++) {
            node *temp = arr[i];
            while (temp != nullptr) {
                node *nextNode = temp->next;
                delete temp;  // Delete the node to avoid memory leaks
                temp = nextNode;
            }
        }
        delete[] arr;  // Delete the array of pointers itself
    }
};

// Main function to interact with the user and test the hash table
int main() {
    hash_table h;  // Create a hash table object
    int choice;

    // Infinite loop to repeatedly show the menu until user chooses to exit
    while (true) {
        cout << "Enter your choice: \n1.Insert Number\n2.Display Hash Table\n3.Exit\n";
        cin >> choice;  // Take user choice

        if (choice == 1) {
            h.insert();  // Call insert function if user chooses option 1
        }
        else if (choice == 2) {
            h.display();  // Call display function if user chooses option 2
        }
        else {
            break;  // Exit the loop if user chooses option 3
        }
    }

    return 0;  // Return 0 to indicate the program finished successfully
}
