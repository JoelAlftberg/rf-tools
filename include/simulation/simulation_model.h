#pragma once

#include "components/component.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace simulation
{

class SimulationModel
{

public:
	void addComponent(std::unique_ptr<components::Component> component)
	{
		components_.push_back(std::move(component));
	}

private:
	std::vector<std::unique_ptr<components::Component>> components_;
	
};

} // namespace simulation
