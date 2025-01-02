#include "Account.h"
#include <iostream>

Account::Account(const std::string& card_number) : card_number(card_number) {}

double Account::getBalance(Database& db)
{
    return db.getBalance(card_number);
}

bool Account::deposit(Database& db, double amount)
{
    if (amount <= 0)
    {
        std::cerr << "Invalid amount" << std::endl;
        return false;
    }
    double new_balance = getBalance(db) + amount;
    bool success = db.updateBalance(card_number, new_balance);
    if (success)
    {
        db.logTransaction(card_number, "deposit", amount);
    }
    return success;
}

bool Account::withdraw(Database& db, double amount)
{
    if (amount <= 0)
    {
        std::cerr << "Invalid amount" << std::endl;
        return false;
    }
    double current_balance = getBalance(db);
    if (current_balance < amount)
    {
        std::cerr << "Insufficient funds" << std::endl;
        return false;
    }

    double new_balance = current_balance - amount;
    bool success = db.updateBalance(card_number, new_balance);
    if (success)
    {
        db.logTransaction(card_number, "withdrawal", amount);
    }
    return success;
}

bool Account::transfer(Database& db, const std::string& to_card_number, double amount)
{
    if (amount <= 0)
    {
        std::cerr << "Invalid amount" << std::endl;
        return false;
    }
    return db.transferFunds(card_number, to_card_number, amount);
}
