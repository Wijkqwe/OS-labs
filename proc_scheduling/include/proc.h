#pragma once
#ifndef PROC_H
#define PROC_H

#include <cstdint>
#include <string>

namespace ps
{
	enum Procstate
	{
		Waiting,
		Running,
		Finished
	};

	struct Proc
	{
		std::string name;
		enum Procstate state;
		uint32_t artime; //: arrival_time
		uint32_t setime; //: service_time
		uint32_t watime; //: waiting_time
		uint32_t retime; //: remain_time
		uint32_t priority; //: small==high

		Proc(const std::string& na, enum Procstate st, 
			uint32_t ar, uint32_t se, uint32_t wa, uint32_t re, uint32_t pr) 
			: name(na), state(st), artime(ar), setime(se), 
				watime(wa), retime(re), priority(pr) {}
		//: Delegating Constructor
		Proc(const std::string& na, uint32_t ar, uint32_t se, uint32_t pr) 
			: Proc(na, Waiting, ar, se, 0, se, pr) {}
	};
} //: namespace ps

#endif
