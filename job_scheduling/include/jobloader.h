#pragma once
#ifndef JOBLOADER_H
#define JOBLOADER_H

#include <vector>
#include <string>
#include "job.h"

namespace js
{
class JobLoader
{
public:
	static std::vector<Job> loadFromFile(const std::string& filepath);
};
}; //: namespace js

#endif
