#ifndef WALLET_H
#define WALLET_H
#include "transaction.h"
#include <vector>

class Wallet {
private:
    std::string address;
    double balance;
    std::vector<Transaction> transactions;

public:
    Wallet(std::string address);
    void addTransaction(Transaction transaction);
    void sendTransaction(Transaction transaction);
    double getBalance();
    std::string getAddress();
    std::vector<Transaction> getTransactions();
    
};

#endif