# 💳 Credit Card Management System — C++

A console-based credit card management system built in C++ demonstrating core Object-Oriented Programming concepts.

---

## 📌 Features

- Credit card type assigned automatically based on credit score
- Make payments and repay outstanding balance
- View full transaction history
- Change PIN with validation
- Input validation and exception handling throughout

---

## 🗂️ Card Types

| Card Type | Credit Limit | Reward Rate | Min. Credit Score |
|-----------|-------------|-------------|-------------------|
| Silver    | ₹20,000     | 1%          | Any               |
| Gold      | ₹50,000     | 2%          | > 675             |
| Platinum  | ₹1,00,000   | 5%          | > 800             |

---

## 🧠 OOP Concepts Used

| Concept | Implementation |
|---|---|
| **Abstraction** | `CreditCard` abstract base class with pure virtual functions |
| **Inheritance** | `SilverCard`, `GoldCard`, `PlatinumCard` extend `CreditCard` |
| **Polymorphism** | Base-class pointer (`CreditCard*`) resolves card type at runtime |
| **Encapsulation** | `protected` members shield internal data; public methods control access |
| **Exception Handling** | `try-catch` with `runtime_error` for invalid operations |

---

## ▶️ How to Run

```bash
# Compile
g++ CreditCardManagement.cpp -o creditcard

# Run
./creditcard
```

Or open in any C++ IDE (VS Code, Code::Blocks, Dev-C++).

---

## 📋 Menu Options

```
1. View card        → Shows card type, limit, balance, reward rate
2. Make payment     → Spend using the card
3. Repay bill       → Pay back outstanding amount
4. View transactions → Full history of payments and repayments
5. Change PIN       → Update 4-digit PIN securely
0. Exit
```

---

## 👤 Author

**Suhas**  
🐙 [GitHub](https://github.com/suhas12-debug)
