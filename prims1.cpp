#include <bits/stdc++.h>
using namespace std;



// Function to run Prim's Algorithm
int primMST(int V, vector<vector<pair<int, int>>>& adj) {
    vector<bool> Visited(V, false); // To track vertices already included in MST
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int totalCost = 0;
    pq.push({0, 0}); // {weight, vertex}

    while (!pq.empty()) {
        auto it = pq.top();
        int weight = it.first;
        int u = it.second;

        pq.pop();

        if (Visited[u])
            continue;   

        Visited[u] = true;
        totalCost += weight;

       for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!Visited[v]) {
                pq.push({w, v});
            }
        }
    }

    return totalCost;
}
void addEdge(vector<vector<pair<int, int>>>& adjList, int u, int v, int weight) {
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight}); // For undirected graph
}
int main() {
    int V = 5;
    vector<vector<pair<int, int>>> adj(V);

    cout<<"hello";
    // Sample graph
    addEdge(adj,0, 1, 2);
    addEdge(adj,0, 3, 6);
    addEdge(adj,1, 2, 3);
    addEdge(adj,1, 3, 8);
    addEdge(adj,1, 4, 5);
    addEdge(adj,2, 4, 7);
    addEdge(adj,3, 4, 9);

    int cost = primMST(V, adj);
    cout << "Minimum cost to connect all offices: " << cost << endl;

    return 0;
}
