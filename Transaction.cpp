#include "Transaction.h"

Transaction::Transaction(const std::string& card_number, const std::string& transaction_type, double amount)
    : card_number(card_number), transaction_type(transaction_type), amount(amount) {}

bool Transaction::log(Database& db)
{
    return db.logTransaction(card_number, transaction_type, amount);
}
