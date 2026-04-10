#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "! Welcome to C++!" << std::endl;

    std::string weight;
    std::cout << "What is your weight? ";
    std::getline(std::cin, weight);
    std::cout << "Wow, " << weight << " I hope thats pounds not kilograms otherwise you might weight more than your mom!" << std::endl;
    return 0;
}