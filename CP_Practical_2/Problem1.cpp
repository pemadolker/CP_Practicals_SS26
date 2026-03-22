#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> mask;
bool used[21];

bool canSit(int a, int b) {
    return (mask[a] & mask[b]) == 0;
}

bool solve(vector<int>& table) {
    if (table.size() == N) {
        // check circular condition
        return canSit(table[0], table[N-1]);
    }

    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            if (table.empty() || canSit(table.back(), i)) {
                used[i] = true;
                table.push_back(i);

                if (solve(table)) return true;

                table.pop_back();
                used[i] = false;
            }
        }
    }
    return false;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> N;
        mask.resize(N);

        for (int i = 0; i < N; i++) {
            int m; cin >> m;
            mask[i] = 0;

            while (m--) {
                int x; cin >> x;
                mask[i] |= (1 << x);
            }
        }

        memset(used, false, sizeof(used));
        vector<int> table;

        if (solve(table)) cout << "YES\n";
        else cout << "NO\n";
    }
}