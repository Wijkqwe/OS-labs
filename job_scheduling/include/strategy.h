#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

#include <memory>
#include <vector>
#include <string>
#include "job.h"

namespace js
{
class Strategy
{
public:
	//: pure virtual function
	virtual Job* SelectJob(std::vector<Job>& jobs, uint32_t current_time) = 0;
};

class FCFSstrategy : public Strategy
{
public:
	static bool FCFScmp(Job a, Job b);
	Job* SelectJob(std::vector<Job>& jobs, uint32_t current_time) override;
};
//: Preemptive
class SJFstrategy : public Strategy
{
public:
	static bool SJFcmp(Job a, Job b);
	Job* SelectJob(std::vector<Job>& jobs, uint32_t current_time) override;
};

class StrategyFactory
{
public:
	static std::unique_ptr<Strategy> CreateStrategy(const std::string type);
};
}; //: namespace js

#endif

