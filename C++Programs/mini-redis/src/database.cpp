#include "database.h"

std::optional<std::string> Database::get(const std::string& keymatch) const
{
    auto it = data.find(keymatch);
    if(it == data.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void Database::set(const std::string& ikey, const std::string& ivalue)
{
    data[ikey] = ivalue;
}

bool Database::del(const std::string &key)
{
    /*
    auto it = data.find(key);
    if(it != data.end()) 
    {
        data.erase(key);
        return true;
    }
    return false;
    */

    /*erase(key) returns the number of elements removed.*/
    return data.erase(key) > 0;
}

bool Database::exists(const std::string& key) const
{   
    /*
    auto it = data.find(key);
    if(it == data.end()) 
    {
        return false;
    }
    return true;
    */
   return data.find(key) != data.end();
}

void Database::fetchAll() const
{
    for(const auto& it : data)
    {
        std::cout << it.first << " : " <<  it.second << std::endl;
    }
}