#include "simulation/simulation_model.h"
#include "simulation/simulation_runner.h"

namespace simulation
{

void SimulationRunner::run()
{
	model_.buildExecutionOrder();
}

} // namespace simulation
