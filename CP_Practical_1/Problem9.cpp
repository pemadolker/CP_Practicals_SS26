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

    int totalSubsets = 1 << N;  // 2^N
    int countEven = 0;

    for(int mask = 0; mask < totalSubsets; mask++) {

        int sum = 0;

        for(int j = 0; j < N; j++) {

            if(mask & (1 << j)) {
                sum += arr[j];
            }

        }

        if(sum % 2 == 0) {
            countEven++;
        }
    }

    cout << "Number of subsets with even sum: " << countEven << endl;

    return 0;
}