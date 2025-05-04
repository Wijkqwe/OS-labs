#pragma once
#ifndef PROCLOADER_H
#define PROCLOADER_H

#include <vector>
#include <string>
#include "proc.h"

namespace ps
{
class ProcLoader
{
public:
	static std::vector<Proc> loadFromFile(const std::string& filepath);
};
}; //: namespace ps

#endif
