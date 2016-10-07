/**
 * Example file for polytope size.
 * Compute the size and perform the executable with massif-valgrind
 *
 */

 #include "../src/hypro/datastructures/Halfspace.h"
 #include "../src/hypro/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;
  unsigned dim = 4;
  unsigned amountOfFacets = 500;

  std::cout << "Example_massif with dimension " << dim << " and facets from " << amountOfFacets << std::endl;

  HPolytope<Number> test_massif, test_massif2, test_massif3, test_massif4;
  std::vector<vector_t<Number>> directions = computeTemplate<Number>(dim,amountOfFacets);

  for(vector_t<Number> direction: directions){
    test_massif.insert(Halfspace<Number>(direction, 1));
  }

  double sizeOfHPolytope = test_massif.sizeOfHPolytope();
  double size = test_massif.size();

  std::cout << "Size of test_massif before reduction is " << sizeOfHPolytope << " and amount of facets is " << size << std::endl;

  return 0;
}
