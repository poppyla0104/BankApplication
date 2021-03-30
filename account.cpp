/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#include "account.h"
#include "transaction.h"


Account::Account()
{
    first_name_ = Default_Value::String;
    last_name_ = Default_Value::String;
    id_ = Default_Value::Number;
    setFunds();
}

Account::Account(string firstName, string lastName, int id)
{
    first_name_ = firstName;
    last_name_ = lastName;
    id_ = id;
    setFunds();
}

Account::~Account(){}


bool Account::setData(const Transaction &transaction)
{
    first_name_ = transaction.getFirst();
    last_name_ = transaction.getLast();
    id_ = transaction.getID();
    return true;
}

//set 10 funds names and assign appropriate linked funds
void Account::setFunds()
{
    funds_[0].setName("Money Market");
    funds_[0].setLink(true);
    funds_[0].setLinkedFund(1);
    funds_[1].setName("Prime Money Market");
    funds_[1].setLink(true);
    funds_[1].setLinkedFund(0);
    funds_[2].setName("Long-Term Bond");
    funds_[2].setLink(true);
    funds_[2].setLinkedFund(3);
    funds_[3].setName("Short-Term Bond");
    funds_[3].setLink(true);
    funds_[3].setLinkedFund(2);
    funds_[4].setName("500 Index Fund");
    funds_[5].setName("Capital Value Fund");
    funds_[6].setName("Growth Equity Fund");
    funds_[7].setName("Growth Index Fund");
    funds_[8].setName("Value Fund");
    funds_[9].setName("Value Stock Index");
}


string Account::getFirstName() const
{
    return first_name_;
}

string Account::getLastName() const {
    return last_name_;
}

int Account::getID() const
{
    return id_;
}

string Account::getName() const {
    return first_name_ + " " + last_name_;
}

Fund Account::getFund(const int & index) const {
    return funds_[index];
}


//add transaction history for each fund
bool Account::addHistory(Transaction transaction, int index)
{
    return funds_[index].addHistory(transaction);
}


//display individual fund's history of transactions
void Account::displayFundHistory(const int & index) const
{
    cout << funds_[index].getName() << ": $" << funds_[index].getBalance() << endl;
    funds_[index].displayHistory();
}


//display whole account's history of transactions
void Account::displayAccountHistory() const
{
    for (int index = 0; index < 10; index++) 
    {
        if (funds_[index].getHistoryCount() > 0) 
        {
            cout << funds_[index].getName() << ": $" << funds_[index].getBalance() << endl;
            funds_[index].displayHistory();
        }
    }
}


//add money to specific fund
bool Account::addFund(int index, int amount)
{
    funds_[index].addMoney(amount);
    return true;
}


//reduce money from specific fund
bool Account::reduceFund(Transaction *transaction,int index, int amount)
{

    //valid transaction
    if (funds_[index].getBalance() >= amount)
    {
        funds_[index].reduceMoney(amount);
        return true;
    }

    //the amount requested exceeds targeted fund balance, use linked funds to cover 
    if(funds_[index].getBalance() < amount)
    {
        int remaining = amount - funds_[index].getBalance();
        //the linked fund can cover the remaining
        if (funds_[index].hasLinked() && funds_[funds_[index].getLinkedFund()].getBalance() >= remaining)
        {
            transaction->setAmount(funds_[index].getBalance());                 //adjust the amount taken from targeted fund
            funds_[index].setFund(0);

            funds_[funds_[index].getLinkedFund()].reduceMoney(remaining);       //take remaining from linked fund
            Transaction remainTransaction = *transaction;
            remainTransaction.setAmount(remaining);
            remainTransaction.setFund(funds_[index].getLinkedFund());                          
            addHistory(remainTransaction, funds_[index].getLinkedFund());       //add history transaction of the remaining for linked fund

            return true;
        }
    }
    return false;
}


bool Account::operator<(const Account& other) const
{
    return id_ < other.id_;
}

bool Account::operator>(const Account& other) const
{
    return id_ > other.id_;
}

bool Account::operator==(const Account& other) const
{
    return id_ == other.id_;
}

bool Account::operator!=(const Account& other) const
{
    return id_ != other.id_;
}


ostream& operator<<(ostream& out_stream, const Account & account)
{
    out_stream << account.first_name_ << " " << account.last_name_ << " Account ID: " << account.id_ << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << "  " << account.getFund(i).getName() << ": $" << account.getFund(i).getBalance() << endl;
    }
    return out_stream;
}
