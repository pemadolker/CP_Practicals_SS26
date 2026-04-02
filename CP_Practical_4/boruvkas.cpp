/*
 * ============================================================
 *  Borůvka's (Barůvka's) Algorithm
 *  Topic: Minimum Spanning Tree (MST)
 *  Time Complexity : O(E log V)
 *  Space Complexity: O(V + E)
 * ============================================================
 *
 *  IDEA (like Prim's and Kruskal's, but parallel!):
 *  - Start: every vertex is its own "component"
 *  - Each round:
 *      For every component, find the CHEAPEST edge that
 *      connects it to a different component.
 *      Add all those cheapest edges to the MST.
 *  - Repeat until only 1 component remains.
 *
 *  Think of it like: every island (component) simultaneously
 *  builds its cheapest bridge to the nearest other island.
 *
 *  Uses Union-Find (Disjoint Set Union) to track components.
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ---- Edge structure ----
struct Edge {
    int u, v, weight;
};

// ============================================================
//  Union-Find (Disjoint Set Union) — used to track components
// ============================================================
struct DSU {
    vector<int> parent, rank_;

    DSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    // Union by rank — keeps tree flat
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false; // already in same component

        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

// ============================================================
//  Borůvka's Algorithm
// ============================================================
int boruvka(int V, vector<Edge>& edges) {
    DSU dsu(V);
    int mstWeight = 0;
    int numComponents = V;    // Start: every vertex is its own component
    int round = 0;

    // Keep going until all vertices are in one component
    while (numComponents > 1) {
        round++;
        cout << "\n--- Round " << round << " (Components: " << numComponents << ") ---\n";

        // cheapest[c] = index of cheapest edge crossing out of component c
        // Initialized to -1 (no edge found yet)
        vector<int> cheapest(V, -1);

        // For every edge, check if it connects two different components
        for (int i = 0; i < (int)edges.size(); i++) {
            int compU = dsu.find(edges[i].u);
            int compV = dsu.find(edges[i].v);

            if (compU == compV) continue; // same component, skip

            // Update cheapest edge for component of u
            if (cheapest[compU] == -1 || edges[i].weight < edges[cheapest[compU]].weight)
                cheapest[compU] = i;

            // Update cheapest edge for component of v
            if (cheapest[compV] == -1 || edges[i].weight < edges[cheapest[compV]].weight)
                cheapest[compV] = i;
        }

        // Now merge components using the cheapest edges found
        for (int c = 0; c < V; c++) {
            if (cheapest[c] == -1) continue; // no outgoing edge from this component

            int idx = cheapest[c];
            int compU = dsu.find(edges[idx].u);
            int compV = dsu.find(edges[idx].v);

            if (compU == compV) continue; // already merged this round

            // Add edge to MST
            dsu.unite(compU, compV);
            mstWeight += edges[idx].weight;
            numComponents--;

            cout << "  Added edge: " << edges[idx].u << " -- "
                 << edges[idx].v << "  (weight " << edges[idx].weight << ")\n";
        }
    }
    return mstWeight;
}

int main() {
    /*
     *  Example Graph (undirected, weighted):
     *
     *      0
     *     /|\
     *   4/ | \2
     *   /  |  \
     *  1   |   2
     *   \  |  /
     *   5\ |1/
     *     \|/
     *      3
     *
     *  Edges: (0,1,4), (0,2,2), (0,3,6), (1,3,5), (2,3,1)
     *
     *  Expected MST edges: 2-3(1), 0-2(2), 0-1(4) → Total = 7
     */

    int V = 4;
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 2},
        {0, 3, 6},
        {1, 3, 5},
        {2, 3, 1}
    };

    cout << "=== Borůvka's Algorithm ===\n";
    cout << "Vertices: " << V << ", Edges: " << edges.size() << "\n";

    int mstCost = boruvka(V, edges);
    cout << "\nTotal MST weight: " << mstCost << "\n";

    return 0;
}

