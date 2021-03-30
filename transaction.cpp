/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#include "transaction.h"

Transaction::Transaction()
{
    transaction_type_ = Default_Value::Character;
    first_name = Default_Value::String;
    last_name = Default_Value::String;
    account_id_ = Default_Value::Number, fund_ = Default_Value::Number;
    to_account_ = Default_Value::Number, to_fund_ = Default_Value::Number;
    amount_ = Default_Value::Number;
    isFailed = false;
}

Transaction::~Transaction(){};


void Transaction::setType(char ch)
{
    transaction_type_ = ch;
}

void Transaction::setAmount(int amount)
{
    amount_ = amount;
}
void Transaction::setFund(int fund)
{
    fund_ = fund;
}

void Transaction::setData(string &info)
{
    this->command = info;

    // tokenize string
    stringstream ss(info);
    string word;

    while(ss >> word)
    {
        words.push_back(word);
    }
}

//check if input data valid
bool Transaction::checkData() 
{
    //bad input
    if (words.size() == 0 || words.size() > 4)
    {
        return false;
    }

    transaction_type_ = (char)words.at(0).at(0);

    // Check valid information
    if (transaction_type_ == TransactionType::Open)
    {
        if (words.size() != 4)
        {
            cout << "ERROR: Bad input. Transaction refused!" << endl;
            return false;
        }
        first_name = words.at(2);
        last_name= words.at(1);
        account_id_ = stoi(words.at(3));
        return true;
    }

    else if (transaction_type_ == TransactionType::Deposit || transaction_type_ == TransactionType::Withdraw)
    {
        if (words.size() != 3 || stoi(words.at(1))/10000 <= 0)
        {
            cout << "ERROR: Transaction \"";
            for(int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }

        fund_ = stoi(words.at(1)) % 10;
        account_id_ = stoi(words.at(1))/10;
        amount_ = stoi(words.at(2));
        return true;
    }

    else if (transaction_type_ == TransactionType::Transfer)
    {
        if (words.size() != 4 || stoi(words.at(1)) < 10000  || stoi(words.at(1)) > 99999
        || stoi(words.at(3)) < 1000 || stoi(words.at(3)) > 99999)
        {
            cout << "ERROR: Transaction \"";
            for(int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        fund_ = stoi(words.at(1)) % 10;
        account_id_ = stoi(words.at(1)) / 10;
        amount_ = stoi(words.at(2)) ;
        to_fund_ = stoi(words.at(3)) % 10;
        to_account_ = stoi(words.at(3)) / 10;
        return true;   
    }

    else if (transaction_type_ == TransactionType::History)
    {
        if (words.size() != 2)
        {
            cout << "ERROR: Transaction \"";
            for(int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        // 5 digits, include id and fund
        if (stoi(words.at(1)) / 10 >= 1000)
        {
            account_id_ = stoi(words.at(1)) / 10;
            fund_ = stoi(words.at(1)) % 10;
            return true;
        }
        // 4 digits, include id only
        else if (stoi(words.at(1)) >= 1000 || stoi(words.at(1)) <= 9999)
        {
            account_id_ = stoi(words.at(1));
            fund_ = -1;
            return true;
        }
        return false;
    }

    // not defined type
    cout << "ERROR: Transaction \"";
    for(int i = 0; i < words.size(); i++)
    {
        cout << words.at(i) << " ";
    }
    cout << "\" failed to process. Transaction information missing." << endl;
    return false;
}

int Transaction::getID() const
{
    return account_id_;
}

int Transaction::getTargetID() const
{
    return to_account_;
}

string Transaction::getFirst() const
{
    return first_name;
}

string Transaction::getLast() const
{
    return last_name;
}

bool Transaction::process(BST & accounts)   
{ 
    //invalid transaction
    if (!checkData()) 
    {
        return false;
    }

    Account* check_account; 
    
    //valid transaction
    if (transaction_type_ == TransactionType::Open)
    {
        //invalid number
        if (account_id_ < 1000 || account_id_ > 9999)
        {
            cout << "ERROR: Invalid ID number \"" << account_id_ << "\". Can not open account" << endl;
            return false;
        }
        Account * a_account = new Account();    // create new account
        a_account->setData(*this);

        // account already exist, delete duplicate
        if(!open(accounts, a_account)) 
        {
            delete a_account;
            a_account = nullptr;
            return false;
        }
        return true;
    }

    //check for valid id
    if (!accounts.retrieve(account_id_, check_account))
    {
        cout << "ERROR: Account " << account_id_  << " not found. Transaction refused." << endl;
        return false;
    }

    if (transaction_type_ == TransactionType::Deposit)
    {
       return deposit(check_account);
    }

    else if (transaction_type_ == TransactionType::Withdraw)
    {
        return withdraw(check_account);
    }

    else if (transaction_type_ == TransactionType::Transfer)
    {
        Account* check_target;
        // check valid target id
        if (accounts.retrieve(to_account_, check_target) == false) 
        {
            cout << "ERROR: Account " << to_account_  << " not found. Transferal refused." << endl;
            return false;
        }  
        return transfer(check_account, check_target);
    }

    else if (transaction_type_ == TransactionType::History)
    {
        return history(check_account);
    }

    else 
        return false;
}

bool Transaction::open(BST & accounts, Account* a_account) 
{
    //
    if(!accounts.insert(a_account)) 
    {
        // print error duplicate
        cout << "ERROR: Account " <<  account_id_ <<  " is already open. Transaction refused." << endl;
        return false;
    }
    return true;
}

bool Transaction::deposit(Account *account)
{  
    //negative amount
    if(amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request negative amount of money. Transaction refused." << endl;

        isFailed = true;
        account->addHistory(*this, fund_);
        return false;
    }

    //success transaction
    if (account->addFund(fund_, amount_))
    {
        account->addHistory(*this, fund_);
        return true;
    }
    return false;
} 


bool Transaction::withdraw(Account *account)
{
    if(amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request negative amount of money. Transaction refused." << endl;

        isFailed = true;
        account->addHistory(*this, fund_);
        return false;
    }

    //success transaction
    if (account->reduceFund(this, fund_, amount_))
    {
        account->addHistory(*this, fund_);
        return true;
    }

    //failed transaction
    cout << "ERROR: Not enough funds to withdraw $" << amount_ << " from " <<
        account->getName() << " " << account->getFund(fund_).getName() << endl;

    isFailed = true;
    account->addHistory(*this, fund_);
    return false;
} 

bool Transaction::transfer(Account* account, Account* target)
{
    if(amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request negative amount of money. Transaction refused." << endl;

        isFailed = true;
        account->addHistory(*this, fund_);
        return false;
    }
    //transfer to same fund
    if (account_id_ == to_account_ && fund_ == to_fund_)
    {
        cout << "ERROR: Transaction \"" << *this << "\" is not valid. Transaction refused." << endl;

        isFailed = true;
        account->addHistory(*this, fund_);
        return false;
    }

    //success transaction
    if (account->reduceFund(this,fund_, amount_))
    {
        account->addHistory(*this, fund_);

        // add history for targeted account
        target->addFund(to_fund_, amount_);
        target->addHistory(*this, to_fund_);
        return true;
    }

    //failed transaction
    cout << "ERROR: Not enough funds to transfer $" << amount_ << " from " <<
        account->getName() << " " << account->getFund(fund_).getName() << " to " <<
        target->getName() << " " << target->getFund(fund_).getName() << endl;

    isFailed = true;
    account->addHistory(*this, fund_);
    return false;
} 

bool Transaction::history(Account* account)
{
    cout << "Transaction History for " << account->getName() << " ";

    //history for specific fund (id + fund passed)
    if (fund_ != -1) 
    {
        account->displayFundHistory(fund_);
    }

    //history for the whole account (only id passed)
    else if (fund_ == -1)
    {
        cout << "by fund." << endl;
        account->displayAccountHistory();
    }
    return true;
} 


ostream& operator<<(ostream& out_stream, const Transaction &transaction)
{
    if (transaction.transaction_type_ == TransactionType::Open) 
    {
        out_stream << transaction.transaction_type_ 
        << " " << transaction.first_name << " " << transaction.last_name
        << " " << transaction.account_id_;
    }

    else if (transaction.transaction_type_ == TransactionType::Deposit
    || transaction.transaction_type_ == TransactionType::Withdraw) 
    {
        out_stream << transaction.transaction_type_ << " " << transaction.account_id_
        << transaction.fund_ << " " << transaction.amount_;
    }

    else if (transaction.transaction_type_ == TransactionType::Transfer) 
    {
        out_stream << transaction.transaction_type_ << " " << transaction.account_id_
        << transaction.fund_ << " " << transaction.amount_ << " " << transaction.to_account_
        << transaction.to_fund_;
    }

    else if (transaction.transaction_type_ == TransactionType::History) 
    {
        out_stream << transaction.transaction_type_ << " " << transaction.account_id_;
        if (transaction.fund_ >= 0)
        {
            out_stream << transaction.fund_;
        }
    }
    
    // invalid type
    else 
    {
        out_stream << transaction.command;
    }

    if (transaction.isFailed) 
    {
        out_stream << " (Failed)";
    }

    return out_stream;
}