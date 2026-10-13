cmake_minimum_required(VERSION 4.0)
project(operater_overload_lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(operater_overload_lab
        main.cpp
        BankAccount.cpp
        BankAccount.h
        CheckingAccount.cpp
        CheckingAccount.h
        SavingsAccount.cpp
        SavingsAccount.h
)
