#include <memory>
#include "iostream"
#include "scheduler.h"

signed main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "error" << std::endl;
		return 0;
	}
	ps::Scheduler scheduler;

	std::string strategyType = argv[1];
	std::string filepath = argv[2];
	
	try
	{
		scheduler.setStrategy(ps::StrategyFactory::CreateStrategy(strategyType));
		scheduler.loadFromFile(filepath);
		scheduler.addObserver(std::make_shared<ps::ProcLogger>());
		scheduler.addObserver(std::make_shared<ps::ProcFinishLogger>());
		scheduler.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
	}

	return 0;
}



