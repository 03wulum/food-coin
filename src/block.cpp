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
    //initialize it sha256 structure
    SHA256_Init(&sha256);
    /*do an update using the initialized sha256 and the previous hash
    ** but you need to turn the previousHash of the block to a c string and include the length in the update.
    */
    SHA256_Update(&sha256, this->previousHash.c_str(), this->previousHash.size()); //this is importand for incremental hashing of chunks of data in a stream
    /**
     * update sha structure with each transaction in the block
    */
    for(std::string transaction : this-> transactions) {
        //size to get length of string
        SHA256_Update(&sha256, transaction.c_str(), transaction.size());
    }
    //& operators is used to get the address of the variables.
    SHA256_Update(&sha256, &this->nonce.c_str(), sizeof(this->nonce));
    SHA256_Update(&sha256, &this->timestamp.c_str(), sizeof(this->timestamp.size()));

    //store the digest, or resulting hash in an array; #32 bytes for SHA-256
    unsigned char hash[SHA256_DIGEST_LENGTH];

    //finalize hash computation, culminating in the update of the hash array
    SHA256_FINAL(hash, &sha256);

    //creates string stream to convert hash array from binary to hexadecimal string
    std::stringstream ss;

    for(int i = 0; i < SHA256_DIGEST_LENGTH.length; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}