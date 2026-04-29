#pragma once

#include "components/component.h"

#include "toml++/toml.hpp"

#include <memory>

namespace components
{

std::unique_ptr<components::Component> createComponent(const toml::table& table);
	
} // namespace components
