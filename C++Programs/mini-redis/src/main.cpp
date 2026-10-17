#include <iostream>

#include "command_handler.h"

int main()
{
    std::cout << "Mini Redis server starting..." << std::endl;
    Database db;
    CommandHandler handler(db);

    // Test SET
    std::cout << "SET name Karan" << std::endl;
    std::cout << handler.execute("SET name Karan") << std::endl;
    // Test GET
    std::cout << "GET name" << std::endl;
    std::cout << handler.execute("GET name") << std::endl;
    // Test EXISTS
    std::cout << "EXISTS name" << std::endl;
    std::cout << handler.execute("EXISTS name") << std::endl;
    // Test DEL
    std::cout << "DEL name" << std::endl;
    std::cout << handler.execute("DEL name") << std::endl;
    // Test GET after DEL
    std::cout << "GET name" << std::endl;
    std::cout << handler.execute("GET name") << std::endl;
    // Test EXISTS after DEL
    std::cout << "EXISTS name" << std::endl;
    std::cout << handler.execute("EXISTS name") << std::endl;
    // Test unknown command
    std::cout << "UNKNOWN name" << std::endl;
    std::cout << handler.execute("UNKNOWN name") << std::endl;
    return 0;
}