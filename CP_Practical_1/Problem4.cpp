#include <iostream>
#include <vector>
#include <deque>  // for deque
using namespace std;

int main() {
    int N, K;
    cout << "Enter size of array N: ";
    cin >> N;
    cout << "Enter window size K: ";
    cin >> K;

    vector<int> arr(N);
    cout << "Enter " << N << " elements: ";
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    deque<int> dq;  // stores indices
    cout << "Sliding window maximums: ";

    for(int i = 0; i < N; i++) {
        // Remove indices that are out of the current window
        while(!dq.empty() && dq.front() <= i - K) {
            dq.pop_front();
        }

        // Remove smaller elements from the back
        while(!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }

        // Add current index to the deque
        dq.push_back(i);

        // Print max of current window
        if(i >= K - 1) {
            cout << arr[dq.front()] << " ";
        }
    }
    cout << endl;

    return 0;
}