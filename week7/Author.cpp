#include "Author.h"
#include <iostream>

Author::Author() : name("Unknown"), birthYear(0) {}

Author::Author(std::string name, int birthYear) : name(name), birthYear(birthYear) {}

std::string Author::getName() const { 
    return name; 
}

int Author::getBirthYear() const { 
    return birthYear; 
}

void Author::display() const {
    std::cout << name << " (born " << birthYear << ")";
}