namespace hypro {

/*
* Compute a uniform distribution of directions for a dimension-dimensional space template polytope
*/
#define PI 3.14159265359
template<typename Number>
static std::vector<vector_t<Number>> computeTemplate(unsigned dimension, unsigned numberDirections) {
	double degree = (360/ (double) numberDirections)* PI / 180.0;
	std::vector<vector_t<Number>> directions, directions2d;

	//create directions2d
	vector_t<Number> templateVector2d = vector_t<Number>::Zero(2); // init templateVector2d
	templateVector2d(0) = 1;
	templateVector2d(1) = 0;
	directions2d.push_back(templateVector2d);

	matrix_t<Number> m(2, 2); //init matrix
	m(0,0) = carl::rationalize<Number>(cos(degree));
	m(0,1) = carl::rationalize<Number>((-1)*sin(degree));
	m(1,0) = carl::rationalize<Number>(sin(degree));
	m(1,1) = carl::rationalize<Number>(cos(degree));

	for(unsigned i=0; i<(numberDirections-1); ++i) {
		//Rotate templateVector
		templateVector2d = m * templateVector2d;
		directions2d.push_back(templateVector2d);
	}

	//copy directions2d into directions
	polytope::dPermutator permutator(dimension, 2);
	std::vector<unsigned> permutation;
	while(!permutator.end()) {
		permutation = permutator();
		for(vector_t<Number> vectorOfdirections2d: directions2d) {
			vector_t<Number> templateVector = vector_t<Number>::Zero(dimension); // init templateVector

			templateVector(permutation.at(0)) = vectorOfdirections2d(0);
			templateVector(permutation.at(1)) = vectorOfdirections2d(1);

			if(std::find(directions.begin(), directions.end(), templateVector)== directions.end()) directions.push_back(templateVector);
		}
	}

	return directions;
}

} // namespace hypro
