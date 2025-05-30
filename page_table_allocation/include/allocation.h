#pragma once
#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdint>
#include "block.h"

namespace dpa
{
class PageTable
{
    public:
        PageTable(const std::string& filepath);
        ~PageTable();
        void run();
    private:
        std::ifstream file;
        std::unordered_map<std::string, Block> blocks;
        uint32_t row = 5;
        unsigned rmsize = row * 32;  //: remain size
        std::vector<uint32_t> pages = std::vector<uint32_t>(row, 0);

        void m_malloc(std::string name, unsigned size);
        void m_free(std::string name);
        void print();
};
};  // namespace dpa

#endif
