#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

// ==========================================
// HELPER FUNCTION FOR INPUT VALIDATION
// ==========================================
// Robust utility to handle menu selections and numeric data entries smoothly.
double getValidDouble(const std::string& prompt, double minVal = 0.0) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "[Error] Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal) {
            std::cout << "[Error] Value cannot be less than " << minVal << ". Try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

int getValidInt(const std::string& prompt, int minVal = 0) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "[Error] Invalid input. Please enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal) {
            std::cout << "[Error] Value cannot be less than " << minVal << ". Try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

// ==========================================
// BANK ACCOUNT CLASS DEFINITION
// ==========================================
/* 
   FIX 1: Renamed class from 'account' to 'BankAccount' to follow standard PascalCase for classes.
   FIX 2: Implemented strict OOP encapsulation by separating private members and public interfaces.
*/
class BankAccount {
private:
    // FIX 3: All data members moved to 'private' to prevent direct outside corruption.
    std::string customerName;
    double balance;
    bool isOpen;         // FIX 4: Clearer boolean flag naming convention ('open' to 'isOpen').
    int accountNumber;   // FIX 4: Cleaner naming ('acc_number' to 'accountNumber').
    std::string accountType; // FIX 4: Cleaner naming ('type' to 'accountType').
    double overdraftLimit;   // BONUS: Configuration for custom overdraft limits.

    // BONUS: Struct to hold individual transaction history records.
    struct Transaction {
        std::string type;
        double amount;
        double runningBalance;
    };
    std::vector<Transaction> transactionHistory;

    // FIX 5: Extracted "magic numbers" from methods into beautifully defined named constants.
    // BONUS: Implemented balance tiers for premium interest rewards.
    const double INTEREST_SAVINGS = 0.03;
    const double INTEREST_CHECKING = 0.01;
    const double INTEREST_BUSINESS = 0.005;
    const double PREMIUM_TIER_BONUS = 0.015;       // Extra 1.5% for high balances
    const double PREMIUM_TIER_THRESHOLD = 10000.0; // Tier boundary at $10,000

    // Internal helper to seamlessly log transactions to history vector
    void recordTransaction(const std::string& type, double amount) {
        Transaction tx = {type, amount, balance};
        transactionHistory.push_back(tx);
    }

public:
    /* 
       FIX 6: Replaced the separate/unvalidated 'setup()' initialization function 
       with a robust constructor enforcing explicit setup and business logic constraints.
    */
    BankAccount(std::string name, int number, std::string type, double initialDeposit = 0.0, double odLimit = 0.0) {
        customerName = name;
        accountNumber = number;
        isOpen = true;
        overdraftLimit = odLimit;
        balance = 0.0; // Base zero before validation step

        // Validate type structure; default to checking if unrecognized
        if (type == "savings" || type == "checking" || type == "business") {
            accountType = type;
        } else {
            std::cout << "[Warning] Invalid account type. Defaulting to 'checking'.\n";
            accountType = "checking";
        }

        // Use standard validation pathway for handling initialization balance
        if (initialDeposit > 0) {
            deposit(initialDeposit);
        }
    }

    // FIX 7: Added 'const' to all getters ensuring they are entirely read-only methods.
    std::string getCustomerName() const { return customerName; }
    int getAccountNumber() const { return accountNumber; }
    std::string getAccountType() const { return accountType; }
    bool checkIsOpen() const { return isOpen; }
    
    // FIX 8: Renamed 'get_money()' to the standard industry naming convention 'getBalance()'.
    double getBalance() const { return balance; }

    /* 
       FIX 9: Added logical gate validation checks. 
       Rejects transactions if account status is closed or inputs are structurally illegal.
    */
    void deposit(double amount) {
        if (!isOpen) {
            std::cout << "[Error] Cannot deposit. Account is closed.\n";
            return;
        }
        if (amount <= 0) {
            std::cout << "[Error] Deposit amount must be positive.\n";
            return;
        }

        balance += amount;
        recordTransaction("Deposit", amount);
        std::cout << "Successfully deposited $" << amount << ". New Balance: $" << balance << "\n";
    }

    /* 
       FIX 10: Implemented balance validation safeguards for withdrawals.
       BONUS: Enhanced validation calculations to support custom overdraft thresholds.
    */
    void withdraw(double amount) {
        if (!isOpen) {
            std::cout << "[Error] Cannot withdraw. Account is closed.\n";
            return;
        }
        if (amount <= 0) {
            std::cout << "[Error] Withdrawal amount must be positive.\n";
            return;
        }
        // Check if transaction breaks safety boundaries: balance + overdraft cushion
        if (balance + overdraftLimit < amount) {
            std::cout << "[Error] Insufficient funds! Withdrawal limit exceeded.\n";
            return;
        }

        balance -= amount;
        recordTransaction("Withdrawal", amount);
        std::cout << "Successfully withdrew $" << amount << ". New Balance: $" << balance << "\n";
    }

