#pragma once

#include "components/component.h"
#include "rf_signal.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>

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

components::Component* getComponent(std::string id)
{
    auto it = components_.find(id);
    if (it != components_.end())
    {
        return it->second.get();
    }
    return nullptr;
}

rf::Signal* getSignal(std::string id)
{
    auto it = signals_.find(id);
    if (it != signals_.end())
    {
        return it->second.get();
    }
    return nullptr;
}

void buildExecutionOrder()
{

    std::unordered_map<std::string, int> degree;
    std::unordered_map<std::string, std::vector<std::string>> dependents;

    for (const auto& [id, component] : components_)
    {
        if (!degree.count(id)) degree[id] = 0;
        for (const auto& input : component->inputs())
        {
            dependents[input].push_back(id);
            degree[id]++;
        }
    }

    std::queue<std::string> buildQueue; 
    for (const auto& [id, signal] : signals_)
    {
        degree[id] = 0;
        buildQueue.push(id);
    }
    
    while (!buildQueue.empty())
    {
        std::string current = buildQueue.front();
        buildQueue.pop();

        executionOrder_.push_back(current);
        
        for (const auto& dependent : dependents[current])
        {
            degree[dependent]--;
            if (degree[dependent] == 0)
            {
                buildQueue.push(dependent);
            }
        }
    }
}

const std::vector<std::string>& executionOrder()
{
    return executionOrder_;
}

const std::vector<std::string>& observers()
{
    return observers_;
}

private:
	std::unordered_map<std::string, std::unique_ptr<rf::Signal>> signals_;
	std::unordered_map<std::string, std::unique_ptr<components::Component>> components_;
	std::vector<std::string> executionOrder_;
	std::vector<std::string>  observers_;
};

} // namespace simulation
