#include <fstream>
#include <iostream>
#include <sstream>
#include "jobloader.h"

namespace js
{
	std::vector<Job> JobLoader::loadFromFile(const std::string& filepath)
	{
		std::vector<Job> jobs;
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
            uint32_t arrival, service;

            if (iss >> name >> arrival >> service) 
			{
                // jobs.emplace_back(name, Waiting, arrival, service, 0, service);
				Job job(name, arrival, service);
				jobs.push_back(job);
            } 
			else 
			{
                std::cerr << "Warning: Invalid line format: " << line << "\n";
            }
        }

        return jobs;
	}
}; // namespace js


