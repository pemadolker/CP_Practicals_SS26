#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {

    int N;
    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N);

    cout << "Enter the numbers: ";
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    priority_queue<int> maxHeap; 
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cout << "Running medians:\n";

    for(int i = 0; i < N; i++) {

        int x = arr[i];

        if(maxHeap.empty() || x <= maxHeap.top()) {
            maxHeap.push(x);
        }
        else {
            minHeap.push(x);
        }

        // Balance heaps
        if(maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if(minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // Calculate median
        if(maxHeap.size() == minHeap.size()) {
            double median = (maxHeap.top() + minHeap.top()) / 2.0;
            cout << median << endl;
        }
        else {
            cout << maxHeap.top() << endl;
        }
    }

    return 0;
}