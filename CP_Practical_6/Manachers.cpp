// =============================================================================
// manacher.cpp — Manacher's Algorithm (Longest Palindromic Substring)
// Course  : Data Structures & Algorithms
// Compile : g++ -std=c++17 manacher.cpp -o manacher
// Run     : ./manacher
// =============================================================================
//
// Finds the longest palindromic substring in O(n) time.
// Naïve approach (expand around each centre): O(n²).
//
// KEY IDEA 1 — String transformation:
//   Insert '#' between every character (and at both ends) so that ALL
//   palindromes become odd-length. This removes the need for separate
//   even/odd cases.
//   "aba"  →  "^#a#b#a#$"   (^ and $ are sentinels to avoid bounds checks)
//
// KEY IDEA 2 — Reuse previously computed radii:
//   Maintain the rightmost palindrome seen so far: centre c, right boundary r.
//   For each new position i, if i < r, its mirror j = 2c - i already has a
//   computed radius p[j]. We can reuse: p[i] = min(r - i, p[j]).
//   This reuse is what reduces the complexity from O(n²) to O(n).
//
// p[i] = radius of palindrome centred at transformed position i.
//
// Time:  O(n)
// Space: O(n)
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// -----------------------------------------------------------------------------
// transform
// "abc" → "^#a#b#c#$"
// ^ and $ act as sentinels so the expansion loop never goes out of bounds.
// -----------------------------------------------------------------------------
static std::string transform(const std::string& s) {
    std::string t = "^#";
    for (char ch : s) { t += ch; t += '#'; }
    t += '$';
    return t;
}

// -----------------------------------------------------------------------------
// compute_radii
// Returns p[] where p[i] = palindrome radius at transformed position i.
// -----------------------------------------------------------------------------
static std::vector<int> compute_radii(const std::string& s) {
    std::string t = transform(s);
    int n = static_cast<int>(t.size());
    std::vector<int> p(n, 0);

    int c = 0, r = 0;   // centre and right boundary of rightmost palindrome

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * c - i;   // mirror of i with respect to c

        // If i is inside the known palindrome, borrow from mirror
        if (i < r)
            p[i] = std::min(r - i, p[mirror]);

        // Expand outward from i as far as possible
        while (t[i + p[i] + 1] == t[i - p[i] - 1])
            p[i]++;

        // Update rightmost palindrome if this one reaches further right
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    return p;
}

// -----------------------------------------------------------------------------
// longest_palindrome
// Finds the maximum radius in p[], maps it back to original string indices.
// Mapping: transformed centre i → original start = (i - radius) / 2
// -----------------------------------------------------------------------------
static std::string longest_palindrome(const std::string& s) {
    if (s.empty()) return "";
    std::vector<int> p   = compute_radii(s);
    int max_radius = 0, centre = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i] > max_radius) { max_radius = p[i]; centre = i; }
    }
    int start = (centre - max_radius) / 2;
    return s.substr(start, max_radius);
}

// -----------------------------------------------------------------------------
// all_palindromes
// Collects every distinct palindromic substring, sorted longest-first.
// -----------------------------------------------------------------------------
static std::vector<std::string> all_palindromes(const std::string& s) {
    std::vector<int>         p = compute_radii(s);
    std::vector<std::string> result;

    for (int i = 1; i < (int)p.size() - 1; i++) {
        if (p[i] > 0)
            result.push_back(s.substr((i - p[i]) / 2, p[i]));
    }

    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    std::sort(result.begin(), result.end(),
              [](const std::string& a, const std::string& b){
                  return a.size() > b.size();
              });
    return result;
}

// -----------------------------------------------------------------------------
// explain — prints transformed string, p[] array, and results
// Useful for screenshots to show the algorithm's internal state.
// -----------------------------------------------------------------------------
static void explain(const std::string& s) {
    std::string      t = transform(s);
    std::vector<int> p = compute_radii(s);

    std::cout << "\nInput         : \"" << s << "\"\n";
    std::cout << "Transformed   : \"" << t << "\"\n";
    std::cout << "Radius array  : [ ";
    for (int v : p) std::cout << v << " ";
    std::cout << "]\n";

    std::string lps = longest_palindrome(s);
    std::cout << "Longest palindrome: \"" << lps
              << "\" (length " << lps.size() << ")\n";

    auto all = all_palindromes(s);
    std::cout << "All distinct palindromic substrings (" << all.size() << "): ";
    for (const auto& ps : all) std::cout << "\"" << ps << "\" ";
    std::cout << "\n";
}

// =============================================================================
// main
// =============================================================================
int main() {
    std::cout << "=================================================\n";
    std::cout << "  Manacher's Algorithm\n";
    std::cout << "=================================================\n";

    // Classic example
    explain("babad");
    // Longest: "bab" or "aba" (both length 3)

    // Even-length palindrome
    explain("cbbd");
    // Longest: "bb"

    // Entire string is a palindrome
    explain("racecar");
    // Longest: "racecar"

    // All same characters
    explain("aaaa");
    // Longest: "aaaa"

    // No palindrome longer than 1
    explain("abcd");

    // Long string
    explain("abacabadabacaba");
    // Longest: "abacabadabacaba" (entire string, length 15)

    // Edge case: empty string
    std::string lps = longest_palindrome("");
    std::cout << "\nEmpty string → longest palindrome: \""
              << lps << "\" (length " << lps.size() << ")\n";

    std::cout << "\n=================================================\n";
    std::cout << "  Done.\n";
    std::cout << "=================================================\n";
    return 0;
}