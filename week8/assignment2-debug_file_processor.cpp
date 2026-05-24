#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm> // Required for min/max functions

using namespace std;

struct Student {
    string lastName;
    string firstName;
    int g1, g2, g3;
    double average;
    int high;
    int low;
};

int main() {
    // --- Read input file ---
    ifstream inFile("grades.txt");
    
    // BUG: File I/O — the input file is opened but the program never checks whether it actually opened successfully.
    // FIX: Added a check using !inFile to see if the file failed to open, printing an error message and terminating if true.
    if (!inFile) {
        cerr << "Error: Could not open grades.txt!" << endl;
        return 1;
    }

    cout << "Reading records from grades.txt..." << endl;
    vector<Student> students;
    string line;
    
    // BUG: Parsing / File I/O — stringstream ss is declared in the wrong place, and while (!inFile.eof()) causes the loop to run one extra time or process data incorrectly because eof is only set *after* a failed read.
    // FIX: Removed the broken stringstream declaration here and shifted entirely to using the safe while(getline(...)) method below.
    
    // --- Parse properly ---
    students.clear();
    
    // BUG: File I/O — the reading loop condition (!inFile.eof()) can cause issues, and the original structure was broken into two separate loops.
    // FIX: Combined the logic into a single, clean while(getline(inFile, line)) loop which safely handles EOF and reads line-by-line.
    while (getline(inFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        // BUG: Parsing — the stringstream object was originally declared outside the loop, causing data from previous lines to bleed or fail to clear.
        // FIX: Declared stringstream ss inside the loop scope so it resets completely with every single line processed.
        stringstream ss(line);
        
        Student s;
        ss >> s.lastName >> s.firstName >> s.g1 >> s.g2 >> s.g3;
        
        s.high = max({s.g1, s.g2, s.g3});
        s.low  = min({s.g1, s.g2, s.g3});
        
        int total = s.g1 + s.g2 + s.g3;
        
        // BUG: Math — the average calculation used integer division (total / 3), dropping all decimal precision.
        // FIX: Divided by 3.0 (a double literal) to force floating-point division and preserve decimal values.
        s.average = total / 3.0; 
        
        students.push_back(s);
    }
    inFile.close();
    
    cout << students.size() << " students loaded." << endl << endl;

    // --- Write report ---
    // BUG: File I/O — the output file opened in default overwrite mode; instructions state it should preserve previous runs by appending.
    // FIX: Added the ios::app flag to open the file in append mode.
    ofstream outFile("grade_report.txt", ios::app); 
    if (!outFile) {
        cerr << "Error: Could not open grade_report.txt for writing!" << endl;
        return 1;
    }

    // --- Display to console and write to file ---
    auto printReport = [&](ostream& out) {
        out << "GRADE REPORT" << endl;
        out << string(20, '-') << endl;
        out << left            
            << setw(20) << "Name"
            << setw(7)  << "Avg"
            << setw(7)  << "High"
            << setw(7)  << "Low"
            << endl;
        out << string(20, '-') << endl;

        double classTotal = 0;
        int topIdx = 0, lowIdx = 0;

        // BUG: Formatting — setw() was placed outside the loop here. Because setw() is not sticky, it only applied to the first element or did not format rows consistently.
        // FIX: Removed the standalone out << setw(20) from out here and placed it properly inside the loop for every row.

        for (int i = 0; i < (int)students.size(); i++) {
            Student& s = students[i];
            string name = s.lastName + ", " + s.firstName;
            
            // BUG: Formatting — numeric columns used the wrong alignment manipulator (left), causing misalignments with the headers.
            // FIX: Left-align the name string with setw(20), then change to right-alignment for the numbers while matching widths.
            out << left  << setw(20) << name
                << right << setw(5)  << fixed << setprecision(1) << s.average << "   "
                << right << setw(4)  << s.high << "   "
                << right << setw(4)  << s.low
                << endl;

            classTotal += s.average;
            if (s.average > students[topIdx].average) topIdx = i;
            if (s.average < students[lowIdx].average) lowIdx = i;
        }

        double classAvg = classTotal / students.size();

        out << endl << "CLASS STATISTICS" << endl;
        out << string(20, '-') << endl;
        out << fixed << setprecision(1);
        out << left << setw(15) << "Class average:" << classAvg << endl;
        out << left << setw(15) << "Top student:"   << students[topIdx].lastName << ", " << students[topIdx].firstName
            << " (" << students[topIdx].average << ")" << endl;
        out << left << setw(15) << "Low student:"   << students[lowIdx].lastName << ", " << students[lowIdx].firstName
            << " (" << students[lowIdx].average << ")" << endl;
    };

    printReport(cout);
    printReport(outFile);
    
    outFile.close();
    cout << endl << "Report written to grade_report.txt" << endl;

    return 0;
}