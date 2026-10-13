/*
Name: [Riley Pancake]
Date: [10.13.2026]
Assignment: Inheritance Lab

Program description:
- Demonstrates inheritance using BankAccount, CheckingAccount, and SavingsAccount.
- Stores account objects through BankAccount pointers and demonstrates polymorphic withdrawals.
- Provides a menu to display accounts, deposit, withdraw, and calculate savings interest.
*/

#include "BankAccount.h"

#include <iostream>
#include <memory>
#include <limits>
#include <vector>

int main() {
    std::vector<std::unique_ptr<BankAccount>> accounts;

    accounts.push_back(std::make_unique<CheckingAccount>(
        "1001", "Alex Smith", 500.00, 2.00));

    accounts.push_back(std::make_unique<SavingsAccount>(
        "1002", "Jordan Lee", 1000.00, 0.05));

    int choice = -1;

    do {
        std::cout << "\n--- Bank Account Menu ---\n"
                  << "1. Display all accounts\n"
                  << "2. Deposit\n"
                  << "3. Withdraw\n"
                  << "4. Calculate savings interest\n"
                  << "0. Exit\n"
                  << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            for (std::size_t i = 0; i < accounts.size(); ++i) {
                std::cout << "\nAccount " << i + 1 << ":";
                BankAccount::printAccount(*accounts[i]);
            }
        } else if (choice == 2 || choice == 3) {
            std::size_t accountNumber;
            double amount;

            std::cout << "Choose account (1-" << accounts.size() << "): ";
            if (!(std::cin >> accountNumber) ||
                accountNumber < 1 ||
                accountNumber > accounts.size()) {
                std::cout << "Invalid account selection.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cout << "Amount: $";
            if (!(std::cin >> amount)) {
                std::cout << "Invalid amount.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            BankAccount* account = accounts[accountNumber - 1].get();

            if (choice == 2) {
                account->deposit(amount);
                std::cout << "Deposit processed.\n";
            } else if (account->withdraw(amount)) {
                // CheckingAccount also deducts its transaction fee.
                std::cout << "Withdrawal successful.\n";
            } else {
                std::cout << "Withdrawal declined.\n";
            }
        } else if (choice == 4) {
            std::size_t accountNumber;

            std::cout << "Choose savings account (1-"
                      << accounts.size() << "): ";

            if (!(std::cin >> accountNumber) ||
                accountNumber < 1 ||
                accountNumber > accounts.size()) {
                std::cout << "Invalid account selection.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            SavingsAccount* savings =
                dynamic_cast<SavingsAccount*>(
                    accounts[accountNumber - 1].get());

            if (savings) {
                savings->calculateInterest();
                std::cout << "Interest calculated and added.\n";
            } else {
                std::cout << "That account is not a savings account.\n";
            }
        } else if (choice != 0) {
            std::cout << "Invalid menu choice.\n";
        }

    } while (choice != 0);

    std::cout << "Goodbye.\n";
    return 0;
}
