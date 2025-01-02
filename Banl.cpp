#include "Bank.h"
#include <iostream>

Bank::Bank()
{
    if (!db.connect())
    {
        std::cerr << "Database connection failed." << std::endl;
        exit(1);
    }
}

ATM Bank::createATM()
{
    return ATM(db);
}
