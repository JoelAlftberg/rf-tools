#include "components/component.h"
#include "components/component_base.h"
#include "components/component_factory.h"

#include "components/lna.h"

#include "toml++/toml.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

namespace components
{

namespace{
ComponentBase readBase(const toml::table& table)
{
	return 
	{
		table["id"].value<std::string>().value(),
		table["type"].value<std::string>().value(),
		table["name"].value_or("")
	};
}
}

using ComponentFactory = std::function<std::unique_ptr<Component>(const toml::table&)>;

static const std::unordered_map<std::string, ComponentFactory> factories
{
	{"lna", [](const toml::table& table) -> std::unique_ptr<Component>
		{
			auto base = readBase(table);
			double gain{table["gain"].value<double>().value()};

			return std::make_unique<LNA>(base, gain);
		}
	},
};

std::unique_ptr<Component> createComponent(const toml::table& table)
{
	std::string type = table["type"].value<std::string>().value();
	auto iter = factories.find(type);
	assert(iter != factories.end());
	return iter->second(table);
}
	
} // namespace components