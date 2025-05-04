#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

#include "proc.h"

namespace ps
{
class Observer
{
public:
	//: pure virtual function
	virtual void onstatechange(Proc& proc, uint32_t current_time) = 0; 
};
class ProcLogger : public Observer
{
public:
	void onstatechange(Proc& proc, uint32_t current_time) override;
};
class ProcFinishLogger : public Observer
{
public:
	void onstatechange(Proc& proc, uint32_t current_time) override;
};
}; //: namespace ps

#endif
