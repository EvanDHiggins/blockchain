#pragma once

#include <array>
#include <vector>
#include <string>

using Sha256 = std::array<unsigned char, 32>;

bool valid_hash(const Sha256& sha);

class Block {
public:

    Block(const std::string & data, uint64_t nonce, const Sha256 & prevHash)
        : data(data),
          nonce(nonce),
          prevHash(prevHash)
    {}

    Block()
        : prevHash({})
    {}

    Sha256 GetHash() const;

    friend std::ostream& operator<<(std::ostream& out, const Block& block);

private:
    std::string data;
    uint64_t nonce;
    Sha256 prevHash;
};

class BlockChain {
public:
    BlockChain()
        : blocks({Block()})
    {}

    const Block& back() const {
        return blocks.back();
    }

    bool valid_block(const Block& block) {
        auto hash = block.GetHash();
        return true;
    }

    bool try_insert(const std::string & data, uint64_t nonce);

    friend std::ostream& operator<<(std::ostream& out, const BlockChain& chain);

private:
    std::vector<Block> blocks;
};

std::ostream& operator<<(std::ostream& out, const Sha256 & sha);

