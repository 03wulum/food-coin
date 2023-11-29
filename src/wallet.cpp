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
std::string Wallet::generateNewAddress() {
    //generate a new private key
    std::string newPrivateKey = generateKeyPair();
    // calc public key from private key
    std::String newPublicKey = getPublicKey();
    // hash public key using our calculateHash function
    std::string hashedPublicKey = Block::calculateHash(newPublicKey)
    
    //  add a version byte and 4byte checksum
     std::string versionAndChecksum = addVersionAndChecksum(hashedPublicKey);
    //encode results using base58?
     std::string newAddress = encodeBase58(versionAndChecksum);
}

EVP_PKEY* Wallet::generateKeyPair() {
    EVP_PKEY *pkey;
    //EVP_PKEY_RSA is not a vriable byt a constant defined in openssl, an identifier for the RSA algorithm
    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    EVP_PKEY_keygen_init(pctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(pctx, 2048);
    EVP_PKEY_keygen(pctx, &pkey);
    EVP_PKEY_CTX_free(pctx);

    return pkey;
}

//get public key from the key pair (private key)
std::string Wallet::getPublicKey(EVP_PKEY *pkey) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bio, pkey);
    BUF_MEM *public_key_mem;

    BIO_get_mem_ptr(bio, &public_key_mem);
    std::string public_key_str(public_key_mem->data, public_key_mem->length);

    BIO_free_all(bio);

    return public_key_str;
}

std::string Wallet::encodeBase58(const std::string& str) {
    BIO *b58 = BIO_new(BIO_f_base64());

    BIO *bmem = BIO_new(BIO_s_mem());
    b58 = BIO_push(b58, bmem);

    BIO_write(b58, str.c_str, str.size());
    BIO_flush(b58);

    BUF_MEM *bptr;
    BIO_get_mem_pter(b58, &bptr);
    std::string encoded_str(bptr->data, bptr->length);

    BIO_free_all(b58);

    return encoded_str;
}

std::String Wallet:addVersionAndChecksum(const std::string& str) {
    // add version byte, like bitcoin
    std::string versionAndChecksum = "00" + str;

    //calc checksum of versioned byte string
    std::string checksum = calculateHash(versionAndChecksum).substr(0,8);

    // append checksum
    versionAndChecksum += checksum;

    return versionAndChecksum;
}