#include <bits/stdc++.h>
using namespace std;

// Class to represent a graph using an adjacency matrix
class Graph {
    int n;  // Number of vertices
    vector<vector<int>> adjMatrix;  // 2D vector to store adjacency matrix

public:
    // Constructor to initialize graph with 'n' vertices
    Graph(int size) {
        n = size;
        adjMatrix.resize(n, vector<int>(n, 0)); // Initialize n x n matrix with 0s
    }

    // Function to take input for the adjacency matrix
    void inputGraph() {
        cout << "Enter adjacency matrix (" << n << " x " << n << "):\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> adjMatrix[i][j];
    }

    // Helper function for recursive DFS traversal
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true; // Mark the current node as visited
        cout << node << " ";  // Print the node

        // Visit all unvisited neighbors
        for (int i = 0; i < n; ++i) {// elemts along each y axis lmnt
            if (adjMatrix[node][i]==1 && !visited[i])
                DFSUtil(i, visited); // explore node connected to currnt node
        }
    }

    // Public function to perform DFS from a starting vertex
    void DFS(int start) {
        vector<bool> visited(n, false); // Track visited vertices
        cout << "DFS traversal: ";
        DFSUtil(start, visited); // Start DFS from the given node
        cout << endl;
    }

    // Function to perform BFS from a starting vertex
    void BFS(int start) {
        vector<bool> visited(n, false); // Track visited vertices
        queue<int> q; // Queue for BFS

        visited[start] = true; // Mark the starting node as visited
        q.push(start); // Enqueue the starting node

        cout << "BFS traversal: ";

        while (!q.empty()) {
            int node = q.front(); // Get the front of the queue
            q.pop(); // Remove it from the queue
            cout << node << " "; // Print the node

            // Visit all unvisited neighbors and enqueue them
            for (int i = 0; i < n; ++i) {
                if (adjMatrix[node][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    // Function to count connected components using DFS
    int countConnectedComponents() {
        vector<bool> visited(n, false); // Track visited vertices
        int components = 0; // Number of connected components

        // Traverse all nodes
        for (int i = 0; i < n; ++i) {  // all node collection
            if (!visited[i]) {
                components++; // Found a new component
                DFSUtil(i, visited); // Perform DFS to visit the entire component
                cout << endl;
            }
        }
        return components;
    }

    // Function to check if the graph is connected
    void checkConnectivity() {
        int components = countConnectedComponents(); // Count components
        if (components == 1)
            cout << "The graph is connected.\n";
        else
            cout << "The graph is not connected. It has " << components << " connected components.\n";
    }
};

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n; // Input number of vertices

    Graph g(n); // Create a graph of size n
    g.inputGraph(); // Input the adjacency matrix

    int start;
    cout << "Enter starting vertex for traversal: ";
    cin >> start; // Input starting node for DFS and BFS

    g.DFS(start); // Perform Depth First Search
    g.BFS(start); // Perform Breadth First Search

    g.checkConnectivity(); // Check if the graph is connected
    return 0;
}
