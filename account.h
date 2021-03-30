/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 4: The Bank
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include <string>
#include "fund.h"

using namespace std;

class Account
{
    friend ostream& operator<<(ostream& out_stream, const Account & account);

    public:
    Account();
    Account(string, string, int);
    ~Account();

    // setter
    bool setData(const Transaction&);
    void setFunds();

    // getter
    int getID() const;
    string getFirstName() const;
    string getLastName() const;
    string getName() const;
    Fund getFund(const int & index) const;

    //add transaction history for each fund
    bool addHistory(Transaction, int);
    //display individual fund's history of transactions
    void displayFundHistory(const int & index) const;
    //display whole account's history of transactions
    void displayAccountHistory() const;
    //add money to specific fund
    bool addFund(int, int);
    //reduce money from specific fund
    bool reduceFund(Transaction*,int, int);

    // overload function
    bool operator<(const Account&) const;
    bool operator>(const Account&) const;
    bool operator==(const Account&) const;
    bool operator!=(const Account&) const;

    private:
    string first_name_;
    string last_name_;
    int id_;
    Fund funds_[10];
};
#endif