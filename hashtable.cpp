#include <bits/stdc++.h>
using namespace std;

void display(const vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        
        cout << v[i] << " "<<endl;
    }
    cout << endl;
}

void insert(vector<int>& v, int val)
{
    int n = v.size();
    int loc = val % n;
    int x = loc; // Save the original location of element

    if (v[loc] == -1) // If the slot is empty
    {
        v[loc] = val;// insert the val
    }
    else
    {    // if the slot is already filled
        loc = (loc + 1) % n; // Start looking from the next slot (circular probing)
        while (loc != x) // keep checking until we return to the original location
        {
            if (v[loc] == -1) // Found an empty slot
            {
                v[loc] = val;
                return;
            }
            loc = (loc + 1) % n; // Move to the next slot
        }
        // If we come back to the original location, the table is full
        cout << "Hash Table Full, Can't insert\n";
    }
}

void deleteElement(vector<int>& v, int val)
{
    int n = v.size();
    int loc = val % n;
    int x = loc; // Save the original location

    if (v[loc] == -1) // If the slot is empty
    {
        cout << "Value not found.\n";
        return;
    }
    while (v[loc] != -1) // Keep searching until we find an empty slot
    {
        if (v[loc] == val) // Value found, delete it
        {
            v[loc] = -1; // Mark the slot as empty
            cout << "Value " << val << " deleted.\n";
            return;
        }
        loc = (loc + 1) % n; // Move to the next slot
        if (loc == x) // We have circled back to the original position
        {
            break;
        }
    }
    cout << "Value not found.\n"; // If we came back to the original location without finding the value
}

void search(const vector<int>& v, int val)
{
    int n = v.size();
    int loc = val % n;
    int x = loc; // Save the original location

    if (v[loc] == -1) // If the slot is empty
    {
        cout << "Value not found.\n";
        return;
    }
    while (v[loc] != -1) // Keep searching until we find an empty slot
    {
        if (v[loc] == val) // Value found
        {
            cout << "Value " << val << " found at index " << loc << ".\n";
            return;
        }
        loc = (loc + 1) % n; // Move to the next slot
        if (loc == x) // We have circled back to the original position
        {
            break;
        }
    }
    cout << "Value not found.\n"; // If we came back to the original location without finding the value
}

int main()
{
    vector<int> hashtable(10, -1); // Initialize hash table with -1 (empty slots)
    int num;
    
    
    vector<vector<int>> vec(3, vector<int>(2, -1));
    while (true)
    {
        cout << " ****MENU**** \n"
             << "1. Insert value\n"
             << "2. Delete value\n"
             << "3. Search value\n"
             << "4. Display Hash Table\n"
             << "5. Exit\n";

        cout << "Enter choice: ";
        int ch;
        cin >> ch;
        switch (ch)
        {
            case 1:
                cout << "Enter Number to insert: ";
                cin >> num;
                insert(hashtable, num);
                break;

            case 2:
                cout << "Enter Number to delete: ";
                cin >> num;
                deleteElement(hashtable, num);
                break;

            case 3:
                cout << "Enter Number to search: ";
                cin >> num;
                search(hashtable, num);
                break;

            case 4:
                cout << "Hash Table: ";
                display(hashtable);
                break;

            case 5:
                cout << "Exiting...\n";
                return 0; // Exit the program

            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
