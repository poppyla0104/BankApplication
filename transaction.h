/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <queue>
#include <sstream>
#include <string>
#include "account.h"
#include "bst.h"

using namespace std;

namespace Default_Value 
{
    static const char Character = '!';
    static string const String = "!";
    static const int Number = -1;
}

enum TransactionType : char 
{
    Open = 'O',
    Deposit = 'D',
    Withdraw = 'W',
    Transfer = 'T',
    History = 'H'
};

class Transaction
{
    friend ostream& operator<<(ostream& out_stream, const Transaction &);
    friend istream& operator>>(istream& in_stream, const Transaction &);

    public:
    Transaction();
    ~Transaction();
    
    //setter
    void setType(char);
    void setAmount(int);
    void setData(string&);
    void setFund(int);

    //getter
    char getType() const;
    int getID() const;
    int getTargetID() const;
    string getFirst() const;
    string getLast() const;

    //use function
    bool process(BST&);
    bool open(BST&, Account*);
    bool deposit(Account*);
    bool withdraw(Account*);
    bool transfer(Account*, Account*);
    bool history(Account*);


    private:
    char transaction_type_;
    string first_name, last_name;
    int account_id_, fund_;
    int to_account_, to_fund_;
    int amount_;
    bool isFailed;
    string command;

    //tokenize input string
    vector<string> words;

    //check if input data valid
    bool checkData();
};
#endif