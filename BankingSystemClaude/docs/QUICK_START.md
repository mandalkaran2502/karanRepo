# Quick Start Guide - Banking Management System

## Prerequisites

Before you begin, ensure you have the following installed:
- **g++** or **clang** compiler with C++11 support
- **make** (optional, for CMake builds)
- **CMake 3.14+** (optional, recommended)

## Quick Start (5 Minutes)

### Option 1: Manual Build (Recommended when CMake unavailable)

```bash
# 1. Navigate to project directory
cd BankingSystem

# 2. Build using the provided script
chmod +x build.sh
./build.sh

# 3. Run the application
./build_manual/bin/BankingSystem
```

### Option 2: CMake Build (Recommended for development)

```bash
# 1. Create build directory
mkdir build && cd build

# 2. Configure with CMake
cmake ..

# 3. Build
cmake --build .

# 4. Run
./bin/BankingSystem
```

## First Time Usage

### Step 1: Create Your First Account

```
Main Menu:
1. Create New Account
2. Login to Existing Account
3. Exit

Your choice: 1

Enter account holder name: Alice Johnson
Enter password (min 4 characters): secure123
Enter initial deposit amount: ₹10000

✅ Account created successfully!
Account Number: 1001  ← SAVE THIS NUMBER!
```

### Step 2: Login

```
Main Menu:
Your choice: 2

Enter account number: 1001
Enter password: secure123

✅ Login successful!
Welcome, Alice Johnson!
```

### Step 3: Perform Operations

#### Deposit Money
```
Account Menu:
Your choice: 1

Enter deposit amount: ₹5000

✅ Successfully deposited ₹5000.00
Current balance: ₹15000.00
```

#### Check Balance
```
Account Menu:
Your choice: 3

💰 BALANCE ENQUIRY
Account Number: 1001
Account Holder: Alice Johnson
Current Balance: ₹15000.00
```

#### Open Fixed Deposit
```
Account Menu:
Your choice: 6

Interest Rates:
  12 months - 6.5% p.a.
  24 months - 7.5% p.a.

Enter FD amount: ₹10000
Enter tenure (12 or 24 months): 12

✅ Fixed Deposit opened successfully!
FD Amount         : ₹10000.00
Tenure            : 12 months
Interest Rate     : 6.5%
Maturity Amount   : ₹10650.00
Maturity Date     : 2027-02-05
```

## Sample Test Scenarios

### Scenario 1: Complete Banking Day

```bash
# Create account
1 → Create Account
Name: Bob Smith
Password: bobpass
Initial: 20000

# Perform transactions
2 → Login (Account: 1001, Password: bobpass)
1 → Deposit ₹5000
2 → Withdraw ₹3000
6 → Open FD (₹10000, 24 months)
3 → Check Balance
5 → View Transaction History
8 → Logout
```

### Scenario 2: Multiple Accounts

```bash
# Account 1
Create: John Doe, pass1234, ₹50000
Login: 1001
Deposit: ₹10000
Open FD: ₹20000, 12 months
Logout

# Account 2
Create: Jane Smith, pass5678, ₹30000
Login: 1002
Withdraw: ₹5000
Open FD: ₹15000, 24 months
Logout
```

## Running Tests

### Manual Test Build (If CMake not available)

```bash
# Build tests manually
cd tests
g++ -std=c++11 -I../include -I/path/to/gtest/include \
    test_account.cpp ../src/*.cpp \
    -L/path/to/gtest/lib -lgtest -lgtest_main -pthread \
    -o test_suite

./test_suite
```

### CMake Test Build

```bash
cd build
cmake ..
make
ctest --output-on-failure
```

## Data Persistence

### Where is my data stored?

```
BankingSystem/
└── data/
    └── accounts.dat    ← All your account data is here
```

### Backing Up Your Data

```bash
# Create backup
cp data/accounts.dat data/accounts_backup_$(date +%Y%m%d).dat

# Restore from backup
cp data/accounts_backup_20260205.dat data/accounts.dat
```

### Resetting the System

