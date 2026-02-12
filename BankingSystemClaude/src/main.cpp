#include <iostream>
#include <limits>
#include <memory>
#include "BankManager.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void displayMainMenu() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           🏦 WELCOME TO SECURE BANK 🏦" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Login to Existing Account" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Enter your choice: ";
}

void displayAccountMenu(const std::string& accountHolder) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           ACCOUNT MENU - " << accountHolder << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "1. Deposit Money" << std::endl;
    std::cout << "2. Withdraw Money" << std::endl;
    std::cout << "3. Balance Enquiry" << std::endl;
    std::cout << "4. Account Details" << std::endl;
    std::cout << "5. Transaction History" << std::endl;
    std::cout << "6. Open Fixed Deposit" << std::endl;
    std::cout << "7. View Fixed Deposits" << std::endl;
    std::cout << "8. Logout" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Enter your choice: ";
}

void handleCreateAccount(BankManager* bank) {
    std::string name, password;
    double initialBalance;
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           CREATE NEW ACCOUNT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter account holder name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter password (min 4 characters): ";
    std::getline(std::cin, password);
    
    std::cout << "Enter initial deposit amount: ₹";
    std::cin >> initialBalance;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "❌ Invalid amount!" << std::endl;
        return;
    }
    
    bank->createAccount(name, password, initialBalance);
}

void handleLogin(BankManager* bank) {
    int accountNumber;
    std::string password;
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           LOGIN" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "❌ Invalid account number!" << std::endl;
        return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    
    auto account = bank->login(accountNumber, password);
    
    if (account == nullptr) {
        pause();
        return;
    }
    
    // Account menu loop
    bool loggedIn = true;
    while (loggedIn) {
        clearScreen();
        displayAccountMenu(account->getAccountHolderName());
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid choice!" << std::endl;
            pause();
            continue;
        }
        
        switch (choice) {
            case 1: {
                double amount;
                std::cout << "\nEnter deposit amount: ₹";
                std::cin >> amount;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "❌ Invalid amount!" << std::endl;
                } else {
                    account->deposit(amount);
                }
                pause();
                break;
            }
            case 2: {
                double amount;
                std::cout << "\nEnter withdrawal amount: ₹";
                std::cin >> amount;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "❌ Invalid amount!" << std::endl;
                } else {
                    account->withdraw(amount);
                }
                pause();
                break;
            }
            case 3:
                account->displayBalance();
                pause();
                break;
            case 4:
                account->displayAccountDetails();
                pause();
                break;
            case 5:
                account->displayTransactionHistory();
                pause();
                break;
            case 6: {
                double amount;
                int tenure;
                
                std::cout << "\n" << std::string(50, '=') << std::endl;
                std::cout << "OPEN FIXED DEPOSIT" << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                std::cout << "Interest Rates:" << std::endl;
                std::cout << "  12 months - 6.5% p.a." << std::endl;
                std::cout << "  24 months - 7.5% p.a." << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                
                std::cout << "Enter FD amount: ₹";
                std::cin >> amount;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "❌ Invalid amount!" << std::endl;
                    pause();
                    break;
                }
                
                std::cout << "Enter tenure (12 or 24 months): ";
                std::cin >> tenure;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "❌ Invalid tenure!" << std::endl;
                } else {
                    account->openFixedDeposit(amount, tenure);
                }
                pause();
                break;
            }
            case 7:
                account->displayFixedDeposits();
                pause();
                break;
            case 8:
                std::cout << "\n👋 Logging out..." << std::endl;
                loggedIn = false;
                pause();
                break;
            default:
                std::cout << "❌ Invalid choice! Please try again." << std::endl;
                pause();
        }
    }
}

int main() {
    BankManager* bank = BankManager::getInstance();
    
    // Load existing data
    bank->loadFromFile("accounts.dat");
    
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMainMenu();
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid choice!" << std::endl;
            pause();
            continue;
        }
        
        switch (choice) {
            case 1:
                handleCreateAccount(bank);
                bank->saveToFile("accounts.dat");
                pause();
                break;
            case 2:
                handleLogin(bank);
                bank->saveToFile("accounts.dat");
                break;
            case 3:
                std::cout << "\n" << std::string(60, '=') << std::endl;
                std::cout << "Thank you for banking with Secure Bank!" << std::endl;
                std::cout << "Have a great day! 👋" << std::endl;
                std::cout << std::string(60, '=') << std::endl;
                bank->saveToFile("accounts.dat");
                running = false;
                break;
            default:
                std::cout << "❌ Invalid choice! Please try again." << std::endl;
                pause();
        }
    }
    
    return 0;
}
