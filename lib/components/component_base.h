#pragma once

#include <string>
#include <vector>

namespace components
{

struct ComponentBase
{
	std::string id;
	std::string type;
	std::string name;
	std::vector<std::string> inputs;
};
	
} // namespace components
