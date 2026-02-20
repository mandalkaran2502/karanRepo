#include "Transaction.h"
#include <ctime>
#include <iostream>
#include <vector>

Transaction::Transaction(Type t, double amt, double balance, const std::string& desc)
    : type(t), amount(amt), balanceAfter(balance), 
      timestamp(std::chrono::system_clock::now()), description(desc) 
      {}

std::string Transaction::toString() const 
{
    std::stringstream ss;
    
    // Convert timestamp to readable format
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    
    // Format type
    std::string typeStr;
    switch(type) {
        case Type::DEPOSIT:
            typeStr = "DEPOSIT   ";
            break;
        case Type::WITHDRAWAL:
            typeStr = "WITHDRAWAL";
            break;
        case Type::FD_OPEN:
            typeStr = "FD OPEN   ";
            break;
        case Type::FD_MATURITY:
            typeStr = "FD MATURITY";
            break;
        case Type::TRANSFER:
            typeStr = "TRANSFER  ";
            break;
    }
    
    ss << timeStr << " | " << typeStr << " | ₹" << std::fixed << std::setprecision(2) 
       << amount << " | Balance: ₹" << balanceAfter;
    
    if (!description.empty()) {
        ss << " | " << description;
    }
    
    return ss.str();
}

std::string Transaction::serialize() const 
{
    std::stringstream ss;
    
    // Format: type|amount|balanceAfter|timestamp|description
    ss << static_cast<int>(type) << "|"
       << amount << "|"
       << balanceAfter << "|"
       << std::chrono::system_clock::to_time_t(timestamp) << "|"
       << description;
    
    return ss.str();
}

Transaction Transaction::deserialize(const std::string& data) 
{
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, '|')) 
    {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 4) {
        throw std::runtime_error("Invalid transaction data");
    }
    
    Type type = static_cast<Type>(std::stoi(tokens[0]));
    double amount = std::stod(tokens[1]);
    double balanceAfter = std::stod(tokens[2]);
    std::time_t time = std::stoll(tokens[3]);
    std::string description = tokens.size() > 4 ? tokens[4] : "";
    
    Transaction trans(type, amount, balanceAfter, description);
    // Reconstruct timestamp
    trans.timestamp = std::chrono::system_clock::from_time_t(time);
    
    return trans;
}

std::string Transaction::typeToString(Type t) 
{
    switch(t) 
    {
        case Type::DEPOSIT: return "DEPOSIT";
        case Type::WITHDRAWAL: return "WITHDRAWAL";
        case Type::FD_OPEN: return "FD_OPEN";
        case Type::FD_MATURITY: return "FD_MATURITY";
        case Type::TRANSFER: return "TRANSFER";
        default: return "UNKNOWN";
    }
}

Transaction::Type Transaction::stringToType(const std::string& s) 
{
    if (s == "DEPOSIT") return Type::DEPOSIT;
    if (s == "WITHDRAWAL") return Type::WITHDRAWAL;
    if (s == "FD_OPEN") return Type::FD_OPEN;
    if (s == "FD_MATURITY") return Type::FD_MATURITY;
    if (s == "TRANSFER") return Type::TRANSFER;
    return Type::DEPOSIT; // default
}
