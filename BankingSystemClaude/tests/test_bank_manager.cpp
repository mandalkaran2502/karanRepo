#include <gtest/gtest.h>
#include "BankManager.h"

class BankManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        BankManager::resetInstance();
        bankManager = BankManager::getInstance();
    }

    void TearDown() override {
        BankManager::resetInstance();
    }

    BankManager* bankManager;
};

// Test Singleton pattern
TEST_F(BankManagerTest, SingletonPattern) {
    BankManager* instance1 = BankManager::getInstance();
    BankManager* instance2 = BankManager::getInstance();
    EXPECT_EQ(instance1, instance2);
}

// Test account creation
TEST_F(BankManagerTest, CreateAccount) {
    int accNum = bankManager->createAccount("Alice", "password", 1000.0);
    EXPECT_GE(accNum, 1001);
    EXPECT_TRUE(bankManager->accountExists(accNum));
}

// Test account creation with empty name
TEST_F(BankManagerTest, CreateAccountEmptyName) {
    int accNum = bankManager->createAccount("", "password", 1000.0);
    EXPECT_EQ(accNum, -1);
}

// Test account creation with short password
TEST_F(BankManagerTest, CreateAccountShortPassword) {
    int accNum = bankManager->createAccount("Bob", "123", 1000.0);
    EXPECT_EQ(accNum, -1);
}

// Test account creation with negative balance
TEST_F(BankManagerTest, CreateAccountNegativeBalance) {
    int accNum = bankManager->createAccount("Charlie", "password", -100.0);
    EXPECT_EQ(accNum, -1);
}

// Test sequential account numbers
TEST_F(BankManagerTest, SequentialAccountNumbers) {
    int acc1 = bankManager->createAccount("Alice", "pass1234", 1000.0);
    int acc2 = bankManager->createAccount("Bob", "pass1234", 2000.0);
    EXPECT_EQ(acc2, acc1 + 1);
}

// Test successful login
TEST_F(BankManagerTest, SuccessfulLogin) {
    int accNum = bankManager->createAccount("Dave", "password123", 1500.0);
    auto account = bankManager->login(accNum, "password123");
    EXPECT_NE(account, nullptr);
    EXPECT_EQ(account->getAccountNumber(), accNum);
}

// Test login with wrong password
TEST_F(BankManagerTest, LoginWrongPassword) {
    int accNum = bankManager->createAccount("Eve", "password123", 1500.0);
    auto account = bankManager->login(accNum, "wrongpassword");
    EXPECT_EQ(account, nullptr);
}

// Test login with non-existent account
TEST_F(BankManagerTest, LoginNonExistentAccount) {
    auto account = bankManager->login(9999, "password");
    EXPECT_EQ(account, nullptr);
}

// Test getAccount method
TEST_F(BankManagerTest, GetAccount) {
    int accNum = bankManager->createAccount("Frank", "password123", 2000.0);
    auto account = bankManager->getAccount(accNum);
    EXPECT_NE(account, nullptr);
    EXPECT_EQ(account->getAccountNumber(), accNum);
}

// Test accountExists method
TEST_F(BankManagerTest, AccountExists) {
    int accNum = bankManager->createAccount("Grace", "password123", 3000.0);
    EXPECT_TRUE(bankManager->accountExists(accNum));
    EXPECT_FALSE(bankManager->accountExists(9999));
}

// Test account count
TEST_F(BankManagerTest, AccountCount) {
    EXPECT_EQ(bankManager->getAccountCount(), 0);
    bankManager->createAccount("Alice", "pass1234", 1000.0);
    EXPECT_EQ(bankManager->getAccountCount(), 1);
    bankManager->createAccount("Bob", "pass1234", 2000.0);
    EXPECT_EQ(bankManager->getAccountCount(), 2);
}

// Test multiple account creation
TEST_F(BankManagerTest, MultipleAccounts) {
    int acc1 = bankManager->createAccount("User1", "pass1234", 1000.0);
    int acc2 = bankManager->createAccount("User2", "pass1234", 2000.0);
    int acc3 = bankManager->createAccount("User3", "pass1234", 3000.0);
    
    EXPECT_TRUE(bankManager->accountExists(acc1));
    EXPECT_TRUE(bankManager->accountExists(acc2));
    EXPECT_TRUE(bankManager->accountExists(acc3));
    EXPECT_EQ(bankManager->getAccountCount(), 3);
}

// Test save and load functionality
TEST_F(BankManagerTest, SaveAndLoad) {
    // Create accounts
    int acc1 = bankManager->createAccount("Alice", "pass1234", 1000.0);
    int acc2 = bankManager->createAccount("Bob", "pass5678", 2000.0);
    
    // Perform some operations
    auto account1 = bankManager->getAccount(acc1);
    account1->deposit(500.0);
    
    // Save to file
    EXPECT_TRUE(bankManager->saveToFile("test_accounts.dat"));
    
    // Reset instance
    BankManager::resetInstance();
    BankManager* newBankManager = BankManager::getInstance();
    
    // Load from file
    EXPECT_TRUE(newBankManager->loadFromFile("test_accounts.dat"));
    
    // Verify loaded data
    EXPECT_EQ(newBankManager->getAccountCount(), 2);
    EXPECT_TRUE(newBankManager->accountExists(acc1));
    EXPECT_TRUE(newBankManager->accountExists(acc2));
    
    auto loadedAccount = newBankManager->getAccount(acc1);
    EXPECT_NE(loadedAccount, nullptr);
    EXPECT_DOUBLE_EQ(loadedAccount->getBalance(), 1500.0);
}

// Test login after save and load
TEST_F(BankManagerTest, LoginAfterSaveLoad) {
    int accNum = bankManager->createAccount("Charlie", "mypassword", 3000.0);
    
    bankManager->saveToFile("test_login.dat");
    
    BankManager::resetInstance();
    BankManager* newBankManager = BankManager::getInstance();
    newBankManager->loadFromFile("test_login.dat");
    
    auto account = newBankManager->login(accNum, "mypassword");
    EXPECT_NE(account, nullptr);
    EXPECT_EQ(account->getAccountNumber(), accNum);
}

// Test load non-existent file
TEST_F(BankManagerTest, LoadNonExistentFile) {
    EXPECT_TRUE(bankManager->loadFromFile("nonexistent_file.dat"));
    EXPECT_EQ(bankManager->getAccountCount(), 0);
}

// Test next account number preservation
TEST_F(BankManagerTest, NextAccountNumberPreservation) {
    bankManager->createAccount("User1", "pass1234", 1000.0);
    int lastAccNum = bankManager->createAccount("User2", "pass1234", 2000.0);
    
    bankManager->saveToFile("test_acc_num.dat");
    
    BankManager::resetInstance();
    BankManager* newBankManager = BankManager::getInstance();
    newBankManager->loadFromFile("test_acc_num.dat");
    
    int newAccNum = newBankManager->createAccount("User3", "pass1234", 3000.0);
    EXPECT_GT(newAccNum, lastAccNum);
}
