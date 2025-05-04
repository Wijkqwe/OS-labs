#include <algorithm>
#include <stdexcept>
#include "strategy.h"

namespace ps
{
	Proc* Strategy::SelectProc(std::vector<Proc>& procs, uint32_t current_time)
	{
		Proc* selected = nullptr;
		
		for (auto& proc : procs)
		{
			if (proc.state == Waiting && proc.artime <= current_time)
			{
				selected = &proc;
				break;
			}
		}

		return selected;
	}


	void FCFSstrategy::sort(std::vector<Proc>& procs)
	{
		std::sort(procs.begin(), procs.end(), [](Proc a, Proc b){return a.artime < b.artime;});
	}

	void SJFstrategy::sort(std::vector<Proc>& procs)
	{
		std::sort(procs.begin(), procs.end(), [](Proc a, Proc b){return a.retime < b.retime;});
	}

	void RRstrategy::sort(std::vector<Proc>& procs)
	{
		std::sort(procs.begin(), procs.end(), [](Proc a, Proc b){return a.artime < b.artime;});
	}

	Proc* RRstrategy::SelectProc(std::vector<Proc>& procs, uint32_t current_time)
	{
		if (remain_time)
		{
			remain_time--;
			return &procs[current_index];
		}

		Proc* selected = nullptr;
		
		for (int32_t i = current_index + 1, j = 0; j < procs.size(); i = (i + 1) % procs.size(), j++)
		{
			if (procs[i].state == Waiting && procs[i].artime <= current_time)
			{
				current_index = i;
				break;
			}
		}

		if (current_index >= 0)
		{
			selected = &procs[current_index];
			remain_time = std::min(round_time, selected->retime);
			remain_time--;
		}
		return selected;
	}

	void Pstrategy::sort(std::vector<Proc>& procs)
	{
		std::sort(procs.begin(), procs.end(), [](Proc a, Proc b)
		{
			if (a.priority ^ b.priority)
				return a.priority < b.priority;
			return a.artime < b.artime;
		});
	}

	Proc* dPstrategy::SelectProc(std::vector<Proc>& procs, uint32_t current_time)
	{
		Proc* selected = nullptr;
		
		for (auto& proc : procs)
		{
			if (proc.state == Waiting && proc.artime <= current_time)
			{
				selected = &proc;
				selected->priority += add_pri;
				break;
			}
		}

		return selected;
	}

	Proc* npPstrategy::SelectProc(std::vector<Proc>& procs, uint32_t current_time)
	{
		if (remain_time)
		{
			remain_time--;
			return last_proc;
		}

		Proc* selected = nullptr;
		
		for (auto& proc : procs)
		{
			if (proc.state == Waiting && proc.artime <= current_time)
			{
				selected = &proc;
				last_proc = selected;
				remain_time = selected->retime;
				remain_time--;
				break;
			}
		}
		return selected;
	}


	std::unique_ptr<Strategy> StrategyFactory::CreateStrategy(const std::string type)
	{
		if (type == "FCFS") 
			return std::make_unique<FCFSstrategy>();
        if (type == "SJF") 
			return std::make_unique<SJFstrategy>();
        if (type == "RR") 
			return std::make_unique<RRstrategy>();
        if (type == "P") 
			return std::make_unique<Pstrategy>();
        if (type == "dP") 
			return std::make_unique<dPstrategy>();
        if (type == "npP") 
			return std::make_unique<npPstrategy>();
		

        throw std::runtime_error("Unknown strategy type");
	}
};
