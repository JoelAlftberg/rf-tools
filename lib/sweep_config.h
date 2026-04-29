#pragma once

#include "lib/frequency_range.h"
#include "lib/parameter.h"

namespace rf
{

struct SweepConfig
{
	double stepCount;
	double stepSize;
	Parameter param;
	double startValue;
	double stopValue;
};

} // namespace rf