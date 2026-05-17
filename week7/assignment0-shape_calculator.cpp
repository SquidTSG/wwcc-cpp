#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits> // Required for std::numeric_limits to clear the input buffer

// Constant for Pi if M_PI is not available
const double PI = 3.14159;

// ==========================================
// HELPER FUNCTION FOR INPUT VALIDATION
// ==========================================
// This handles characters, spaces, returns, and numbers <= 0 smoothly
double getValidDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        // Check if the user typed non-numeric data (letters, symbols)
        if (std::cin.fail()) {
            std::cout << "[Error] Invalid input. Please enter a valid number.\n";
            std::cin.clear(); // Clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad characters
            continue;
        }

        // Check if the number breaks the structural geometry rule (> 0)
        if (value <= 0) {
            std::cout << "[Error] Value must be greater than 0. Try again.\n";
            continue;
        }

        // If everything is clean, return the value
        return value;
    }
}

// ==========================================
// RECTANGLE CLASS DEFINITION
// ==========================================
class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle(double l, double w) {
        setLength(l);
        setWidth(w);
    }

    // Const Getters
    double getLength() const { return length; }
    double getWidth() const { return width; }

    // Setters with validation
    void setLength(double l) {
        if (l > 0) {
            length = l;
        } else {
            std::cout << "[Error] Length must be greater than 0. Value unchanged.\n";
        }
    }

    void setWidth(double w) {
        if (w > 0) {
            width = w;
        } else {
            std::cout << "[Error] Width must be greater than 0. Value unchanged.\n";
        }
    }

    // Overloaded area() methods
    double area() const {
        return length * width;
    }

    void area(double& result) const {
        result = length * width;
    }

    // Method chaining resize() using explicit 'this' pointer
    Rectangle& resize(double factor) {
        if (factor > 0) {
            this->length *= factor;
            this->width *= factor;
        } else {
            std::cout << "[Error] Scale factor must be greater than 0.\n";
        }
        return *this; 
    }
};

// ==========================================
// CIRCLE CLASS DEFINITION
// ==========================================
class Circle {
private:
    double radius;

public:
    // Constructor
    Circle(double r) {
        setRadius(r);
    }

    // Setter with validation
    void setRadius(double r) {
        if (r > 0) {
            radius = r;
        } else {
            std::cout << "[Error] Radius must be greater than 0. Value unchanged.\n";
        }
    }

    // Const Getter
    double getRadius() const { return radius; }

    // Methods defined outside the class definition
    double area() const;
    double circumference() const;

    // Overloaded print methods
    void print() const {
        std::cout << "Circle (Radius: " << radius << ")\n"
                  << "Area: " << area() << "\n"
                  << "Circumference: " << circumference() << "\n";
    }

    void print(bool detailed) const {
        if (detailed) {
            std::cout << "Circle details:\n"
                      << "  Radius:        " << radius << "\n"
                      << "  Area:          pi x " << radius << "^2 = " << area() << "\n"
                      << "  Circumference: 2 x pi x " << radius << " = " << circumference() << "\n";
        } else {
            print();
        }
    }
};

// Defining Circle methods OUTSIDE the class definition
double Circle::area() const {
    return PI * radius * radius;
}

double Circle::circumference() const {
    return 2 * PI * radius;
}

// ==========================================
// BONUS CHALLENGE: TRIANGLE CLASS
// ==========================================
class Triangle {
private:
    double side1, side2, side3;

    // Helper method to validate triangle inequality theorem
    bool isValidTriangle(double s1, double s2, double s3) const {
        return (s1 > 0 && s2 > 0 && s3 > 0) && 
               (s1 + s2 > s3) && 
               (s1 + s3 > s2) && 
               (s2 + s3 > s1);
    }

public:
    // Constructor with validation
    Triangle(double s1, double s2, double s3) {
        if (isValidTriangle(s1, s2, s3)) {
            side1 = s1;
            side2 = s2;
            side3 = s3;
        } else {
            std::cout << "[Warning] Invalid triangle sides. Defaulting to equilateral (1,1,1).\n";
            side1 = side2 = side3 = 1.0;
        }
    }

    // Heron's formula for Area
    double area() const {
        double s = (side1 + side2 + side3) / 2.0; // Semi-perimeter
        return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    // Determine type of triangle
    std::string getType() const {
        if (side1 == side2 && side2 == side3) {
            return "equilateral";
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            return "isosceles";
        } else {
            return "scalene";
        }
    }

    // Method chaining scale()
    Triangle& scale(double factor) {
        if (factor > 0) {
            this->side1 *= factor;
            this->side2 *= factor;
            this->side3 *= factor;
        } else {
            std::cout << "[Error] Scale factor must be greater than 0.\n";
        }
        return *this;
    }

    void printInfo() const {
        std::cout << "Triangle (" << side1 << ", " << side2 << ", " << side3 << ")\n"
                  << "  Type: " << getType() << "\n"
                  << "  Area: " << area() << "\n";
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    // Setup consistent decimal formatting (2 decimal places)
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "SHAPE CALCULATOR\n";
    std::cout << "----------------\n\n";

    // 1. Get Bulletproof User Input for Rectangle
    double userLength = getValidDouble("Enter Rectangle Length: ");
    double userWidth = getValidDouble("Enter Rectangle Width: ");
    std::cout << "\n";

    // Create instance with validated inputs directly via constructor
    Rectangle rect(userLength, userWidth);

    // Display Rectangle Results
    std::cout << "Rectangle (Length: " << rect.getLength() << ", Width: " << rect.getWidth() << ")\n";
    std::cout << "Area: " << rect.area() << "\n";
    
    double areaRef = 0.0;
    rect.area(areaRef); // Calls overloaded reference method
    std::cout << "Area via reference: " << areaRef << "\n\n";


    // 2. Get Bulletproof User Input for Circle
    double userRadius = getValidDouble("Enter Circle Radius: ");
    std::cout << "\n";

    Circle circ(userRadius);

    // Display Circle Results
    circ.print();
    std::cout << "\n";
    circ.print(true); // Detailed output
    std::cout << "\n";


    // 3. Test Method Chaining on Rectangle
    std::cout << "Method chaining:\n";
    std::cout << "  Original:   Length = " << rect.getLength() << ", Width = " << rect.getWidth() << "\n";
    
    // Chain example: scales up by 2.0
    rect.resize(2.0); 
    std::cout << "  After resize(2.0): Length = " << rect.getLength() << ", Width = " << rect.getWidth() << "\n\n";


    // 4. Test Const Object constraints (Hardcoded as requested to prove safety syntax)
    std::cout << "Const Object Demonstration:\n";
    const Circle constCircle(5.0);
    std::cout << "  Const Circle Radius: " << constCircle.getRadius() << "\n";
    std::cout << "  Const Circle Area:   " << constCircle.area() << "\n\n";


    // 5. Test Bonus Challenge (Triangle User Input)
    std::cout << "Enter 3 sides for a Triangle:\n";
    double s1 = getValidDouble("Side 1: ");
    double s2 = getValidDouble("Side 2: ");
    double s3 = getValidDouble("Side 3: ");
    std::cout << "\n";

    Triangle tri(s1, s2, s3);
    tri.printInfo();
    
    std::cout << "  After scaling by 2.0 via method chaining:\n";
    tri.scale(2.0);
    tri.printInfo();

    return 0;
}