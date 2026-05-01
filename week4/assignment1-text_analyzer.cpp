#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper function to strip punctuation from a string
string cleanWord(string str) {
    string result = "";
    for (char c : str) {
        if (!ispunct(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    string input;

    cout << "TEXT ANALYZER" << endl;
    cout << "-------------" << endl;
    cout << "Enter a sentence or paragraph:" << endl;
    getline(cin, input);

    // 1. Character Count
    int charCount = input.length();

    // 2. Sentence Count (Detecting . ! ?)
    int sentenceCount = 0;
    for (char c : input) {
        if (c == '.' || c == '!' || c == '?') {
            sentenceCount++;
        }
    }

    // 3. Word Analysis (using stringstream)
    stringstream ss(input);
    string tempWord;
    int wordCount = 0;
    string longestWord = "";
    double totalLettersOnly = 0;

    while (ss >> tempWord) {
        wordCount++;
        
        // Strip punctuation for accurate length and "longest word" check
        string stripped = cleanWord(tempWord);
        totalLettersOnly += stripped.length();

        if (stripped.length() > cleanWord(longestWord).length()) {
            longestWord = stripped;
        }
    }

    // 4. Calculate Average
    double avgLength = (wordCount > 0) ? (totalLettersOnly / wordCount) : 0.0;

    // Display Analysis
    cout << "\nAnalysis:" << endl;
    cout << "  Characters (with spaces): " << charCount << endl;
    cout << "  Word count:               " << wordCount << endl;
    cout << "  Sentence count:           " << sentenceCount << endl;
    cout << "  Longest word:             " << longestWord << endl;
    cout << fixed << setprecision(1);
    cout << "  Average word length:      " << avgLength << " characters" << endl;

    // 5. Case Conversions
    string upper = input;
    for (int i = 0; i < upper.length(); i++) {
        upper[i] = toupper(upper[i]);
    }

    string lower = input;
    for (int i = 0; i < lower.length(); i++) {
        lower[i] = tolower(lower[i]);
    }

    cout << "\nUppercase:" << endl;
    cout << "  " << upper << endl;

    cout << "\nLowercase:" << endl;
    cout << "  " << lower << endl;

    return 0;
}