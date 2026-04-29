#include "cli/cli.h"
#include "parser/parser.h"
#include "simulation/simulation_model.h"
#include "simulation/simulation_runner.h"

#include <string>

namespace cli
{

CLI::CLI(int argc, char* argv[])
	: arguments_{argv, static_cast<size_t>(argc)}
{

	if (argc < 2)
	{
		std::cerr << "check rf-tools --help" << "\n";
		exit(1);
	}

	std::string_view moduleCommand{argv[1]};

	getModule(moduleCommand);
}

void CLI::getModule(std::string_view moduleArg)
{
	if ("sim" == moduleArg)
	{
		module_ = Module::Simulation;
	}
	else
	{
		module_ = Module::Invalid;
	}
}

void CLI::run()
{
	switch(module_)
	{
		case Module::Simulation:
		{
			runSim();
			break;
		}
		case Module::Invalid:
		{
			runListModules();
			break;
		}
	}
}

void CLI::runSim()
{
	if (arguments_.size() < 3)
	{
		std::cout << "printHelp(Module::Simulation)" << "\n";
		//printHelp(Module::Simulation);
		exit(1);
	}

	std::string modelFile{};
	std::string outputFile{};
	bool verbose{false};

	for (size_t i{2U}; i < arguments_.size(); ++i)
	{
		std::string_view arg{arguments_[i]};
		if ("--model" == arg or "-m" == arg)
		{
			if (i + 1 < arguments_.size())
			{
				modelFile = std::string_view{arguments_[++i]};
			}
		}
		if ("--output" == arg or "-o" == arg)
		{
			if (i + 1 < arguments_.size())
			{
				outputFile = std::string_view{arguments_[++i]};
			}
		}
		if ("--verbose" == arg or "-v" == arg)
		{
			verbose = true;
		}
	}

	if (modelFile.empty())
	{
		std::cout << "No model specified." << "\n";
		std::cout << "Use --model=<model.toml> to specify a model to simulate" << "\n";
		exit(1);
	}
	if (outputFile.empty()) { outputFile = "output.csv"; }

	simulation::SimulationModel simModel{parser::parse(modelFile)};

	simulation::SimulationRunner runner{simModel};

	if (verbose)
	{ 
		std::cout << "Model file: " << modelFile << "\n";
		std::cout << "Output file: " << outputFile << "\n";
		std::cout << "Parsed simulation model from " << modelFile << "\n";
		simModel.print(); 
	}

	runner.run();

}

void CLI::runListModules()
{
	std::cout << "Usage: rf-tools <module>" << "\n\n";
	std::cout << "Available modules:" << "\n";
	std::cout << " * sim" << "\n";
	exit(0);
}

	
} // namespace cli
