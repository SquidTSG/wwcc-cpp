#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double x1, y1, x2, y2;
    
    cout << "Enter the coordinates of the first point:" << endl;
    cout << "x1: ";
    cin >> x1;
    cout << "y1: ";
    cin >> y1;
    
    cout << "Enter the coordinates of the second point:" << endl;
    cout << "x2: ";
    cin >> x2;
    cout << "y2: ";
    cin >> y2;
    
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    
    cout << fixed << setprecision(2);
    cout << "The distance between (" << x1 << "," << y1 << ") and (" << x2 << "," << y2 << ") is: " << distance << endl;
    
    return 0;
}