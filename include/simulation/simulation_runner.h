#pragma once

#include "simulation/simulation_model.h"

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

};
	
} // namespace simulation
