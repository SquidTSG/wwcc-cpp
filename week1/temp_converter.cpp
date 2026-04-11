#include <iostream>
#include <iomanip>

int main() {
    double temperature;
    char unit;
    double convertedTemp;

    std::cout << "Temp Converter" << std::endl;

    std::cout << "enter temperature Value ";
    std::cin >> temperature;

    std::cout << "enter unit (C for Celsius, F for Fahrenheit): ";
    std::cin >> unit;
    std::cout << std::fixed << std::setprecision(2);
    
    if (unit == 'C' || unit == 'c') {
        convertedTemp = (temperature * 9.0 / 5.0) + 32;
        std::cout <<  temperature << "°C is equal to " << convertedTemp << "°F" << std::endl;
    }
    else if (unit == 'F' || unit == 'f') {
        convertedTemp = (temperature -32) * 5.0 / 9.0;
        std::cout <<  temperature << "°F is equal to " << convertedTemp << "°C" << std::endl;
    }
    else {
        std::cout << "invalid unit entered." << std::endl;
    }

    return 0;
}