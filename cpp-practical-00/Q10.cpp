#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for max_element, min_element
#include <numeric>    // for accumulate
using namespace std;

class Student {
private:
    string name;
    int studentNumber;
    vector<float> marks;

public:
    // Parameterized constructor
    Student(string n, int sn) {
        name = n;
        studentNumber = sn;
    }

    // Add a mark
    void addMark(float m) {
        marks.push_back(m);
    }

    // Get average
    float getAverage() {
        if (marks.empty()) return 0;
        float sum = accumulate(marks.begin(), marks.end(), 0.0f);
        return sum / marks.size();
    }

    // Get highest mark
    float getHighest() {
        if (marks.empty()) return 0;
        return *max_element(marks.begin(), marks.end());
    }

    // Get lowest mark
    float getLowest() {
        if (marks.empty()) return 0;
        return *min_element(marks.begin(), marks.end());
    }

    // Get classification based on average
    string getClassification() {
        float avg = getAverage();
        if (avg >= 75) return "Distinction";
        else if (avg >= 60) return "Merit";
        else if (avg >= 40) return "Pass";
        else return "Fail";
    }

    // Print report
    void printReport() {
        cout << "\n--- Academic Report ---" << endl;
        cout << "Student Name: " << name << endl;
        cout << "Student Number: " << studentNumber << endl;
        cout << "Marks: ";
        for (float m : marks) cout << m << " ";
        cout << endl;
        cout << "Highest Mark: " << getHighest() << endl;
        cout << "Lowest Mark: " << getLowest() << endl;
        cout << "Average Mark: " << getAverage() << endl;
        cout << "Classification: " << getClassification() << endl;
    }
};

int main() {
    // Create student object
    Student s1("Pema Dolker", 2230294);

    // Add marks
    s1.addMark(78);
    s1.addMark(62);
    s1.addMark(45);
    s1.addMark(90);
    s1.addMark(55);

    // Print report
    s1.printReport();

    return 0;
}