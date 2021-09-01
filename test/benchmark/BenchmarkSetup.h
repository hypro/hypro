/**
 * File that holds the struct containing information about the benchmark, which is to be generated
 * @file BenchmarkSetup.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

namespace hypro {
template <typename Number>
struct BenchmarkSetup {
	unsigned size;
	unsigned vertices;
	unsigned dimension;
	Number minValue;
	Number maxValue;
};
}  // namespace hypro