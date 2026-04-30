#include <iostream>
#include <string>
#include <iomanip>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to determine letter grade based on score
char getLetterGrade(double score) {
    if (score >= 90) return 'A';
    if (score >= 80) return 'B';
    if (score >= 70) return 'C';
    if (score >= 60) return 'D';
    return 'F';
}

int main() {
    const int NUM_QUIZZES = 5;
    double scores[NUM_QUIZZES];
    int distribution[5] = {0, 0, 0, 0, 0}; 

    cout << "QUIZ GRADE TRACKER" << endl;
    cout << "------------------" << endl;

    // Input Phase with Validation
    for (int i = 0; i < NUM_QUIZZES; i++) {
        while (true) {
            cout << "Enter score for Quiz " << (i + 1) << " (0-100): ";
            cin >> scores[i];

            // Check if input was a number AND within valid range
            if (cin.fail() || scores[i] < 0 || scores[i] > 100) {
                cout << "Invalid input. Please enter a number between 0 and 100." << endl;
                
                cin.clear(); // Reset the error flags
                // Discard the invalid input from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                // Input is valid, break the while loop
                break;
            }
        }
    }

    // --- (Rest of the calculation and display logic remains the same) ---
    double total = 0;
    double highest = scores[0];
    double lowest = scores[0];
    int highIndex = 0;
    int lowIndex = 0;

    for (int i = 0; i < NUM_QUIZZES; i++) {
        total += scores[i];
        if (scores[i] > highest) { highest = scores[i]; highIndex = i; }
        if (scores[i] < lowest) { lowest = scores[i]; lowIndex = i; }
        
        char grade = getLetterGrade(scores[i]);
        if (grade == 'A') distribution[0]++;
        else if (grade == 'B') distribution[1]++;
        else if (grade == 'C') distribution[2]++;
        else if (grade == 'D') distribution[3]++;
        else if (grade == 'F') distribution[4]++;
    }

    double average = total / NUM_QUIZZES;

    cout << "\nQuiz Results:" << endl;
    for (int i = 0; i < NUM_QUIZZES; i++) {
        cout << "  Quiz " << (i + 1) << ":  " << scores[i] << " (" << getLetterGrade(scores[i]) << ")" << endl;
    }

    cout << fixed << setprecision(1);
    cout << "\nStatistics:\n  Average: " << average << "\n  Highest: " << highest 
         << " (Quiz " << highIndex + 1 << ")\n  Lowest: " << lowest 
         << " (Quiz " << lowIndex + 1 << ")\n  Overall: " << getLetterGrade(average) << endl;

    return 0;
}