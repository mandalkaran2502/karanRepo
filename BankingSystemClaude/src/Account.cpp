#include "Account.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <functional>

Account::Account(int accNum, const std::string& name, const std::string& pass, double initialBalance)
    : accountNumber(accNum), accountHolderName(name), balance(initialBalance) {
    
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
    
    passwordHash = hashPassword(pass);
    
    // Add initial deposit transaction
    if (initialBalance > 0) {
        addTransaction(Transaction::Type::DEPOSIT, initialBalance, "Initial deposit");
    }
}

std::string Account::hashPassword(const std::string& password) const {
    // Simple hash for demonstration (in production, use proper hashing like bcrypt)
    std::hash<std::string> hasher;
    size_t hash = hasher(password);
    std::stringstream ss;
    ss << hash;
    return ss.str();
}

bool Account::verifyPassword(const std::string& pass) const {
    return hashPassword(pass) == passwordHash;
}

void Account::addTransaction(Transaction::Type type, double amount, const std::string& desc) {
    Transaction trans(type, amount, balance, desc);
    transactionHistory.push_back(trans);
    
    // Keep only last 5 transactions
    if (transactionHistory.size() > MAX_TRANSACTION_HISTORY) {
        transactionHistory.pop_front();
    }
}

bool Account::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "❌ Deposit amount must be positive!" << std::endl;
        return false;
    }
    
    balance += amount;
    addTransaction(Transaction::Type::DEPOSIT, amount, "Cash deposit");
    
    std::cout << "✅ Successfully deposited ₹" << std::fixed << std::setprecision(2) 
              << amount << std::endl;
    std::cout << "Current balance: ₹" << balance << std::endl;
    
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "❌ Withdrawal amount must be positive!" << std::endl;
        return false;
    }
    
    if (amount > balance) {
        std::cout << "❌ Insufficient balance! Available: ₹" << std::fixed 
                  << std::setprecision(2) << balance << std::endl;
        return false;
    }
    
    balance -= amount;
    addTransaction(Transaction::Type::WITHDRAWAL, amount, "Cash withdrawal");
    
    std::cout << "✅ Successfully withdrawn ₹" << std::fixed << std::setprecision(2) 
              << amount << std::endl;
    std::cout << "Current balance: ₹" << balance << std::endl;
    
    return true;
}

void Account::displayBalance() const {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "💰 BALANCE ENQUIRY" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolderName << std::endl;
    std::cout << "Current Balance: ₹" << std::fixed << std::setprecision(2) 
              << balance << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void Account::displayAccountDetails() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "📋 ACCOUNT DETAILS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Account Number    : " << accountNumber << std::endl;
    std::cout << "Account Holder    : " << accountHolderName << std::endl;
    std::cout << "Current Balance   : ₹" << std::fixed << std::setprecision(2) 
              << balance << std::endl;
    std::cout << "Active FDs        : " << fixedDeposits.size() << std::endl;
    
    if (!fixedDeposits.empty()) {
        double totalFDAmount = 0;
        for (const auto& fd : fixedDeposits) {
            totalFDAmount += fd->getPrincipal();
        }
        std::cout << "Total FD Amount   : ₹" << std::fixed << std::setprecision(2) 
                  << totalFDAmount << std::endl;
    }
    
    std::cout << std::string(60, '=') << std::endl;
}

void Account::displayTransactionHistory() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "📜 TRANSACTION HISTORY (Last " << transactionHistory.size() << " transactions)" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (transactionHistory.empty()) {
        std::cout << "No transactions yet." << std::endl;
    } else {
        int count = 1;
        for (const auto& trans : transactionHistory) {
            std::cout << count++ << ". " << trans.toString() << std::endl;
        }
    }
    
    std::cout << std::string(80, '=') << std::endl;
}

