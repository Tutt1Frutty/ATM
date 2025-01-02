#include "ATM.h"
#include <iostream>

ATM::ATM(Database& db) : db(db), current_card(nullptr), current_account(nullptr) {}

bool ATM::insertCard(const std::string& card_number, const std::string& pin_code)
{
    if (!db.cardExists(card_number))
    {
        std::cerr << "Invalid card number" << std::endl;
        return false;
    }
    Card* card = new Card(card_number, pin_code);
    if (card->authenticate(db))
    {
        current_card = card;
        current_account = new Account(card_number);
        return true;
    }
    delete card;
    return false;
}

void ATM::showBalance()
{
    if (current_account)
    {
        std::cout << "Balance: " << current_account->getBalance(db) << std::endl;
    }
}

bool ATM::deposit(double amount)
{
    return current_account && current_account->deposit(db, amount);
}

bool ATM::withdraw(double amount)
{
    return current_account && current_account->withdraw(db, amount);
}

bool ATM::transfer(const std::string& to_card_number, double amount)
{
    return current_account && current_account->transfer(db, to_card_number, amount);
}

void ATM::ejectCard()
{
    delete current_card;
    delete current_account;
    current_card = nullptr;
    current_account = nullptr;
}
