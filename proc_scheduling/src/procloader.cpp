#include <fstream>
#include <iostream>
#include <sstream>
#include "procloader.h"

namespace ps
{
	std::vector<Proc> ProcLoader::loadFromFile(const std::string& filepath)
	{
		std::vector<Proc> procs;
        std::ifstream file(filepath);
        
        if (!file.is_open()) 
		{
            throw std::runtime_error("Cannot open file: " + filepath);
        }

        std::string line;
        while (std::getline(file, line)) 
		{
            std::istringstream iss(line);
            std::string name;
            uint32_t arrival, service, priority;

            if (iss >> name >> arrival >> service >> priority) 
			{
                // procs.emplace_back(name, Waiting, arrival, service, 0, service);
				Proc proc(name, arrival, service, priority);
				procs.push_back(proc);
            } 
			else 
			{
                std::cerr << "Warning: Invalid line format: " << line << "\n";
            }
        }

        return procs;
	}
}; // namespace ps


