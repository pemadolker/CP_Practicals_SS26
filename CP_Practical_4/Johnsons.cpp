/*
 * ============================================================
 *  Johnson's Algorithm
 *  Topic: All-Pairs Shortest Path (handles negative weights)
 *  Time Complexity : O(V^2 log V + VE)  [using min-heap Dijkstra]
 *  Space Complexity: O(V^2)
 * ============================================================
 *
 *  WHY JOHNSON'S INSTEAD OF FLOYD-WARSHALL?
 *  Floyd-Warshall is O(V^3). Johnson's is faster on SPARSE graphs
 *  (few edges). It runs Dijkstra from every vertex, but first
 *  re-weights edges to make all weights non-negative
 *  (Dijkstra cannot handle negative weights).
 *
 *  STEPS:
 *  1. Add a new source vertex 'q' connected to all vertices with edge weight 0.
 *  2. Run Bellman-Ford from 'q' to get potentials h[v] for every vertex.
 *  3. Re-weight each edge: w'(u,v) = w(u,v) + h[u] - h[v]  (always >= 0)
 *  4. Run Dijkstra from every vertex on the re-weighted graph.
 *  5. Adjust results back: dist[u][v] = dijkDist[u][v] - h[u] + h[v]
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = 1e8;

// ---- Edge structure ----
struct Edge {
    int to, weight;
};

// ---- Bellman-Ford ----
// Returns false if a negative cycle exists, true otherwise.
// Fills h[] with shortest distances from source.
bool bellmanFord(vector<vector<Edge>>& graph, int src, int V, vector<int>& h) {
    h.assign(V, INF);
    h[src] = 0;

    // Relax all edges V-1 times
    for (int iter = 0; iter < V - 1; iter++) {
        for (int u = 0; u < V; u++) {
            if (h[u] == INF) continue;
            for (auto& e : graph[u]) {
                if (h[u] + e.weight < h[e.to]) {
                    h[e.to] = h[u] + e.weight;
                }
            }
        }
    }

    // Check for negative cycle (one more relaxation would still update)
    for (int u = 0; u < V; u++) {
        if (h[u] == INF) continue;
        for (auto& e : graph[u]) {
            if (h[u] + e.weight < h[e.to]) {
                return false; // Negative cycle detected!
            }
        }
    }
    return true;
}

// ---- Dijkstra (on re-weighted graph) ----
// Returns shortest distances from src using a min-heap (priority queue).
vector<int> dijkstra(vector<vector<Edge>>& graph, int src, int V) {
    // Min-heap: {distance, vertex}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    vector<int> dist(V, INF);

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        // Skip outdated entries
        if (d > dist[u]) continue;

        for (auto& e : graph[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

// ---- Johnson's Algorithm ----
void johnsonsAlgorithm(int V, vector<tuple<int,int,int>>& edges) {
    // Step 1: Add a new virtual vertex 'q' (index V)
    //         Connect q -> every original vertex with weight 0
    int totalV = V + 1;
    int q = V; // index of virtual vertex

    vector<vector<Edge>> graph(totalV);
    for (auto& [u, v, w] : edges) {
        graph[u].push_back({v, w});
    }
    // Add zero-weight edges from virtual source q to all vertices
    for (int i = 0; i < V; i++) {
        graph[q].push_back({i, 0});
    }

    // Step 2: Run Bellman-Ford from q to get potentials h[]
    vector<int> h;
    if (!bellmanFord(graph, q, totalV, h)) {
        cout << "Graph contains a negative cycle! Johnson's cannot proceed.\n";
        return;
    }
    cout << "\nPotentials h[] from Bellman-Ford:\n";
    for (int i = 0; i < V; i++) cout << "  h[" << i << "] = " << h[i] << "\n";

    // Step 3: Re-weight all edges: w'(u,v) = w(u,v) + h[u] - h[v]
    vector<vector<Edge>> reWeighted(V);
    for (auto& [u, v, w] : edges) {
        int newW = w + h[u] - h[v];
        reWeighted[u].push_back({v, newW});
    }

    // Step 4 & 5: Dijkstra from every vertex, then un-reweight
    cout << "\nAll-Pairs Shortest Paths (Johnson's Algorithm):\n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << "  " << j << "   ";
    cout << "\n";

    for (int u = 0; u < V; u++) {
        vector<int> dijk = dijkstra(reWeighted, u, V);
        cout << "  " << u << "  ";
        for (int v = 0; v < V; v++) {
            // Adjust back: real_dist = dijkDist - h[u] + h[v]
            if (dijk[v] == INF)
                cout << " INF  ";
            else
                cout << "  " << dijk[v] - h[u] + h[v] << "   ";
        }
        cout << "\n";
    }
}

int main() {
    int V = 4;

    /*
     *  Same graph as Floyd-Warshall example:
     *  0->1 (3), 0->3 (10), 1->2 (2), 2->3 (-4), 3->1 (7)
     */
    vector<tuple<int,int,int>> edges = {
        {0, 1, 3},
        {0, 3, 10},
        {1, 2, 2},
        {2, 3, -4},  // Negative weight edge
        {3, 1, 7}
    };

    cout << "=== Johnson's Algorithm ===\n";
    cout << "Vertices: " << V << ", Edges: " << edges.size() << "\n";

    johnsonsAlgorithm(V, edges);

    return 0;
}
