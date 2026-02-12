# Banking Management System - Software Architecture Document

## Version 1.0.0
**Date:** February 5, 2026  
**Author:** Development Team  
**Status:** Final

---

## Table of Contents

1. [Executive Summary](#executive-summary)
2. [System Overview](#system-overview)
3. [Architecture Design](#architecture-design)
4. [Design Patterns](#design-patterns)
5. [Class Diagrams](#class-diagrams)
6. [Component Diagrams](#component-diagrams)
7. [Sequence Diagrams](#sequence-diagrams)
8. [Data Persistence](#data-persistence)
9. [Technology Stack](#technology-stack)
10. [Build System](#build-system)
11. [Testing Strategy](#testing-strategy)
12. [Security Considerations](#security-considerations)

---

## Executive Summary

The Banking Management System is a console-based application developed in C++11 that provides comprehensive banking functionalities including account management, transactions, and fixed deposits. The system employs industry-standard design patterns and modern C++ features to ensure maintainability, scalability, and robustness.

### Key Features:
- Account creation with unique account numbers
- Secure login system
- Deposit and withdrawal operations
- Balance enquiry
- Transaction history (last 5 transactions)
- Fixed deposit functionality (12 and 24 months)
- File-based data persistence
- Comprehensive unit testing

---

## System Overview

### Purpose
The Banking Management System provides a complete solution for managing bank accounts and financial transactions through a console interface.

### Scope
- User account management
- Financial transactions
- Fixed deposit investments
- Transaction history tracking
- Persistent data storage

### Constraints
- Console-based user interface
- Single-user session at a time
- File-based storage (no database)
- Simple password hashing (demonstration purposes)

---

## Architecture Design

### Architectural Style: Layered Architecture

```
┌─────────────────────────────────────┐
│     Presentation Layer              │
│  (Console UI - main.cpp)            │
└─────────────────────────────────────┘
            ↓
┌─────────────────────────────────────┐
│     Business Logic Layer            │
│  (BankManager, Account)             │
└─────────────────────────────────────┘
            ↓
┌─────────────────────────────────────┐
│     Data Layer                      │
│  (Transaction, FixedDeposit)        │
└─────────────────────────────────────┘
            ↓
┌─────────────────────────────────────┐
│     Persistence Layer               │
│  (FileManager)                      │
└─────────────────────────────────────┘
```

### Layer Responsibilities

#### 1. Presentation Layer
- User interface and interaction
- Input validation
- Display formatting
- Menu navigation

#### 2. Business Logic Layer
- Account management (BankManager)
- Banking operations (Account)
- Business rules enforcement
- Authentication

#### 3. Data Layer
- Domain models
- Transaction records
- Fixed deposit calculations
- Data validation

#### 4. Persistence Layer
- File I/O operations
- Data serialization
- Data deserialization
- File system management

---

## Design Patterns

### 1. Singleton Pattern

**Implementation:** BankManager class

**Purpose:** Ensure only one instance of BankManager exists throughout the application lifecycle.

**Benefits:**
- Global point of access
- Controlled instantiation
- Thread-safe implementation

**Code Structure:**
```cpp
class BankManager {
private:
    static std::unique_ptr<BankManager> instance;
    static std::mutex mutex_;
    BankManager();  // Private constructor
    
public:
    static BankManager* getInstance();
    // Delete copy constructor and assignment
    BankManager(const BankManager&) = delete;
    BankManager& operator=(const BankManager&) = delete;
};
```

### 2. Factory Pattern (Implicit)

**Implementation:** Account and FixedDeposit creation through BankManager

**Purpose:** Centralize object creation and ensure proper initialization.

**Benefits:**
- Encapsulation of creation logic
- Consistent object initialization
- Easy to extend with new account types

### 3. Repository Pattern

**Implementation:** FileManager class

**Purpose:** Abstract data access layer and provide consistent API for persistence.

**Benefits:**
- Separation of concerns
- Testability
- Easy to swap storage mechanisms

---

## Class Diagrams

### Core Classes Hierarchy

```
┌─────────────────────────────────────────────────────────────┐
│                        BankManager                          │
│  (Singleton)                                                │
├─────────────────────────────────────────────────────────────┤
│ - instance: unique_ptr<BankManager>                         │
│ - mutex_: mutex                                             │
│ - accounts: map<int, shared_ptr<Account>>                   │
│ - nextAccountNumber: int                                    │
├─────────────────────────────────────────────────────────────┤
│ + getInstance(): BankManager*                               │
│ + createAccount(name, password, balance): int               │
│ + login(accountNumber, password): shared_ptr<Account>       │
│ + getAccount(accountNumber): shared_ptr<Account>            │
│ + accountExists(accountNumber): bool                        │
│ + saveToFile(filename): bool                                │
│ + loadFromFile(filename): bool                              │
└─────────────────────────────────────────────────────────────┘
                            │
                            │ manages
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                        Account                              │
├─────────────────────────────────────────────────────────────┤
│ - accountNumber: int                                        │
│ - accountHolderName: string                                 │
│ - passwordHash: string                                      │
│ - balance: double                                           │
│ - transactionHistory: deque<Transaction>                    │
│ - fixedDeposits: vector<shared_ptr<FixedDeposit>>           │
├─────────────────────────────────────────────────────────────┤
│ + Account(accNum, name, password, initialBalance)           │
│ + deposit(amount): bool                                     │
│ + withdraw(amount): bool                                    │
│ + verifyPassword(password): bool                            │
│ + openFixedDeposit(amount, tenure): bool                    │
│ + displayBalance()                                          │
│ + displayAccountDetails()                                   │
│ + displayTransactionHistory()                               │
│ + serialize(): string                                       │
│ + deserialize(data): shared_ptr<Account>                    │
└─────────────────────────────────────────────────────────────┘
            │                              │
            │ contains                     │ contains
            ▼                              ▼
┌──────────────────────────┐   ┌─────────────────────────────┐
│     Transaction          │   │      FixedDeposit           │
├──────────────────────────┤   ├─────────────────────────────┤
│ - type: Type             │   │ - principal: double         │
│ - amount: double         │   │ - tenure: int               │
│ - balanceAfter: double   │   │ - interestRate: double      │
│ - timestamp: time_point  │   │ - openDate: time_point      │
│ - description: string    │   ├─────────────────────────────┤
├──────────────────────────┤   │ + calculateMaturityAmount() │
│ + toString(): string     │   │ + getMaturityDate(): string │
│ + serialize(): string    │   │ + serialize(): string       │
└──────────────────────────┘   └─────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│                      FileManager                            │
├─────────────────────────────────────────────────────────────┤
│ - dataDirectory: string                                     │
├─────────────────────────────────────────────────────────────┤
│ + ensureDataDirectory(): bool                               │
│ + writeToFile(filename, data): bool                         │
│ + readFromFile(filename): string                            │
│ + fileExists(filename): bool                                │
│ + getFilePath(filename): string                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Component Diagrams

### High-Level Component Architecture

```
┌───────────────────────────────────────────────────────────────┐
│                      User Interface                           │
│                      (Console App)                            │
└───────────────────────────────────────────────────────────────┘
                            │
                            │ uses
                            ▼
┌───────────────────────────────────────────────────────────────┐
│                    BankManager Component                      │
│  ┌─────────────────────────────────────────────────────┐     │
│  │  - Account Management                                │     │
│  │  - Authentication                                    │     │
│  │  - Session Management                                │     │
│  └─────────────────────────────────────────────────────┘     │
└───────────────────────────────────────────────────────────────┘
            │                                │
            │ manages                        │ uses
            ▼                                ▼
┌──────────────────────────┐    ┌────────────────────────────┐
│   Account Component      │    │  FileManager Component     │
│  ┌────────────────────┐  │    │  ┌──────────────────────┐ │
│  │ - Transactions     │  │    │  │ - File I/O           │ │
│  │ - Balance Mgmt     │  │    │  │ - Serialization      │ │
│  │ - FD Operations    │  │    │  │ - Directory Mgmt     │ │
│  └────────────────────┘  │    │  └──────────────────────┘ │
└──────────────────────────┘    └────────────────────────────┘
            │
            │ contains
            ▼
┌──────────────────────────────────────────────┐
│     Transaction & FixedDeposit Components    │
│  ┌────────────────────────────────────────┐  │
│  │  - Transaction Recording               │  │
│  │  - FD Calculation                      │  │
│  │  - Interest Computation                │  │
│  └────────────────────────────────────────┘  │
└──────────────────────────────────────────────┘
```

---

## Sequence Diagrams

### 1. Account Creation Flow

```
User          Console UI      BankManager        Account         FileManager
 │                │                │                │                │
 │  Select "Create Account"       │                │                │
 ├───────────────>│                │                │                │
 │                │                │                │                │
 │  Enter Details │                │                │                │
 ├───────────────>│                │                │                │
 │                │  createAccount()│               │                │
 │                ├───────────────>│                │                │
 │                │                │  new Account() │                │
 │                │                ├───────────────>│                │
 │                │                │<───────────────┤                │
 │                │                │  Store account │                │
 │                │                │                │                │
 │                │                │  saveToFile()  │                │
 │                │                ├───────────────────────────────>│
 │                │                │                │   Write data   │
 │                │                │<───────────────────────────────┤
 │                │<───────────────┤                │                │
 │  Display success                │                │                │
 │<───────────────┤                │                │                │
```

### 2. Login and Transaction Flow

```
User        Console UI    BankManager    Account    FileManager
 │              │              │             │            │
 │  Login       │              │             │            │
 ├─────────────>│              │             │            │
 │              │  login()     │             │            │
 │              ├─────────────>│             │            │
 │              │              │ verify      │            │
 │              │              │ password    │            │
 │              │              ├────────────>│            │
 │              │              │<────────────┤            │
 │              │<─────────────┤             │            │
 │              │  Return Account            │            │
 │<─────────────┤              │             │            │
 │              │              │             │            │
 │  Deposit     │              │             │            │
 ├─────────────>│              │             │            │
 │              │              │  deposit()  │            │
 │              │              ├────────────>│            │
 │              │              │             │ Update     │
 │              │              │             │ balance    │
 │              │              │             │ Add txn    │
 │              │              │<────────────┤            │
 │              │              │  saveToFile()            │
 │              │              ├─────────────────────────>│
 │              │              │             │   Persist  │
 │              │              │<─────────────────────────┤
 │              │<─────────────┤             │            │
 │<─────────────┤              │             │            │
 │  Display success            │             │            │
```

### 3. Fixed Deposit Creation Flow

```
User      Console UI    Account       FixedDeposit    Transaction
 │            │             │               │              │
 │  Open FD   │             │               │              │
 ├───────────>│             │               │              │
 │            │  openFixedDeposit()         │              │
 │            ├────────────>│               │              │
 │            │             │  Validate     │              │
 │            │             │  amount &     │              │
 │            │             │  tenure       │              │
 │            │             │               │              │
 │            │             │  new FixedDeposit()          │
 │            │             ├──────────────>│              │
 │            │             │               │ Calculate    │
 │            │             │               │ maturity     │
 │            │             │<──────────────┤              │
 │            │             │               │              │
 │            │             │  Deduct from balance         │
 │            │             │               │              │
 │            │             │  Add transaction             │
 │            │             ├─────────────────────────────>│
 │            │             │<─────────────────────────────┤
 │            │<────────────┤               │              │
 │<───────────┤             │               │              │
 │  Display FD details      │               │              │
```

---

## Data Persistence

### File Structure

```
BankingSystem/
│
├── data/
│   └── accounts.dat    # Main accounts database file
│
└── test_data/          # Test data directory (for unit tests)
```

### Serialization Format

#### Account Data Format:
```
accNum|name|passwordHash|balance
TRANSACTIONS:count
type|amount|balanceAfter|timestamp|description
...
FDS:count
principal|tenure|interestRate|timestamp
...
ACCOUNT_END
```

#### Complete File Format:
```
NEXT_ACCOUNT:1005
ACCOUNT_COUNT:2
---ACCOUNTS---
ACCOUNT_START
1001|John Doe|hash123|5000.50
TRANSACTIONS:3
0|1000.0|6000.0|1234567890|Initial deposit
1|500.0|5500.0|1234567900|Cash withdrawal
0|500.0|6000.0|1234567910|Cash deposit
FDS:1
5000.0|12|6.5|1234568000
ACCOUNT_END
ACCOUNT_START
1002|Jane Smith|hash456|10000.00
TRANSACTIONS:2
0|10000.0|10000.0|1234567920|Initial deposit
2|3000.0|7000.0|1234567930|FD opened for 24 months
FDS:1
3000.0|24|7.5|1234567930
ACCOUNT_END
```

---

## Technology Stack

### Programming Language
- **C++11**
  - Smart pointers (unique_ptr, shared_ptr)
  - Lambda expressions
  - Auto type deduction
  - Range-based for loops
  - Move semantics
  - Standard containers (map, vector, deque)
  - Chrono library for time operations
  - Mutex for thread safety

### Build System
- **CMake 3.14+**
  - Modern CMake practices
  - Out-of-source builds
  - Target-based configuration
  - Automatic test discovery

### Testing Framework
- **Google Test (gtest) 1.14.0**
  - Unit testing
  - Test fixtures
  - Assertions and expectations
  - Test discovery

### File System
- **Standard C++ filesystem**
  - POSIX-compliant operations
  - Cross-platform compatibility

---

## Build System

### Project Structure

```
BankingSystem/
├── CMakeLists.txt          # Main CMake configuration
├── include/                # Header files
│   ├── Account.h
│   ├── BankManager.h
│   ├── FileManager.h
│   ├── FixedDeposit.h
│   └── Transaction.h
├── src/                    # Implementation files
│   ├── Account.cpp
│   ├── BankManager.cpp
│   ├── FileManager.cpp
│   ├── FixedDeposit.cpp
│   ├── Transaction.cpp
│   └── main.cpp
├── tests/                  # Unit tests
│   ├── test_account.cpp
│   ├── test_bank_manager.cpp
│   ├── test_file_manager.cpp
│   └── test_fixed_deposit.cpp
├── data/                   # Data directory
├── docs/                   # Documentation
└── bin/                    # Build output (created by CMake)
```

### Build Commands

```bash
# Create build directory
mkdir build && cd build

# Configure project
cmake ..

# Build project
cmake --build .

# Run tests
ctest --output-on-failure

# Run application
./bin/BankingSystem
```

### CMake Targets

- **BankingLib**: Static library with core functionality
- **BankingSystem**: Main executable
- **BankingTests**: Test executable

---

## Testing Strategy

### Test Coverage

#### 1. Account Tests (test_account.cpp)
- Account creation
- Password verification
- Deposit operations (positive, negative, zero)
- Withdrawal operations (sufficient, insufficient, negative)
- Multiple transactions
- Transaction history limit (max 5)
- Fixed deposit operations
- Serialization/deserialization

#### 2. Fixed Deposit Tests (test_fixed_deposit.cpp)
- FD creation (12 and 24 months)
- Maturity amount calculation
- Invalid tenure validation
- Negative/zero amount validation
- Maturity date calculation
- Serialization/deserialization
- Interest calculation accuracy

#### 3. Bank Manager Tests (test_bank_manager.cpp)
- Singleton pattern verification
- Account creation
- Sequential account numbers
- Login authentication
- Account existence checks
- Save and load functionality
- Data persistence
- Multi-account management

#### 4. File Manager Tests (test_file_manager.cpp)
- Directory creation
- File read/write operations
- File existence checks
- Line-based I/O
- Large file handling
- Special characters
- File overwriting
- File deletion

### Test Execution

```bash
# Run all tests
cd build
ctest

# Run with verbose output
ctest --verbose

# Run specific test
./bin/BankingTests --gtest_filter=AccountTest.*

# Generate coverage report (if configured)
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make coverage
```

---

## Security Considerations

### 1. Password Management
- **Current Implementation**: Simple hash function for demonstration
- **Production Recommendation**: Use bcrypt, scrypt, or Argon2
- Passwords stored as hashes, never in plaintext
- Minimum password length enforced (4 characters)

### 2. Input Validation
- All user inputs validated before processing
- Amount validation (positive values)
- Account number verification
- Tenure validation for fixed deposits

### 3. Data Integrity
- Transaction atomicity (all or nothing)
- Balance verification before withdrawal
- Account number uniqueness
- File system error handling

### 4. Session Management
- Single active session per account
- Logout functionality
- No session persistence across restarts

### 5. File Security
- Data stored in dedicated directory
- File permissions should be restricted (OS-level)
- **Production Recommendation**: 
  - Encrypt sensitive data at rest
  - Use database with proper access controls
  - Implement audit logging

---

## Future Enhancements

### Phase 2 Recommendations

1. **Enhanced Security**
   - Implement proper password hashing (bcrypt)
   - Add encryption for stored data
   - Implement session tokens
   - Add audit logging

2. **Additional Features**
   - Transfer between accounts
   - Loan management
   - Recurring deposits
   - Statement generation
   - Multi-currency support

3. **Technical Improvements**
   - Replace file storage with SQL database
   - Add network/REST API support
   - Implement multi-threading for concurrent users
   - Add configuration file support
   - Implement logging framework

4. **User Experience**
   - GUI interface (Qt or similar)
   - Email notifications
   - SMS alerts
   - Mobile app integration
   - Multi-language support

5. **Testing & Quality**
   - Integration tests
   - Performance tests
   - Load testing
   - Security testing
   - Code coverage > 90%

---

## Glossary

- **FD**: Fixed Deposit
- **DXA**: Document Exchange Architecture units (1440 DXA = 1 inch)
- **Singleton**: Design pattern ensuring single instance
- **Serialization**: Converting objects to storable format
- **Smart Pointer**: Automatic memory management pointer
- **Mutex**: Mutual exclusion lock for thread safety

---

## Revision History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0.0 | Feb 5, 2026 | Dev Team | Initial release |

---

## Conclusion

The Banking Management System demonstrates a well-architected, maintainable C++11 application with proper separation of concerns, design patterns, and comprehensive testing. The modular design allows for easy extension and maintenance while the file-based persistence provides a foundation that can be migrated to database systems in future iterations.

The system successfully implements all required functional requirements while maintaining code quality, testability, and adherence to modern C++ best practices.
