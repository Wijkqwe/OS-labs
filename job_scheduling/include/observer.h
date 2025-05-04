#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

#include "job.h"

namespace js
{
class Observer
{
public:
	//: pure virtual function
	virtual void onstatechange(Job& job, uint32_t current_time) = 0; 
};
class JobLogger : public Observer
{
public:
	void onstatechange(Job& job, uint32_t current_time) override;
};
class JobFinishLogger : public Observer
{
public:
	void onstatechange(Job& job, uint32_t current_time) override;
};
}; //: namespace js

#endif
