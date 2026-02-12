#include "FixedDeposit.h"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>

FixedDeposit::FixedDeposit(double amount, int months)
    : principal(amount), tenure(months), openDate(std::chrono::system_clock::now()) {
    
    if (amount <= 0) {
        throw std::invalid_argument("FD amount must be positive");
    }
    
    if (tenure != 12 && tenure != 24) {
        throw std::invalid_argument("FD tenure must be 12 or 24 months");
    }
    
    // Set interest rate based on tenure
    if (tenure == 12) {
        interestRate = 6.5;  // 6.5% for 12 months
    } else {
        interestRate = 7.5;  // 7.5% for 24 months
    }
}

double FixedDeposit::calculateMaturityAmount() const {
    // Simple interest calculation: A = P * (1 + (r * t))
    // where r is rate per year, t is time in years
    double rate = interestRate / 100.0;
    double years = tenure / 12.0;
    double maturityAmount = principal * (1 + (rate * years));
    
    return maturityAmount;
}

std::string FixedDeposit::getMaturityDate() const {
    // Add tenure months to open date
    std::time_t openTime = std::chrono::system_clock::to_time_t(openDate);
    std::tm* tm = std::localtime(&openTime);
    
    tm->tm_mon += tenure;
    // Handle year overflow
    while (tm->tm_mon >= 12) {
        tm->tm_mon -= 12;
        tm->tm_year++;
    }
    
    std::time_t maturityTime = std::mktime(tm);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&maturityTime));
    
    return std::string(buffer);
}

std::string FixedDeposit::serialize() const {
    std::stringstream ss;
    
    // Format: principal|tenure|interestRate|timestamp
    ss << principal << "|"
       << tenure << "|"
       << interestRate << "|"
       << std::chrono::system_clock::to_time_t(openDate);
    
    return ss.str();
}

FixedDeposit FixedDeposit::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 4) {
        throw std::runtime_error("Invalid FD data");
    }
    
    double principal = std::stod(tokens[0]);
    int tenure = std::stoi(tokens[1]);
    double interestRate = std::stod(tokens[2]);
    std::time_t time = std::stoll(tokens[3]);
    
    FixedDeposit fd(principal, tenure);
    fd.interestRate = interestRate;
    fd.openDate = std::chrono::system_clock::from_time_t(time);
    
    return fd;
}
