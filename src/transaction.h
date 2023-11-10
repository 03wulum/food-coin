#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

class Transaction {
public:

    std::string sender;
    std::string receiver;
    int amount;

    Transaction(std::string sender, std::string receiver, int amount);
    std::string toString();
};

#endif