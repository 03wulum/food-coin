#include "block.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>


Block::Block(int index, std::string previousHash, std::vector<std::string> transactions, long timestamp, int nonce)
{
    this->index = index;
    this->previousHash = previousHash;
    this->transactions = transactions;
    this->timestamp = timestamp;
    this->nonce = nonce;

    this->hash = calculateHash();
}

std::string Block:: getHash() {
    return this->hash;
}

std::string Block::calculateHash()
{
    // Create a buffer to store the hash
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    // Create a new EVP_MD_CTX
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    // Initialize the EVP_MD_CTX with SHA256
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // Update the EVP_MD_CTX with the previousHash
    EVP_DigestUpdate(mdctx, this->previousHash.c_str(), this->previousHash.size());

    // Update the EVP_MD_CTX with each transaction
    for (std::string transaction : this->transactions)
    {
        EVP_DigestUpdate(mdctx, transaction.c_str(), transaction.size());
    }

    // Update the EVP_MD_CTX with the nonce and timestamp
    EVP_DigestUpdate(mdctx, (char *)&this->nonce, sizeof(this->nonce));
    EVP_DigestUpdate(mdctx, (char *)&this->timestamp, sizeof(this->timestamp));

    // Finalize the hash computation
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // Clean up
    EVP_MD_CTX_free(mdctx);

    // Convert the hash to a hexadecimal string
    std::stringstream ss;
    for (int i = 0; i < hash_len; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}
