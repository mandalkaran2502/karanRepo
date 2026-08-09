#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include <map>
#include <memory>
#include <mutex>
#include "Account.h"

/**
 * @brief BankManager class - Singleton pattern
 * Manages all bank accounts and operations
 */
class BankManager 
{
private:
    static std::unique_ptr<BankManager> instance;
    static std::mutex mutex_;

    std::map<int, std::shared_ptr<Account>> accounts;
    int nextAccountNumber;

    // Private constructor for Singleton
    BankManager();

    // Delete copy constructor and assignment operator
    BankManager(const BankManager&) = delete;
    BankManager& operator=(const BankManager&) = delete;

public:
    /**
     * @brief Get singleton instance
     */
    static BankManager* getInstance();

    /**
     * @brief Create a new account
     * @return Account number of newly created account
     */
    int createAccount(const std::string& name, const std::string& password, double initialBalance);

    /**
     * @brief Login to account
     * @return Shared pointer to account if successful, nullptr otherwise
     */
    std::shared_ptr<Account> login(int accountNumber, const std::string& password);

    /**
     * @brief Get account by account number (for admin/testing)
     */
    std::shared_ptr<Account> getAccount(int accountNumber);

    /**
     * @brief Check if account exists
     */
    bool accountExists(int accountNumber) const;

    /**
     * @brief Get total number of accounts
     */
    size_t getAccountCount() const { return accounts.size(); }

    /**
     * @brief Save all accounts to file
     */
    bool saveToFile(const std::string& filename);

    /**
     * @brief Load all accounts from file
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Get next account number (for testing)
     */
    int getNextAccountNumber() const { return nextAccountNumber; }

    /**
     * @brief Reset instance (for testing)
     */
    static void resetInstance();
};

#endif // BANK_MANAGER_H
