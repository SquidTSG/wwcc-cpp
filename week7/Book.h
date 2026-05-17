#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Author.h"

class Book {
private:
    std::string title;
    int publicationYear;
    std::string isbn;
    Author author;     // Composition: Nested object
    bool isCheckedOut; // Tracks checkout status for bonus challenge

public:
    // Constructor using initialization lists
    Book(std::string title, int pubYear, std::string isbn, Author auth);

    // Const Getters
    std::string getTitle() const;
    int getPublicationYear() const;
    std::string getIsbn() const;
    Author getAuthor() const;
    bool getCheckedOutStatus() const;

    // Setters with validation
    void setPublicationYear(int year);
    void setCheckedOutStatus(bool status);

    // Display Info
    void display() const;
};

#endif