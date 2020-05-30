#pragma once

#include "adapt.h"

struct Plugin {
	virtual void register_adapters() = 0;
};
