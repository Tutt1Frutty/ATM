#pragma once

#include "ATM.h"
#include "Database.h"

class Bank
{
public:
    Bank();

    ATM createATM();

private:
    Database db;
};

