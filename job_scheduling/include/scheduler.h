#pragma once
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "job.h"
#include "observer.h"
#include "strategy.h"

namespace js
{
class Scheduler
{
private:
	std::vector<Job> jobs;
	std::unique_ptr<Strategy> strategy;
	std::vector<std::shared_ptr<Observer>> observers;
	uint32_t current_time;
	void notifyObservers(Job& job);
public:
	Scheduler();

	void setStrategy(std::unique_ptr<Strategy> newstrategy);
	void addObserver(std::shared_ptr<Observer> observer);
    void run();
    void printStatistics() const;
    void loadFromFile(const std::string& filepath);
};
}; //: namespace js

#endif
