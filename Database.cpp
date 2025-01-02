#include "Database.h"
#include <iostream>

Database::Database() : conn(nullptr) {}

Database::~Database()
{
    if (conn)
    {
        PQfinish(conn);
    }
}

bool Database::connect()
{
    conn = PQconnectdb("dbname=postgres user=postgres password=123456 hostaddr=127.0.0.1 port=8888");
    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cerr << "Connection error: " << PQerrorMessage(conn) << std::endl;
        return false;
    }
    return true;
}

bool Database::authenticateCard(const std::string& card_number, const std::string& pin_code)
{
    std::string query = "SELECT pin_code FROM bank_cards WHERE card_number = '" + card_number + "'";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return false;
    }

    bool authenticated = (pin_code == PQgetvalue(res, 0, 0));
    PQclear(res);
    return authenticated;
}

double Database::getBalance(const std::string& card_number)
{
    std::string query = "SELECT account_balance FROM bank_cards WHERE card_number = '" + card_number + "'";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return -1;
    }

    double balance = std::stod(PQgetvalue(res, 0, 0));
    PQclear(res);
    return balance;
}

bool Database::updateBalance(const std::string& card_number, double new_balance)
{
    std::string query = "UPDATE bank_cards SET account_balance = " + std::to_string(new_balance) + " WHERE card_number = '" + card_number + "'";
    PGresult* res = PQexec(conn, query.c_str());

    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return success;
}

bool Database::logTransaction(const std::string& card_number, const std::string& transaction_type, double amount)
{
    std::string query = "INSERT INTO transactions (card_number, transaction_type, amount) VALUES ('" + card_number + "', '" + transaction_type + "', " + std::to_string(amount) + ")";
    PGresult* res = PQexec(conn, query.c_str());

    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return success;
}

bool Database::transferFunds(const std::string& from_card, const std::string& to_card, double amount)
{
    double from_balance = getBalance(from_card);
    double to_balance = getBalance(to_card);

    if (from_balance < amount) return false;

    updateBalance(from_card, from_balance - amount);
    updateBalance(to_card, to_balance + amount);
    logTransaction(from_card, "transfer_out", amount);
    logTransaction(to_card, "transfer_in", amount);

    return true;
}

bool Database::cardExists(const std::string& card_number)
{
    std::string query = "SELECT 1 FROM bank_cards WHERE card_number = '" + card_number + "' LIMIT 1";
    PGresult* res = PQexec(conn, query.c_str());

    bool exists = (PQresultStatus(res) == PGRES_TUPLES_OK) && (PQntuples(res) > 0);
    PQclear(res);
    return exists;
}
