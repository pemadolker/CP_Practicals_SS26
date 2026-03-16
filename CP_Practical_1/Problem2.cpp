#include <iostream>
#include <vector>
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
        numbers.push_back(value); // add to vector
    }

       cout << "\nArray in reverse order: ";
    for(int i = N - 1; i >= 0; i--) { // start from last index
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}