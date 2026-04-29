#pragma once

#include "parameter.h"

namespace rf
{

class Signal
{

public:

	Signal(std::string id, double frequency, double power)
	: id_{id}
	, frequency_{frequency_}
	, power_{power} 
	{}

	double power() const
	{
		return power_;
	}

	void setPower(double power)
	{
		power_ = power;
	}

	const std::string& id()
	{
		return id_;
	}


private:
	std::string id_;
	double frequency_{0.0};
	double power_{0.0};
};

}