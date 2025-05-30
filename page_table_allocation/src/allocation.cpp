#include "allocation.h"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace dpa
{
PageTable::PageTable(const std::string& filepath)
{
    file.open(filepath);
    if (!file.is_open())
        throw std::runtime_error("error");

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    unsigned row, column;
    Block tmp;
    while (iss >> row >> column)
    {
        pages[row] |= (1 << column);
        rmsize--;
        tmp.size++;
        tmp.pos.emplace_back(row, column);
    }
    blocks["first"] = tmp;
}
PageTable::~PageTable()
{
    if (file.is_open())
        file.close();
}
void PageTable::run()
{
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line[0] == 'p')
            print();
        else
        {
            std::istringstream iss(line);
            std::string name;
            char c;
            if (iss >> c >> name)
            {
                if (c == 'a')
                {
                    if (blocks.count(name))
                    {
                        std::cout << name << " exist\n" << std::endl;
                        continue;
                    }
                    unsigned size;
                    if (iss >> size)
                    {
                        if (rmsize < size)
                            std::cout << "free size no exist\n" << std::endl;
                        else
						{
							m_malloc(name, size);
							std::cout << "add block\n" << std::endl;
						}
                    }
                }
                else if (c == 'd')
                {
                    if (!blocks.count(name))
                    {
                        std::cout << name << " not exist\n" << std::endl;
                        continue;
                    }
                    m_free(name);
					std::cout << "free block\n" << std::endl;
                }
            }
        }
    }
}

void PageTable::m_malloc(std::string name, unsigned size)
{
    Block tmp;
    tmp.size = size;
    for (int i = 0; i <= pages.size(); ++i)
    {
        for (int j = 0; j <= 31; ++j)
        {
            if (!(pages[i] & (1 << j)))
            {
				pages[i] |= (1 << j);
                tmp.pos.emplace_back(i, j);
                size--;
                rmsize--;
                if (!size)
                {
                    blocks[name] = tmp;
                    return;
                }
            }
        }
    }
}

void PageTable::m_free(std::string name)
{
    for (auto b : blocks[name].pos)
    {
        pages[b.first] &= ~(1 << b.second);
        rmsize++;
    }
    blocks.erase(name);
}

void PageTable::print()
{
	std::cout << "remain size: " << rmsize << std::endl;
    for (auto p : pages)
    {
        std::cout << "    ";
        for (int i = 0; i <= 31; ++i)
        {
            std::cout << ((p & (1 << i)) >> i) << " ";
        }
        std::cout << std::endl;
    }
    for (auto bl : blocks)
    {
        std::cout << "  name: " << bl.first << " size: " << bl.second.size << std::endl;
		std::cout << "pos: ";
		unsigned i = 1;
        for (auto p : bl.second.pos)
        {
            std::cout << p.first << " " << p.second << " " << " \n"[(i++ % 10) == 0];
        }
		std::cout << std::endl;
    }
	std::cout << std::endl;
}

};  // namespace dpa
