#pragma once

#include <string>
#include "Database.h"

class Account
{
public:
    Account(const std::string& card_number);

    double getBalance(Database& db);
    bool deposit(Database& db, double amount);
    bool withdraw(Database& db, double amount);
    bool transfer(Database& db, const std::string& to_card_number, double amount);

private:
    std::string card_number;
};

