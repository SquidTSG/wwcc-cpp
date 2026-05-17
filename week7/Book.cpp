#include "Book.h"
#include <iostream>

// Constructor using explicit member initialization lists
Book::Book(std::string title, int pubYear, std::string isbn, Author auth)
    : title(title), publicationYear(pubYear), isbn(isbn), author(auth), isCheckedOut(false) {
    // Invoke validation routing logic inside the body constructor 
    setPublicationYear(pubYear);
}

std::string Book::getTitle() const { return title; }
int Book::getPublicationYear() const { return publicationYear; }
std::string Book::getIsbn() const { return isbn; }
Author Book::getAuthor() const { return author; }
bool Book::getCheckedOutStatus() const { return isCheckedOut; }

void Book::setPublicationYear(int year) {
    if (year > 0) {
        publicationYear = year;
    } else {
        std::cout << "[Warning] Year must be positive. Defaulting to 2026.\n";
        publicationYear = 2026;
    }
}

void Book::setCheckedOutStatus(bool status) {
    isCheckedOut = status;
}

void Book::display() const {
    std::cout << "\"" << title << "\" (" << publicationYear << ")\n"
              << "   Author: ";
    author.display();
    std::cout << "\n   ISBN: " << isbn << "\n"
              << "   Availability: " << (isCheckedOut ? "Checked Out" : "Available") << "\n";
}