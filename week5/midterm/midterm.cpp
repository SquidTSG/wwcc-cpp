#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Nested struct to track when an item was last updated
struct Date {
    int month;
    int day;
    int year;
};

// Main data structure for inventory items
struct Product {
    string name;
    string sku;
    int quantity;
    double price;
    int reorderPoint;
    Date lastRestocked;
};

// Function Prototypes
void displayMenu();
void addProduct(Product inventory[], int &count, const int MAX);
void showInventory(const Product inventory[], int count);
void searchProduct(const Product inventory[], int count);
double calculateTotalValue(const Product inventory[], int count);

const int MAX_PRODUCTS = 50;

int main() {
    Product warehouse[MAX_PRODUCTS];
    int productCount = 0;
    int choice = 0;
    bool keepRunning = true;

    cout << "--- Inventory Management System ---" << endl;

    do {
        displayMenu();
        
        string userInput;
        getline(cin, userInput);

        // Validation for Menu Selection
        if (userInput.empty() || userInput.find_first_not_of(' ') == string::npos) {
            cout << "Selection cannot be empty. Please enter 1-5." << endl;
            continue; 
        }

        try {
            choice = stoi(userInput); 
        } catch (...) {
            cout << "Invalid input. Please enter a number (1-5)." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                addProduct(warehouse, productCount, MAX_PRODUCTS);
                break;
            case 2:
                showInventory(warehouse, productCount);
                break;
            case 3:
                searchProduct(warehouse, productCount);
                break;
            case 4: {
                double total = calculateTotalValue(warehouse, productCount);
                cout << fixed << setprecision(2);
                cout << "\nTotal Inventory Market Value: $" << total << endl;
                break;
            }
            case 5:
                keepRunning = false;
                cout << "Exiting... System Offline." << endl;
                break;
            default:
                cout << "Invalid selection. Please choose 1-5." << endl;
        }
    } while (keepRunning);

    return 0;
}

void displayMenu() {
    cout << "\n1. Add Product" << endl;
    cout << "2. View Inventory" << endl;
    cout << "3. Search Inventory" << endl;
    cout << "4. Calculate Total Value" << endl;
    cout << "5. Exit" << endl;
    cout << "Selection: ";
}

// Function to handle all inputs safely
string getSafeInput(string prompt) {
    string temp;
    while (true) {
        cout << prompt;
        getline(cin, temp);
        if (temp.empty() || temp.find_first_not_of(' ') == string::npos) {
            cout << "Error: This field cannot be empty or just spaces." << endl;
        } else {
            return temp;
        }
    }
}

void addProduct(Product inventory[], int &count, const int MAX) {
    if (count >= MAX) {
        cout << "Error: Inventory capacity reached." << endl;
        return;
    }

    Product p;
    
    // Now using the safe input logic for every single field
    p.name = getSafeInput("Item Name: ");
    p.sku = getSafeInput("SKU Code: ");

    // Handle numeric inputs by reading string first, then converting
    while (true) {
        try {
            p.quantity = stoi(getSafeInput("Current Quantity: "));
            break; 
        } catch (...) { cout << "Please enter a whole number for quantity." << endl; }
    }

    while (true) {
        try {
            p.price = stod(getSafeInput("Unit Price: ")); // stod = string to double
            break;
        } catch (...) { cout << "Please enter a decimal number for price." << endl; }
    }

    while (true) {
        try {
            p.reorderPoint = stoi(getSafeInput("Low Stock Threshold: "));
            break;
        } catch (...) { cout << "Please enter a whole number for threshold." << endl; }
    }

    p.lastRestocked = {5, 3, 2026}; 
    inventory[count] = p;
    count++;
    cout << "Item logged successfully." << endl;
}

void showInventory(const Product inventory[], int count) {
    if (count == 0) {
        cout << "\nNo items currently in stock." << endl;
        return;
    }

    cout << "\n" << left << setw(15) << "SKU" << setw(20) << "NAME" << setw(10) << "QTY" << "PRICE" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << inventory[i].sku 
             << setw(20) << inventory[i].name 
             << setw(10) << inventory[i].quantity 
             << "$" << inventory[i].price << endl;
        
        if (inventory[i].quantity <= inventory[i].reorderPoint) {
            cout << "  >> ALERT: REORDER REQUIRED <<" << endl;
        }
    }
}

void searchProduct(const Product inventory[], int count) {
    if (count == 0) {
        cout << "Inventory is empty. Nothing to search." << endl;
        return;
    }

    string query = getSafeInput("Search by Name or SKU: ");

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (inventory[i].name.find(query) != string::npos || inventory[i].sku == query) {
            cout << "\nMatch Found: " << inventory[i].name << " (" << inventory[i].sku << ")" << endl;
            cout << "Available: " << inventory[i].quantity << " | Price: $" << inventory[i].price << endl;
            found = true;
        }
    }

    if (!found) cout << "No matches found for '" << query << "'." << endl;
}

double calculateTotalValue(const Product inventory[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += (inventory[i].price * inventory[i].quantity);
    }
    return total;
}