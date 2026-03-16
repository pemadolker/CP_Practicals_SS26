#include <iostream>
#include <vector>
using namespace std;

int main() {

    int N;
    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N);

    cout << "Enter the elements: ";
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter target sum: ";
    cin >> target;

    int totalSubsets = 1 << N;
    int count = 0;

    for(int mask = 0; mask < totalSubsets; mask++) {

        int sum = 0;

        for(int j = 0; j < N; j++) {

            if(mask & (1 << j)) {
                sum += arr[j];
            }

        }

        if(sum == target) {
            count++;
        }

    }

    cout << "Number of subsets with sum equal to target: " << count << endl;

    return 0;
}