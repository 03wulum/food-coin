#include "block.h"
#include <openssl/sha.h>
#include <sstream>

Block::Block(int index, std::string previousHash, std::vector<std::string> transactions, long timestamp, int nonce) {
    this->previousHash = previousHash;
    this->transactions = transactions;
    this->timestamp = timestamp;
    this->nonce = nonce;

    this->hash = calculateHash();

}

std::string Block::calculateHash() {
    //SHA context to hold state of the computation
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
}