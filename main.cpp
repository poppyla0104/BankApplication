/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#include <iostream>
#include "bank.h"

int main()
{
    //open my bank
    Bank myBank;

    //process transactions from file
    myBank.processFromFile("BankTransIn.txt");

    //print all accounts
    myBank.display();

    return 0;
}