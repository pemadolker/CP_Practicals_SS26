#include <iostream>
using namespace std;

int main() {

    int studentNumber = 2230294;  // store your student number here
    int sum = 0;
    int temp = studentNumber;

    // Find sum of digits
    while (temp > 0) {
        sum = sum + (temp % 10);
        temp = temp / 10;
    }

    // Check odd or even
    if (studentNumber % 2 == 0) {
        cout << "Odd or Even: Even" << endl;
    } else {
        cout << "Odd or Even: Odd" << endl;
    }

    // Display results
    cout << "Student Number: " << studentNumber << endl;
    cout << "Sum of Digits: " << sum << endl;
    cout << "Remainder when divided by 7: " << studentNumber % 7 << endl;
    cout << "Student Number multiplied by 3: " << studentNumber * 3 << endl;

    return 0;
}