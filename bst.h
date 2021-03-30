/*Poppy La
Instructor: Dr.Dimpsey
Course 342 B
Program 5: The Bank
*/

#ifndef BST_H
#define BST_H

#include <iostream>
#include "account.h"

using namespace std;

class BST
{
    public:
    BST();
    ~BST(); 
    
    bool insert(Account *);

    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool retrieve(const int &, Account * &) const;

    // displays the contents of a tree to cout
    void display() const;
    void empty(); 
    bool isEmpty() const;
    
    private:
    struct Node
    { 
        Account *p_acct_;
        Node *right_;
        Node *left_;
    };
    
    Node * root;
    bool insertHelper(Node*&, Account*);
    bool retrieveHelper(Node*, const int&, Account *&) const;
    void emptyHelper(Node*&);
    void displayHelper(Node*) const; 
};
#endif