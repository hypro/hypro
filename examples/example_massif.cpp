/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/lib/datastructures/Hyperplane.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;
  unsigned dim = 5;
  unsigned amountOfFacets = 6;
  unsigned amountOfReducedFacets = 4;

  std::cout << "Example_massif with dimension " << dim << " and facets from " << amountOfFacets << " to " << amountOfReducedFacets << std::endl;

	/* Do stuff here */

  // HPolytopes Examples
  HPolytope<Number> test_massif, test_massif2, test_massif3, test_massif4;
  std::vector<vector_t<Number>> directions = test_massif.computeTemplate(dim,amountOfFacets);


  for(vector_t<Number> direction: directions){
    test_massif.insert(Hyperplane<Number>(direction, 1));
  }


  //HPolytope<Number> test_massif2 = test_massif;
  //std::cout << "Size of test_massif is " << test_massif.size() << std::endl;


  //while(test_massif.size()>0){
  //  test_massif.erase(0);
  //}
  double sizeOfHPolytopeBefore = test_massif.sizeOfHPolytope();
  double sizeBefore = test_massif.size();

  std::cout << "Size of test_massif before reduction is " << sizeOfHPolytopeBefore << " and amount of facets is " << sizeBefore << std::endl;

  test_massif = test_massif.reduce_directed(test_massif.computeTemplate(dim,amountOfReducedFacets), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

  double sizeOfHPolytopeAfter = test_massif.sizeOfHPolytope();
  double sizeAfter = test_massif.size();

  double relationSize = sizeBefore/sizeAfter;
  double relationSizeOfHPoly = sizeOfHPolytopeBefore/sizeOfHPolytopeAfter;

  std::cout << "Size of test_massif after reduction is " << sizeOfHPolytopeAfter << " and amount of facets is " << sizeAfter << std::endl << std::endl;
  std::cout << "Relation fo size: " << relationSize << ", relation of polySize: " << relationSizeOfHPoly << " and relation of relations: " <<  relationSize/relationSizeOfHPoly << std::endl;

  return 0;
}
