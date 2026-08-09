#include <cassert>
#include <iostream>

#include "database.h"

int main()
{
    Database db;

    // 1. SET new key
    db.set("name", "Karan");

    // 2. GET existing key
    auto name = db.get("name");

    assert(name.has_value());
    assert(name.value() == "Karan");

    // 3. GET missing key
    auto unknown = db.get("unknown");

    assert(!unknown.has_value());

    // 4. SET existing key -> verify overwrite
    db.set("name", "Rahul");

    auto updatedName = db.get("name");

    assert(updatedName.has_value());
    assert(updatedName.value() == "Rahul");

    // 5. SET empty value -> verify different from missing
    db.set("empty", "");

    auto emptyValue = db.get("empty");

    // Key exists, but its value is empty
    assert(emptyValue.has_value());
    assert(emptyValue.value() == "");

    // Missing key should return nullopt
    auto missingValue = db.get("missing");

    assert(!missingValue.has_value());

    // 6. EXISTS existing key
    assert(db.exists("name"));

    // Empty value key also exists
    assert(db.exists("empty"));

    // 7. EXISTS missing key
    assert(!db.exists("unknown"));

    // 8. DEL existing key
    assert(db.del("name"));

    // Verify key no longer exists
    assert(!db.exists("name"));

    // 9. DEL missing key
    assert(!db.del("unknown"));

    // 10. GET after DEL
    auto deletedValue = db.get("name");

    assert(!deletedValue.has_value());

    std::cout << "All database tests passed!" << std::endl;

    return 0;

}
