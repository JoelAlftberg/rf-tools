#pragma once

#include "simulation/simulation_model.h"
#include "toml++/toml.hpp"

#include <iostream>

namespace parser
{

class Parser
{

public:

	simulation::SimulationModel parse(const std::string_view path);

private:
	
};
	
} // namespace parser
