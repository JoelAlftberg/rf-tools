#pragma once

#include "components/component.h"
#include "components/component_base.h"
#include "frequency_range.h"
#include "freq_point.h"
#include "rf_signal.h"

#include <cassert>
#include <string>
#include <vector>

namespace components
{

struct LNASpec
{
	std::vector<rf::FreqPoint> gain;
	std::vector<rf::FreqPoint> noiseFigure;
	std::vector<rf::FreqPoint> oip3;
	rf::FrequencyRange freqRange;
};

class LNA : public Component
{

public:

	LNA(ComponentBase base, LNASpec spec)
		: Component(base)
		, spec_{spec}
	{}

	std::vector<rf::Signal> process(const std::vector<rf::Signal>& input) override
	{
		assert(!input.empty());
		rf::Signal output{input[0]};
		return {output};
	}

private:
	LNASpec spec_;

};
	
} // namespace components
