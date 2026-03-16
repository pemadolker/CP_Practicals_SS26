#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int studentNumber;
    int age;
    const int currentYear = 2026;  // Change this if needed

    // Prompt user for input
    cout << "Enter your full name: ";
    getline(cin, name);  // allows spaces in the name

    cout << "Enter your student number: ";
    cin >> studentNumber;

    cout << "Enter your age: ";
    cin >> age;

    // Calculations
    int birthYear = currentYear - age;
    int yearTurning100 = birthYear + 100;

    // Display formatted summary
    cout << "\n--- User Summary ---\n";
    cout << "Name: " << name << endl;
    cout << "Student Number: " << studentNumber << endl;
    cout << "Age: " << age << endl;
    cout << "Year of Birth: " << birthYear << endl;
    cout << "Year you will turn 100: " << yearTurning100 << endl;

    return 0;
}