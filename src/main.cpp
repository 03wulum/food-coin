#include <iostream>
#include "block.h"
#include "blockchain.h"
#include "transaction.h"
#include "wallet.h"

int main() {
    // Create a new blockchain.
    Blockchain blockchain;

    // Create a new wallet.
    Wallet wallet("WalletAddress");

    // Create a new transaction.
    Transaction transaction("senderAddress", "receiverAddress", 100);

    // Add the transaction to the wallet.
    wallet.sendTransaction(transaction);

    // Add a new block containing the transaction to the blockchain.
    std::vector<std::string> transactions{transaction.toString()};
    Block block(blockchain.getChainLength(), blockchain.getLatestBlock().getHash(), transactions, time(0), 0);
    blockchain.addBlock(block);

    return 0;
}