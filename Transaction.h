#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

/**
 * @brief Transaction class to store banking transaction details
 */
class Transaction 
{
public:
    enum class Type 
    {
        DEPOSIT,
        WITHDRAWAL,
        FD_OPEN,
        FD_MATURITY,
        TRANSFER
    };

private:
    Type type;
    double amount;
    double balanceAfter;
    std::chrono::system_clock::time_point timestamp;
    std::string description;

public:
    /**
     * @brief Constructor for Transaction
     */
    Transaction(Type t, double amt, double balance, const std::string& desc = "");

    /**
     * @brief Get transaction type
     */
    Type getType() const { return type; }

    /**
     * @brief Get transaction amount
     */
    double getAmount() const { return amount; }

    /**
     * @brief Get balance after transaction
     */
    double getBalanceAfter() const { return balanceAfter; }

    /**
     * @brief Get timestamp
     */
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }

    /**
     * @brief Get description
     */
    std::string getDescription() const { return description; }

    /**
     * @brief Convert transaction to string format
     */
    std::string toString() const;

    /**
     * @brief Serialize transaction to string for file storage
     */
    std::string serialize() const;

    /**
     * @brief Deserialize transaction from string
     */
    static Transaction deserialize(const std::string& data);

    /**
     * @brief Convert transaction type to string
     */
    static std::string typeToString(Type t);

    /**
     * @brief Convert string to transaction type
     */
    static Type stringToType(const std::string& s);
};

#endif // TRANSACTION_H
