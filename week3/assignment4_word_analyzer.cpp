#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits> // Needed for clearing the buffer

using namespace std;

// --- Function Prototypes ---
int countVowels(string word);
int countConsonants(string word);
char firstLetter(string word);
string reverseString(string word);
bool isPalindrome(string word);
string getStats(string word);
bool isValidWord(string word);

int main() {
    string choice;
    bool keepGoing = true;

    while (keepGoing) {
        string input;
        bool validWord = false;

        while (!validWord) {
            cout << "Enter a word: ";
            // Use getline to catch everything the user typed (including spaces)
            getline(cin, input);

            if (isValidWord(input)) {
                validWord = true;
            } else {
                cout << "Invalid! Use letters only (no spaces, numbers, or symbols).\n" << endl;
            }
        }

        cout << "\nWord Analysis:" << endl;
        cout << "-------------" << endl;
        cout << "Original word: " << input << endl;
        cout << "Number of vowels: " << countVowels(input) << endl;
        cout << "Number of consonants: " << countConsonants(input) << endl;
        cout << "First letter: " << firstLetter(input) << endl;
        cout << "Reversed: " << reverseString(input) << endl;
        cout << "Is palindrome: " << (isPalindrome(input) ? "Yes" : "No") << endl;
        
        cout << getStats(input) << endl;

        bool validChoice = false;
        while (!validChoice) {
            cout << "\nWould you like to analyze another word? (y/n): ";
            getline(cin, choice); // Use getline here too to keep the buffer clean

            if (choice.empty()) continue;

            char c = tolower(choice[0]);
            if (c == 'y') {
                validChoice = true;
                cout << endl;
            } else if (c == 'n') {
                validChoice = true;
                keepGoing = false;
                cout << "Goodbye!" << endl;
            } else {
                cout << "Invalid choice. Please enter 'y' for yes or 'n' for no." << endl;
            }
        }
    }

    return 0;
}

// --- Implementation ---

bool isValidWord(string word) {
    if (word.empty()) return false;
    for (char c : word) {
        // Now checks if there's a space or non-letter
        if (!isalpha(c)) return false; 
    }
    return true;
}

int countVowels(string word) {
    int count = 0;
    for (char c : word) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') count++;
    }
    return count;
}

int countConsonants(string word) {
    int count = 0;
    for (char c : word) {
        c = tolower(c);
        if (isalpha(c) && !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) count++;
    }
    return count;
}

char firstLetter(string word) {
    return word.empty() ? '\0' : word[0];
}

string reverseString(string word) {
    string rev = word;
    reverse(rev.begin(), rev.end());
    return rev;
}

bool isPalindrome(string word) {
    int start = 0;
    int end = word.length() - 1;
    while (start < end) {
        if (tolower(word[start]) != tolower(word[end])) return false;
        start++;
        end--;
    }
    return true;
}

string getStats(string word) {
    string palStatus = isPalindrome(word) ? "is a palindrome" : "is not a palindrome";
    return "STATS: '" + word + "' has " + to_string(word.length()) + " characters, " +
           to_string(countVowels(word)) + " vowels, " +
           to_string(countConsonants(word)) + " consonants, and " + palStatus + ".";
}