#include <iostream>
#include "blockchain.hpp"
#include "picosha2.h"

namespace sha = picosha2;

void f() {
    uint64_t nonce = 0;
    Sha256 hash = {};
    while(!valid_hash(hash)) {
        ++nonce;
        Block b("Hello, world!", nonce, Sha256{});
        hash = b.GetHash();
    }
}

uint64_t mine_nonce(const BlockChain & blockChain, const std::string & data)
{
    uint64_t nonce = 0;
    Block b(data, nonce, blockChain.back().GetHash());
    while(!valid_hash(b.GetHash())) {
        ++nonce;
        b = Block(data, nonce, blockChain.back().GetHash());
    }
    std::cout << "Found nonce: " << nonce << " for data: " << data << std::endl;
    return nonce;
}

int main() {

    BlockChain chain;

    auto insert = [&](const std::string& str) {
        chain.try_insert(str, mine_nonce(chain, str));
    };

    insert("Hello, world!");
    insert("Test string");
    insert("asdf asdf asdf asdf asdf asdf");
    std::cout << chain;
}
