#include <iostream>
#include <iomanip>  // For setw()
using namespace std;

int main() {
    int start, end;

    cout << "Multiplication Table Generator" << endl << endl;

    cout << "Enter starting number: ";
    cin >> start;

    cout << "Enter ending number: ";
    cin >> end;

    if (start > end) {
        cout << "Error: Starting number must be less than ending number." << endl;
        return 1;
    }

    cout << endl;

    cout << setw(6) << " ";
    for (int i = start; i <= end; i++){
        cout << setw(6) << i;
    }
    cout << endl;

    cout << "       " << string((end - start + 4)* 6, '-') << endl;

    for (int i = start; i <= end; i++) {
        cout << setw(4) << i << " |";
        for (int j = start; j <= end; j++) {
            cout << setw(6) << i * j;
        }
        
        cout << endl;
    
    }

    return 0;
}