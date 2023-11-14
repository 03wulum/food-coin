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
    //use EVP library from open ssl in declaring a pointer to EVO structure
    // hold state of message digest
    EVP_MD_CTX *mdctx = NULL;
    // *sigholds digital signture array
    unsigned char *sig = Null;
    // length of the signature
    size_t slen;

    // create digest context
    if(!(mdctx = EVP_MD_CTX_new())) handleErrors() //implement handle errors

    //Load private key
    BIO *bio = BIO_new_mem_buf(privateKey.data(), privateKey.size());
    //check if bio object was created
    if(!bio) handleErrors();
    //read privatekey from BIO in evep structure
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    //check if pkey exist: if it private key was read succesfully
    if(!pkey) handleErrors();

    //initial signing of digest
    //we set the mdctx (our hash?) to the EVPSHA-256 hash function;
    // and the private key to the pkey; checking eqaulity to 1 in openssl conventions is to see if successful
    if(1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey)) handleErrors();
    //continue with update using message
    if(1 != EVP_DigestSignUpdate(mdctx, msg.data(), msg.size())) handleErrors();

    //this function finlizes signing
    if(1 != EVP_DigestSignFinal(mdctx, NULL, &slen)) handleErrors();
    //allocate emory for signature based on size
    if(!(sig = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * slen))) handleErrors();

    this-> signture = std::string((char*)sig, slen);

    //do a clean up; note even the BIO structure has a freeing method
    OPENSSL_free(sig);
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkeu);
    BIO_free(bio);
}

double Transaction::getAmount() {
    return this->amount;
}
void Transaction::setFee(double fee) {
    
}

