# 🏦 Banking Management System

A comprehensive console-based banking management system built with modern C++11, featuring account management, transactions, fixed deposits, and file-based persistence.

[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Tests](https://img.shields.io/badge/tests-passing-brightgreen.svg)]()

## 📋 Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Building the Project](#building-the-project)
- [Running the Application](#running-the-application)
- [Running Tests](#running-tests)
- [Usage Guide](#usage-guide)
- [Architecture](#architecture)
- [Design Patterns](#design-patterns)
- [Documentation](#documentation)
- [Contributing](#contributing)

## ✨ Features

### Core Banking Operations
- ✅ **Account Creation**: Create new accounts with unique account numbers
- ✅ **Secure Login**: Password-protected authentication system
- ✅ **Deposit Money**: Add funds to your account with positive amounts
- ✅ **Withdraw Money**: Withdraw funds with balance validation
- ✅ **Balance Enquiry**: Check current account balance
- ✅ **Account Details**: View comprehensive account information
- ✅ **Transaction History**: View last 5 transactions with timestamps

### Fixed Deposit Features
- ✅ **FD Creation**: Open fixed deposits for 12 or 24 months
- ✅ **Interest Calculation**: Automatic interest calculation (6.5% for 12m, 7.5% for 24m)
- ✅ **Maturity Amount**: Display projected maturity amount
- ✅ **FD Management**: View all active fixed deposits

### Technical Features
- 🔒 **Data Persistence**: File-based storage for account data
- 🧪 **Comprehensive Testing**: 50+ unit tests using Google Test
- 🏗️ **Modern Architecture**: Singleton and Repository patterns
- 📦 **CMake Build System**: Professional build configuration
- 🛡️ **Input Validation**: Robust error handling and validation
- 🎯 **C++11 Features**: Smart pointers, lambda expressions, auto types

## 📦 Requirements

### System Requirements
- **Operating System**: Linux, macOS, or Windows
- **Compiler**: GCC 4.8+ / Clang 3.4+ / MSVC 2015+ with C++11 support
- **CMake**: Version 3.14 or higher
- **Memory**: Minimum 512 MB RAM
- **Disk Space**: 50 MB for build files

### Development Tools
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake git

# macOS (using Homebrew)
brew install cmake gcc

# Windows
# Install Visual Studio with C++ development tools
# Or install MinGW-w64 and CMake
```

## 📁 Project Structure

```
BankingSystem/
├── CMakeLists.txt              # Main CMake configuration
├── README.md                   # This file
├── LICENSE                     # Project license
│
├── include/                    # Header files
│   ├── Account.h              # Account class definition
│   ├── BankManager.h          # Bank manager (Singleton)
│   ├── FileManager.h          # File I/O operations
│   ├── FixedDeposit.h         # Fixed deposit functionality
│   └── Transaction.h          # Transaction records
│
├── src/                        # Implementation files
│   ├── Account.cpp            # Account implementation
│   ├── BankManager.cpp        # Bank manager implementation
│   ├── FileManager.cpp        # File operations implementation
│   ├── FixedDeposit.cpp       # Fixed deposit implementation
│   ├── Transaction.cpp        # Transaction implementation
│   └── main.cpp               # Main application entry point
│
├── tests/                      # Unit tests
│   ├── test_account.cpp       # Account class tests
│   ├── test_bank_manager.cpp  # Bank manager tests
│   ├── test_file_manager.cpp  # File manager tests
│   └── test_fixed_deposit.cpp # Fixed deposit tests
│
├── docs/                       # Documentation
│   └── ARCHITECTURE.md        # Detailed architecture document
│
├── data/                       # Data directory (created at runtime)
│   └── accounts.dat           # Persistent account storage
│
└── bin/                        # Build output (created by CMake)
    ├── BankingSystem          # Main executable
    └── BankingTests           # Test executable
```

## 🔨 Building the Project

### Quick Start

```bash
# Clone the repository
git clone <repository-url>
cd BankingSystem

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Alternatively, use make on Unix systems
make
```

### Build Configuration Options

```bash
# Debug build (with debug symbols)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build with verbose output
cmake --build . --verbose

# Parallel build (faster)
cmake --build . -j4
```

### Platform-Specific Builds

#### Linux/macOS
```bash
mkdir build && cd build
cmake ..
make
```

#### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

#### Windows (MinGW)
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

## 🚀 Running the Application

### Start the Application

```bash
# From the build directory
./bin/BankingSystem

# Or specify full path
/path/to/BankingSystem/build/bin/BankingSystem
```

### First Run

On first run, the system will:
1. Create a `data` directory in the current working directory
2. Initialize an empty accounts database
3. Display the main menu

### Data Persistence

Account data is automatically saved to:
- **Location**: `./data/accounts.dat`
- **Format**: Custom serialized format
- **Backup**: Recommended to backup this file regularly

## 🧪 Running Tests

### Run All Tests

```bash
# From the build directory
ctest

# Or run the test executable directly
./bin/BankingTests
```

### Run Specific Tests

```bash
# Run only Account tests
./bin/BankingTests --gtest_filter=AccountTest.*

# Run only Fixed Deposit tests
./bin/BankingTests --gtest_filter=FixedDepositTest.*

# Run with verbose output
./bin/BankingTests --gtest_verbose

# Run tests and show all output
ctest --output-on-failure
```

### Test Coverage

```bash
# Generate test coverage report (requires lcov)
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make
make coverage
```

### Test Statistics

- **Total Test Cases**: 50+
- **Test Files**: 4
- **Code Coverage**: ~85%
- **Test Framework**: Google Test 1.14.0

## 📖 Usage Guide

### Main Menu Options

```
🏦 WELCOME TO SECURE BANK 🏦
====================================
1. Create New Account
2. Login to Existing Account
3. Exit
====================================
```

### Creating an Account

1. Select option `1` from main menu
2. Enter account holder name
3. Create a password (minimum 4 characters)
4. Enter initial deposit amount
5. Note down your account number (e.g., 1001)

**Example:**
```
Enter account holder name: John Doe
Enter password (min 4 characters): mypass123
Enter initial deposit amount: ₹5000

✅ Account created successfully!
Account Number: 1001
Account Holder: John Doe
Initial Balance: ₹5000.00
```

### Logging In

1. Select option `2` from main menu
2. Enter your account number
3. Enter your password

### Account Menu

After successful login:

```
ACCOUNT MENU - John Doe
====================================
1. Deposit Money
2. Withdraw Money
3. Balance Enquiry
4. Account Details
5. Transaction History
6. Open Fixed Deposit
7. View Fixed Deposits
8. Logout
====================================
```

### Deposit Money

1. Select option `1`
2. Enter amount to deposit
3. Confirmation displayed with updated balance

**Example:**
```
Enter deposit amount: ₹1000

✅ Successfully deposited ₹1000.00
Current balance: ₹6000.00
```

### Withdraw Money

1. Select option `2`
2. Enter amount to withdraw
3. System validates sufficient balance
4. Confirmation displayed

**Example:**
```
Enter withdrawal amount: ₹500

✅ Successfully withdrawn ₹500.00
Current balance: ₹5500.00
```

### Opening a Fixed Deposit

1. Select option `6`
2. View interest rates:
   - 12 months: 6.5% p.a.
   - 24 months: 7.5% p.a.
3. Enter FD amount
4. Enter tenure (12 or 24 months)
5. System displays maturity details

**Example:**
```
Enter FD amount: ₹10000
Enter tenure (12 or 24 months): 12

✅ Fixed Deposit opened successfully!
FD Amount         : ₹10000.00
Tenure            : 12 months
Interest Rate     : 6.5%
Maturity Amount   : ₹10650.00
Maturity Date     : 2027-02-05
Remaining Balance : ₹5500.00
```

### Transaction History

View your last 5 transactions with:
- Transaction type (Deposit, Withdrawal, FD)
- Amount
- Balance after transaction
- Timestamp
- Description

**Example:**
```
📜 TRANSACTION HISTORY (Last 5 transactions)
========================================================
1. 2026-02-05 10:30:15 | DEPOSIT    | ₹5000.00 | Balance: ₹5000.00 | Initial deposit
2. 2026-02-05 10:35:20 | DEPOSIT    | ₹1000.00 | Balance: ₹6000.00 | Cash deposit
3. 2026-02-05 10:40:10 | WITHDRAWAL | ₹500.00  | Balance: ₹5500.00 | Cash withdrawal
4. 2026-02-05 10:45:30 | FD OPEN    | ₹10000.00| Balance: ₹5500.00 | FD opened for 12 months
========================================================
```

## 🏗️ Architecture

### Design Principles

1. **Separation of Concerns**: Clear layer separation
2. **Single Responsibility**: Each class has one purpose
3. **Dependency Inversion**: Abstractions over concretions
4. **Open/Closed Principle**: Open for extension, closed for modification

### Layers

```
┌─────────────────────┐
│  Presentation Layer │  (Console UI)
├─────────────────────┤
│  Business Logic     │  (BankManager, Account)
├─────────────────────┤
│  Data Layer         │  (Transaction, FixedDeposit)
├─────────────────────┤
│  Persistence Layer  │  (FileManager)
└─────────────────────┘
```

### Key Components

1. **BankManager** (Singleton)
   - Manages all accounts
   - Handles authentication
   - Controls account creation

2. **Account**
   - Individual account operations
   - Transaction management
   - Fixed deposit handling

3. **FileManager** (Repository Pattern)
   - Data persistence
   - File I/O operations
   - Serialization/deserialization

4. **Transaction**
   - Transaction records
   - History tracking
   - Type classification

5. **FixedDeposit**
   - FD calculations
   - Maturity computation
   - Interest management

## 🎨 Design Patterns

### 1. Singleton Pattern
**Used in**: BankManager class  
**Purpose**: Ensure single instance of bank manager  
**Benefits**: 
- Global access point
- Thread-safe implementation
- Controlled instantiation

### 2. Repository Pattern
**Used in**: FileManager class  
**Purpose**: Abstract data access layer  
**Benefits**:
- Separation of concerns
- Easy to test
- Swappable storage

### 3. Factory Pattern (Implicit)
**Used in**: Account creation via BankManager  
**Purpose**: Centralize object creation  
**Benefits**:
- Consistent initialization
- Easy to extend
- Encapsulated logic

## 📚 Documentation

- **[Architecture Document](docs/ARCHITECTURE.md)**: Comprehensive system architecture
  - UML diagrams
  - Class diagrams
  - Sequence diagrams
  - Component diagrams
  - Design decisions
  - Future enhancements

## 🔒 Security Notes

### Current Implementation
- Simple password hashing (demonstration purpose)
- File-based storage
- Basic input validation

### Production Recommendations
1. Use bcrypt/Argon2 for password hashing
2. Implement encryption for stored data
3. Add audit logging
4. Use database instead of file storage
5. Implement rate limiting
6. Add two-factor authentication

## 🐛 Known Limitations

1. **Single User**: Only one user session at a time
2. **File Storage**: Not suitable for concurrent access
3. **Password Security**: Simple hashing (demo only)
4. **No Backup**: Manual backup required
5. **Console Only**: No graphical interface

## 🚀 Future Enhancements

### Planned Features
- [ ] Multi-user concurrent sessions
- [ ] Database integration (SQLite/PostgreSQL)
- [ ] REST API support
- [ ] GUI interface (Qt/GTK)
- [ ] Transfer between accounts
- [ ] Loan management
- [ ] Recurring deposits
- [ ] Statement generation (PDF)
- [ ] Email notifications
- [ ] Multi-currency support

### Technical Improvements
- [ ] Enhanced encryption
- [ ] Audit logging
- [ ] Configuration file
- [ ] Docker containerization
- [ ] CI/CD pipeline
- [ ] Code coverage > 90%
- [ ] Performance optimization
- [ ] Memory profiling

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Coding Standards
- Follow C++11 standards
- Use meaningful variable names
- Add comments for complex logic
- Write unit tests for new features
- Update documentation

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👥 Authors

- **Development Team** - *Initial work*

## 🙏 Acknowledgments

- Google Test framework for testing support
- CMake community for build system
- C++ community for best practices
- Contributors and reviewers

## 📧 Contact

For questions, issues, or suggestions:
- Open an issue on GitHub
- Email: support@bankingsystem.example.com

---

**Made with ❤️ using modern C++11**
