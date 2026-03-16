#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;

    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> numbers;  // dynamic container

    // Reading N numbers
    for(int i = 0; i < N; i++) {
        int value;
        cout << "Enter number " << i + 1 << ": ";
        cin >> value;
        numbers.push_back(value);   // add to vector
    }

    // Assume first element as min and max
    int max = numbers[0];
    int min = numbers[0];
    int sum = 0;

    // Loop through vector
    for(int i = 0; i < N; i++) {
        if(numbers[i] > max) {
            max = numbers[i];
        }

        if(numbers[i] < min) {
            min = numbers[i];
        }

        sum = sum + numbers[i];
    }

    // Output results
    cout << "\nMaximum element: " << max << endl;
    cout << "Minimum element: " << min << endl;
    cout << "Sum of elements: " << sum << endl;

    return 0;
}
