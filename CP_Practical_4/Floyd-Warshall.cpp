/*
 * ============================================================
 *  Floyd-Warshall Algorithm
 *  Topic: All-Pairs Shortest Path
 *  Time Complexity : O(V^3)
 *  Space Complexity: O(V^2)
 * ============================================================
 *
 *  IDEA:
 *  For every pair (i, j), check if going through an
 *  intermediate vertex 'k' gives a shorter path than the
 *  current known path.
 *
 *      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *
 *  We repeat this for every possible intermediate vertex k.
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <climits>   // for INT_MAX
using namespace std;

// A large value to represent "no direct edge / infinity"
const int INF = 1e8;

void floydWarshall(vector<vector<int>>& dist, int V) {
    // Try every vertex as an intermediate point
    for (int k = 0; k < V; k++) {
        // For every source vertex i
        for (int i = 0; i < V; i++) {
            // For every destination vertex j
            for (int j = 0; j < V; j++) {
                // If going i -> k -> j is shorter, update
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& dist, int V) {
    cout << "\nShortest distance matrix:\n";
    cout << "     ";
    for (int i = 0; i < V; i++) cout << "  " << i << "   ";
    cout << "\n";

    for (int i = 0; i < V; i++) {
        cout << "  " << i << "  ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << " INF  ";
            else
                cout << "  " << dist[i][j] << "   ";
        }
        cout << "\n";
    }
}

int main() {
    int V = 4; // Number of vertices

    /*
     *  Example Graph (directed, weighted):
     *
     *       10
     *  0 ------> 3
     *  |          ^
     *  |          |
     *  v   -4     |
     *  1 -------> 2
     *   \        /
     *    \  3   /  2
     *     \    /
     *      v  v
     *       (nothing)
     *
     *  Edge list:
     *  0->1 (3), 0->3 (10), 1->2 (2), 2->3 (-4), 3->1 (7)
     */

    // Initialize distance matrix with INF (no direct path)
    vector<vector<int>> dist(V, vector<int>(V, INF));

    // Distance from a vertex to itself is 0
    for (int i = 0; i < V; i++) dist[i][i] = 0;

    // Add edges (u, v, weight)
    dist[0][1] = 3;
    dist[0][3] = 10;
    dist[1][2] = 2;
    dist[2][3] = -4;  // Negative edge (Floyd-Warshall handles this!)
    dist[3][1] = 7;

    cout << "=== Floyd-Warshall Algorithm ===\n";
    cout << "Vertices: " << V << "\n";

    cout << "\nInitial distance matrix (INF = no direct edge):";
    printMatrix(dist, V);

    // Run the algorithm
    floydWarshall(dist, V);

    cout << "\nAfter running Floyd-Warshall:";
    printMatrix(dist, V);

    // Check for negative cycles
    // If dist[i][i] < 0 for any i, a negative cycle exists
    bool hasNegCycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            hasNegCycle = true;
            break;
        }
    }
    if (hasNegCycle)
        cout << "\n[WARNING] Negative cycle detected!\n";
    else
        cout << "\nNo negative cycles detected.\n";

    return 0;
}

