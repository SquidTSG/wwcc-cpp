#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "Book.h"

class Library {
private:
    std::string name;
    std::vector<Book> catalog; // Composition: Collection of Book objects

    // Helper utility for case-insensitive processing loops
    std::string toLowerCase(std::string str) const;

public:
    Library(std::string name);

    void addBook(const Book& book);
    void displayCatalog() const;
    void searchByAuthor(const std::string& authorName) const;
    void searchByTitle(const std::string& keyword) const;
    void showStats() const;

    // Bonus hooks to process mutations across the storage catalog
    bool checkoutBook(const std::string& title);
    bool returnBook(const std::string& title);
};

#endif