```bash
# Delete all data (fresh start)
rm -f data/accounts.dat

# Or delete entire data directory
rm -rf data/
```

## Common Issues and Solutions

### Issue 1: "Permission denied" when running

```bash
# Solution: Make the file executable
chmod +x build_manual/bin/BankingSystem
```

### Issue 2: "data directory not found"

```bash
# Solution: Create data directory
mkdir -p data
```

### Issue 3: Build fails with "C++11 not supported"

```bash
# Solution: Update compiler or specify C++11
g++ -std=c++11 ...
# Or
export CXXFLAGS="-std=c++11"
```

### Issue 4: "Account not found" after restart

```bash
# Check if data file exists
ls -la data/accounts.dat

# If missing, accounts were not saved
# Always logout properly or use Exit option from main menu
```

## Performance Tips

1. **Regular Backups**: Backup `accounts.dat` weekly
2. **Cleanup**: Remove old backup files periodically
3. **File Size**: If data file grows >10MB, consider archiving old data
4. **Permissions**: Set data directory permissions to 700 for security

```bash
chmod 700 data/
```

## Security Best Practices

### For Development/Testing

1. Use strong passwords (even in development)
2. Don't commit data files to version control
3. Add `data/` to `.gitignore`

### For Production (Future)

1. Implement proper encryption
2. Use secure password hashing (bcrypt/Argon2)
3. Enable audit logging
4. Use database instead of file storage
5. Implement backup automation

## Advanced Usage

### Running in Background

```bash
# Linux/Mac
nohup ./build_manual/bin/BankingSystem &

# Check running processes
ps aux | grep BankingSystem
```

### Automation Script

```bash
#!/bin/bash
# auto_backup.sh - Automated daily backup

DATE=$(date +%Y%m%d)
SOURCE="data/accounts.dat"
DEST="backups/accounts_$DATE.dat"

mkdir -p backups
cp $SOURCE $DEST
echo "Backup created: $DEST"

# Keep only last 7 backups
cd backups && ls -t | tail -n +8 | xargs rm -f
```

## Getting Help

### Within Application

- All menus show available options
- Invalid inputs show error messages
- Use `8` in Account Menu to logout safely

### Command Line Help

```bash
# View README
cat README.md

# View Architecture
cat docs/ARCHITECTURE.md

# Check build status
./build.sh
```

### Debugging

```bash
# Build with debug symbols
g++ -g -std=c++11 -DDEBUG ...

# Run with gdb
gdb ./build_manual/bin/BankingSystem
```

## What's Next?

After getting comfortable with basic operations:

1. **Read the Architecture Document**: `docs/ARCHITECTURE.md`
2. **Explore the Source Code**: Start with `src/main.cpp`
3. **Run Unit Tests**: Ensure everything works
4. **Customize**: Add new features or modify existing ones
5. **Contribute**: See `README.md` for contribution guidelines

## Quick Reference Card

```
╔══════════════════════════════════════════════╗
║         BANKING SYSTEM QUICK REFERENCE       ║
╠══════════════════════════════════════════════╣
║ BUILD:    ./build.sh                         ║
║ RUN:      ./build_manual/bin/BankingSystem   ║
║ DATA:     ./data/accounts.dat                ║
║ BACKUP:   cp data/accounts.dat backup.dat    ║
╠══════════════════════════════════════════════╣
║ MAIN MENU:                                   ║
║   1 - Create Account                         ║
║   2 - Login                                  ║
║   3 - Exit                                   ║
╠══════════════════════════════════════════════╣
║ ACCOUNT MENU:                                ║
║   1 - Deposit    2 - Withdraw                ║
║   3 - Balance    4 - Details                 ║
║   5 - History    6 - Open FD                 ║
║   7 - View FDs   8 - Logout                  ║
╠══════════════════════════════════════════════╣
║ FD RATES:                                    ║
║   12 months: 6.5% p.a.                       ║
║   24 months: 7.5% p.a.                       ║
╚══════════════════════════════════════════════╝
```

---

**Happy Banking! 🏦**
