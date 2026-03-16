#include <iostream>
#include <vector>
#include <algorithm> // for sort
using namespace std;

int main() {
    int N;
    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> numbers;

    // Step 1: read N numbers
    for(int i = 0; i < N; i++) {
        int value;
        cout << "Enter number " << i + 1 << ": ";
        cin >> value;
        numbers.push_back(value);
    }

    // Step 2: sort the vector
    sort(numbers.begin(), numbers.end());

    // Step 3: print unique numbers
    cout << "\nUnique numbers: ";
    for(int i = 0; i < N; i++) {
        // print first number OR print number if different from previous
        if(i == 0 || numbers[i] != numbers[i - 1]) {
            cout << numbers[i] << " ";
        }
    }
    cout << endl;

    return 0;
}