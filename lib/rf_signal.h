#pragma once

#include "parameter.h"

namespace rf
{

class Signal
{

public:

	double power() const
	{
		return power_;
	}

	void setPower(double power)
	{
		power_ = power;
	}


private:
	double frequency_{0.0};
	double power_{0.0};
};

}