#include <iostream>

int main() {
    double num1, num2;
    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter second number: ";
    std::cin >> num2;   
    std::cout << "The sum is: " << num1 + num2 << std::endl;
    std::cout << "The difference is: " << num1 - num2 << std::endl;
    std::cout << "The product is: " << num1 * num2 << std::endl;
    std::cout << "The quotient is: " << num1 / num2 << std::endl;

    return 0;
}
