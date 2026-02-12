#include <gtest/gtest.h>
#include "Account.h"

class AccountTest : public ::testing::Test {
protected:
    void SetUp() override {
        testAccount = std::make_shared<Account>(1001, "John Doe", "password123", 1000.0);
    }

    void TearDown() override {
        testAccount.reset();
    }

    std::shared_ptr<Account> testAccount;
};

// Test account creation
TEST_F(AccountTest, AccountCreation) {
    EXPECT_EQ(testAccount->getAccountNumber(), 1001);
    EXPECT_EQ(testAccount->getAccountHolderName(), "John Doe");
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test password verification
TEST_F(AccountTest, PasswordVerification) {
    EXPECT_TRUE(testAccount->verifyPassword("password123"));
    EXPECT_FALSE(testAccount->verifyPassword("wrongpassword"));
}

// Test deposit with positive amount
TEST_F(AccountTest, DepositPositiveAmount) {
    EXPECT_TRUE(testAccount->deposit(500.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1500.0);
}

// Test deposit with negative amount
TEST_F(AccountTest, DepositNegativeAmount) {
    EXPECT_FALSE(testAccount->deposit(-100.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test deposit with zero amount
TEST_F(AccountTest, DepositZeroAmount) {
    EXPECT_FALSE(testAccount->deposit(0.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test withdrawal with sufficient balance
TEST_F(AccountTest, WithdrawSufficientBalance) {
    EXPECT_TRUE(testAccount->withdraw(300.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 700.0);
}

// Test withdrawal with insufficient balance
TEST_F(AccountTest, WithdrawInsufficientBalance) {
    EXPECT_FALSE(testAccount->withdraw(1500.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test withdrawal with negative amount
TEST_F(AccountTest, WithdrawNegativeAmount) {
    EXPECT_FALSE(testAccount->withdraw(-100.0));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test multiple transactions
TEST_F(AccountTest, MultipleTransactions) {
    testAccount->deposit(500.0);
    testAccount->withdraw(200.0);
    testAccount->deposit(300.0);
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1600.0);
}

// Test transaction history limit (max 5)
TEST_F(AccountTest, TransactionHistoryLimit) {
    testAccount->deposit(100.0);
    testAccount->deposit(100.0);
    testAccount->deposit(100.0);
    testAccount->deposit(100.0);
    testAccount->deposit(100.0);
    testAccount->deposit(100.0); // 6th transaction
    
    // Should have only 5 transactions (excluding initial deposit)
    EXPECT_EQ(testAccount->getTransactionHistory().size(), 5);
}

// Test opening FD with valid parameters
TEST_F(AccountTest, OpenFixedDeposit12Months) {
    EXPECT_TRUE(testAccount->openFixedDeposit(500.0, 12));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 500.0);
    EXPECT_EQ(testAccount->getFixedDeposits().size(), 1);
}

TEST_F(AccountTest, OpenFixedDeposit24Months) {
    EXPECT_TRUE(testAccount->openFixedDeposit(500.0, 24));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 500.0);
    EXPECT_EQ(testAccount->getFixedDeposits().size(), 1);
}

// Test opening FD with invalid tenure
TEST_F(AccountTest, OpenFixedDepositInvalidTenure) {
    EXPECT_FALSE(testAccount->openFixedDeposit(500.0, 18));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
    EXPECT_EQ(testAccount->getFixedDeposits().size(), 0);
}

// Test opening FD with insufficient balance
TEST_F(AccountTest, OpenFixedDepositInsufficientBalance) {
    EXPECT_FALSE(testAccount->openFixedDeposit(1500.0, 12));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
    EXPECT_EQ(testAccount->getFixedDeposits().size(), 0);
}

// Test opening FD with negative amount
TEST_F(AccountTest, OpenFixedDepositNegativeAmount) {
    EXPECT_FALSE(testAccount->openFixedDeposit(-500.0, 12));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 1000.0);
}

// Test multiple FDs
TEST_F(AccountTest, OpenMultipleFixedDeposits) {
    EXPECT_TRUE(testAccount->openFixedDeposit(300.0, 12));
    EXPECT_TRUE(testAccount->openFixedDeposit(200.0, 24));
    EXPECT_DOUBLE_EQ(testAccount->getBalance(), 500.0);
    EXPECT_EQ(testAccount->getFixedDeposits().size(), 2);
}

// Test account with negative initial balance
TEST(AccountCreationTest, NegativeInitialBalance) {
    EXPECT_THROW({
        Account account(1002, "Jane Doe", "pass", -100.0);
    }, std::invalid_argument);
}

// Test serialization and deserialization
TEST_F(AccountTest, SerializationDeserialization) {
    testAccount->deposit(500.0);
    testAccount->withdraw(200.0);
    testAccount->openFixedDeposit(300.0, 12);
    
    std::string serialized = testAccount->serialize();
    auto deserializedAccount = Account::deserialize(serialized);
    
    EXPECT_EQ(deserializedAccount->getAccountNumber(), testAccount->getAccountNumber());
    EXPECT_EQ(deserializedAccount->getAccountHolderName(), testAccount->getAccountHolderName());
    EXPECT_DOUBLE_EQ(deserializedAccount->getBalance(), testAccount->getBalance());
    EXPECT_EQ(deserializedAccount->getFixedDeposits().size(), testAccount->getFixedDeposits().size());
}
