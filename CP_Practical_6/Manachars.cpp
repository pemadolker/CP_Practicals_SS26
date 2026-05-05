#include <iostream>
#include <vector>
using namespace std;

string preprocess(const string& s) {
    string t = "^";
    for (char c : s) {
        t += "#" + string(1, c);
    }
    t += "#$";
    return t;
}

string longestPalindrome(string s) {
    string T = preprocess(s);
    int n = T.size();

    vector<int> P(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;

        if (i < right)
            P[i] = min(right - i, P[mirror]);

        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
            P[i]++;

        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    string s = "babad";
    cout << "Longest Palindrome: " << longestPalindrome(s) << endl;
    return 0;
}