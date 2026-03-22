#include <bits/stdc++.h>
using namespace std;

struct State {
    int time, pos, coins, skips;

    bool operator>(const State &other) const {
        return time > other.time;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> toll(N + 1);
    for (int i = 1; i <= N; i++) cin >> toll[i];

    // Min time for each state
    map<tuple<int,int,int>, int> dist;

    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push({0, 1, M, 0});
    dist[{1, M, 0}] = 0;

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        int time = cur.time;
        int pos = cur.pos;
        int coins = cur.coins;
        int skips = cur.skips;

        // If we already found a better path, skip
        if (dist[{pos, coins, skips}] < time) continue;

        if (pos == N) {
            cout << time << "\n";
            return 0;
        }

        // PAY
        if (coins >= toll[pos]) {
            int newCoins = coins - toll[pos];
            auto next = make_tuple(pos+1, newCoins, skips);

            if (!dist.count(next) || dist[next] > time + 1) {
                dist[next] = time + 1;
                pq.push({time + 1, pos+1, newCoins, skips});
            }
        }

        // SKIP
        if (skips < K) {
            auto next = make_tuple(pos+1, coins, skips+1);

            if (!dist.count(next) || dist[next] > time + 2) {
                dist[next] = time + 2;
                pq.push({time + 2, pos+1, coins, skips+1});
            }
        }
    }

    cout << -1 << "\n";
}