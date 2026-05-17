#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "Library.h"

// ==========================================
// BAD CHARACTER INPUT SENSORY SAFEGUARDS
// ==========================================
int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "[Error] Invalid number string. Enter numerical values only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

std::string getValidString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (value.empty() || value.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            std::cout << "[Error] Value cannot be blank. Try again.\n";
            continue;
        }
        return value;
    }
}

// ==========================================
// MAIN MENU IMPLEMENTATION
// ==========================================
int main() {
    Library lib("Central City Library");

    // Preseed historical defaults to match sample specifications flawlessly
    lib.addBook(Book("The Great Gatsby", 1925, "9780743273565", Author("F. Scott Fitzgerald", 1896)));
    lib.addBook(Book("1984", 1949, "9780451524935", Author("George Orwell", 1903)));
    lib.addBook(Book("Animal Farm", 1945, "9780451526342", Author("George Orwell", 1903)));

    while (true) {
        std::cout << "\nLIBRARY MANAGEMENT SYSTEM\n"
                  << "--------------------------\n"
                  << "Library: Central City Library\n\n"
                  << "1. Add Book\n"
                  << "2. Display All Books\n"
                  << "3. Search by Author\n"
                  << "4. Search by Title\n"
                  << "5. Show Stats\n"
                  << "6. Borrow a Book\n"
                  << "7. Return a Book\n"
                  << "8. Exit System\n\n";

        int choice = getValidInt("Enter choice: ");
        std::cout << "\n";

        if (choice == 1) {
            std::string title = getValidString("Enter Book Title: ");
            int year = getValidInt("Enter Publication Year: ");
            std::string isbn = getValidString("Enter ISBN Code: ");
            std::string authName = getValidString("Enter Author Name: ");
            int authBirth = getValidInt("Enter Author Birth Year: ");

            Author author(authName, authBirth);
            Book newBook(title, year, isbn, author);
            lib.addBook(newBook);
        } 
        else if (choice == 2) {
            lib.displayCatalog();
        } 
        else if (choice == 3) {
            std::string authorQuery = getValidString("Search by author: ");
            lib.searchByAuthor(authorQuery);
        } 
        else if (choice == 4) {
            std::string titleQuery = getValidString("Search by title keyword: ");
            lib.searchByTitle(titleQuery);
        } 
        else if (choice == 5) {
            lib.showStats();
        } 
        else if (choice == 6) {
            std::string borrowTitle = getValidString("Enter title of book to borrow: ");
            lib.checkoutBook(borrowTitle);
        } 
        else if (choice == 7) {
            std::string returnTitle = getValidString("Enter title of book to return: ");
            lib.returnBook(returnTitle);
        } 
        else if (choice == 8) {
            std::cout << "Goodbye!\n";
            break;
        } 
        else {
            std::cout << "[Error] Choice out of range. Try numbers 1-8.\n";
        }
    }
    return 0;
}