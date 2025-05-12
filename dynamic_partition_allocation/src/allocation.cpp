#include "allocation.h"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace dpa
{
FirstFit::FirstFit(const std::string& filepath)
{
    file.open(filepath);
    if (!file.is_open())
        throw std::runtime_error("error");
    std::string ma;
    std::getline(file, ma);
    blocks.emplace_back("free", atoi(ma.c_str()), 0);
}
FirstFit::~FirstFit()
{
    if (file.is_open())
        file.close();
}
void FirstFit::run()
{
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line[0] == 'p')
            print();
        else if (line[0] == 'a')
        {
            std::istringstream iss(line);
            std::string name;
            unsigned size;
            char c;

            if (iss >> c >> name >> size)
            {
                if (block_name.count(name))
                {
                    std::cout << name << " exist\n" << std::endl;
                    continue;
                }

                if (add(Block(name, size)))
                {
                    std::cout << "add " << name << "\n" << std::endl;
                    block_name.insert(name);
                }
                else
                {
                    std::cout << "free size no exist\n" << std::endl;
                }
            }
        }
        else if (line[0] == 'd')
        {
            std::istringstream iss(line);
            std::string name;
            char c;
            if (iss >> c >> name)
            {
                if (del(name))
                {
                    std::cout << "del " << name << "\n" << std::endl;
                    block_name.erase(name);
                }
                else
                {
                    std::cout << name << " no exist\n" << std::endl;
                }
            }
        }
        sort();
    }
}

void* FirstFit::add(Block b)
{
    for (auto& bl : blocks)
    {
        if (bl.name == "free" && bl.size >= b.size)
        {
            if (b.size == bl.size)
                bl.name = b.name;
            else
            {
                b.begin = bl.begin;
                bl.begin += b.size;
                bl.size -= b.size;
                blocks.push_back(b);
            }

            void* addr = &b.begin;
            return addr;
        }
    }
    return nullptr;
}

void* FirstFit::del(std::string s)
{
    for (size_t i = 0; i < blocks.size(); ++i)
    {
        if (blocks[i].name == s)
        {
            void* addr = &blocks[i].begin;

            if (i != 0 && i != blocks.size() - 1 && blocks[i - 1].name == "free" && blocks[i + 1].name == "free")
            {
                blocks[i - 1].size += blocks[i].size + blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
                blocks.erase(blocks.begin() + i);
            }
            else if (i != 0 && blocks[i - 1].name == "free")
            {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }
            else if (i != blocks.size() - 1 && blocks[i + 1].name == "free")
            {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }
            else
            {
                blocks[i].name = "free";
            }

            return addr;
        }
    }
    return nullptr;
}

void FirstFit::print()
{
    std::cout << " name";
    for (int i = 0; i < 10 - 5; ++i)
        std::cout << " ";
    std::cout << " begin";
    for (int i = 0; i < 10 - 6; ++i)
        std::cout << " ";
    std::cout << " size" << std::endl;

    for (auto bl : blocks)
    {
        std::cout << bl.name;
        for (int i = 0; i < 10 - bl.name.size(); ++i)
            std::cout << " ";

        std::cout << bl.begin;
        for (int i = 0; i < 10 - std::to_string(bl.begin).size(); ++i)
            std::cout << " ";
        std::cout << bl.size << std::endl;
    }
    std::cout << std::endl;
}
void FirstFit::sort()
{
    std::sort(blocks.begin(), blocks.end(),
              [](Block a, Block b)
              {
                  return a.begin < b.begin;
              });
}

};  // namespace dpa
