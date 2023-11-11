#ifndef WALLET_H
#define WALLET_H
#include "transaction.h"
#include <vector>

class Wallet {
private:
    std::string address;
    std::string privateKey;
    double balance;
    std::vector<Transaction> transactions;

public:
    Wallet(std::string address, std::string privateKey);
    void addTransaction(Transaction transaction);
    void sendTransaction(Transaction transaction);
    //to send to the network
    void broadcastTransaction(const Transaction& transaction);
    double getBalance();
    double calculateTransactionFee(const Transaction& transaction);
    std::string getAddress();
    std::vector<Transaction> getTransactions();
};

#endif