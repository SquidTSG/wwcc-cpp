# Midterm: Inventory Management System


 Name: Dillan Widmar
 Project: Estate Inventory Management System
 Course: CS & IT - C++ Programming
 Description: A midterm project managing product stock with robust input validation.
 

## Project Overview
This C++ application is a robust inventory management tool designed to track products, SKUs, and stock levels. It features advanced input validation to ensure that accidental key presses (like the spacebar or Enter) do not break the user experience or cause interface scrolling.

## Key Features
*   **Safe Input System:** Every text box and menu selection is protected. If a user enters only spaces or leaves a field blank, the program will prompt them to try again immediately.
*   **Crash Protection:** Uses string-to-number conversion (`stoi` and `stod`) with error handling to ensure that typing letters into numeric fields (like price or quantity) does not crash the application.
*   **Low Stock Tracking:** Automatically alerts the user when an item's quantity falls below its specific reorder point.
*   **Search Functionality:** Supports partial name searching and exact SKU matching.
*   **Financial Reporting:** Generates a real-time total market value for all items stored in the system.

## How to Use
1.  **Compile:** Use a standard compiler like `g++ main.cpp -o inventory`.
2.  **Run:** Open the executable.
3.  **Navigate:** Use the numeric menu (1-5).
    *   **1:** Add an item. You must fill out all fields.
    *   **2:** View the full inventory table.
    *   **3:** Search for a specific item.
    *   **4:** View the total value of all stock.
    *   **5:** Close the program.

## Technical Implementation
*   **Structs:** Utilizes a `Product` struct with a nested `Date` struct.
*   **Data Storage:** Items are stored in a fixed-size array of 50 elements.
*   **Input Management:** Exclusively uses `getline()` for all user interactions to maintain a clean input buffer.
*   **Formatting:** Uses `<iomanip>` (specifically `setw` and `setprecision`) to create a professional-looking console table.