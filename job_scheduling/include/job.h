#pragma once
#ifndef JOB_H
#define JOB_H

#include <cstdint>
#include <string>

namespace js
{
	enum Jobstate
	{
		Waiting,
		Running,
		Finished
	};

	struct Job
	{
		std::string name;
		enum Jobstate state;
		uint32_t artime; //: arrival_time
		uint32_t setime; //: service_time
		uint32_t watime; //: waiting_time
		uint32_t retime; //: remain_time

		Job(const std::string& na, enum Jobstate st, 
			uint32_t ar, uint32_t se, uint32_t wa, uint32_t re) 
			: name(na), state(st), artime(ar), setime(se), watime(wa), retime(re) {}
		//: Delegating Constructor
		Job(const std::string& na, uint32_t ar, uint32_t se) 
			: Job(na, Waiting, ar, se, 0, se) {}
	};
} //: namespace js

#endif