bool Account::openFixedDeposit(double amount, int tenure) {
    if (amount <= 0) {
        std::cout << "❌ FD amount must be positive!" << std::endl;
        return false;
    }
    
    if (tenure != 12 && tenure != 24) {
        std::cout << "❌ FD tenure must be 12 or 24 months!" << std::endl;
        return false;
    }
    
    if (amount > balance) {
        std::cout << "❌ Insufficient balance! Available: ₹" << std::fixed 
                  << std::setprecision(2) << balance << std::endl;
        return false;
    }
    
    try {
        auto fd = std::make_shared<FixedDeposit>(amount, tenure);
        fixedDeposits.push_back(fd);
        
        balance -= amount;
        std::stringstream desc;
        desc << "FD opened for " << tenure << " months";
        addTransaction(Transaction::Type::FD_OPEN, amount, desc.str());
        
        std::cout << "\n✅ Fixed Deposit opened successfully!" << std::endl;
        std::cout << "FD Amount         : ₹" << std::fixed << std::setprecision(2) 
                  << amount << std::endl;
        std::cout << "Tenure            : " << tenure << " months" << std::endl;
        std::cout << "Interest Rate     : " << fd->getInterestRate() << "%" << std::endl;
        std::cout << "Maturity Amount   : ₹" << fd->calculateMaturityAmount() << std::endl;
        std::cout << "Maturity Date     : " << fd->getMaturityDate() << std::endl;
        std::cout << "Remaining Balance : ₹" << balance << std::endl;
        
        return true;
    } catch (const std::exception& e) {
        std::cout << "❌ Error opening FD: " << e.what() << std::endl;
        return false;
    }
}

void Account::displayFixedDeposits() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "💎 FIXED DEPOSITS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (fixedDeposits.empty()) {
        std::cout << "No active fixed deposits." << std::endl;
    } else {
        int count = 1;
        for (const auto& fd : fixedDeposits) {
            std::cout << "\nFD #" << count++ << ":" << std::endl;
            std::cout << "  Principal        : ₹" << std::fixed << std::setprecision(2) 
                      << fd->getPrincipal() << std::endl;
            std::cout << "  Tenure           : " << fd->getTenure() << " months" << std::endl;
            std::cout << "  Interest Rate    : " << fd->getInterestRate() << "%" << std::endl;
            std::cout << "  Maturity Amount  : ₹" << fd->calculateMaturityAmount() << std::endl;
            std::cout << "  Maturity Date    : " << fd->getMaturityDate() << std::endl;
        }
    }
    
    std::cout << std::string(80, '=') << std::endl;
}

std::string Account::serialize() const {
    std::stringstream ss;
    
    // Format: accNum|name|passwordHash|balance
    ss << accountNumber << "|"
       << accountHolderName << "|"
       << passwordHash << "|"
       << balance << "\n";
    
    // Serialize transactions
    ss << "TRANSACTIONS:" << transactionHistory.size() << "\n";
    for (const auto& trans : transactionHistory) {
        ss << trans.serialize() << "\n";
    }
    
    // Serialize FDs
    ss << "FDS:" << fixedDeposits.size() << "\n";
    for (const auto& fd : fixedDeposits) {
        ss << fd->serialize() << "\n";
    }
    
    return ss.str();
}

std::shared_ptr<Account> Account::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string line;
    
    // Parse account info
    std::getline(ss, line);
    std::stringstream lineStream(line);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(lineStream, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 4) {
        throw std::runtime_error("Invalid account data");
    }
    
    int accNum = std::stoi(tokens[0]);
    std::string name = tokens[1];
    std::string passHash = tokens[2];
    double balance = std::stod(tokens[3]);
    
    // Create account with dummy password (hash is stored)
    auto account = std::make_shared<Account>(accNum, name, "dummy", 0);
    account->passwordHash = passHash;
    account->balance = balance;
    account->transactionHistory.clear(); // Remove initial transaction
    
    // Parse transactions
    std::getline(ss, line);
    if (line.find("TRANSACTIONS:") == 0) {
        int transCount = std::stoi(line.substr(13));
        for (int i = 0; i < transCount; ++i) {
            std::getline(ss, line);
            if (!line.empty()) {
                account->transactionHistory.push_back(Transaction::deserialize(line));
            }
        }
    }
    
    // Parse FDs
    std::getline(ss, line);
    if (line.find("FDS:") == 0) {
        int fdCount = std::stoi(line.substr(4));
        for (int i = 0; i < fdCount; ++i) {
            std::getline(ss, line);
            if (!line.empty()) {
                account->fixedDeposits.push_back(
                    std::make_shared<FixedDeposit>(FixedDeposit::deserialize(line))
                );
            }
        }
    }
    
    return account;
}
