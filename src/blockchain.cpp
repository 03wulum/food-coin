#include "blockchain.h"

Blockchain::Blockchain() {
    // add genesis block
    std::vector<std::string> transactions{};

    //initialize gen block with 0 for both index, prev block, timestamp, and nonce
    // above we initialized an empty transaction for the genesis block
    Block genesisBlock(0,"0", transactions, time(0), 0);

    //add te genesisBlock, which is just an instance of block to the chain
    chain.push_back(genesisBlock);
}

void Blockchain::addBlock(Block block) {
    //what does this do?
    chain.push_back(block);
}

int Blockchain::getChainLength() {
    return chain.size();
}

Block Blockchain::getLatestBlock() {
    return chain.back()
}

// chain getter function
std::vector<Block> Blockchain::getChain() {
    return chain;
}