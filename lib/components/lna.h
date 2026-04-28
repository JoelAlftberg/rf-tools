#pragma once

#include "components/component.h"
#include "components/component_base.h"
#include "frequency_range.h"
#include "rf_signal.h"

#include <cassert>
#include <string>
#include <vector>

namespace components
{

class LNA : public Component
{

public:

	LNA(ComponentBase base, double gain)
	: Component(base)
	, gain_{gain}
	{}

	std::vector<rf::Signal> process(const std::vector<rf::Signal>& input) override
	{
		assert(!input.empty());
		rf::Signal output{input[0]};
		output.setPower(output.power() + gain_); 
		return {output};
	}

private:
	double gain_;

};
	
} // namespace components
