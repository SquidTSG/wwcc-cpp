#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int findMax(const int* arr, int size) {
    if (arr == nullptr || size <= 0) {
        return 0;
    }
    int maxVal = *arr;
    for (int i = 1; i < size; ++i) {
        if (*(arr + i) > maxVal) {
            maxVal = *(arr + i);
        }
    }
    return maxVal;
}

void writeNote(ofstream& file, const string& note) {
    if (file.is_open()) {
        file << note << "\n";
    }
}

void displayNotes(ifstream& file) {
    string line;
    while (getline(file, line)) {
        cout << "  " << line << endl;
    }
}

string getValidString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        bool hasContent = false;
        for (char c : input) {
            if (!isspace(c)) {
                hasContent = true;
                break;
            }
        }
        
        if (!hasContent) {
            cout << "Error: Input cannot be empty or just spaces. Please try again." << endl;
            continue;
        }
        return input;
    }
}

int getValidInt(const string& prompt) {
    string input;
    int number;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        stringstream ss(input);
        if (ss >> number) {
            char extra;
            if (!(ss >> extra)) {
                return number;
            }
        }
        cout << "Error: Invalid numeric input. Please enter a valid integer." << endl;
    }
}

double getValidDouble(const string& prompt) {
    string input;
    double number;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        stringstream ss(input);
        if (ss >> number) {
            char extra;
            if (!(ss >> extra)) {
                return number;
            }
        }
        cout << "Error: Invalid numeric input. Please enter a valid decimal number." << endl;
    }
}

char getValidChar(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.length() == 1 && !isspace(input.at(0))) {
            return input.at(0);
        }
        cout << "Error: Invalid input. Please enter exactly one non-space character." << endl;
    }
}

int main() {
    cout << "=== INITIALIZING DATA FOR PART 1 ===" << endl;
    int age = getValidInt("Enter an integer value (e.g., age): ");
    double gpa = getValidDouble("Enter a double value (e.g., gpa): ");
    char grade = getValidChar("Enter a char value (e.g., grade): ");
    
    cout << "\n=== PART 1: MEMORY AND ADDRESSING ===" << endl;
    cout << "\nVariable values and addresses:" << endl;
    cout << "  int    age    = " << age << "      at address " << &age << endl;
    cout << "  double gpa    = " << gpa << "    at address " << &gpa << endl;
    cout << "  char   grade  = '" << grade << "'     at address " << static_cast<const void*>(&grade) << endl;
    
    cout << "\nReference demonstration:" << endl;
    cout << "  Before: age = " << age << endl;
    int& ageRef = age;
    ageRef = ageRef + 1;
    cout << "  After modifying through reference: age = " << age << endl;
    
    cout << "\nPointer demonstration:" << endl;
    int* agePtr = nullptr;
    agePtr = &age;
    
    if (agePtr != nullptr) {
        cout << "  Pointer stores address: " << agePtr << endl;
        cout << "  Value at that address:  " << *agePtr << endl;
        *agePtr = 100;
        cout << "  After modifying through pointer: age = " << age << endl;
    }
    
    cout << "\nSetup for swap function:" << endl;
    int x = getValidInt("Enter first integer (x) to swap: ");
    int y = getValidInt("Enter second integer (y) to swap: ");
    
    cout << "\nSwap function (by reference):" << endl;
    cout << "  Before: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "  After swap: x = " << x << ", y = " << y << endl;
    
    cout << "\nSetup for Array values:" << endl;
    int arr[5];
    for (int i = 0; i < 5; ++i) {
        arr[i] = getValidInt("Enter array value for index " + to_string(i) + ": ");
    }
    
    cout << "\nArray-pointer relationship:" << endl;
    cout << "  arr[0] = " << arr[0] << "    *(arr + 0) = " << *(arr + 0) << endl;
    cout << "  arr[1] = " << arr[1] << "   *(arr + 1) = " << *(arr + 1) << endl;
    
    int maxVal = findMax(arr, 5);
    cout << "  Maximum value (via pointer): " << maxVal << endl;
    
    cout << "\n=== PART 2: FILE I/O ===" << endl;
    cout << endl;
    
    string note1 = getValidString("Enter note 1: ");
    string note2 = getValidString("Enter note 2: ");
    string note3 = getValidString("Enter note 3: ");
    
    ofstream outFile("notes.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Could not open notes.txt for writing." << endl;
        return 1;
    }
    
    writeNote(outFile, note1);
    writeNote(outFile, note2);
    writeNote(outFile, note3);
    outFile.close();
    
    cout << "\nNotes written to notes.txt successfully." << endl;
    
    ifstream inFile("notes.txt");
    if (!inFile) {
        cerr << "Error: Could not open notes.txt for reading." << endl;
        return 1;
    }
    
    cout << "\nReading notes back from file:" << endl;
    displayNotes(inFile);
    inFile.close();
    
    return 0;
}