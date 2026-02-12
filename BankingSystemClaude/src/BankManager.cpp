#include "BankManager.h"
#include "FileManager.h"
#include <iostream>
#include <sstream>

// Initialize static members
std::unique_ptr<BankManager> BankManager::instance = nullptr;
std::mutex BankManager::mutex_;

BankManager::BankManager() : nextAccountNumber(1001) {}

BankManager* BankManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr) {
        instance = std::unique_ptr<BankManager>(new BankManager());
    }
    return instance.get();
}

int BankManager::createAccount(const std::string& name, const std::string& password, double initialBalance) {
    if (name.empty()) {
        std::cout << "❌ Account holder name cannot be empty!" << std::endl;
        return -1;
    }
    
    if (password.length() < 4) {
        std::cout << "❌ Password must be at least 4 characters long!" << std::endl;
        return -1;
    }
    
    if (initialBalance < 0) {
        std::cout << "❌ Initial balance cannot be negative!" << std::endl;
        return -1;
    }
    
    try {
        int accNum = nextAccountNumber++;
        auto account = std::make_shared<Account>(accNum, name, password, initialBalance);
        accounts[accNum] = account;
        
        std::cout << "\n✅ Account created successfully!" << std::endl;
        std::cout << "Account Number: " << accNum << std::endl;
        std::cout << "Account Holder: " << name << std::endl;
        std::cout << "Initial Balance: ₹" << std::fixed << std::setprecision(2) 
                  << initialBalance << std::endl;
        std::cout << "\n⚠️  Please remember your account number and password!" << std::endl;
        
        return accNum;
    } catch (const std::exception& e) {
        std::cout << "❌ Error creating account: " << e.what() << std::endl;
        return -1;
    }
}

std::shared_ptr<Account> BankManager::login(int accountNumber, const std::string& password) {
    auto it = accounts.find(accountNumber);
    
    if (it == accounts.end()) {
        std::cout << "❌ Account not found!" << std::endl;
        return nullptr;
    }
    
    if (!it->second->verifyPassword(password)) {
        std::cout << "❌ Invalid password!" << std::endl;
        return nullptr;
    }
    
    std::cout << "\n✅ Login successful!" << std::endl;
    std::cout << "Welcome, " << it->second->getAccountHolderName() << "!" << std::endl;
    
    return it->second;
}

std::shared_ptr<Account> BankManager::getAccount(int accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}

bool BankManager::accountExists(int accountNumber) const {
    return accounts.find(accountNumber) != accounts.end();
}

bool BankManager::saveToFile(const std::string& filename) {
    FileManager fileManager;
    if (!fileManager.ensureDataDirectory()) {
        std::cout << "❌ Error creating data directory!" << std::endl;
        return false;
    }
    
    std::stringstream ss;
    
    // Save next account number
    ss << "NEXT_ACCOUNT:" << nextAccountNumber << "\n";
    ss << "ACCOUNT_COUNT:" << accounts.size() << "\n";
    ss << "---ACCOUNTS---\n";
    
    // Save all accounts
    for (const auto& pair : accounts) {
        ss << "ACCOUNT_START\n";
        ss << pair.second->serialize();
        ss << "ACCOUNT_END\n";
    }
    
    if (fileManager.writeToFile(filename, ss.str())) {
        std::cout << "✅ Data saved successfully!" << std::endl;
        return true;
    } else {
        std::cout << "❌ Error saving data!" << std::endl;
        return false;
    }
}

bool BankManager::loadFromFile(const std::string& filename) {
    FileManager fileManager;
    
    if (!fileManager.fileExists(filename)) {
        std::cout << "ℹ️  No existing data file found. Starting fresh." << std::endl;
        return true;
    }
    
    std::string data = fileManager.readFromFile(filename);
    if (data.empty()) {
        std::cout << "❌ Error reading data file!" << std::endl;
        return false;
    }
    
    std::stringstream ss(data);
    std::string line;
    
    // Parse next account number
    std::getline(ss, line);
    if (line.find("NEXT_ACCOUNT:") == 0) {
        nextAccountNumber = std::stoi(line.substr(13));
    }
    
    // Skip account count line
    std::getline(ss, line);
    
    // Skip separator
    std::getline(ss, line);
    
    // Parse accounts
    while (std::getline(ss, line)) {
        if (line == "ACCOUNT_START") {
            std::stringstream accountData;
            while (std::getline(ss, line) && line != "ACCOUNT_END") {
                accountData << line << "\n";
            }
            
            try {
                auto account = Account::deserialize(accountData.str());
                accounts[account->getAccountNumber()] = account;
            } catch (const std::exception& e) {
                std::cout << "⚠️  Error loading account: " << e.what() << std::endl;
            }
        }
    }
    
    std::cout << "✅ Loaded " << accounts.size() << " account(s) from file." << std::endl;
    return true;
}

void BankManager::resetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    instance.reset();
}
