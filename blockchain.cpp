#include "blockchain.hpp"
#include "picosha2.h"
#include <iostream>

bool valid_hash(const Sha256& sha) {
    return sha[0] == 0 && sha[1] == 0;
}


Sha256 Block::GetHash() const
{
    std::vector<unsigned char> block_data(this->data.begin(), this->data.end());
    std::vector<unsigned char> nonce_bytes( (unsigned char*) &this->nonce, ((unsigned char*) (&this->nonce)) + 8);
    block_data.insert(begin(block_data), begin(nonce_bytes), end(nonce_bytes));
    block_data.insert(begin(block_data), begin(prevHash), end(prevHash));

    Sha256 sha;
    picosha2::hash256(begin(block_data), end(block_data),
                      begin(sha), end(sha));

    return sha;
}

bool BlockChain::try_insert(const std::string & data, uint64_t nonce) {
    auto block = Block(data, nonce, this->back().GetHash());
    if(this->valid_block(block)) {
        blocks.push_back(block);
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Block& block)
{
    out << "Hash: " << block.GetHash() << " ";
    out << "Data: \"" << block.data << "\" ";
    out << "Nonce: " << block.nonce << " ";
    out << "PrevHash: " << block.prevHash;
    return out;
}

std::ostream& operator<<(std::ostream& out, const BlockChain& chain)
{
    size_t i = 0;
    for(const auto& block : chain.blocks) {
        out << i << ": " << block << std::endl;
        ++i;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Sha256 & sha) {
    out << picosha2::bytes_to_hex_string(begin(sha), end(sha));
    return out;
}
