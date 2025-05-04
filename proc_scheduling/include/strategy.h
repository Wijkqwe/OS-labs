#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

#include <memory>
#include <vector>
#include <string>
#include "proc.h"

namespace ps
{
class Strategy
{
public:
	uint32_t remain_time = 0;
	//: pure virtual function
	// virtual Proc* SelectProc(std::vector<Proc>& procs, uint32_t current_time) = 0;
	virtual Proc* SelectProc(std::vector<Proc>& procs, uint32_t current_time);
	virtual void sort(std::vector<Proc>& procs) = 0;
};

class FCFSstrategy : public Strategy
{
public:
	void sort(std::vector<Proc>& procs) override;
};

//: Preemptive
class SJFstrategy : public Strategy
{
public:
	void sort(std::vector<Proc>& procs) override;
};

class RRstrategy : public Strategy
{
public:
	void sort(std::vector<Proc>& procs) override;
	Proc* SelectProc(std::vector<Proc>& procs, uint32_t current_time) override;
private:
	uint32_t round_time = 10;
	int32_t current_index = -1;
};

//: Preemptive
class Pstrategy : public Strategy
{
public:
	void sort(std::vector<Proc>& procs) override;
};
//: dynamic
class dPstrategy : public Pstrategy
{
public:
	Proc* SelectProc(std::vector<Proc>& procs, uint32_t current_time) override;
private:
	uint32_t add_pri = 1;
};
//: not preemptive
class npPstrategy : public Pstrategy
{
public:
	Proc* SelectProc(std::vector<Proc>& procs, uint32_t current_time) override;
private:
	Proc* last_proc = nullptr;
};


class StrategyFactory
{
public:
	static std::unique_ptr<Strategy> CreateStrategy(const std::string type);
};
}; //: namespace ps

#endif

