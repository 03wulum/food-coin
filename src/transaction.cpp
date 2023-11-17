#include "transaction.h"
#include "sstream"
#include "stdexcept"
#include <iostream> 
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

bool handleErrors(void);

//macro for error handling
#define CHECK_AND_HANDLE_ERROR(op) if(!(op)) { \
    if(handleErrors()) { \
        return false; \
    } \
}


bool handleErrors(void) {
    unsigned long errCode;
    bool isError = false;
    //check if error code not equal to 0
    while(errCode = ERR_get_error() != 0) {
        char *err = ERR_error_string(errCode, NULL);
        std::cerr << "Error: " << err << std::endl;
        isError = true;
    }
    return isError;
}

Transaction::Transaction(std::string sender, std::string receiver, double amount)
    : sender(sender), receiver(receiver), amount(amount), fee(0) {}
/**
 * convert transaction objects to strings;
*/
std::string Transaction::toString() const{
    std::stringstream ss;
    ss << sender << receiver << amount;
    return ss.str();
}

bool Transaction::sign(std::string privateKey) {
    //use EVP library from open ssl in declaring a pointer to EVO structure
    // hold state of message digest
    EVP_MD_CTX *mdctx = NULL;
    // *sigholds digital signture array
    unsigned char *sig = nullptr;
    // length of the signature
    size_t slen;
    ///concatenate msg components
    this->msg = this->sender + this->receiver + std::to_string(this->amount) + std::to_string(this->fee);

    // create digest context
    CHECK_AND_HANDLE_ERROR(!(mdctx = EVP_MD_CTX_new()))//implement handle errors

    //Load private key
    BIO *bio = BIO_new_mem_buf(privateKey.data(), privateKey.size());
    //check if bio object was created
    CHECK_AND_HANDLE_ERROR(!bio);
    //read privatekey from BIO in evep structure
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    //check if pkey exist: if it private key was read succesfully
    CHECK_AND_HANDLE_ERROR(!pkey);

    //initial signing of digest
    //we set the mdctx (our hash?) to the EVPSHA-256 hash function;
    // and the private key to the pkey; checking eqaulity to 1 in openssl conventions is to see if successful
    CHECK_AND_HANDLE_ERROR(1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey));
    //continue with update using message
    CHECK_AND_HANDLE_ERROR(1 != EVP_DigestSignUpdate(mdctx, msg.data(), msg.size()));

    //this function finalizes signing operation
    // called initially with NUll sig paramater to obtain length of signature
    // it will return the signature that we can use late to verify integrity and authencity of the message
    CHECK_AND_HANDLE_ERROR(1 != EVP_DigestSignFinal(mdctx, NULL, &slen));
    //allocate emory for signature based on size
    CHECK_AND_HANDLE_ERROR(!(sig = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * slen)));

    this->signature = std::string((char*)sig, slen);

    // Obtain the signature
    CHECK_AND_HANDLE_ERROR(1 != EVP_DigestSignFinal(mdctx, sig, &slen));

    //do a clean up; note even the BIO structure has a freeing method
    OPENSSL_free(sig);
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    BIO_free(bio);
    return true;
}

// a const member function, it is telling us that amount
double Transaction::getAmount() const {
    return this->amount;
}
void Transaction::setFee(double fee) {
 if(fee < 0) {
    throw std::invalid_argument("Fee cannot be negative!");
 }  else {
    this->fee = fee;
 } 
}