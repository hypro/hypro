#pragma once

#include "Settings.h"

#include <vector>

namespace hypro {

struct Strategy {
	std::vector<AnalysisParameters> Settings{};
};

}  // namespace hypro
