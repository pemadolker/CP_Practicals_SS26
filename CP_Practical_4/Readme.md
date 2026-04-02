# Graph Algorithm Implementations

## Overview

This practical implements three graph algorithms in C++:

- **Floyd-Warshall** — All-pairs shortest paths (handles negative edges)
- **Johnson's** — All-pairs shortest paths optimized for sparse graphs
- **Boruvka's** — Minimum Spanning Tree (MST) construction

---



## Algorithm Details

### 1. Floyd-Warshall

**Problem:** All-pairs shortest paths  
**Time:** O(V³) · **Space:** O(V²)

Uses dynamic programming with the recurrence:

```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

For every pair `(i, j)`, it checks whether routing through an intermediate vertex `k` gives a shorter path. Supports negative edge weights and detects negative cycles (`dist[i][i] < 0`).

**Sample Graph (4 vertices, 5 edges):**

```
0 -> 1  (weight  3)
0 -> 3  (weight 10)
1 -> 2  (weight  2)
2 -> 3  (weight -4)
3 -> 1  (weight  7)
```

**Expected Output:**

```
Shortest distance matrix:
     0     1     2     3
  0  0     3     5     1
  1  INF   0     2    -2
  2  INF   3     0    -4
  3  INF   7     9     0
```

> `dist[0][3]` = 1 via path `0→1→2→3` = 3 + 2 + (−4) = 1

---

### 2. Johnson's Algorithm

**Problem:** All-pairs shortest paths (sparse graph optimized)  
**Time:** O(V² log V + VE) · **Space:** O(V²)

Converts a graph with negative edges to one with non-negative edges using re-weighting, then runs Dijkstra from every vertex.

**Steps:**
1. Add a virtual vertex `q` with 0-weight edges to every vertex
2. Run Bellman-Ford from `q` to get potentials `h[v]`
3. Re-weight every edge: `w'(u, v) = w(u, v) + h[u] − h[v]`
4. Run Dijkstra from every vertex on the re-weighted graph
5. Recover real distances: `real_dist(u, v) = dijkstra_dist − h[u] + h[v]`

**Sample Output:**

```
Potentials h[] from Bellman-Ford:
  h[0] = 0,  h[1] = 0,  h[2] = 0,  h[3] = -4

All-Pairs Shortest Paths (Johnson's):
     0     1     2     3
  0  0     3     5     1
  1  INF   0     2    -2
  2  INF   3     0    -4
  3  INF   7     9     0
```

> Output matches Floyd-Warshall exactly (verified).

---

### 3. Boruvka's Algorithm

**Problem:** Minimum Spanning Tree  
**Time:** O(E log V) · **Space:** O(V + E)

Every vertex starts as its own component. In each round, every component picks its cheapest outgoing edge; all selected edges are added to the MST simultaneously, and components merge. Repeats until one component remains.

Uses **DSU (Disjoint Set Union / Union-Find)** with path compression and union by rank.

**Sample Graph (4 vertices):**

```
0 -- 1  (weight 4)
0 -- 2  (weight 2)
0 -- 3  (weight 6)
1 -- 3  (weight 5)
2 -- 3  (weight 1)
```

**Expected Output:**

```
--- Round 1 (Components: 4) ---
  Added edge: 2 -- 3  (weight 1)
  Added edge: 0 -- 2  (weight 2)
  Added edge: 0 -- 1  (weight 4)

Total MST weight: 7
```

---

## Comparison Table

| Feature | Floyd-Warshall | Johnson's | Boruvka's |
|---|---|---|---|
| Problem Type | All-Pairs Shortest Path | All-Pairs Shortest Path | Minimum Spanning Tree |
| Time Complexity | O(V³) | O(V² log V + VE) | O(E log V) |
| Space Complexity | O(V²) | O(V²) | O(V + E) |
| Negative Weights | Yes | Yes (re-weighting) | N/A |
| Negative Cycle Detection | Yes | Via Bellman-Ford | N/A |
| Graph Type | Directed / Undirected | Directed / Undirected | Undirected only |
| Best For | Dense, small graphs | Sparse, large graphs | MST construction |
| Core Technique | DP matrix | Bellman-Ford + Dijkstra | Union-Find (DSU) |
| Year Invented | 1962 | 1977 | 1926 |

---

## When to Use Which

- **Floyd-Warshall** — Small or dense graphs; simple to implement
- **Johnson's** — Sparse graphs needing all-pairs shortest paths
- **Boruvka's** — MST problems; especially suited to parallel/distributed systems

---

## Key Takeaways

- Shortest path algorithms and spanning tree algorithms solve fundamentally different problems
- Floyd-Warshall is dynamic programming applied to graphs
- Johnson's re-weighting trick makes Dijkstra usable on graphs with negative weights
- Union-Find (DSU) with path compression is highly efficient for component tracking
- Always verify output against a known test case when implementing graph algorithms