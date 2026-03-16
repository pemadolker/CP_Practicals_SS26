#include <iostream>
#include <string>
#include <cctype>   // for toupper and tolower
using namespace std;

int main() {
    string fullName = "Pema Dolker";  // <-- put your full name here

    // 1. Total character count including spaces
    cout << "Total Characters (including spaces): " << fullName.length() << endl;

    // 2. Name in uppercase
    string upperName = fullName;
    for (int i = 0; i < upperName.length(); i++) {
        upperName[i] = toupper(upperName[i]);
    }
    cout << "Uppercase: " << upperName << endl;

    // 3. Name in lowercase
    string lowerName = fullName;
    for (int i = 0; i < lowerName.length(); i++) {
        lowerName[i] = tolower(lowerName[i]);
    }
    cout << "Lowercase: " << lowerName << endl;

    // 4. Initials

    string initials = "";
    initials += toupper(fullName[0]);
    initials += '.';
    for (int i = 0; i < fullName.length(); i++) {
        if (fullName[i] == ' ' && i + 1 < fullName.length()) {
            initials += toupper(fullName[i + 1]);
            initials += '.';  // add dot after each initial
        }
    }
    cout << "Initials: " << initials << endl;

    // 5. Length of first name
    int firstNameLength = 0;
    for (int i = 0; i < fullName.length(); i++) {
        if (fullName[i] == ' ') break;
        firstNameLength++;
    }
    cout << "Length of First Name: " << firstNameLength << endl;

    return 0;
}