/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/lib/util/Plotter.h"
 #include "../src/lib/datastructures/Hyperplane.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
 #include "../src/lib/representations/volumeApproximation.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;

	/* Do stuff here */

  // HPolytopes Examples
  HPolytope<Number> test_massif;
  std::vector<vector_t<Number>> directions = test_massif.computeTemplate(2,1000);

  for(vector_t<Number> direction: directions){
    test_massif.insert(Hyperplane<Number>(direction, 1));
  }

  HPolytope<Number> test_massif2 = test_massif;
  //std::cout << "Size of test_massif is " << test_massif.size() << std::endl;

  //test_massif = test_massif.reduce_directed(test_massif.computeTemplate(2,50), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

  //std::cout << "Size of test_massif after reduction is " << test_massif.size() << std::endl;
  return 0;
}
