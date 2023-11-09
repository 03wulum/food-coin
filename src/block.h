#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

class Block
{
public:
    int index;
    std::string previousHash;
    std::string hash;
    std::vector<std::string> transactions;
    long timestamp;
    int nonce;

    Block(int index, std::string previousHash, std::vector<std::string> transactions, long timestamp, int nonce);

    // method for calculating block hash
    std::string calculateHash();
}

#endif