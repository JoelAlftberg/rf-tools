#pragma once

#include "components/component.h"
#include "rf_signal.h"

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
	components_[component->id()] = std::move(component);
}

void addSignal(std::unique_ptr<rf::Signal> signal)
{
	signals_[signal->id()] = std::move(signal);
}

void buildExecutionOrder()
{

}


private:
	std::unordered_map<std::string, std::unique_ptr<rf::Signal>> signals_;
	std::unordered_map<std::string, std::unique_ptr<components::Component>> components_;
	std::vector<std::string> executionOrder_;
};

} // namespace simulation
