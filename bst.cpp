/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#include "bst.h"

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    empty();
} 

//insert account
bool BST::insert(Account *account)
{
    return insertHelper(root, account);
}

bool BST::insertHelper(Node *& node, Account* account)
{
    //empty node
    if (node == nullptr) 
    {
        node = new Node;
        node->p_acct_ = account;
        node->left_ = nullptr;
        node->right_ = nullptr;
        return true;
    }
    else if (*account < *node->p_acct_) 
    {
        return insertHelper(node->left_, account);
    }
    else if (*account > *node->p_acct_) 
    {
        return insertHelper(node->right_, account);
    }
    else 
    {
        return false;
    }
}  


//looking for specific account id
bool BST::retrieve(const int &id, Account * &account) const
{
    //empty tree
    if(root == nullptr)
    {
        account = nullptr;
        return false;
    }
    else
    {
        return retrieveHelper(root, id, account);
    }
}

bool BST::retrieveHelper(Node* node, const int& id, Account *& account) const
{
    //account not found
    if(node == nullptr)
    {
        account = nullptr;
        return false;
    }

    if (id < node->p_acct_->getID())
    {
        return retrieveHelper(node->left_, id, account);
    }
    else if(id > node->p_acct_->getID())
    {
        return retrieveHelper(node->right_, id, account);
    }
    else 
    {
        account = node->p_acct_;      //account found
        return true;
    }
}


//display all opened accounts
void BST::display() const
{
    displayHelper(this->root);
}

void BST::displayHelper(Node* node) const
{
    if (node != nullptr)
    {
        displayHelper(node->left_);
        cout << *node->p_acct_ << endl;
        displayHelper(node->right_);
    }
}


//dellete all accounts
void BST::empty()
{
    if(root != nullptr) 
    {
    emptyHelper(root);
    root = nullptr;
    }
}

void BST::emptyHelper(Node *& node)
{
    if (node != nullptr)
    {
        emptyHelper(node->left_);
        emptyHelper(node->right_);
        delete node->p_acct_;
        delete node;
    }
}

//check if tree is empty
bool BST::isEmpty() const
{
    return root == nullptr;
}