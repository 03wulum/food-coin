#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    std::string signature;
    std::string msg;
    double amount;
    double fee;//this is the transaction fee

public:
    Transaction(std::string sender, std::string receiver, double amount);
    std::string toString();
    bool sign(std::string privateKey);
    double getAmount() const;
    void setFee(double fee);
};

#endif