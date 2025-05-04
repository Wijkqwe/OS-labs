#pragma once
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "proc.h"
#include "observer.h"
#include "strategy.h"

namespace ps
{
class Scheduler
{
private:
	std::vector<Proc> procs;
	std::unique_ptr<Strategy> strategy;
	std::vector<std::shared_ptr<Observer>> observers;
	uint32_t current_time;
	void notifyObservers(Proc& proc);
public:
	Scheduler();

	void setStrategy(std::unique_ptr<Strategy> newstrategy);
	void addObserver(std::shared_ptr<Observer> observer);
    void run();
    void printStatistics() const;
    void loadFromFile(const std::string& filepath);
};
}; //: namespace ps

#endif
