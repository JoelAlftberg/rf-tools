#pragma once

#include "components/component.h"
#include "rf_signal.h"
#include "simulation/simulation_model.h"
#include <cassert>

namespace simulation
{

class SimulationRunner
{

public:
	
	SimulationRunner(SimulationModel& simModel)
		: model_{simModel}
	{}
    
    void run();


private:
	SimulationModel& model_;
    std::unordered_map<std::string, rf::Signal> intermediateSignals_;
    std::unordered_map<std::string, rf::Signal> outputs_;
};
	
} // namespace simulation
