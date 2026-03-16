#include <iostream>
#include <queue>  // for priority_queue
using namespace std;

int main() {
    int N, K;
    cout << "Enter number of elements N: ";
    cin >> N;
    cout << "Enter K: ";
    cin >> K;

    priority_queue<int> pq;  // max heap

    cout << "Enter " << N << " numbers: ";
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        pq.push(x);  // add to priority_queue
    }

    cout << "K largest elements: ";
    for(int i = 0; i < K; i++) {
        if(!pq.empty()) {
            cout << pq.top() << " ";  // get largest
            pq.pop();                 // remove it
        }
    }
    cout << endl;

    return 0;
}