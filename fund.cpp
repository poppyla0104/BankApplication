/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 4: The Bank
*/

#include "fund.h"
#include "transaction.h"

Fund::Fund()
{
    fund_balance_ = 0;
    linked_fund_ = -1;
    has_linked_ = false;
}

Fund::~Fund(){}

void Fund::setName(string name)
{
    fund_name_ = name;
}

void Fund::setFund(int balance)
{
    fund_balance_ = balance;
}

//set if the linked fund for this fund is valid
void Fund::setLink(bool flag)
{
    has_linked_ = flag;
}

//set the linked fund for this fund
void Fund::setLinkedFund(int other)
{
    linked_fund_ = other;
}


string Fund::getName() const
{
    return fund_name_;
}

int Fund::getBalance() const
{
    return fund_balance_;
}

//get the linked fund's index of this fund
int Fund::getLinkedFund() const
{
    return linked_fund_;
}

//display fund's history
void Fund::displayHistory() const
{
    for(int i = 0; i < history_.size(); i++) {
        cout << "  " << history_.at(i) << endl;
    }
}

//add fund's transaction history
bool Fund::addHistory(Transaction transaction)
{
    history_.push_back(transaction);
    return true;
}

int Fund::getHistoryCount() const {
    return history_.size();
}

//return if fund has linked fund
bool Fund::hasLinked()
{
    return has_linked_;
}

void Fund::addMoney(int amount)
{
    fund_balance_ += amount;
}

void Fund::reduceMoney(int amount)
{
    fund_balance_ -= amount;
}