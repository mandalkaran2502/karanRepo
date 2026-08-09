/* This is the database file */

#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>

class Database
{
private:
    std::unordered_map<std::string, std::string> data;

public:
    Database() = default;
    void set(const std::string& ikey, const std::string& ivalue);
    std::optional<std::string> get(const std::string&) const;
    bool del(const std::string& key);
    bool exists(const std::string& key) const;
    void fetchAll() const;
};

