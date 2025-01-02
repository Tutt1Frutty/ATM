#pragma once

#include <string>
#include "Database.h"

class Transaction
{
public:
    Transaction(const std::string& card_number, const std::string& transaction_type, double amount);

    bool log(Database& db);

private:
    std::string card_number;
    std::string transaction_type; // "deposit", "withdrawal", "transfer"
    double amount;
};


