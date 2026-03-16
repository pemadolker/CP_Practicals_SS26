#include <iostream>
#include <string>
using namespace std;

// Function to calculate sum of digits
int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to count vowels in a string
int countVowels(string s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = tolower(s[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

// Function to reverse a string
string reverseString(string s) {
    string rev = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        rev += s[i];
    }
    return rev;
}

int main() {
    // Hardcoded info
    int studentNumber = 2230294;
    string fullName = "Pema Dolker";

    // Call functions
    int sumDigits = digitSum(studentNumber);
    bool primeCheck = isPrime(studentNumber);
    int vowelsCount = countVowels(fullName);
    string reversedName = reverseString(fullName);

    // Display formatted summary
    cout << "--- Function Results Summary ---" << endl;
    cout << "digitSum(" << studentNumber << ") = " << sumDigits << endl;
    cout << "isPrime(" << studentNumber << ") = " << (primeCheck ? "True" : "False") << endl;
    cout << "countVowels(\"" << fullName << "\") = " << vowelsCount << endl;
    cout << "reverseString(\"" << fullName << "\") = " << reversedName << endl;

    return 0;
}