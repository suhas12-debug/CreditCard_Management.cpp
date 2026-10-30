#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ── BASE CLASS ───────────────────────────────────────────────
// Blueprint for all card types. Holds common data and functions.
class CreditCard {
protected:
    int pin;
    double limit;
    double balance;
    vector<string> transactions;

public:
    CreditCard(int p, double l) {
        pin     = p;
        limit   = l;
        balance = 0;
    }

    virtual ~CreditCard() = default;

    // Must be defined by every child class
    virtual string cardType() const = 0;
    virtual double rewardRate() const = 0;

    // Make a purchase using the card
    void pay(double amount) {
        if (amount <= 0 || balance + amount > limit)
            throw runtime_error("Invalid amount or credit limit exceeded");

        balance += amount;
        transactions.push_back("Payment: " + to_string(amount));
        cout << "Payment successful!\n";
    }

    // Pay back the outstanding balance
    void repay(double amount) {
        if (amount <= 0 || amount > balance)
            throw runtime_error("Invalid repayment amount");

        balance -= amount;
        transactions.push_back("Repayment: " + to_string(amount));
        cout << "Repayment successful!\n";
    }

    // Display card summary
    void showDetails() const {
        cout << "\nCard: "               << cardType()         << "\n"
             << "Limit: "               << limit              << "\n"
             << "Outstanding balance: " << balance            << "\n"
             << "Reward rate: "         << rewardRate() * 100 << "%\n";
    }

    // Print all past transactions
    void showTransactions() const {
        cout << "\nTransaction history:\n";
        for (const string& t : transactions)
            cout << "- " << t << "\n";
        if (transactions.empty())
            cout << "No transactions yet.\n";
    }

    // Verify old PIN then set new one
    void changePIN(int oldPIN, int newPIN) {
        if (oldPIN != pin)
            throw runtime_error("Incorrect current PIN");
        if (newPIN < 1000 || newPIN > 9999)
            throw runtime_error("PIN must contain 4 digits");
        pin = newPIN;
        cout << "PIN changed successfully!\n";
    }
};

// ── CARD TYPES ───────────────────────────────────────────────
// Each card type sets its own limit and reward rate

class SilverCard : public CreditCard {
public:
    SilverCard(int pin) : CreditCard(pin, 20000) {}
    string cardType() const override { return "Silver"; }
    double rewardRate() const override { return 0.01; }
};

class GoldCard : public CreditCard {
public:
    GoldCard(int pin) : CreditCard(pin, 50000) {}
    string cardType() const override { return "Gold"; }
    double rewardRate() const override { return 0.02; }
};

class PlatinumCard : public CreditCard {
public:
    PlatinumCard(int pin) : CreditCard(pin, 100000) {}
    string cardType() const override { return "Platinum"; }
    double rewardRate() const override { return 0.05; }
};

// ── CARDHOLDER ───────────────────────────────────────────────
class CardHolder {
    string name;
public:
    CardHolder(string n) { name = n; }
    void showName() const { cout << "\nWelcome, " << name << "!\n"; }
};

// ── MAIN ─────────────────────────────────────────────────────
int main() {
    string name;
    int score, pin, choice;

    cout << "Enter cardholder name: ";
    getline(cin, name);
    CardHolder user(name);

    cout << "Enter credit score: ";
    cin >> score;
    cout << "Set a 4-digit PIN: ";
    cin >> pin;

    // Validate PIN
    if (pin < 1000 || pin > 9999) {
        cout << "Invalid PIN.\n";
        return 0;
    }

    // Create all card objects
    SilverCard   silver(pin);
    GoldCard     gold(pin);
    PlatinumCard platinum(pin);

    // Assign card based on credit score
    CreditCard* card;
    if (score > 800)      card = &platinum;
    else if (score > 675) card = &gold;
    else                  card = &silver;

    user.showName();
    cout << "Your " << card->cardType() << " card is ready!\n";

    // Menu loop
    while (true) {
        cout << "\n1. View card\n2. Make payment\n3. Repay bill"
             << "\n4. View transactions\n5. Change PIN\n0. Exit\nChoice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                card->showDetails();
            } else if (choice == 2) {
                double amount;
                cout << "Enter payment amount: ";
                cin >> amount;
                card->pay(amount);
            } else if (choice == 3) {
                double amount;
                cout << "Enter repayment amount: ";
                cin >> amount;
                card->repay(amount);
            } else if (choice == 4) {
                card->showTransactions();
            } else if (choice == 5) {
                int oldPIN, newPIN;
                cout << "Enter current and new PIN: ";
                cin >> oldPIN >> newPIN;
                card->changePIN(oldPIN, newPIN);
            } else if (choice == 0) {
                cout << "Thank you!\n";
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
