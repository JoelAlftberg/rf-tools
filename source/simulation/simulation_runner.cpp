#include "simulation/simulation_model.h"
#include "simulation/simulation_runner.h"
#include "rf_signal.h"

namespace simulation
{

void SimulationRunner::run()
{

    model_.buildExecutionOrder();  
    std::vector<std::string> executionOrder = model_.executionOrder(); 

    for (const auto& id : executionOrder)
    {
        rf::Signal* signal = model_.getSignal(id);
        if (nullptr != signal)
        {
            intermediateSignals_.emplace(id, *signal);
            continue;
        }
        components::Component* component = model_.getComponent(id);
        assert(component != nullptr);

        std::vector<rf::Signal> inputs; 
        for (const auto& inputId : component->inputs()) 
        {
            auto it = intermediateSignals_.find(inputId);
            if (it != intermediateSignals_.end())
            {
                inputs.push_back(it->second);
            }
        }

        std::vector<rf::Signal> outputs{component->process(inputs)};
        for (auto& signal : outputs)
        {
            intermediateSignals_.emplace(id, signal);    
        }

    }

    for (const auto& id : model_.observers())
    {
        auto it = intermediateSignals_.find(id);  
        if (it != intermediateSignals_.end())
        {
            outputs_.emplace(id, it->second);
        }
    }
}

} // namespace simulation
