#pragma once

#include "components/component_base.h"
#include "rf_signal.h"

#include <string>
#include <vector>

namespace components
{

class Component 
{

public:

	Component(ComponentBase base)
		: id_{base.id}
		, type_{base.type}
		, name_{base.name}
	{}

	virtual ~Component() = default;

	virtual std::vector<rf::Signal> process(const std::vector<rf::Signal>& input) = 0;

	std::string& name() const
	{
		return name_;
	}

private:
	std::string id_;
	std::string type_;
	std::string name_;

};

}