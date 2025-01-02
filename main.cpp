#include <iostream>
#include "Database.h"
#include "ATM.h"

void displayMenu(bool cardInserted)
{
    std::cout << "\nSelect an option:" << std::endl;
    if (!cardInserted)
    {
        std::cout << "1. Insert Card" << std::endl;
    }
    else
    {
        std::cout << "1. Eject Card" << std::endl;
        std::cout << "2. Check Balance" << std::endl;
        std::cout << "3. Deposit" << std::endl;
        std::cout << "4. Withdraw" << std::endl;
        std::cout << "5. Transfer" << std::endl;
    }
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

int main()
{
    Database db;
    if (!db.connect())
    {
        std::cerr << "Failed to connect to the database. Exiting." << std::endl;
        return 1;
    }

    ATM atm(db);
    std::string card_number, pin_code;
    bool cardInserted = false;

    while (true)
    {
        displayMenu(cardInserted);
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            if (!cardInserted)
            {  // Insert Card
                std::cout << "Enter card number: ";
                std::cin >> card_number;
                std::cout << "Enter PIN code: ";
                std::cin >> pin_code;

                cardInserted = atm.insertCard(card_number, pin_code);
                if (cardInserted)
                {
                    std::cout << "Card accepted." << std::endl;
                }
                else
                {
                    std::cout << "Failed to authenticate card.\n";
                }
            }
            else
            {  // Eject Card
                cardInserted = false;
                atm.ejectCard();
                std::cout << "Card ejected." << std::endl;
            }
        }
        else if (choice == 2 && cardInserted)
        {  // Check Balance
            atm.showBalance();
        }
        else if (choice == 3 && cardInserted)
        {  // Deposit
            double amount;
            std::cout << "Enter deposit amount: ";
            std::cin >> amount;
            if (atm.deposit(amount)) {
                std::cout << "Deposit successful." << std::endl;
            }
        }
        else if (choice == 4 && cardInserted)
        {  // Withdraw
            double amount;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> amount;
            if (atm.withdraw(amount))
            {
                std::cout << "Withdrawal successful." << std::endl;
            }
        }
        else if (choice == 5 && cardInserted)
        {  // Transfer
            std::string to_card_number;
            double amount;
            std::cout << "Enter recipient card number: ";
            std::cin >> to_card_number;
            std::cout << "Enter transfer amount: ";
            std::cin >> amount;
            if (atm.transfer(to_card_number, amount))
            {
                std::cout << "Transfer successful." << std::endl;
            }
        }
        else if (choice == 0)
        {  // Exit
            std::cout << "Exiting program." << std::endl;
            break;
        }
        else
        {
            if (!cardInserted && (choice >= 2 && choice <= 5))
            {
                std::cout << "Please insert a valid card first." << std::endl;
            }
            else
            {
                std::cout << "Invalid option. Please try again." << std::endl;
            }
        }
    }

    return 0;
}
