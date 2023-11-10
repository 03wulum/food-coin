#include "wallet.h"

//constructor, sets inital vlues to class meber during object instation
// pasing address when object wallet is creatd, and set balance to 0
Wallet::Wallet(std::string address) : address(address), balance(0.0) {}

void Wallet::addTransaction(Transaction transaction) {
    transactions.push_back(transaction)
    balance += transaction.getAmount();
}

void Wallet::sendTransaction(Transaction transaction) {
    // first sign transaction
    transaction.sign(this->privateKey);
    // next calculate fee for transaction
    double fee = calculateTranactionFee(transaction);

    // make sure fee is added to transaction
    transaction.setFee(fee);

    //add the transaction to the wallet record
    addTransaction(transaction);

    // apparently now you need to broadcast to the network
    broadcastTransaction(transaction);

}

double Wallet::getBalance() {
    return balance;
}
std::string Wallet::getAddress() {
    return address;
}
std::vector<Transaction> Wallet::getTransactions() {
    return transactions;
}
