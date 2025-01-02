#include "Card.h"

Card::Card(const std::string& card_number, const std::string& pin_code)
    : card_number(card_number), pin_code(pin_code) {}

bool Card::authenticate(Database& db)
{
    return db.authenticateCard(card_number, pin_code);
}

std::string Card::getCardNumber() const
{
    return card_number;
}
