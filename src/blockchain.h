#include "block.h"
#include "transaction.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pendingTransactions

public:
    Blockchain();
    void addBlock(Block block);
    void addPendingTransaction(Transaction transaction) {
        //add new pending transction to pending transactions vector
        pendingTransactions.push_back(transaction)
    }
    int getChainLength();
    Block getLatestBlock();
    Block mineBlock();

    //declare getChain function
    std::vector<Block> getChain();
};
