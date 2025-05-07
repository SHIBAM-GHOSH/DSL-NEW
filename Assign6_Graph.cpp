#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix
    vector<bool> visited; // Visited array for traversal

public:
    // Constructor: Initialize adjacency matrix and visited array
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0)); // Initialize matrix with 0
        visited.resize(V, false); // Initialize visited vector with false
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Since it's an undirected graph
    }

    void resetVisited() {
        fill(visited.begin(), visited.end(), false); // Reset visited array
    }

    void DFS(int start) {
        visited[start] = true;
        cout << start << " ";

        for (int i = 0; i < V; i++) {
            if (adjMatrix[start][i] == 1 && !visited[i]) {
                DFS(i);
            }
        }
    }

    void BFS(int start) {
        resetVisited(); // Ensure BFS starts fresh
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    
    int countConnectedComponents() {
        resetVisited(); // Reset visited before counting components
        int count = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                count++;
                cout << "Component " << count << ": ";
                DFS(i);
                cout << endl;
            }
        }

        return count;
    }

    bool isConnected() {
        return countConnectedComponents() == 1;
    }
};

int main() {
    int vertices, edges, u, v;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edges;

    Graph g(vertices);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "\nDFS Traversal: ";
    g.resetVisited(); // Reset before DFS
    g.DFS(0);

    cout << "\nBFS Traversal: ";
    g.BFS(0);

    int components = g.countConnectedComponents();
    cout << "\nTotal Connected Components: " << components << endl;

    if (components == 1)
        cout << "Graph is connected." << endl;
    else
        cout << "Graph is not connected." << endl;

    return 0;
}

