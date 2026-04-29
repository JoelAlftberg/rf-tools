#include "components/component_factory.h"
#include "parser/parser.h"
#include "simulation/simulation_model.h"

#include <iostream>
#include <memory>

namespace parser
{

simulation::SimulationModel parse(const std::string_view path)
{
	toml::table table{};
	simulation::SimulationModel simModel{};

	try
	{
		table = toml::parse_file(path);
	}
	catch(const toml::parse_error& err)
	{
		std::cerr << err.what() << '\n';
	}
	
	auto& components{*table["component"].as_array()};

	for (auto& element : components)
	{
		const auto& component{*element.as_table()};

		simModel.addComponent(components::createComponent(component));
	}

	auto& signals{*table["signal"].as_array()};

	for (auto & element : signals)
	{
		const auto& signalTable{*element.as_table()};

		std::string id{signalTable["id"].value<std::string>().value()};
		double frequency{signalTable["frequency"].value<double>().value()};
		double power{signalTable["power"].value<double>().value()};

		simModel.addSignal(std::make_unique<rf::Signal>(id, frequency, power));
	}
	
	return simModel;
}
	
} // namespace parser
