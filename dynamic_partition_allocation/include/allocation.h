#pragma once
#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <fstream>
#include <unordered_set>
#include <vector>
#include "block.h"

namespace dpa
{
class FirstFit
{
    public:
        FirstFit(const std::string& filepath);
        ~FirstFit();
        void run();
    private:
        std::ifstream file;
        std::vector<Block> blocks;
        std::unordered_set<std::string> block_name = {"free"};
        void* add(Block b);
        void* del(std::string s);
        void print();
        void sort();
};
};  // namespace dpa

#endif
