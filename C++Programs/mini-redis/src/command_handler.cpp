#include <sstream>
#include <vector>
#include "command_handler.h"
CommandHandler::CommandHandler(Database& database)
:database(database)
{}

std::string CommandHandler::execute(const std::string& command)
{
    std::istringstream iss(command);
    std::string commandName;
    iss >> commandName;
    if(commandName == "SET")
    {
        std::string key;
        std::string value;
        iss >> key;
        iss >> value;
        if(key.empty() || value.empty())
        {
            return "Error: SET requires key and value";
        }
        return handleSet(key,value);
    }
    if(commandName  == "GET")
    {
        std::string key;
        iss  >> key;
        if(key.empty())
        {
            return "Error: GET requires key";
        }
        return handleGet(key);
    }
    if(commandName == "EXISTS")
    {
        std::string key;
        iss >> key;
        if(key.empty())
        {
            return "Error: EXISTS requires key";
        }
        return handleExists(key);
    }
    if(commandName == "DEL")
    {
        std::string key;
        iss >> key;
        if(key.empty())
        {
            return "Error: DEL requires key";
        }
        return handleDel(key);
    }
    return "Error: unknown command";
}

std::string CommandHandler::handleSet(const std::string& key, const std::string& value)
{
    database.set(key,value);
    return "ok";
}

std::string CommandHandler::handleGet(const std::string& key)
{
    auto value = database.get(key);
    if(!value.has_value())
    {
        return "(nil)";
    }
    return value.value();
}

std::string CommandHandler::handleExists(const std::string& key)
{
    if(database.exists(key))
    {
        return "1";
    }
    return "0";
}

std::string CommandHandler::handleDel(const std::string& key)
{
    if(database.del(key))
    {
        return "1";
    }
    return "0";
}