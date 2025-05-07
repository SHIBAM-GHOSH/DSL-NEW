#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge with two endpoints and a weight
class Edge {
   public:
    int u, v, weight;
};

// Comparator to sort edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Kruskal's algorithm without using DSU
int kruskalMST(int V, vector<Edge>& edges) {
    // Initially, each vertex is its own component
    vector<int> component(V);
    for (int i = 0; i < V; i++) component[i] = i;

    sort(edges.begin(), edges.end(), compare);  // Sort edges by weight

    int cost = 0;  // Total MST cost

    for (auto edge : edges) {
        // If u and v are in different components, include the edge
        if (component[edge.u] != component[edge.v]) {
            cout << "Selected Edge: " << edge.u << " - " << edge.v << " with cost " << edge.weight << endl;
            cost += edge.weight;

            // Merge components: update all nodes in v's component to u's component
            int oldComp = component[edge.v];
            int newComp = component[edge.u];
            for (int i = 0; i < V; i++) {
                if (component[i] == oldComp)
                    component[i] = newComp;
            }
        }
    }

    return cost;
}

int main() {
    int V = 5;

    // Edge list input
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };

    int cost = kruskalMST(V, edges);
    cout << "Minimum cost to connect all offices: " << cost << endl;

    return 0;
}
