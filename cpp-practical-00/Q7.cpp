#include <iostream>
#include <string>
using namespace std;

int main() {
    // 1. Declare integer array with your first name
    int pema_marks[5] = {78, 62, 45, 90, 55};  // 5 test marks (hardcoded)

    int size = 5;
    int sum = 0;
    int highest = pema_marks[0];
    int lowest = pema_marks[0];
    int aboveAverageCount = 0;

    // 2. Display all marks with index, find sum, highest, lowest
    cout << "--- Marks List ---" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Mark[" << i << "] = " << pema_marks[i] << endl;
        sum += pema_marks[i];
        if (pema_marks[i] > highest) highest = pema_marks[i];
        if (pema_marks[i] < lowest) lowest = pema_marks[i];
    }

    // 3. Calculate average
    double average = sum / double(size);

    // 4. Count marks above average
    for (int i = 0; i < size; i++) {
        if (pema_marks[i] > average) aboveAverageCount++;
    }

    // 5. Display highest, lowest, average, number above average
    cout << "\nHighest Mark: " << highest << endl;
    cout << "Lowest Mark: " << lowest << endl;
    cout << "Average Mark: " << average << endl;
    cout << "Number of Marks Above Average: " << aboveAverageCount << endl;

    // 6. Display simple bar for each mark (1 * per 10 marks)
    cout << "\n--- Marks Bar ---" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Mark[" << i << "]: ";
        int stars = pema_marks[i] / 10;
        for (int j = 0; j < stars; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}