#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <string>

namespace dpa
{
struct Block
{
        std::string name;
        unsigned size, begin;
        Block(std::string n, unsigned s, unsigned b) : name(n), size(s), begin(b) {};
        Block(std::string n, unsigned s) : Block(n, s, 0) {};
};
};  // namespace dpa

#endif