#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<pair<int,int>>> adj(N+1);

    for (int i = 0; i < M; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<ll> dist(N+1, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;

    dist[1] = 0;
    pq.push({0,1});

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;

        for (auto [v,w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << (dist[N] == INF ? -1 : dist[N]) << "\n";
}