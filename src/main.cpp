#include <iostream>
#include "block.h"
#include "blockchain.h"
#include "transaction.h"
#include "wallet.h"

// Create a new blockchain.
Blockchain blockchain;

// Create a new wallet.
Wallet wallet("WalletAddress", "gfuidhgufidgu3f");

void createNewAddress() {
    // Generate a new address for the wallet.
    std::string newAddress = wallet.generateNewAddress();
    std::cout << "New address: " << newAddress << std::endl;
}

void checkBalance() {
    // Check the balance of the wallet.
    double balance = wallet.getBalance();
    std::cout << "Balance: " << balance << std::endl;
}

void sendTransaction() {
    // Get the sender address, receiver address, and amount from the user.
    std::string senderAddress, receiverAddress;
    double amount;
    std::cout << "Enter sender address: ";
    std::cin >> senderAddress;
    std::cout << "Enter receiver address: ";
    std::cin >> receiverAddress;
    std::cout << "Enter amount: ";
    std::cin >> amount;

    // Create a new transaction.
    Transaction transaction(senderAddress, receiverAddress, amount);

    // Add the transaction to the wallet.
    wallet.sendTransaction(transaction);
}

void mineBlock() {
    std::cout << "Mining these blocks bro!";
    // For simplicity, let's assume mining automatically adds pending transactions to a new block.
    // Block newBlock = blockchain.mineBlock();
    // std::cout << "Block mined: " << newBlock.getHash() << std::endl;
}
void runInProd() {
    int choice = 0;
    while (choice != 5) {
        std::cout << "1. Create new address\n2. Check balance\n3. Send transaction\n4. Mine block\n5. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createNewAddress();
            break;
        case 2:
            checkBalance();
            break;
        case 3:
            sendTransaction();
            break;
        case 4:
            mineBlock();
            break;
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please choose again.\n";
            break;
        }
    }
}

int main() {
    bool isDev = true;
    if(!isDev) {
        runInProd();
    } else {
        // Create a new blockchain.
        Blockchain blockchain;

        // Create a new wallet.
        Wallet wallet("WalletAddress", "gfuidhgufidgu3f");

        // Create a new transaction.
        Transaction transaction("senderAddress", "receiverAddress", 100);

        // Add the transaction to the wallet.
        wallet.sendTransaction(transaction);

        // Add a new block containing the transaction to the blockchain.
        std::vector<std::string> transactions{transaction.toString()};
        Block block(blockchain.getChainLength(), blockchain.getLatestBlock().getHash(), transactions, time(0), 0);
        blockchain.addBlock(block);
    }
    return 0;     
}