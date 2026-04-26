#include <iostream>
#include <iomanip>
using namespace std;

// Conversion functions
double usdToEuro(double usd) {
    const double rate = 0.85;
    return usd * rate;
}

double usdToGBP(double usd) {
    const double rate = 0.75;
    return usd * rate;
}

double usdToJPY(double usd) {
    const double rate = 110.33;
    return usd * rate;
}

// Static counter function
int trackConversions() {
    static int count = 0;
    count++;
    return count;
}

int main() {
    int choice;
    double amount;
    char again = 'y';

    while (again == 'y' || again == 'Y') {
        cout << "\nCURRENCY CONVERTER\n";
        cout << "------------------\n";
        cout << "1. Convert USD to Euro (EUR)\n";
        cout << "2. Convert USD to British Pound (GBP)\n";
        cout << "3. Convert USD to Japanese Yen (JPY)\n";
        cout << "4. Exit\n";

        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        // Validate menu choice
        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            continue;
        }

        if (choice == 4) {
            break;
        }

        cout << "Enter amount in USD: ";
        cin >> amount;

        // Validate amount
        if (cin.fail() || amount < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid amount. Please enter a positive number.\n";
            continue;
        }

        double result = 0.0;

        switch (choice) {
            case 1:
                result = usdToEuro(amount);
                cout << fixed << setprecision(2);
                cout << amount << " USD = " << result << " EUR\n";
                break;
            case 2:
                result = usdToGBP(amount);
                cout << fixed << setprecision(2);
                cout << amount << " USD = " << result << " GBP\n";
                break;
            case 3:
                result = usdToJPY(amount);
                cout << fixed << setprecision(2);
                cout << amount << " USD = " << result << " JPY\n";
                break;
        }

        int total = trackConversions();
        cout << "\nNumber of conversions performed: " << total << "\n";

        cout << "\nWould you like to perform another conversion? (y/n): ";
        cin >> again;

        // Validate y/n input
        while (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
            cout << "Invalid input. Enter 'y' or 'n': ";
            cin >> again;
        }
    }

    cout << "\nBye\n";
    return 0;
}