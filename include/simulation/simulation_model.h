#pragma once

#include "components/component.h"
#include "rf_signal.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace simulation
{

class SimulationModel
{

public:

void print()
{
	for (const auto& [id, component] : components_)
	{
		std::cout << "Component: " << id << "\n";
	}

	for (const auto& [id, signal] : signals_)
	{
		std::cout << "Signal: " << id << "\n";
	}

	for (const auto& observer : observers_)
	{
		std::cout << "Observer: " << observer << "\n";
	}
}

void addComponent(std::unique_ptr<components::Component> component)
{
	components_[component->id()] = std::move(component);
}

void addSignal(std::unique_ptr<rf::Signal> signal)
{
	signals_[signal->id()] = std::move(signal);
}

void addObserver(std::string id)
{
	observers_.push_back(id);
}

void buildExecutionOrder()
{

}

private:
	std::unordered_map<std::string, std::unique_ptr<rf::Signal>> signals_;
	std::unordered_map<std::string, std::unique_ptr<components::Component>> components_;
	std::vector<std::string> executionOrder_;
	std::vector<std::string>  observers_;
};

} // namespace simulation
