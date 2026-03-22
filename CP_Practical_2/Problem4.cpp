#include <bits/stdc++.h>
using namespace std;

vector<int> seg, A;

void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    seg[node] = max(seg[2*node], seg[2*node+1]);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        seg[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*node, l, mid, pos, val);
    else update(2*node+1, mid+1, r, pos, val);

    seg[node] = max(seg[2*node], seg[2*node+1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INT_MIN;
    if (ql <= l && r <= qr) return seg[node];

    int mid = (l + r) / 2;
    return max(query(2*node, l, mid, ql, qr),
               query(2*node+1, mid+1, r, ql, qr));
}

int main() {
    int N, K, Q;
    cin >> N >> K >> Q;

    A.resize(N);
    for (int &x : A) cin >> x;

    seg.resize(4*N);
    build(1, 0, N-1);

    while (Q--) {
        int type; cin >> type;

        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            update(1, 0, N-1, pos-1, val);
        } else {
            int i; cin >> i;
            cout << query(1, 0, N-1, i-K, i-1) << "\n";
        }
    }
}