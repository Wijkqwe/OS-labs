#include <iostream>
#include "observer.h"

namespace ps
{
	void ProcLogger::onstatechange(Proc& proc, uint32_t current_time)
	{
        std::cout << "[LOG] Time " << current_time << " - Proc ** "
			<< proc.name << " ** is " << "Running" << "\n";
		std::cout << "    waiting time: " << proc.watime << " remain time: "
			<< proc.retime << "\n";
	}
	void ProcFinishLogger::onstatechange(Proc& proc, uint32_t current_time)
	{
		if (proc.state != Finished)
			return;
		double wttime = (double)(proc.setime + proc.watime) / proc.setime;
		std::cout << "[Finished] - Proc ** " << proc.name << " **\n"
			<< "    arrival time: " << proc.artime << " waiting time: "
			<< proc.watime << " finished time: " << current_time + 1 << "\n"
			<< "    turnaround time: " << proc.setime + proc.watime
			<< " weighted turnaround time: " << wttime << "\n";
	}
};

