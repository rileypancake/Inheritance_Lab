#ifndef INHERITANCE_LAB_BANKACCOUNT_H
#define INHERITANCE_LAB_BANKACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string* accountHolderName;
    double balance;

public:
    // Constructors
    BankAccount();
    BankAccount(std::string accountNumber,
                std::string accountHolderName,
                double balance);

    // Rule of Three
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount();

    // Getters
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // Account operations
    void deposit(double amount);
    virtual bool withdraw(double amount);

    // Arithmetic assignment operators
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);

    // Comparison operators
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    // Static utility functions
    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();
};

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    CheckingAccount(std::string accountNumber,
                    std::string accountHolderName,
                    double balance,
                    double transactionFee);

    bool withdraw(double amount) override;
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string accountNumber,
                   std::string accountHolderName,
                   double balance,
                   double interestRate);

    void calculateInterest();
};

#endif // INHERITANCE_LAB_BANKACCOUNT_H
