/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#include "bank.h"
#include <string>
#include <fstream>

using namespace std;

Bank::Bank() {}

Bank::~Bank() {}


void Bank::processFromFile(const string & file_name) 
{
    ifstream in_file;
    in_file.open(file_name);

    // check if file exist
    if (!in_file.is_open()) 
    {
        cout << "Could not read file " << endl; 
    }

    string transactionInfor;

    //read until the end of "file"
    while (!in_file.eof()) 
    {
        
        //read each line
        getline(in_file, transactionInfor, '\n');
            
        //create new transaction
        Transaction * a_stransaction = new Transaction();

        a_stransaction->setData(transactionInfor);

        //put transaction in queue
        transactions_queue_.push(*a_stransaction);

        delete a_stransaction;
    }
    in_file.close();

    processTransaction();
}

void Bank::processTransaction() 
{

    // process all transaction until queue empty
    while(!transactions_queue_.empty())
    {
        transactions_queue_.front().process(accounts);
        transactions_queue_.pop();
    }
}


void Bank::display() 
{
    cout << "Processing Done. Final Balances" << endl;
    accounts.display();
}