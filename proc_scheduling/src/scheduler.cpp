#include <algorithm>
#include "procloader.h"
#include "scheduler.h"


namespace ps
{
	Scheduler::Scheduler():current_time(0){}

	void Scheduler::notifyObservers(Proc& proc)
	{
		for (auto& ob : observers)
		{
			ob->onstatechange(proc, current_time);
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
            bool allFinished = std::all_of(procs.begin(), procs.end(), 
                [](const Proc& j) 
				{ return j.state == Finished; });
            if (allFinished) 
				break;
			
			strategy->sort(procs);

            for (auto& proc : procs) 
			{
                if (proc.state == Waiting && proc.artime <= current_time) 
				{
                    proc.watime++;
                }
            }

            if (/*std::unique_ptr<Proc>*/Proc* proc = strategy->SelectProc(procs, current_time)) 
			{
                proc->state = Running;
                proc->retime--;
				proc->watime--;
                
                if (proc->retime == 0) 
				{
                    proc->state = Finished;
                }
				else
				{
					proc->state = Waiting;
				}
                
                notifyObservers(*proc);
            }
            current_time++;
        }
	}

	void Scheduler::loadFromFile(const std::string& filepath)
	{
		auto loadedProcs = ProcLoader::loadFromFile(filepath);
        procs.insert(procs.end(), loadedProcs.begin(), loadedProcs.end());
	}
};


