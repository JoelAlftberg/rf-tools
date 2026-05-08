#pragma once

#include <filesystem>
#include <iostream>
#include <span>

namespace cli
{

enum class Module
{
	Simulation,
	Invalid
};

class CLI
{

public:

	CLI(int argc, char* argv[]);	

	void run();

private:
	void getModule(std::string_view moduleArg);
	
	void runSim();
	void runListModules();

	std::span<char*> arguments_;
	Module module_;
};

}