    /* 
       FIX 11: Replaced unreadable compound expressions ('money = money * 1.03') with arithmetic operators.
       BONUS: Implemented multi-tiered conditional logic paths checking premium eligibility status.
    */
    void applyInterest() {
        if (!isOpen) return;

        double rate = 0.0;
        if (accountType == "savings") rate = INTEREST_SAVINGS;
        else if (accountType == "checking") rate = INTEREST_CHECKING;
        else if (accountType == "business") rate = INTEREST_BUSINESS;

        // Apply Premium Tier Bonus if balance clears the designated bar
        if (balance >= PREMIUM_TIER_THRESHOLD) {
            rate += PREMIUM_TIER_BONUS;
            std::cout << "[Premium Tier Applied] Extra interest rate awarded!\n";
        }

        double interestEarned = balance * rate;
        balance += interestEarned;
        
        if (interestEarned > 0) {
            recordTransaction("Interest Earned", interestEarned);
            std::cout << "Interest applied at " << (rate * 100) << "%. Earned: $" << interestEarned << "\n";
        }
    }

    // FIX 7: Marked print logic as 'const' to maintain structural read-only access.
    void printSummary() const {
        std::cout << "\n===============================\n"
                  << "        ACCOUNT SUMMARY        \n"
                  << "===============================\n"
                  << "Account Number: " << accountNumber << "\n"
                  << "Customer Name:  " << customerName << "\n"
                  << "Account Type:   " << accountType << "\n"
                  << "Status:         " << (isOpen ? "Open" : "Closed") << "\n"
                  << "Current Balance: $" << balance << "\n"
                  << "Overdraft Limit: $" << overdraftLimit << "\n"
                  << "===============================\n\n";
    }

    // BONUS: View designated window frames of the transactions registry vector.
    void printLastTransactions(int n) const {
        std::cout << "--- LAST " << n << " TRANSACTIONS FOR ACCOUNT #" << accountNumber << " ---\n";
        if (transactionHistory.empty()) {
            std::cout << " No transaction records found.\n\n";
            return;
        }

        // Determine loop count (handle cases where total transactions are less than n)
        int totalTx = transactionHistory.size();
        int count = std::min(n, totalTx);

        for (int i = totalTx - count; i < totalTx; ++i) {
            const auto& tx = transactionHistory[i];
            std::cout << " [" << tx.type << "] Amount: $" << tx.amount 
                      << " | Running Balance: $" << tx.runningBalance << "\n";
        }
        std::cout << "--------------------------------------------\n\n";
    }

    void closeAccount() {
        isOpen = false;
        std::cout << "Account #" << accountNumber << " has been securely closed.\n";
    }
};

// ==========================================
// MAIN FUNCTION (FULLY INTERACTIVE)
// ==========================================
int main() {
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "BANKING REGISTRATION INTERFACE\n";
    std::cout << "------------------------------\n";

    // Dynamic configuration collection via validated UI streams
    std::string name;
    std::cout << "Enter Customer Full Name: ";
    std::getline(std::cin, name);

    int accNum = getValidInt("Enter Desired Account Number: ", 1);

    std::string type;
    while (true) {
        std::cout << "Enter Account Type (savings / checking / business): ";
        std::cin >> type;
        if (type == "savings" || type == "checking" || type == "business") break;
        std::cout << "[Error] Unrecognized account tier. Try again.\n";
    }

    double initDeposit = getValidDouble("Enter Initial Deposit Amount ($): ");
    double odLimit = getValidDouble("Configure Overdraft Protection Limit ($): ");

    // Initialize clean instance securely using input streams through constructor
    BankAccount userAccount(name, accNum, type, initDeposit, odLimit);
    userAccount.printSummary();

    // INTERACTIVE MANAGEMENT MENU LOOP
    while (userAccount.checkIsOpen()) {
        std::cout << "--- ACCOUNT MANAGEMENT OPTIONS ---\n"
                  << "1. Deposit Funds\n"
                  << "2. Withdraw Funds\n"
                  << "3. Run Monthly Interest Assessment\n"
                  << "4. View Transaction Audit History\n"
                  << "5. Print Full Account Summary\n"
                  << "6. Close Account & Exit System\n";
        
        int choice = getValidInt("Select Option (1-6): ", 1);
        std::cout << "\n";

        if (choice == 1) {
            double amt = getValidDouble("Enter Deposit Amount: ");
            userAccount.deposit(amt);
        } 
        else if (choice == 2) {
            double amt = getValidDouble("Enter Withdrawal Amount: ");
            userAccount.withdraw(amt);
        } 
        else if (choice == 3) {
            userAccount.applyInterest();
        } 
        else if (choice == 4) {
            int count = getValidInt("How many recent transactions do you want to view? ", 1);
            userAccount.printLastTransactions(count);
        } 
        else if (choice == 5) {
            userAccount.printSummary();
        } 
        else if (choice == 6) {
            userAccount.closeAccount();
            break;
        } 
        else {
            std::cout << "[Error] Choice out of bounds. Select a valid action.\n";
        }
        std::cout << "\n";
    }

    std::cout << "\nSystem terminated cleanly. Have a wonderful day!\n";
    return 0;
}