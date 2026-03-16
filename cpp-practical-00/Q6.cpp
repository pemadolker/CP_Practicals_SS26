#include <iostream>
#include <string>
using namespace std;

int main() {
    // Hardcoded info
    string firstName = "Pema";        // first name
    string fullName = "Pema Dolker";  // full name
    int studentNumber = 2230294;      // student number

    int firstNameLength = firstName.length();
    int fullNameLength = fullName.length();

    // 1. Print first name N times (N = number of characters in first name)
    cout << "--- First Name Printed N Times ---" << endl;
    for (int i = 0; i < firstNameLength; i++) {
        cout << firstName << endl;
    }

    cout << "\n--- Right-Angled Triangle of Asterisks ---" << endl;
    // 2. Right-angled triangle (height = length of full name)
    for (int i = 1; i <= fullNameLength; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n--- Multiplication Table ---" << endl;
    // 3. Multiplication table for last digit of student number
    int lastDigit = studentNumber % 10;
    for (int i = 1; i <= 10; i++) {
        cout << lastDigit << " x " << i << " = " << lastDigit * i << endl;
    }

    return 0;
}