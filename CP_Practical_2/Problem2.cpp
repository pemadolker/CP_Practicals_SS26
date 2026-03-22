#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (int &x : A) cin >> x;

        int ans = 0;

        for (int bit = 31; bit >= 0; bit--) {
            int test = ans | (1 << bit);

            int count = 0;
            bool ok = false;

            for (int i = 0; i < N; i++) {
                if ((A[i] & test) == test)
                    count++;
                else
                    count = 0;

                if (count >= K) {
                    ok = true;
                    break;
                }
            }

            if (ok) ans = test;
        }

        cout << ans << "\n";
    }
}