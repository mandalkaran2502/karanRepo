#ifndef FIXED_DEPOSIT_H
#define FIXED_DEPOSIT_H

#include <chrono>
#include <string>

/**
 * @brief Fixed Deposit class to handle FD operations
 */
class FixedDeposit {
private:
    double principal;
    int tenure; // in months (12 or 24)
    double interestRate;
    std::chrono::system_clock::time_point openDate;

public:
    /**
     * @brief Constructor for Fixed Deposit
     * @param amount Principal amount
     * @param months Tenure in months (12 or 24)
     */
    FixedDeposit(double amount, int months);

    /**
     * @brief Calculate maturity amount
     * @return Maturity amount with interest
     */
    double calculateMaturityAmount() const;

    /**
     * @brief Get tenure
     */
    int getTenure() const { return tenure; }

    /**
     * @brief Get principal amount
     */
    double getPrincipal() const { return principal; }

    /**
     * @brief Get interest rate
     */
    double getInterestRate() const { return interestRate; }

    /**
     * @brief Get open date
     */
    std::chrono::system_clock::time_point getOpenDate() const { return openDate; }

    /**
     * @brief Get maturity date as string
     */
    std::string getMaturityDate() const;

    /**
     * @brief Serialize FD to string
     */
    std::string serialize() const;

    /**
     * @brief Deserialize FD from string
     */
    static FixedDeposit deserialize(const std::string& data);
};

#endif // FIXED_DEPOSIT_H
