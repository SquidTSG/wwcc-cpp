#include "Library.h"
#include <iostream>
#include <algorithm>

Library::Library(std::string name) : name(name) {}

std::string Library::toLowerCase(std::string str) const {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void Library::addBook(const Book& book) {
    catalog.push_back(book);
    std::cout << "Successfully added \"" << book.getTitle() << "\" to the catalog.\n";
}

void Library::displayCatalog() const {
    std::cout << "\nCATALOG:\n";
    if (catalog.empty()) {
        std::cout << "The library catalog is currently empty.\n";
        return;
    }
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << i + 1 << ". ";
        catalog[i].display();
        std::cout << "\n";
    }
}

void Library::searchByAuthor(const std::string& authorName) const {
    std::string searchTarget = toLowerCase(authorName);
    bool found = false;

    std::cout << "Books by " << authorName << ":\n";
    for (const auto& book : catalog) {
        if (toLowerCase(book.getAuthor().getName()).find(searchTarget) != std::string::npos) {
            std::cout << "  - \"" << book.getTitle() << "\" (" << book.getPublicationYear() << ")\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found matching author: " << authorName << "\n";
    }
}

void Library::searchByTitle(const std::string& keyword) const {
    std::string searchTarget = toLowerCase(keyword);
    bool found = false;

    std::cout << "Books matching keyword \"" << keyword << "\":\n";
    for (const auto& book : catalog) {
        if (toLowerCase(book.getTitle()).find(searchTarget) != std::string::npos) {
            std::cout << "  - \"" << book.getTitle() << "\" by " << book.getAuthor().getName() << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No items match your catalog query keyword.\n";
    }
}

void Library::showStats() const {
    std::cout << "\nSTATS:\n"
              << "  Total books in catalog: " << catalog.size() << "\n";
}

bool Library::checkoutBook(const std::string& title) {
    std::string searchTarget = toLowerCase(title);
    for (auto& book : catalog) {
        if (toLowerCase(book.getTitle()) == searchTarget) {
            if (book.getCheckedOutStatus()) {
                std::cout << "[Error] \"" << book.getTitle() << "\" is already checked out!\n";
                return false;
            }
            book.setCheckedOutStatus(true);
            std::cout << "Successfully borrowed \"" << book.getTitle() << "\".\n";
            return true;
        }
    }
    std::cout << "[Error] Book title not found in catalog archive.\n";
    return false;
}

bool Library::returnBook(const std::string& title) {
    std::string searchTarget = toLowerCase(title);
    for (auto& book : catalog) {
        if (toLowerCase(book.getTitle()) == searchTarget) {
            if (!book.getCheckedOutStatus()) {
                std::cout << "[Warning] \"" << book.getTitle() << "\" wasn't checked out.\n";
                return false;
            }
            book.setCheckedOutStatus(false);
            std::cout << "Successfully returned \"" << book.getTitle() << "\".\n";
            return true;
        }
    }
    std::cout << "[Error] Destination return index match missing.\n";
    return false;
}