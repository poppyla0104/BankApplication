/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <fstream>
#include <queue>
#include "transaction.h"
#include "bst.h"

using namespace std;

class Bank
{
    public:
    
    Bank();
    ~Bank();

    // read data from file and then process all transaction
    void processFromFile(const string & file_name);

    // display all report of all accounts
    void display();

    private:  
    queue<Transaction> transactions_queue_; 
    BST accounts;                           
    void processTransaction();   
};
#endif