#include "components/component.h"
#include "components/component_base.h"
#include "components/component_factory.h"
#include "components/lna.h"

#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <toml++/toml.hpp>
#include <unordered_map>

namespace components
{

namespace
{

std::vector<rf::FreqPoint> readFreqPointsOrScalar(const toml::table& table, std::string_view key);

ComponentBase readBase(const toml::table& table)
{
	std::vector<std::string> inputs;

	if (nullptr != table["inputs"].as_array())
	{
		for (auto& input : *table["inputs"].as_array())
		{
			inputs.push_back(input.value<std::string>().value());
		}
	}

	return 
	{
		table["id"].value<std::string>().value(),
		table["type"].value<std::string>().value(),
		table["name"].value_or(""),
		inputs,
	};
}

rf::FrequencyRange readFreqRange(const toml::table& table)
{
	rf::FrequencyRange range;

	if (nullptr != table["freq_range"].as_array())
	{
		auto* rangeTable{table["freq_range"].as_array()};
		
		if (rangeTable->size() != 2)
		{
			throw std::runtime_error("freq_range must have exactly two values: [min, max]");
		}

		range.low 	= (*rangeTable)[0].value<double>().value();
		range.high 	= (*rangeTable)[1].value<double>().value();
	}

	return range;
}

std::vector<rf::FreqPoint> parseFreqPoints(const toml::array& array, std::string_view valueKey)
{
	std::vector<rf::FreqPoint> points;

	for (auto& element : array)
	{
		rf::FreqPoint point;
		auto* pointTable = element.as_table();
		
		if (nullptr == pointTable)
		{
			throw std::runtime_error(std::format("Invalid frequency point"));
		}

		double freq{(*pointTable)["freq"].value<double>().value()};
		double value{(*pointTable)[valueKey].value<double>().value()};

		point.frequency = freq;
		point.value 	= value;

		points.push_back(point);
	}

	return points;
}

std::vector<rf::FreqPoint> readFreqPointsOrScalar(const toml::table& table, std::string_view key)
{
	std::vector<rf::FreqPoint> points;

	if (table[key].is_number())
	{
		double value{table[key].value<double>().value()};
		rf::FreqPoint freqPoint{0.0, value};

		points.push_back(freqPoint);
	}
	else if (table[key].is_array())
	{
		points = parseFreqPoints(*table[key].as_array(), key);
	}
	else
	{
		throw std::runtime_error(std::format("No '{}' specified for component '{}'.", key, table["id"].value<std::string>().value()));
	}

	return points;
}

LNASpec readLNASpec(const toml::table& table)
{
	LNASpec spec;

	spec.freqRange		= readFreqRange(table);
	spec.gain 			= readFreqPointsOrScalar(table, "gain");
	spec.noiseFigure 	= readFreqPointsOrScalar(table, "noise_figure");
	spec.oip3 			= readFreqPointsOrScalar(table, "oip3");

	return spec;
}

} // anonymous namespace

using ComponentFactory = std::function<std::unique_ptr<Component>(const toml::table&)>;

static const std::unordered_map<std::string, ComponentFactory> factories
{
	{"lna", [](const toml::table& table) -> std::unique_ptr<Component>
		{
			auto 	base{readBase(table)};
			LNASpec spec{readLNASpec(table)};
			return std::make_unique<LNA>(base, spec);
		}
	},
};

std::unique_ptr<Component> createComponent(const toml::table& table)
{
	std::string type = table["type"].value<std::string>().value();
	auto iter = factories.find(type);

	if (iter == factories.end())
	{
		throw std::runtime_error(std::format("Factory missing for type '{}'", iter->first));
	}
	return iter->second(table);
}
	
} // namespace components