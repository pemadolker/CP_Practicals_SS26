#include <iostream>
#include <vector>
#include <algorithm>  // for sort, min_element, max_element
#include <numeric>    // for accumulate
using namespace std;

int main() {
    // Declare vector using student number
    vector<int> v2230294;
    int value;

    // Populate vector at runtime
    cout << "Enter 6 integer values for the vector:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Value " << i + 1 << ": ";
        cin >> value;
        v2230294.push_back(value);
    }

    // Display vector before sorting
    cout << "\nVector before sorting: ";
    for (int v : v2230294) cout << v << " ";
    cout << endl;

    // Sort vector in ascending order
    sort(v2230294.begin(), v2230294.end());

    // Display vector after sorting
    cout << "Vector after sorting: ";
    for (int v : v2230294) cout << v << " ";
    cout << endl;

    // Find min, max, and sum using STL
    int minVal = *min_element(v2230294.begin(), v2230294.end());
    int maxVal = *max_element(v2230294.begin(), v2230294.end());
    int sumVal = accumulate(v2230294.begin(), v2230294.end(), 0);
    double average = double(sumVal) / v2230294.size();

    cout << "\nMinimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum of values: " << sumVal << endl;
    cout << "Average value: " << average << endl;

    // Remove all values below average
    v2230294.erase(
        remove_if(v2230294.begin(), v2230294.end(), [average](int x){ return x < average; }),
        v2230294.end()
    );

    // Display final vector
    cout << "\nVector after removing values below average: ";
    for (int v : v2230294) cout << v << " ";
    cout << endl;

    return 0;
}