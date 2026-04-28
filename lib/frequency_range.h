#pragma once

namespace rf
{

struct FrequencyRange
{
	double low;
	double high;
	
	double bandwidth() const
	{
		return high - low;
	}

	double centerFreq() const
	{
		return low + ((high - low) / 2);
	}
};
	
} // namespace rf


