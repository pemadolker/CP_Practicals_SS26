#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cout << "Enter number of elements N: ";
    cin >> N;

    vector<int> numbers(N);
    cout << "Enter " << N << " elements: ";
    for(int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    int totalSubsets = 1 << N; // 2^N subsets

    cout << "All subsets:\n";

    for(int mask = 0; mask < totalSubsets; mask++) {
        cout << "{";
        for(int j = 0; j < N; j++) {
            if(mask & (1 << j)) {  // check if j-th bit is 1
                cout << numbers[j] << " ";
            }
        }
        cout << "}\n";
    }

    return 0;
}