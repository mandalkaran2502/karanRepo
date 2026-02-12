# UML Diagrams and Visual Documentation

## Banking Management System - Visual Architecture Guide

---

## Table of Contents

1. [Class Diagrams](#class-diagrams)
2. [Sequence Diagrams](#sequence-diagrams)
3. [Use Case Diagrams](#use-case-diagrams)
4. [Component Diagrams](#component-diagrams)
5. [State Diagrams](#state-diagrams)
6. [Activity Diagrams](#activity-diagrams)
7. [Deployment Diagram](#deployment-diagram)

---

## Class Diagrams

### Main Class Diagram

```
┌──────────────────────────────────────────────────────────────────────┐
│                        <<Singleton>>                                 │
│                        BankManager                                   │
├──────────────────────────────────────────────────────────────────────┤
│ - instance: unique_ptr<BankManager> {static}                         │
│ - mutex_: mutex {static}                                             │
│ - accounts: map<int, shared_ptr<Account>>                            │
│ - nextAccountNumber: int                                             │
├──────────────────────────────────────────────────────────────────────┤
│ - BankManager()                                                      │
│ - BankManager(const BankManager&) = delete                           │
│ - operator=(const BankManager&) = delete                             │
├──────────────────────────────────────────────────────────────────────┤
│ + getInstance(): BankManager* {static}                               │
│ + createAccount(name: string, pass: string, bal: double): int        │
│ + login(accNum: int, pass: string): shared_ptr<Account>              │
│ + getAccount(accNum: int): shared_ptr<Account>                       │
│ + accountExists(accNum: int): bool                                   │
│ + saveToFile(filename: string): bool                                 │
│ + loadFromFile(filename: string): bool                               │
│ + resetInstance(): void {static}                                     │
└──────────────────────────────────────────────────────────────────────┘
                              │
                              │ 1
                              │ manages
                              │ *
                              ▼
┌──────────────────────────────────────────────────────────────────────┐
│                           Account                                    │
├──────────────────────────────────────────────────────────────────────┤
│ - accountNumber: int                                                 │
│ - accountHolderName: string                                          │
│ - passwordHash: string                                               │
│ - balance: double                                                    │
│ - transactionHistory: deque<Transaction>                             │
│ - fixedDeposits: vector<shared_ptr<FixedDeposit>>                    │
│ - MAX_TRANSACTION_HISTORY: size_t = 5 {const, static}                │
├──────────────────────────────────────────────────────────────────────┤
│ - hashPassword(password: string): string                             │
│ - addTransaction(type: Type, amount: double, desc: string): void     │
├──────────────────────────────────────────────────────────────────────┤
│ + Account(accNum: int, name: string, pass: string, balance: double) │
│ + getAccountNumber(): int                                            │
│ + getAccountHolderName(): string                                     │
│ + getBalance(): double                                               │
│ + verifyPassword(pass: string): bool                                 │
│ + deposit(amount: double): bool                                      │
│ + withdraw(amount: double): bool                                     │
│ + openFixedDeposit(amount: double, tenure: int): bool                │
│ + displayBalance(): void                                             │
│ + displayAccountDetails(): void                                      │
│ + displayTransactionHistory(): void                                  │
│ + displayFixedDeposits(): void                                       │
│ + serialize(): string                                                │
│ + deserialize(data: string): shared_ptr<Account> {static}            │
└──────────────────────────────────────────────────────────────────────┘
            │ 1                                 │ 1
            │ contains                          │ contains
            │ 0..5                              │ 0..*
            ▼                                   ▼
┌────────────────────────────────┐   ┌──────────────────────────────────┐
│        Transaction             │   │       FixedDeposit               │
├────────────────────────────────┤   ├──────────────────────────────────┤
│ <<enumeration>>                │   │ - principal: double              │
│ Type                           │   │ - tenure: int                    │
│   DEPOSIT                      │   │ - interestRate: double           │
│   WITHDRAWAL                   │   │ - openDate: time_point           │
│   FD_OPEN                      │   ├──────────────────────────────────┤
│   FD_MATURITY                  │   │ + FixedDeposit(amt: double,      │
│   TRANSFER                     │   │                months: int)       │
├────────────────────────────────┤   │ + calculateMaturityAmount():     │
│ - type: Type                   │   │   double                          │
│ - amount: double               │   │ + getTenure(): int                │
│ - balanceAfter: double         │   │ + getPrincipal(): double          │
│ - timestamp: time_point        │   │ + getInterestRate(): double       │
│ - description: string          │   │ + getMaturityDate(): string       │
├────────────────────────────────┤   │ + serialize(): string             │
│ + Transaction(type: Type,      │   │ + deserialize(data: string):      │
│   amt: double, bal: double,    │   │   FixedDeposit {static}           │
│   desc: string)                │   └──────────────────────────────────┘
│ + toString(): string           │
│ + serialize(): string          │
│ + deserialize(data: string):   │
│   Transaction {static}         │
└────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────┐
│                          FileManager                                 │
├──────────────────────────────────────────────────────────────────────┤
│ - dataDirectory: string                                              │
├──────────────────────────────────────────────────────────────────────┤
│ + FileManager(dataDir: string)                                       │
│ + ensureDataDirectory(): bool                                        │
│ + writeToFile(filename: string, data: string): bool                  │
│ + readFromFile(filename: string): string                             │
│ + fileExists(filename: string): bool                                 │
│ + getFilePath(filename: string): string                              │
│ + writeLinesToFile(filename: string, lines: vector<string>): bool    │
│ + readLinesFromFile(filename: string): vector<string>                │
│ + deleteFile(filename: string): bool                                 │
└──────────────────────────────────────────────────────────────────────┘
```

---

## Sequence Diagrams

### 1. Create Account Sequence

```
┌────┐    ┌────────┐    ┌──────────┐    ┌─────────┐    ┌───────────┐
│User│    │Console │    │BankMgr   │    │Account  │    │FileMgr    │
└──┬─┘    └───┬────┘    └────┬─────┘    └────┬────┘    └─────┬─────┘
   │           │              │               │               │
   │ Create    │              │               │               │
   │ Account   │              │               │               │
   ├──────────>│              │               │               │
   │           │              │               │               │
   │           │ createAccount()              │               │
   │           ├─────────────>│               │               │
   │           │              │               │               │
   │           │              │ Validate Input│               │
   │           │              ├──────────────>│               │
   │           │              │               │               │
   │           │              │new Account()  │               │
   │           │              ├──────────────>│               │
   │           │              │               │               │
   │           │              │ Hash Password │               │
   │           │              │<──────────────┤               │
   │           │              │               │               │
   │           │              │ Store Account │               │
   │           │              │<──────────────┤               │
   │           │              │               │               │
   │           │              │ saveToFile()  │               │
   │           │              ├──────────────────────────────>│
   │           │              │               │               │
   │           │              │               │ Serialize Data│
   │           │              │               │<──────────────┤
   │           │              │               │               │
   │           │              │               │ Write to File │
   │           │              │<──────────────────────────────┤
   │           │              │               │               │
   │           │ Return AccNum│               │               │
   │           │<─────────────┤               │               │
   │           │              │               │               │
   │  Display  │              │               │               │
   │  Success  │              │               │               │
   │<──────────┤              │               │               │
   │           │              │               │               │
```

### 2. Login and Deposit Sequence

```
┌────┐    ┌────────┐    ┌──────────┐    ┌─────────┐
│User│    │Console │    │BankMgr   │    │Account  │
└──┬─┘    └───┬────┘    └────┬─────┘    └────┬────┘
   │           │              │               │
   │  Login    │              │               │
   ├──────────>│              │               │
   │           │              │               │
   │           │ login()      │               │
   │           ├─────────────>│               │
   │           │              │               │
   │           │              │ Find Account  │
   │           │              ├──────────────>│
   │           │              │               │
   │           │              │verifyPassword()
   │           │              ├──────────────>│
   │           │              │               │
   │           │              │    true       │
   │           │              │<──────────────┤
   │           │              │               │
   │           │Return Account│               │
   │           │<─────────────┤               │
   │           │              │               │
   │  Welcome  │              │               │
   │<──────────┤              │               │
   │           │              │               │
   │  Deposit  │              │               │
   ├──────────>│              │               │
   │           │              │               │
   │           │              │ deposit()     │
   │           │              ├──────────────>│
   │           │              │               │
   │           │              │Validate Amount│
   │           │              │<──────────────┤
   │           │              │               │
   │           │              │Update Balance │
   │           │              │<──────────────┤
   │           │              │               │
   │           │              │Add Transaction│
   │           │              │<──────────────┤
   │           │              │               │
   │           │              │   Success     │
   │           │              │<──────────────┤
   │           │              │               │
   │  Display  │              │               │
   │  Success  │              │               │
   │<──────────┤              │               │
   │           │              │               │
```

### 3. Open Fixed Deposit Sequence

```
┌────┐    ┌─────────┐    ┌──────────┐    ┌──────────┐
│User│    │Account  │    │FixedDep  │    │Trans     │
└──┬─┘    └────┬────┘    └────┬─────┘    └────┬─────┘
   │           │              │               │
   │Open FD    │              │               │
   ├──────────>│              │               │
   │           │              │               │
   │           │Validate      │               │
   │           │Amount &      │               │
   │           │Tenure        │               │
   │           ├──────┐       │               │
   │           │      │       │               │
   │           │<─────┘       │               │
   │           │              │               │
   │           │Check Balance │               │
   │           ├──────┐       │               │
   │           │      │       │               │
   │           │<─────┘       │               │
   │           │              │               │
   │           │new FixedDeposit()            │
   │           ├─────────────>│               │
   │           │              │               │
   │           │              │Set Parameters │
   │           │              ├─────┐         │
   │           │              │     │         │
   │           │              │<────┘         │
   │           │              │               │
   │           │              │Calculate      │
   │           │              │Interest       │
   │           │              ├─────┐         │
   │           │              │     │         │
   │           │              │<────┘         │
   │           │              │               │
   │           │ FD Object    │               │
   │           │<─────────────┤               │
   │           │              │               │
   │           │Deduct Balance│               │
   │           ├──────┐       │               │
   │           │      │       │               │
   │           │<─────┘       │               │
   │           │              │               │
   │           │Add Transaction               │
   │           ├─────────────────────────────>│
   │           │              │               │
   │           │              │Create Trans   │
   │           │              │Record         │
   │           │              │<──────────────┤
   │           │              │               │
   │  Display  │              │               │
   │  FD       │              │               │
   │  Details  │              │               │
   │<──────────┤              │               │
   │           │              │               │
```

---

## Use Case Diagrams

### Banking System Use Cases

```
                    Banking Management System
    ┌──────────────────────────────────────────────────┐
    │                                                  │
    │   ┌─────────────────┐      ┌────────────────┐   │
    │   │ Create Account  │      │ Login          │   │
    │   └────────┬────────┘      └───────┬────────┘   │
    │            │                        │            │
    │            │        ┌───────────────┤            │
    │            │        │               │            │
    │            │        │  ┌────────────▼────────┐   │
    │            │        │  │ View Balance        │   │
    │            │        │  └─────────────────────┘   │
    │            │        │                            │
┌───┴────┐       │        │  ┌─────────────────────┐   │
│        │       │        │  │ Deposit Money       │   │
│  User  ├───────┘        │  └─────────────────────┘   │
│        │                │                            │
└───┬────┘                │  ┌─────────────────────┐   │
    │                     │  │ Withdraw Money      │   │
    │                     │  └─────────────────────┘   │
    │                     │                            │
    │                     │  ┌─────────────────────┐   │
    │                     │  │ View Transactions   │   │
    │                     │  └─────────────────────┘   │
    │                     │                            │
    │                     │  ┌─────────────────────┐   │
    │                     │  │ Open Fixed Deposit  │   │
    │                     │  └──────────┬──────────┘   │
    │                     │             │              │
    │                     │             │              │
    │                     │  ┌──────────▼──────────┐   │
    │                     └─>│ View Fixed Deposits │   │
    │                        └─────────────────────┘   │
    │                                                  │
    │   ┌─────────────────┐                            │
    │   │ View Account    │                            │
    │   │ Details         │                            │
    │   └─────────────────┘                            │
    │                                                  │
    └──────────────────────────────────────────────────┘
```

### Actor Relationships

```
┌─────────────┐
│   User      │────┐
└─────────────┘    │
                   │ authenticates as
                   │
                   ▼
         ┌──────────────────┐
         │ Account Holder   │
         └────────┬─────────┘
                  │
                  │ performs
                  │
      ┌───────────┼───────────┐
      │           │           │
      ▼           ▼           ▼
┌──────────┐ ┌──────────┐ ┌──────────┐
│ Banking  │ │ FD       │ │ Account  │
│ Txn      │ │ Mgmt     │ │ Mgmt     │
└──────────┘ └──────────┘ └──────────┘
```

---

## Component Diagrams

### System Component View

```
┌────────────────────────────────────────────────────────────┐
│                  Presentation Layer                        │
│                                                            │
│  ┌──────────────────────────────────────────────────┐     │
│  │          Console User Interface                  │     │
│  │  - Main Menu                                     │     │
│  │  - Account Menu                                  │     │
│  │  - Input/Output Handling                         │     │
│  └──────────────────────────────────────────────────┘     │
└───────────────────────┬────────────────────────────────────┘
                        │
                        │ uses
                        ▼
┌────────────────────────────────────────────────────────────┐
│                  Business Logic Layer                      │
│                                                            │
│  ┌─────────────────────┐         ┌──────────────────────┐ │
│  │   BankManager       │◄────────┤   Account            │ │
│  │   (Singleton)       │         │                      │ │
│  │  - Account Mgmt     │  manages│  - Transactions      │ │
│  │  - Authentication   │         │  - FD Operations     │ │
│  │  - Session Control  │         │  - Balance Mgmt      │ │
│  └──────────┬──────────┘         └──────────┬───────────┘ │
└─────────────┼────────────────────────────────┼─────────────┘
              │                                │
              │ uses                           │ uses
              ▼                                ▼
┌──────────────────────────┐      ┌──────────────────────────┐
│  Persistence Layer       │      │    Data Layer            │
│                          │      │                          │
│  ┌────────────────────┐  │      │  ┌────────────────────┐ │
│  │   FileManager      │  │      │  │   Transaction      │ │
│  │  - File I/O        │  │      │  └────────────────────┘ │
│  │  - Serialization   │  │      │                          │
│  │  - Directory Mgmt  │  │      │  ┌────────────────────┐ │
│  └────────────────────┘  │      │  │   FixedDeposit     │ │
└──────────────────────────┘      │  └────────────────────┘ │
                                  └──────────────────────────┘
              │                                │
              │ stores/retrieves               │ serialized to
              ▼                                ▼
┌────────────────────────────────────────────────────────────┐
│                   File System                              │
│                                                            │
│               data/accounts.dat                            │
└────────────────────────────────────────────────────────────┘
```

---

## State Diagrams

### Account State Diagram

```
          ┌──────────┐
          │  Start   │
          └────┬─────┘
               │
               │ create
               ▼
       ┌───────────────┐
       │  Initialized  │◄────────┐
       └───────┬───────┘         │
               │                 │ logout
               │ login           │
               ▼                 │
       ┌───────────────┐         │
    ┌──┤    Active     │─────────┘
    │  └───────┬───────┘
    │          │
    │          │ transaction
    │          ▼
    │  ┌───────────────┐
    │  │ Processing    │
    │  │ Transaction   │
    │  └───────┬───────┘
    │          │
    │          │ complete
    │          ▼
    └──────────┤
               │
               │ close account
               ▼
       ┌───────────────┐
       │    Closed     │
       └───────────────┘
```

### Fixed Deposit State Diagram

```
    ┌──────────┐
    │  Start   │
    └────┬─────┘
         │
         │ create
         ▼
 ┌──────────────┐
 │   Pending    │
 └──────┬───────┘
        │
        │ validate & deduct
        ▼
 ┌──────────────┐       ┌──────────────┐
 │    Active    │──────>│  Calculate   │
 │              │       │  Interest    │
 └──────┬───────┘       └──────────────┘
        │
        │ reach maturity date
        ▼
 ┌──────────────┐
 │   Matured    │
 └──────┬───────┘
        │
        │ credit amount
        ▼
 ┌──────────────┐
 │   Closed     │
 └──────────────┘
```

---

## Activity Diagrams

### Deposit Money Activity

```
        ┌───────────┐
        │   Start   │
        └─────┬─────┘
              │
              ▼
      ┌───────────────┐
      │ Get Amount    │
      │ from User     │
      └───────┬───────┘
              │
              ▼
      ┌───────────────┐      No    ┌───────────────┐
      │ Amount > 0?   ├────────────>│ Show Error    │
      └───────┬───────┘             └───────┬───────┘
              │ Yes                         │
              ▼                             │
      ┌───────────────┐                     │
      │ Add to Balance│                     │
      └───────┬───────┘                     │
              │                             │
              ▼                             │
      ┌───────────────┐                     │
      │ Create        │                     │
      │ Transaction   │                     │
      │ Record        │                     │
      └───────┬───────┘                     │
              │                             │
              ▼                             │
      ┌───────────────┐                     │
      │ Add to History│                     │
      │ (Keep Last 5) │                     │
      └───────┬───────┘                     │
              │                             │
              ▼                             │
      ┌───────────────┐                     │
      │ Save to File  │                     │
      └───────┬───────┘                     │
              │                             │
              ▼                             │
      ┌───────────────┐                     │
      │ Show Success  │◄────────────────────┘
      └───────┬───────┘
              │
              ▼
        ┌───────────┐
        │    End    │
        └───────────┘
```

### Open Fixed Deposit Activity

```
         ┌───────────┐
         │   Start   │
         └─────┬─────┘
               │
               ▼
       ┌───────────────┐
       │ Get Amount &  │
       │ Tenure        │
       └───────┬───────┘
               │
               ▼
       ┌───────────────┐
       │ Valid Tenure? │──No──┐
       │ (12 or 24)    │      │
       └───────┬───────┘      │
               │ Yes          │
               ▼              │
       ┌───────────────┐      │
       │ Amount > 0?   │──No──┤
       └───────┬───────┘      │
               │ Yes          │
               ▼              │
       ┌───────────────┐      │
       │ Balance >=    │──No──┤
       │ Amount?       │      │
       └───────┬───────┘      │
               │ Yes          │
               ▼              │
       ┌───────────────┐      │
       │ Create FD     │      │
       │ Object        │      │
       └───────┬───────┘      │
               │              │
               ▼              │
       ┌───────────────┐      │
       │ Calculate     │      │
       │ Interest &    │      │
       │ Maturity      │      │
       └───────┬───────┘      │
               │              │
               ▼              │
       ┌───────────────┐      │
       │ Deduct from   │      │
       │ Balance       │      │
       └───────┬───────┘      │
               │              │
               ▼              │
       ┌───────────────┐      │
       │ Create        │      │
       │ Transaction   │      │
       └───────┬───────┘      │
               │              │
               ▼              │
       ┌───────────────┐      │
       │ Save to File  │      │
       └───────┬───────┘      │
               │              │
               ▼              │
       ┌───────────────┐      │
       │ Show FD       │      │
       │ Details       │      │
       └───────┬───────┘      │
               │              │
               ▼              ▼
               │      ┌───────────────┐
               │      │ Show Error    │
               │      └───────┬───────┘
               │              │
               ▼              ▼
         ┌───────────┐
         │    End    │
         └───────────┘
```

---

## Deployment Diagram

### Single Machine Deployment

```
┌───────────────────────────────────────────────────────────┐
│                  User's Computer                          │
│                                                           │
│  ┌─────────────────────────────────────────────────┐     │
│  │            Operating System                     │     │
│  │         (Linux / macOS / Windows)               │     │
│  │                                                 │     │
│  │  ┌───────────────────────────────────────┐     │     │
│  │  │      BankingSystem Process            │     │     │
│  │  │                                       │     │     │
│  │  │  ┌─────────────────────────────┐     │     │     │
│  │  │  │  Console UI Thread          │     │     │     │
│  │  │  └─────────────────────────────┘     │     │     │
│  │  │                                       │     │     │
│  │  │  ┌─────────────────────────────┐     │     │     │
│  │  │  │  BankManager (Singleton)    │     │     │     │
│  │  │  │  - Thread-safe              │     │     │     │
│  │  │  └─────────────────────────────┘     │     │     │
│  │  │                                       │     │     │
│  │  │  ┌─────────────────────────────┐     │     │     │
│  │  │  │  Account Objects            │     │     │     │
│  │  │  └─────────────────────────────┘     │     │     │
│  │  │                                       │     │     │
│  │  │  ┌─────────────────────────────┐     │     │     │
│  │  │  │  FileManager                │     │     │     │
│  │  │  └─────────────────────────────┘     │     │     │
│  │  │                │                     │     │     │
│  │  └────────────────┼─────────────────────┘     │     │
│  │                   │                           │     │
│  └───────────────────┼───────────────────────────┘     │
│                      │                                 │
│                      │ File I/O                        │
│                      ▼                                 │
│  ┌───────────────────────────────────────────────┐    │
│  │            File System                        │    │
│  │                                               │    │
│  │  ┌─────────────────────────────────┐         │    │
│  │  │   data/                         │         │    │
│  │  │     └── accounts.dat            │         │    │
│  │  └─────────────────────────────────┘         │    │
│  └───────────────────────────────────────────────┘    │
│                                                       │
└───────────────────────────────────────────────────────┘
```

---

## Design Pattern Relationships

```
┌────────────────────────────────────────────────────────────────┐
│                    Design Patterns Used                        │
└────────────────────────────────────────────────────────────────┘

    ┌─────────────────────┐
    │  Singleton Pattern  │
    │   (BankManager)     │
    └──────────┬──────────┘
               │
               │ ensures single instance
               │
               ▼
    ┌─────────────────────┐
    │   Factory Pattern   │
    │  (Account Creation) │
    └──────────┬──────────┘
               │
               │ creates
               │
               ▼
    ┌─────────────────────┐
    │  Repository Pattern │
    │   (FileManager)     │
    └──────────┬──────────┘
               │
               │ persists
               │
               ▼
    ┌─────────────────────┐
    │   Domain Objects    │
    │ (Account, FD, Txn)  │
    └─────────────────────┘
```

---

## Threading Model

```
┌──────────────────────────────────────────────┐
│           Main Thread                        │
│                                              │
│  ┌────────────────────────────────────┐     │
│  │  Console UI Loop                   │     │
│  │  - Read user input                 │     │
│  │  - Display menus                   │     │
│  │  - Show results                    │     │
│  └────────────┬───────────────────────┘     │
│               │                              │
│               │ calls                        │
│               ▼                              │
│  ┌────────────────────────────────────┐     │
│  │  BankManager                       │     │
│  │  - Mutex protected                 │     │
│  │  - Thread-safe getInstance()       │     │
│  └────────────┬───────────────────────┘     │
│               │                              │
│               │ operates on                  │
│               ▼                              │
│  ┌────────────────────────────────────┐     │
│  │  Account Objects                   │     │
│  │  - No direct thread access         │     │
│  │  - Accessed via BankManager        │     │
│  └────────────┬───────────────────────┘     │
│               │                              │
│               │ persists via                 │
│               ▼                              │
│  ┌────────────────────────────────────┐     │
│  │  FileManager                       │     │
│  │  - Synchronous I/O                 │     │
│  └────────────────────────────────────┘     │
│                                              │
└──────────────────────────────────────────────┘

Note: Current implementation is single-threaded.
Mutex in BankManager prepares for future multi-threading.
```

---

This visual documentation provides comprehensive UML diagrams and architectural views of the Banking Management System, making it easier to understand the system structure, component interactions, and data flow.
