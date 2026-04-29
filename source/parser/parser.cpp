#include "components/component_factory.h"
#include "parser/parser.h"
#include "simulation/simulation_model.h"

#include <filesystem>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <toml++/toml.hpp>

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
	

	if (nullptr == table["component"].as_array())
	{
		std::cerr << "No components in configuration" << "\n";
		return simModel;
	}

	if (nullptr == table["signal"].as_array())
	{
		std::cerr << "No signal in configuration" << "\n";
		return simModel;
	}

	if (nullptr == table["output"].as_table())
	{
		std::cerr << "No output in configuration" << "\n";
		return simModel;
	}

	auto& components{*table["component"].as_array()};

	for (auto& element : components)
	{
		const auto& component{*element.as_table()};
		toml::table merged{component};

		if (nullptr != component["part"].as_string())
		{
			std::string componentType{component["type"].value<std::string>().value()};
			std::string partName{component["part"].value<std::string>().value()};

			toml::table part{readPartFile(componentType, partName)};
			
			for (auto& [key, value] : part)
			{
				merged.insert(key, value);
			}
		}
		
		simModel.addComponent(components::createComponent(merged));
	}

	auto& signals{*table["signal"].as_array()};

	for (auto& element : signals)
	{
		const auto& signalTable{*element.as_table()};

		std::string id{signalTable["id"].value<std::string>().value()};
		double frequency{signalTable["frequency"].value<double>().value()};
		double power{signalTable["power"].value<double>().value()};

		simModel.addSignal(std::make_unique<rf::Signal>(id, frequency, power));
	}

	const auto& outputTable{*table["output"].as_table()};

	const auto&  observes{*outputTable["observe"].as_array()};

	for ( auto& element : observes)
	{
		simModel.addObserver(element.value<std::string>().value());
	}

	return simModel;
}

toml::table readPartFile(const std::string& componentType, const std::string& partName)
{
	std::filesystem::path partPath{std::format("parts/{}/{}.toml", componentType, partName)};
	
	if (!std::filesystem::is_regular_file(partPath))
	{
		throw std::runtime_error(std::format("Part '{}' not found for component of type '{}", partName, componentType));
	}

	return toml::parse_file(partPath.string());
}
	
} // namespace parser
