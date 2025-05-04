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
	js::Scheduler scheduler;

	std::string strategyType = argv[1];
	std::string filepath = argv[2];
	
	try
	{
		scheduler.setStrategy(js::StrategyFactory::CreateStrategy(strategyType));
		scheduler.loadFromFile(filepath);
		scheduler.addObserver(std::make_shared<js::JobLogger>());
		scheduler.addObserver(std::make_shared<js::JobFinishLogger>());
		scheduler.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
	}

	return 0;
}



