#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int &x : A) cin >> x;

    deque<int> dq;

    for (int i = 0; i < N; i++) {
        while (!dq.empty() && dq.front() <= i - K)
            dq.pop_front();

        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= K - 1)
            cout << A[dq.front()] << " ";
    }
}