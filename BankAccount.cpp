#include "BankAccount.h"
#include <iostream>
#include <limits>

// Default constructor
BankAccount::BankAccount() {
    accountNumber = "";
    accountHolderName = new std::string("");
    balance = 0.0;
}

// Parameterized constructor
BankAccount::BankAccount(std::string accountNumber,
                         std::string accountHolderName,
                         double balance) {
    this->accountNumber = accountNumber;
    this->accountHolderName = new std::string(accountHolderName);
    this->balance = balance;
}

// Copy constructor
BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    accountHolderName = new std::string(*other.accountHolderName);
    balance = other.balance;
}

// Copy assignment operator
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;

        delete accountHolderName;
        accountHolderName = new std::string(*other.accountHolderName);

        balance = other.balance;
    }

    return *this;
}

// Virtual destructor
BankAccount::~BankAccount() {
    delete accountHolderName;
}

// Getters
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return *accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

// Deposit
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

// Withdraw
bool BankAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;
    return true;
}

// += operator
BankAccount& BankAccount::operator+=(double amount) {
    if (amount > 0) {
        balance += amount;
    }

    return *this;
}

// -= operator
BankAccount& BankAccount::operator-=(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    }

    return *this;
}

// == operator
bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

// < operator
bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

// > operator
bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

// Static print function
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "\nAccount Number: "
              << account.getAccountNumber() << "\n";

    std::cout << "Account Holder: "
              << account.getAccountHolderName() << "\n";

    std::cout << "Balance: $"
              << account.getBalance() << "\n";
}

// Static create function
BankAccount BankAccount::createAccountFromInput() {
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    std::cout << "Enter account holder name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, accountHolderName);

    while (accountHolderName.empty()) {
        std::cout << "Account holder name cannot be empty.\n";
        std::cout << "Enter account holder name: ";
        std::getline(std::cin, accountHolderName);
    }

    std::cout << "Enter starting balance: ";

    while (!(std::cin >> balance) || balance < 0) {
        std::cout << "Invalid balance. Please enter a non-negative number: ";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }

    return BankAccount(accountNumber, accountHolderName, balance);
}

// CheckingAccount constructor
CheckingAccount::CheckingAccount(std::string accountNumber,
                                 std::string accountHolderName,
                                 double balance,
                                 double transactionFee)
    : BankAccount(accountNumber, accountHolderName, balance),
      transactionFee(transactionFee >= 0 ? transactionFee : 0) {}

// CheckingAccount withdraw: deducts the requested amount plus the fee
bool CheckingAccount::withdraw(double amount) {
    if (amount <= 0) {
        return false;
    }

    return BankAccount::withdraw(amount + transactionFee);
}

// SavingsAccount constructor
SavingsAccount::SavingsAccount(std::string accountNumber,
                               std::string accountHolderName,
                               double balance,
                               double interestRate)
    : BankAccount(accountNumber, accountHolderName, balance),
      interestRate(interestRate >= 0 ? interestRate : 0) {}

// Add interest to the savings account.
// For example, an interest rate of 0.05 adds 5%.
void SavingsAccount::calculateInterest() {
    *this += getBalance() * interestRate;
}
