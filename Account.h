#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>
#include <deque>
#include "Transaction.h"
#include "FixedDeposit.h"

/**
 * @brief Account class representing a bank account
 */
class Account 
{
private:
    int accountNumber;
    std::string accountHolderName;
    std::string passwordHash;  // Stored as hashed password
    double balance;
    std::deque<Transaction> transactionHistory;  // Using deque for efficient front/back operations
    std::vector<std::shared_ptr<FixedDeposit>> fixedDeposits;
    
    static const size_t MAX_TRANSACTION_HISTORY = 5;

    /**
     * @brief Add transaction to history (maintains only last 5)
     */
    void addTransaction(Transaction::Type type, double amount, const std::string& desc = "");

    /**
     * @brief Hash password (simple hash for demonstration)
     */
    std::string hashPassword(const std::string& password) const;

public:
    /**
     * @brief Constructor for new account
     */
    Account(int accNum, const std::string& name, const std::string& pass, double initialBalance);

    /**
     * @brief Get account number
     */
    int getAccountNumber() const { return accountNumber; }

    /**
     * @brief Get account holder name
     */
    std::string getAccountHolderName() const { return accountHolderName; }

    /**
     * @brief Get current balance
     */
    double getBalance() const { return balance; }

    /**
     * @brief Get transaction history
     */
    const std::deque<Transaction>& getTransactionHistory() const { return transactionHistory; }

    /**
     * @brief Get fixed deposits
     */
    const std::vector<std::shared_ptr<FixedDeposit>>& getFixedDeposits() const { return fixedDeposits; }

    /**
     * @brief Verify password
     */
    bool verifyPassword(const std::string& pass) const;

    /**
     * @brief Deposit money
     * @param amount Amount to deposit (must be positive)
     * @return true if successful, false otherwise
     */
    bool deposit(double amount);

    /**
     * @brief Withdraw money
     * @param amount Amount to withdraw
     * @return true if successful, false if insufficient balance
     */
    bool withdraw(double amount);

    /**
     * @brief Display current balance
     */
    void displayBalance() const;

    /**
     * @brief Display account details
     */
    void displayAccountDetails() const;

    /**
     * @brief Display last 5 transactions
     */
    void displayTransactionHistory() const;

    /**
     * @brief Open a fixed deposit
     * @param amount FD amount
     * @param tenure Tenure in months (12 or 24)
     * @return true if successful, false otherwise
     */
    bool openFixedDeposit(double amount, int tenure);

    /**
     * @brief Display all fixed deposits
     */
    void displayFixedDeposits() const;

    /**
     * @brief Serialize account to string
     */
    std::string serialize() const;

    /**
     * @brief Deserialize account from string
     */
    static std::shared_ptr<Account> deserialize(const std::string& data);
};

#endif // ACCOUNT_H
