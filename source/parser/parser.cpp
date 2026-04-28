#include "components/component_factory.h"
#include "parser/parser.h"
#include "simulation/simulation_model.h"

#include <iostream>

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
		std::string id = component["id"].value<std::string>().value();
		std::string type = component["type"].value<std::string>().value();
		std::string name = component["name"].value_or("");

		simModel.addComponent(components::createComponent(table));
	}
	
	return simModel;
}
	
} // namespace parser
