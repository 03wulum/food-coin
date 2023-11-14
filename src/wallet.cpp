#include "wallet.h"
#include "stdexcept"
#include <iostream> 

//constructor, sets inital vlues to class meber during object instation
// pasing address when object wallet is creatd, and set balance to 0
// pass private key as well when wallet object is create in order to sign transactions
Wallet::Wallet(std::string address, std::string privateKey) : address(address), privateKey(privateKey), balance(0.0) {}

void Wallet::addTransaction(Transaction transaction) {
    transactions.push_back(transaction);
    balance += transaction.getAmount();
}

void Wallet::broadcastTransaction(const Transaction& transaction) {

}

void Wallet::sendTransaction(Transaction transaction) {
    // first sign transaction
    transaction.sign(this->privateKey);
    // next calculate fee for transaction
    double fee = calculateTransactionFee(transaction);

    // make sure fee is added to transaction
    try{
       transaction.setFee(fee); 
    } catch(const std::invalid_argument& e) {
        std::cerr << "Failed to set transaction fee: " << e.what() << std::endl;
    }
    

    //add the transaction to the wallet record
    addTransaction(transaction);

    // apparently now you need to broadcast to the network
    broadcastTransaction(transaction);

}

double Wallet::getBalance() {
    return balance;
}
double Wallet::calculateTransactionFee(const Transaction& transaction) {
    const double feePercent = 0.02;
    return transaction.getAmount() * feePercent;
}
std::string Wallet::getAddress() {
    return address;
}
std::vector<Transaction> Wallet::getTransactions() {
    return transactions;
}
