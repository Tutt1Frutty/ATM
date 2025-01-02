#pragma once

#include <string>
#include <libpq-fe.h>

class Database
{
public:
    Database();
    ~Database();

    bool connect();
    bool authenticateCard(const std::string& card_number, const std::string& pin_code);
    double getBalance(const std::string& card_number);
    bool updateBalance(const std::string& card_number, double new_balance);
    bool logTransaction(const std::string& card_number, const std::string& transaction_type, double amount);
    bool transferFunds(const std::string& from_card, const std::string& to_card, double amount);
    bool cardExists(const std::string& card_number);
private:
    PGconn* conn;
};
