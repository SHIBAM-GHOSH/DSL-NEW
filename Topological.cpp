#include <bits/stdc++.h>
#include <queue>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list for the graph

public:
    // Constructor to initialize the graph with V vertices
    Graph(int vertices) {
        V = vertices;  
        adj.resize(V);  // Resize adjacency list to accommodate V vertices
    }
    // Function to add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adj[u].push_back(v);  // Add v to the adjacency list of u
    }
    void topologicalSortDFSUtil(int i, vector<int>& visited, stack<int>& Stack)                           
    {
        visited[i] = 1;  // Mark the current vertex as visited
        // Explore all the neighbors of the current vertex(mov forwrd from currnt node)
        for (int nb : adj[i]) {
            if (!visited[nb]) {  // If neighbor hasn't been visited
                topologicalSortDFSUtil(nb, visited, Stack);  // Recurse for the neighbor
            }
        }
        // Push the current vertex to the stack (this is the "post-order" operation)
        Stack.push(i);
    }

    // Function to perform topological sort using DFS
    void topologicalSortDFS() {
        vector<int> visited(V, 0);  
        stack<int> Stack;  // Stack to store the topological order

        // Loop through all vertices and apply DFS for any unvisited vertex
        for (int i = 0; i < V; i++) {
            if (visited[i]==0) {// works only if i not visited
                topologicalSortDFSUtil(i, visited, Stack);  // Call the DFS utility function
            }   // this func explores all node connected to currnt node
        }
        // Print the topological order (nodes are popped from stack)
        cout << "Topological Order (DFS-based): ";
        while (!Stack.empty()) {
            cout << Stack.top() << " ";  // Print top element of stack
            Stack.pop();  // Remove the top element
        }
        cout << endl;
    }

    // Helper function for DFS traversal (recursive)
    void DFSUtil(int node, vector<int>& visited) {
        visited[node] = 1;  // Mark the current vertex as visited
        cout << node << " ";  // Print the current vertex

        // Visit all unvisited neighbors of the current vertex
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);  // Recursively visit the neighbor
            }
        }
    }

    // Function to perform DFS traversal starting from a given vertex
    void DFS(int start) {
        vector<int> visited(V, 0);  // Initialize visited array with 0
        cout << "DFS Traversal from vertex " << start << ": ";
        DFSUtil(start, visited);  // Call DFSUtil starting from the start vertex
        cout << endl;
    }

    // Function to perform BFS traversal starting from a given vertex
    void BFS(int start) {
        vector<int> visited(V, 0);  // Initialize visited array with 0
        queue<int> q;  // Queue to store the vertices to be visited

        visited[start] = 1;  // Mark the start vertex as visited
        q.push(start);  // Push the start vertex into the queue

        cout << "BFS Traversal from vertex " << start << ": ";

        // While there are vertices in the queue, perform BFS
        while (!q.empty()) {
            int curr = q.front();  // Get the vertex from the front of the queue
            q.pop();  // Remove the vertex from the queue
            cout << curr << " ";  // Print the current vertex

            // Explore all unvisited neighbors of the current vertex
            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {  // If neighbor hasn't been visited
                    visited[neighbor] = 1;  // Mark it as visited
                    q.push(neighbor);  // Push it into the queue for future exploration
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V = 6;  // Number of vertices in the graph
    Graph g(V);  // Create a graph with 6 vertices

    // Add directed edges to the graph
    g.addEdge(0, 5);
    g.addEdge(5, 2);
    g.addEdge(0, 4);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
// adj[] = { {5,4}, {},{3},{1 }, { 1}, {2}}
    // Perform topological sort using DFS
    g.topologicalSortDFS();

    // Perform DFS traversal starting from vertex 0
    g.DFS(0);

    // Perform BFS traversal starting from vertex 0
    g.BFS(0);

    return 0;  // Return 0 to indicate successful execution
}
