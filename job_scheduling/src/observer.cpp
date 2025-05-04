#include <iostream>
#include "observer.h"

namespace js
{
	void JobLogger::onstatechange(Job& job, uint32_t current_time)
	{
        std::cout << "[LOG] Time " << current_time << " - Job " 
			<< job.name << " is " << "Running" << "\n";
		std::cout << "    waiting time: " << job.watime << " remain time: "
			<< job.retime << "\n";
	}
	void JobFinishLogger::onstatechange(Job& job, uint32_t current_time)
	{
		if (job.state != Finished)
			return;
		double wttime = (double)(job.setime + job.watime) / job.setime;
		std::cout << "[Finished] - Job " << job.name << "\n"
			<< "    arrival time: " << job.artime << " waiting time: "
			<< job.watime << " finished time: " << current_time + 1 << "\n"
			<< "    turnaround time: " << job.setime + job.watime
			<< " weighted turnaround time: " << wttime << "\n";
	}
};

