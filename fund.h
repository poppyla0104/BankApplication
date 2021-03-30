/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#ifndef FUND_H
#define FUND_H
#include <iostream>
#include <vector>

class Transaction;

using namespace std;

class Fund
{
    friend ostream& operator<<(ostream& out_stream, const Fund &);
    
    public:
    Fund();
    ~Fund();

    // setter
    void setName(string);
    void setFund(int);
    //set if the linked fund for this fund is valid
    void setLink(bool);
    //set the linked fund for this fund
    void setLinkedFund(int);

    // getter
    string getName() const;
    int getBalance() const;
    //get the linked fund's index of this fund
    int getLinkedFund() const;
    int getHistoryCount() const;

    // use function
    //display fund's history
    void displayHistory() const;
    //add fund's transaction history
    bool addHistory(Transaction);
    //return if fund has linked fund
    bool hasLinked();
    void addMoney(int);
    void reduceMoney(int);

    private:
    string fund_name_;
    int fund_balance_;
    int linked_fund_;
    bool has_linked_;
    vector<Transaction> history_;
};
#endif