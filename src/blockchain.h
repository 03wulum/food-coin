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
    Block mineBlock();

    //declare getChain function
    std::vector<Block> getChain();
};
