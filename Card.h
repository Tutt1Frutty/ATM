#pragma once

#include <string>
#include "Database.h"

class Card
{
public:
    Card(const std::string& card_number, const std::string& pin_code);

    bool authenticate(Database& db);
    std::string getCardNumber() const;

private:
    std::string card_number;
    std::string pin_code;
};

