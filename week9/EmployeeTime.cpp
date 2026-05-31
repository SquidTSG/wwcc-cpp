#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>

using namespace std;

enum class Department { ENGINEERING, SALES, HR, OPERATIONS };

constexpr double OVERTIME_THRESHOLD = 40.0;
constexpr double OVERTIME_MULTIPLIER = 1.5;
constexpr double MAX_WEEKLY_HOURS = 168.0;

struct Employee {
    string name;
    Department dept;

    // BUG: hourlyRate was an int, which removed cents from fractional rates
    // FIX: changed hourlyRate to double so fractional rates are preserved
    double hourlyRate; // Bug 2: should be double

    double hoursWorked;
};

// Returns the display name for a department
string deptName(Department d) {
    switch (d) {
        case Department::ENGINEERING: return "Engineering";
        case Department::SALES: return "Sales";
        case Department::HR: return "HR";
        case Department::OPERATIONS: return "Operations";

        // BUG: no default case meant an invalid department could cause undefined behavior
        // FIX: added a default return value so the function always returns a string
        default: return "Unknown";
    }
}

// Validate hours input — returns true if valid
bool validHours(double hours) {
    // BUG: validHours only checked the upper bound and allowed negative hours
    // FIX: added a lower bound check so hours below zero are rejected
    if (hours < 0 || hours > MAX_WEEKLY_HOURS) { // Bug 4: only checks upper bound
        cout << "Error: hours must be between 0 and " << MAX_WEEKLY_HOURS << "\n";
        return false;
    }

    return true;
}

// Calculate weekly pay for one employee (with overtime)
double calculatePay(const Employee& e) {
    if (e.hoursWorked <= OVERTIME_THRESHOLD) {
        return e.hoursWorked * e.hourlyRate;
    } else {
        // BUG: overtime rate was applied to all hours instead of only hours over 40
        // FIX: regular hours are paid normally and only extra hours use the overtime multiplier
        double regularPay = OVERTIME_THRESHOLD * e.hourlyRate;
        double overtimeHours = e.hoursWorked - OVERTIME_THRESHOLD;
        double overtimePay = overtimeHours * e.hourlyRate * OVERTIME_MULTIPLIER;
        return regularPay + overtimePay;
    }
}

// Display a single employee row
void printEmployee(const Employee& e) {
    cout << left << setw(20) << e.name
         << setw(14) << deptName(e.dept)
         << right << setw(8) << fixed << setprecision(2) << e.hoursWorked << " hrs"
         << setw(10) << "$" + to_string(e.hourlyRate).substr(0, to_string(e.hourlyRate).find(".") + 3) + "/hr"
         << setw(12) << "$" + to_string(calculatePay(e)).substr(0, to_string(calculatePay(e)).find(".") + 3)
         << "\n";
}

// Display all employees
void displayAll(const vector<Employee>& employees) {
    cout << "\n=== Employee Time Report ===\n";
    cout << left << setw(20) << "Name"
         << setw(14) << "Department"
         << right << setw(8) << "Hours"
         << setw(10) << "Rate"
         << setw(12) << "Pay" << "\n";
    cout << string(64, '-') << "\n";

    for (const auto& emp : employees) {
        printEmployee(emp);
    }
}

// Calculate total payroll cost
double totalPayroll(const vector<Employee>& employees) {
    // BUG: accumulate started with 0, which is an int and could cause incorrect accumulation
    // FIX: changed the starting value to 0.0 so payroll is accumulated as a double
    return accumulate(employees.begin(), employees.end(), 0.0, // Bug 5: integer init
        [](double sum, const Employee& e) {
            return sum + calculatePay(e);
        });
}


void sortByHours(vector<Employee>& employees) {
    sort(employees.begin(), employees.end(),
        [](const Employee& a, const Employee& b) {
            return a.hoursWorked > b.hoursWorked;
        });

    cout << "\n=== Hours Ranking ===\n";
    displayAll(employees);
}


void getDepartmentStats(const vector<Employee>& employees, Department dept) {
    vector<Employee> filtered;

    copy_if(employees.begin(), employees.end(), back_inserter(filtered),
        [dept](const Employee& e) {
            return e.dept == dept;
        });

    double totalHours = accumulate(filtered.begin(), filtered.end(), 0.0,
        [](double sum, const Employee& e) {
            return sum + e.hoursWorked;
        });

    double totalPay = accumulate(filtered.begin(), filtered.end(), 0.0,
        [](double sum, const Employee& e) {
            return sum + calculatePay(e);
        });

    double averagePay = filtered.empty() ? 0.0 : totalPay / filtered.size();

    cout << "\n=== " << deptName(dept) << " Department Stats ===\n";
    cout << "Employees: " << filtered.size() << "\n";
    cout << fixed << setprecision(2);
    cout << "Total hours: " << totalHours << "\n";
    cout << "Average weekly pay: $" << averagePay << "\n";
}


void exportPayrollReport(const vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error: could not open " << filename << "\n";
        return;
    }

    vector<Department> departments = {
        Department::ENGINEERING,
        Department::SALES,
        Department::HR,
        Department::OPERATIONS
    };

    outFile << fixed << setprecision(2);
    outFile << "=== Payroll Report ===\n\n";

    for (Department dept : departments) {
        double subtotal = 0.0;

        outFile << "=== " << deptName(dept) << " ===\n";

        for (const auto& emp : employees) {
            if (emp.dept == dept) {
                double pay = calculatePay(emp);
                subtotal += pay;

                outFile << left << setw(20) << emp.name
                        << right << setw(12) << "$" << pay << "\n";
            }
        }

        outFile << "Subtotal: $" << subtotal << "\n\n";
    }

    outFile << "Total Payroll: $" << totalPayroll(employees) << "\n";

    outFile.close();

    cout << "Payroll report saved to " << filename << "\n";
}

int main() {
    vector<Employee> employees = {
        {"Alice Chen", Department::ENGINEERING, 42.00, 45.0},
        {"Bob Martinez", Department::SALES, 28.00, 38.0},
        {"Carol Singh", Department::HR, 35.50, 32.5}, // fractional rate
        {"David Park", Department::ENGINEERING, 38.00, 50.0},
        {"Emma Wilson", Department::OPERATIONS, 30.00, 29.0},
        {"Frank Torres", Department::SALES, 45.00, 44.5}, // overtime
        {"Grace Kim", Department::HR, 33.50, 33.5}, // fractional rate
        {"Henry Okafor", Department::OPERATIONS, 29.00, 55.0}, // overtime
    };

    cout << "=== HR Time Tracker ===\n";

    // Validate a sample input
    cout << "\nValidating hours entry -5: " << (validHours(-5) ? "valid" : "invalid") << "\n"; // should be invalid

    displayAll(employees);

    cout << "\nTotal payroll this week: $" << fixed << setprecision(2) << totalPayroll(employees) << "\n";


    sortByHours(employees);
    getDepartmentStats(employees, Department::ENGINEERING);
    exportPayrollReport(employees, "payroll_report.txt");

    return 0;
}