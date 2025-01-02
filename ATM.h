#pragma once

#include "Card.h"
#include "Account.h"
#include "Database.h"

class ATM
{
public:
    ATM(Database& db);

    bool insertCard(const std::string& card_number, const std::string& pin_code);
    void showBalance();
    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(const std::string& to_card_number, double amount);
    void ejectCard();

private:
    Database& db;
    Card* current_card;
    Account* current_account;
};

