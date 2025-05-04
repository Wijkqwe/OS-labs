#include <algorithm>
#include <stdexcept>
#include "strategy.h"

namespace js
{
	bool FCFSstrategy::FCFScmp(Job a, Job b)
	{
		return a.artime < b.artime;
	}

	Job* FCFSstrategy::SelectJob(std::vector<Job>& jobs, uint32_t current_time)
	{
		Job* selected = nullptr;
		// std::vector<Job> jobss(jobs);
		std::sort(jobs.begin(), jobs.end(), FCFScmp);

		// uint8_t fl = 0;
		for (auto& job : jobs)
		{
			if (job.state == Waiting && job.artime <= current_time && !selected)
			{
				selected = &job;
				// fl = 1;
				break;
			}
		}
		//: make_unique points to new object
/*		if (fl)
			return std::make_unique<Job>(selected->name, selected->artime, selected->setime);
		else*/
		
		return selected;
	}

	bool SJFstrategy::SJFcmp(Job a, Job b)
	{
		return a.retime < b.retime;
	}

	Job* SJFstrategy::SelectJob(std::vector<Job>& jobs, uint32_t current_time)
	{
		Job* selected = nullptr;
		std::sort(jobs.begin(), jobs.end(), SJFcmp);

		for (auto& job : jobs)
		{
			if (job.state == Waiting && job.artime <= current_time && !selected)
			{
				selected = &job;
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

        throw std::runtime_error("Unknown strategy type");
	}
};
