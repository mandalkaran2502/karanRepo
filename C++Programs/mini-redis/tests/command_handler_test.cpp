#include "command_handler.h"

#include <cassert>
#include <iostream>

int main()
{
    Database db;
    CommandHandler handler(db);

    // 1. SET: add a new key
    assert(handler.execute("SET name Karan") == "ok");

    // 2. GET: retrieve an existing key
    assert(handler.execute("GET name") == "Karan");

    // 3. SET: overwrite an existing key
    assert(handler.execute("SET name Rahul") == "ok");
    assert(handler.execute("GET name") == "Rahul");

    // 4. EXISTS: check an existing key
    assert(handler.execute("EXISTS name") == "1");

    // 5. EXISTS: check a missing key
    assert(handler.execute("EXISTS unknown") == "0");

    // 6. GET: retrieve a missing key
    assert(handler.execute("GET unknown") == "(nil)");

    // 7. DEL: delete an existing key
    assert(handler.execute("DEL name") == "1");

    // 8. GET: verify the key was deleted
    assert(handler.execute("GET name") == "(nil)");

    // 9. DEL: delete a key that does not exist
    assert(handler.execute("DEL unknown") == "0");

    // 10. Unknown command
    assert(handler.execute("UNKNOWN name") == "Error: unknown command");

    std::cout << "All command handler tests passed!" << std::endl;

    return 0;
}
