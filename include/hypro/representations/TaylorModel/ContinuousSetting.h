#pragma once

namespace hypro {

// TaylorModel/continous
struct UtilSetting {
	static constexpr unsigned MAX_ITER_NUM = 50;
	static constexpr float STOP_RATIO = 0.99f;
};

}  // namespace hypro