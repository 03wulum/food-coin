#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

class Transaction {
public:

    std::string sender;
    std::string receiver;
    int amount;

    Transaction(std::string sender, std::string receiver, double amount);
    std::string toString();
    void sign(std::string privateKey);
    double getAmount();
    void setFee(double fee);
};

#endif