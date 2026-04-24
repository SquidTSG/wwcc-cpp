#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

// --- Function Prototypes ---
std::string format(int value);
std::string format(double value);                // Overload for default (2 decimal places)
std::string format(double value, int precision); // Overload for custom precision
std::string format(std::string text);

// Helper to fix the input stream when a user types the wrong data type
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    bool running = true;

    while (running) {
        std::cout << "--- Overloaded Print Formatter ---" << std::endl;
        std::cout << "1. Run Standard Demo with hardcoded values" << std::endl; //I didnt know if you wanted me to have custom input for the demo or not, so i just made both options available. The demo will run with hardcoded values, and the custom options will allow user input.
        std::cout << "2. Format Custom Integer" << std::endl;
        std::cout << "3. Format Custom Double" << std::endl;
        std::cout << "4. Format Custom String" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Select an option (1-5): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Error: Please enter a number between 1 and 5.\n" << std::endl;
            clearInput();
            continue;
        }

        if (choice == 1) {
            // --- THE BUILT-IN DEMO VERSION ---
            std::cout << "\n--- STARTING DEMO ---\n" << std::endl;
            
            std::cout << "Integer formatting:\nOriginal: 1234567\nFormatted: " << format(1234567) << "\n" << std::endl;
            
            std::cout << "Double formatting (default 2 decimal places):\nOriginal: 45.6789\nFormatted: " << format(45.6789) << "\n" << std::endl;
            
            std::cout << "Double formatting (custom decimal places):\nOriginal: 45.6789 with precision 3\nFormatted: " << format(45.6789, 3) << "\n" << std::endl;
            
            std::cout << "String formatting:\nOriginal: \"hello world of c++ programming\"\nFormatted: \"" << format("hello world of c++ programming") << "\"\n" << std::endl;
            
            std::cout << "--- END OF DEMO ---\n" << std::endl;
        } 
        else if (choice == 2) {
            int val;
            std::cout << "Enter integer: ";
            while (!(std::cin >> val)) {
                std::cout << "Invalid. Please enter a whole number: ";
                clearInput();
            }
            std::cout << "Formatted: " << format(val) << "\n" << std::endl;
        } 
        else if (choice == 3) {
            double val;
            int prec;
            std::cout << "Enter decimal number: ";
            while (!(std::cin >> val)) {
                std::cout << "Invalid. Please enter a double: ";
                clearInput();
            }
            std::cout << "Enter precision (e.g., 2): ";
            while (!(std::cin >> prec) || prec < 0) {
                std::cout << "Invalid. Enter a positive number: ";
                clearInput();
            }
            std::cout << "Formatted: " << format(val, prec) << "\n" << std::endl;
        } 
        else if (choice == 4) {
            std::string text;
            std::cout << "Enter text: ";
            clearInput(); 
            std::getline(std::cin, text);
            std::cout << "Formatted: \"" << format(text) << "\"\n" << std::endl;
        } 
        else if (choice == 5) {
            running = false;
            continue;
        }

        // --- Yes/No Re-ask Logic ---
        if (running) {
            char response;
            bool valid = false;
            while (!valid) {
                std::cout << "Return to menu? (y/n): ";
                std::cin >> response;
                response = std::tolower(response);
                if (response == 'y') {
                    valid = true;
                } else if (response == 'n') {
                    valid = true;
                    running = false;
                } else {
                    std::cout << "Invalid response. Type 'y' or 'n'." << std::endl;
                    clearInput();
                }
            }
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}

// --- Overloaded Function Implementations ---

// Integer with commas: Iterates backward adding commas every 3 digits.
std::string format(int value) {
    std::string s = std::to_string(std::abs(value));
    int i = s.length() - 3;
    while (i > 0) {
        s.insert(i, ",");
        i -= 3;
    }
    return (value < 0) ? "-" + s : s;
}

// Double Default: Calls the precision version with '2' as the argument.
std::string format(double value) {
    return format(value, 2);
}

// Double Custom: Uses stringstream and iomanip for rounding and precision.
std::string format(double value, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

// String Title Case: Checks for spaces and capitalizes the next character.
std::string format(std::string text) {
    bool capNext = true;
    for (char &c : text) {
        if (std::isspace(c)) {
            capNext = true;
        } else if (capNext) {
            c = std::toupper(c);
            capNext = false;
        }
    }
    return text;
}