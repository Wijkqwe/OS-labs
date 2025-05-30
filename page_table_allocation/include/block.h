#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

namespace dpa
{
struct Block
{
        unsigned size;
        std::vector<std::pair<unsigned, unsigned>> pos;
        Block(unsigned s, std::vector<std::pair<unsigned, unsigned>> p) : size(s), pos(p) {};
        Block() : Block(0, std::vector<std::pair<unsigned, unsigned>>()) {}
};
};  // namespace dpa

#endif