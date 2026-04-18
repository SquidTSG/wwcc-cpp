#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
using namespace std;

int main() {
    srand(time(0));

    int secretNumber = rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;

    cout << "Number Guessing Game" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl << endl;

    while (guess != secretNumber) {
        cout << "Enter Your Guess: ";
        if (!(cin >> guess)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(100, '\n');
            continue; 
        }
        attempts++;

        if (guess < secretNumber){
            cout << "Too low." << endl;
        }
        else if (guess > secretNumber) {
            cout << "Too high." << endl;
        }
    }

    cout << "YOU GOT IT! It only took you " << attempts << " attempts." << endl;


    return 0;
}