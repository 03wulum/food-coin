#include "block.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain();
    void addBlock(Block block);
    int getChainLength();
    Block getLatestBlock();

    //declare getChain function
    std::Vector<Block> getChain();
};
