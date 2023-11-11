#include "transaction.h"
#include "sstream"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

Transaction::Transaction(std::string sender, std::string receiver, double amount) {
    this->sender = sender;
    this->receiver = receiver;
    this->amount = amount; 
}
/**
 * convert transaction objects to strings;
*/
std::string Transaction::toString() {
    std::stringstream ss;
    ss << sender << receiver << amount;
    return ss.str();
}

void Transaction::sign(std::string privateKey) {
    
}

double Transaction::getAmount() {
    return this->amount;
}
void Transaction::setFee(double fee) {
    
}

