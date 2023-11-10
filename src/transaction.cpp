#include "transaction.h"
#include "sstream"

Transaction::Transaction(std::string sender, std::string receiver, int amount) {
    this->sender = sender;
    this->receiver = receiver;
    this->amoutn = amount; 
}
/**
 * convert transaction objects to strings;
*/
std::string Transaction::toString() {
    std::stringstream ss;
    ss << sender << receiver << amount;
    return ss.str();
}

