#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string name;
    int birthYear;

public:
    // Constructor
    Author(); // Default constructor for vector allocations
    Author(std::string name, int birthYear);

    // Const Getters
    std::string getName() const;
    int getBirthYear() const;

    // Display Info
    void display() const;
};

#endif