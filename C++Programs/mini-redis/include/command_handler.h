#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>
#include "database.h"

class CommandHandler
{
    public:
    explicit CommandHandler(Database& database);
    std::string execute(const std::string& command);

    private:

    Database database;

    std::string handleSet(const std::string& key, const std::string& value);
    std::string handleGet(const std::string& key);
    std::string handleExists(const std::string& key);
    std::string handleDel(const std::string& key);
};

#endif // COMMAND_HANDLER_H