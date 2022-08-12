#pragma once

namespace hypro {
/*
	// Structure for Options used in running reachability analysis
	struct Options {
		IntersectionMethod_t intersectMethod;
		int testCase;
	};
*/
// Zonotope.h
struct ZonotopeSetting {
	static constexpr unsigned ZONOTOPE_ORDERLIMIT = 4;
};
}  // namespace hypro