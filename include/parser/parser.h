#pragma once

#include "simulation/simulation_model.h"
#include "toml++/toml.hpp"

#include <iostream>

namespace parser
{

simulation::SimulationModel parse(const std::string_view path);
toml::table readPartFile(const std::string& partName, const std::string& componentType);

} // namespace parser
