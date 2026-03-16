#include <iostream>
#include <string>
using namespace std;

int main() {
    // Hardcoded student info
    string name = "Pema Dolker";
    int studentNumber = 2230294;

    int mark;

    // Prompt user
    cout << "Enter mark: ";
    cin >> mark;

    // Input validation
    if (mark < 0 || mark > 100) {
        cout << "Error: Mark must be between 0 and 100!" << endl;
    } else {
        string grade;
        string resultMessage;

        // Classify mark
        if (mark >= 75) {
            grade = "Distinction";
            resultMessage = "Congratulations, " + name + "! Excellent work!";
        } else if (mark >= 60) {
            grade = "Merit";
            resultMessage = "Congratulations, " + name + "! You have passed.";
        } else if (mark >= 40) {
            grade = "Pass";
            resultMessage = "Well done, " + name + "! You have passed.";
        } else {
            grade = "Fail";
            resultMessage = "Sorry, " + name + ". You did not pass.";
        }

        // Display formatted output
        cout << "----------------------------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Student Number: " << studentNumber << endl;
        cout << "Mark : " << mark << endl;
        cout << "Grade : " << grade << endl;
        cout << "Result : " << resultMessage << endl;
    }

    return 0;
}