#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>

// function prototype
// the & symbol indicates pass-by-reference, allowing us to "return" 3 values.
void convertTemperature(double inputTemp, char unit, double &c, double &f, double &k);

// Helper to fix input stream errors
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    double val;
    char unit;
    bool running = true;

    std::cout << "--- Temperature Converter ---" << std::endl;

    while (running) {
        // 1. Get Temperature Value
        std::cout << "\nEnter a temperature value: ";
        while (!(std::cin >> val)) {
            std::cout << "Invalid input. Please enter a number: ";
            clearInput();
        }

        // 2. Get and Validate Unit
        bool validUnit = false;
        while (!validUnit) {
            std::cout << "Enter the unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
            std::cin >> unit;
            unit = std::toupper(unit); // Handle lowercase input

            if (unit == 'C' || unit == 'F' || unit == 'K') {
                validUnit = true;
            } else {
                std::cout << "Error: '" << unit << "' is not a valid unit. " << std::endl;
                clearInput();
            }
        }

        // 3. Prepare variables for pass-by-reference
        double celsius, fahrenheit, kelvin;

        // 4. Call the conversion function
        convertTemperature(val, unit, celsius, fahrenheit, kelvin);

        // 5. Display Results
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nTemperature Conversions:" << std::endl;
        std::cout << "Celsius:    " << celsius << "°C" << std::endl;
        std::cout << "Fahrenheit: " << fahrenheit << "°F" << std::endl;
        std::cout << "Kelvin:     " << kelvin << "K" << std::endl;

        // 6. Re-ask to continue
        char response;
        bool validResponse = false;
        while (!validResponse) {
            std::cout << "\nConvert another temperature? (y/n): ";
            std::cin >> response;
            response = std::tolower(response);
            if (response == 'y') {
                validResponse = true;
            } else if (response == 'n') {
                validResponse = true;
                running = false;
            } else {
                std::cout << "Please enter 'y' or 'n'." << std::endl;
                clearInput();
            }
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}

/**
 * logic: first converts the input to Celsius as a "base," 
 * then calculates Fahrenheit and Kelvin from that base.
 */
void convertTemperature(double inputTemp, char unit, double &c, double &f, double &k) {
    // Step 1: Normalize input to Celsius
    switch (unit) {
        case 'C':
            c = inputTemp;
            break;
        case 'F':
            c = (inputTemp - 32) * 5.0 / 9.0;
            break;
        case 'K':
            c = inputTemp - 273.15;
            break;
    }

    // Step 2: calculate others from Celsius base
    f = (c * 9.0 / 5.0) + 32;
    k = c + 273.15;
}