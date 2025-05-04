#include <algorithm>
#include "jobloader.h"
#include "scheduler.h"


namespace js
{
	Scheduler::Scheduler():current_time(0){}

	void Scheduler::notifyObservers(Job& job)
	{
		for (auto& ob : observers)
		{
			ob->onstatechange(job, current_time);
		}
	}

	void Scheduler::setStrategy(std::unique_ptr<Strategy> newstrategy)
	{
		strategy = std::move(newstrategy);
	}

	void Scheduler::addObserver(std::shared_ptr<Observer> observer)
	{
		observers.push_back(observer);
	}

	void Scheduler::run()
	{
		while (true) 
		{
            bool allFinished = std::all_of(jobs.begin(), jobs.end(), 
                [](const Job& j) 
				{ return j.state == Finished; });
            if (allFinished) 
				break;

            for (auto& job : jobs) 
			{
                if (job.state == Waiting && job.artime <= current_time) 
				{
                    job.watime++;
                }
            }

            if (/*std::unique_ptr<Job>*/Job* job = strategy->SelectJob(jobs, current_time)) 
			{
                job->state = Running;
                job->retime--;
				job->watime--;
                
                if (job->retime == 0) 
				{
                    job->state = Finished;
                }
				else
				{
					job->state = Waiting;
				}
                
                notifyObservers(*job);
            }
            current_time++;
        }
	}

	void Scheduler::loadFromFile(const std::string& filepath)
	{
		auto loadedJobs = JobLoader::loadFromFile(filepath);
        jobs.insert(jobs.end(), loadedJobs.begin(), loadedJobs.end());
	}
};


