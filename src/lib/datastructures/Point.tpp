namespace hypro {
	
	template<typename Number>
	Point<Number>::Point() : mCoordinates()
	{}
	
	template<typename Number>
	Point<Number>::Point(const Number& _value)
	{
		mCoordinates = vector_t<Number>(1);
		mCoordinates(0) = _value;
	}
	
	template<typename Number>
	Point<Number>::Point(std::initializer_list<Number> _coordinates)
	{
		unsigned count = 0;
		mCoordinates = vector_t<Number>(_coordinates.size());
		for(auto& coordinate : _coordinates)
		{
			mCoordinates(count) = Number(coordinate);
			++count;
		}
	}

	template<typename Number>
	Point<Number>::Point(std::vector<Number> _coordinates)
	{
		unsigned count = 0;
		mCoordinates = vector_t<Number>(_coordinates.size());
		for(unsigned j = 0; j < _coordinates.size(); ++j)
		{
			mCoordinates(count) = _coordinates.at(count);
			++count;
		}
	}

	template<typename Number>
	Point<Number>::Point(const coordinateMap& _coordinates) 
	{
		mCoordinates = vector_t<Number>(_coordinates.size());
		for(auto& coordinatepair : _coordinates) {
			mCoordinates(hypro::VariablePool::getInstance().dimension(coordinatepair.first)) = coordinatepair.second;
		}
	}
	
	template<typename Number>
	Point<Number>::Point(const vector_t<Number>& _vector) :
		mCoordinates(_vector)
	{}

	template<typename Number>
	Point<Number>::Point(const Point<Number>& _p) 
	{
		mCoordinates = _p.rawCoordinates();
		for(auto& neighbor : _p.mNeighbors)
		{
			mNeighbors.push_back(neighbor);
		}

		for(auto& composite : _p.mComposedOf)
		{
			mComposedOf.push_back(composite);
		}
	}
	
	template<typename Number>
	std::vector<Point<Number> > Point<Number>::neighbors() const {
		//return mNeighbors;
		//TODO fix (does this have bad side effects?)
		std::vector<Point<Number>> res;
		for (unsigned i =0; i<mNeighbors.size(); ++i) {
			res.push_back( (mNeighbors.at(i)) );
		}
		return res;
	}

	template<typename Number>
	void Point<Number>::setNeighbors(const std::vector<Point<Number> >& _neighbors) {
		mNeighbors = _neighbors;
	}

	template<typename Number>
	void Point<Number>::joinNeighbors(const std::vector<Point<Number> >& _neighbors) {
		for(unsigned i = 0; i<_neighbors.size(); i++){
			if(!isNeighbor(_neighbors.at(i))){
				addNeighbor(_neighbors.at(i));
			}
		}
	}

	template<typename Number>
	void Point<Number>::addNeighbor(const Point<Number>& _neighbor) {
		bool alreadyNeighbor = false;
		for(unsigned i = 0; i< mNeighbors.size(); i++) {
			if(mNeighbors.at(i) == _neighbor){
				alreadyNeighbor = true;
			}
		}
		if(!alreadyNeighbor) {
			mNeighbors.push_back(_neighbor);
		}
	}

	template<typename Number>
	bool Point<Number>::isNeighbor(const Point<Number>& _neighbor) {
		for(unsigned i = 0; i< mNeighbors.size(); i++) {
			if(mNeighbors.at(i) == _neighbor){
				return true;
			}
		}
		return false;
	}

	template<typename Number>
	void Point<Number>::removeNeighbor(const Point<Number>& _neighbor) {
		for(unsigned i = 0; i < mNeighbors.size(); i++){
			if((mNeighbors.at(i)) == (_neighbor)) {
				mNeighbors.erase(mNeighbors.begin() + i);
				break;
			}
		}
	}

	template<typename Number>
	std::vector<Point<Number> > Point<Number>::composedOf() const {
		return mComposedOf;
	}

	template<typename Number>
	void Point<Number>::setComposition(const std::vector<Point<Number> >& _elements) {
		mComposedOf = _elements;
	}

	template<typename Number>
	void Point<Number>::addToComposition(const Point<Number>& _element) {
		mComposedOf.push_back(_element);
	}
	
	template<typename Number>
	Point<Number> Point<Number>::origin() const
	{
		vector_t<Number> coordinates = vector_t<Number>::Zero(this->dimension());
		Point<Number> result = Point<Number>(coordinates);
		return result;
	}
	
	template<typename Number>
	Number Point<Number>::coordinate(const carl::Variable& _var) const
	{
		return mCoordinates(hypro::VariablePool::getInstance().dimension(_var));
	}
	
	template<typename Number>
	Number Point<Number>::coordinate(unsigned _dimension) const
	{
		assert(mCoordinates.size() > _dimension);
		return mCoordinates(_dimension);
	}

	template<typename Number>
	typename Point<Number>::coordinateMap Point<Number>::coordinates() const 
	{
		coordinateMap res;
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i) {
			res.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), mCoordinates(i)));
		}
		return res;
	}

	template<typename Number>
	vector_t<Number> Point<Number>::rawCoordinates() const {
		return mCoordinates;
	}

	template<typename Number>
	void Point<Number>::setCoordinate(const carl::Variable& _dim, const Number& _value)
	{
		unsigned dim = hypro::VariablePool::getInstance().dimension(_dim);
		assert(dim >= 0);
		if(dim >= mCoordinates.rows()) {
			vector_t<Number> old = mCoordinates;
			mCoordinates.resize(dim+1);
			mCoordinates.topLeftCorner(old.rows(),1) = old;
		}
		mCoordinates(dim) = _value;
	}
	
	template<typename Number>
	void Point<Number>::coordinatesFromVector(const vector_t<Number>& vector)
	{
		mCoordinates = vector;
	}

	template<typename Number>
	unsigned Point<Number>::dimension() const 
	{
		return mCoordinates.rows();
	}

	template<typename Number>
	void Point<Number>::reduceDimension(unsigned _dimension) {
		if(_dimension < mCoordinates.rows()){
			vector_t<Number> newCoordinates = vector_t<Number>(_dimension);
			newCoordinates.block(0,0,_dimension,1) = mCoordinates.block(0,0,_dimension,1);
			mCoordinates = newCoordinates;
			std::cout << "Reduced dimension: " << mCoordinates.transpose() << std::endl;
		}
		assert(mCoordinates.rows() <= _dimension);
	}
	
	template<typename Number>
	std::vector<carl::Variable> Point<Number>::variables() const
	{
		std::vector<carl::Variable> variables;
		for(unsigned i = 0; i != mCoordinates.rows(); ++i)
		{
			variables.push_back(hypro::VariablePool::getInstance().carlVarByIndex(i));
		}
		return variables;
	}
	
	template<typename Number>
	Point<Number> Point<Number>::extAdd(const Point<Number>& _rhs) const
	{
		assert(mCoordinates.rows() == _rhs.rawCoordinates().rows());

		Point<Number> result = Point<Number>(mCoordinates + _rhs.rawCoordinates());
		return result;
	}

	template<typename Number>
	Number Point<Number>::distance(const Point<Number>& _rhs) const {
			return ( (mCoordinates - _rhs.rawCoordinates()).norm() );
	}
	
	template<typename Number>
	std::vector<Number> Point<Number>::polarCoordinates( const Point<Number>& _origin,  bool _radians) const
	{
		Point<Number> base = *this - _origin;
		std::vector<Number> result;
		
		// 1st component of the result is the radial part, the following components are the angles.
		Number radialCoordinate = Number(0);
		for(unsigned i = 0; i < base.dimension(); ++i)
		{
			Number square;
			square = pow(base.mCoordinates(i), 2);
			radialCoordinate += square;
		}
		radialCoordinate = sqrt(radialCoordinate);
		result.insert(result.begin(), radialCoordinate);
		
		// compute polar angles
		Number angle;
		for(unsigned dimension = 0; dimension < base.dimension()-1; ++dimension)
		{
			angle = 0;
			for(auto dimension2 = dimension; dimension2 < base.dimension(); ++dimension2)
			{
				Number square;
				square = pow(base.rawCoordinates()(dimension2), 2); // TODO: Check if this does the right thing and why angle += (*dimension) ... does not work
				angle += square;
			}
			angle = sqrt(angle);
			angle = base.mCoordinates(dimension) / angle;
			angle = acos(angle);
			if(!_radians)
			{
				angle /= 2*PI_DN ;
				angle *= 360;
			}
			result.insert(result.end(), angle);
		}
		if((base.mCoordinates(base.dimension()-1)) < Number(0))
		{
			Number tmp = result.back();
			result.pop_back();
			if(!_radians)
			{
				tmp = Number(360) - tmp;
			}
			else
			{
				tmp = -tmp;
			}
			result.push_back(tmp);
		}
		assert(result.size() == this->dimension());
		return result;
	}
	
	template<typename Number>
	Point<Number> Point<Number>::newEmpty() const
	{
		vector_t<Number> origin = vector_t<Number>::Zero(this->dimension());
		return Point<Number>(origin);
	}
	
	template<typename Number>
	bool Point<Number>::move(const Point<Number>& _p) 
	{
		mCoordinates = mCoordinates + _p.rawCoordinates();
		bool negative = false;
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i) {
			if(mCoordinates(i) < 0) {
				negative = true;
				break;
			}
		}
		return negative;
	}

	template<typename Number>
	Point<Number> Point<Number>::linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const
	{
		if(A.cols() == b.rows())
			return Point<Number>(A*mCoordinates + b);
		else
			return Point<Number>(A*mCoordinates);
	}

	template<typename Number>
	Number Point<Number>::sum() const {
		Number sum = mCoordinates.dot(vector_t<Number>::One(mCoordinates.rows()));
		return sum;
	}

	template<typename Number>
	void Point<Number>::incrementInFixedDim(const carl::Variable& _d) {
		mCoordinates(hypro::VariablePool::getInstance().dimension(_d)) += 1;
	}
	
	template<typename Number>
	void Point<Number>::incrementInFixedDim(unsigned _d) {
		mCoordinates(_d) += 1;
	}

	template<typename Number>
	void Point<Number>::incrementInAllDim(const Number& _val)
	{
		vector_t<Number> one = vector_t<Number>::Ones(mCoordinates.rows());
		one *= _val;
		mCoordinates += one;
	}

	template<typename Number>
	void Point<Number>::decrementInFixedDim(const carl::Variable& _d)
	{
		mCoordinates(hypro::VariablePool::getInstance().dimension(_d)) -= 1;
	}
	
	template<typename Number>
	void Point<Number>::decrementInFixedDim(unsigned _d)
	{
		mCoordinates(_d) -= 1;
	}

	template<typename Number>
	Point<Number> Point<Number>::getPredecessorInDimension(const carl::Variable& _d) const
	{
		Point<Number> pred = Point<Number>(*this);
		pred.decrementInFixedDim(_d);
		return pred;
	}
	
	template<typename Number>
	Point<Number> Point<Number>::getPredecessorInDimension(unsigned _d) const
	{
		Point<Number> pred = Point<Number>(*this);
		pred.decrementInFixedDim(_d);
		return pred;
	}
	 
	template<typename Number>
	bool Point<Number>::isInBoundary(const Point<Number>& _boundary) const 
	{
		return (mCoordinates < _boundary.rawCoordinates());
	}

	template<typename Number>
	bool Point<Number>::hasDimension(const carl::Variable& _i) const
	{
		return (mCoordinates.rows() > hypro::VariablePool::getInstance().dimension(_i));
	}
	
	template<typename Number>
	bool Point<Number>::hasDimensions(const std::vector<carl::Variable>& _variables) const
	{
		for (auto it : _variables) {
			if (!hasDimension(it)) return false;
		}
		return true;
	}

	template<typename Number>
	bool Point<Number>::haveEqualCoordinate(const Point<Number>& _p2) const 
	{
		if( dimension() == _p2.dimension() )
		{
			for (unsigned i = 0 ; i < mCoordinates.rows(); ++i)
			{
				if ( mCoordinates(i) == _p2.rawCoordinates()(i) ) return true;
			}
		}
		return false;
	}
	
	template<typename Number>
	bool Point<Number>::haveSameDimensions(const Point<Number>& _p) const
	{
		return (dimension() == _p.dimension());
	}
	
	template<typename Number>
	Point<Number>& Point<Number>::operator+=(const Point<Number>& _rhs)
	{
		assert(this->dimension() == _rhs.dimension());
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
		{
			mCoordinates(i) += _rhs.at(i); 
		}
		return *this;
	}
	
	template<typename Number>
	Point<Number>& Point<Number>::operator-=(const Point<Number>& _rhs)
	{
		assert(this->dimension() == _rhs.dimension());
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
		{
			mCoordinates(i) -= _rhs.at(i);
		}
		return *this;
	}
	
	template<typename Number>
	Point<Number>& Point<Number>::operator/=(unsigned _quotient)
	{
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
		{
			mCoordinates(i) = mCoordinates(i)/_quotient;
		}
		return *this;
	}
	
	template<typename Number>
	Point<Number>& Point<Number>::operator*=(const Number _factor)
	{
		for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
		{
			mCoordinates(i) = mCoordinates(i)*_factor;
		}
		return *this;
	}

	template<typename Number>
	Number& Point<Number>::operator[] (const carl::Variable& _i)
	{
		unsigned dim = hypro::VariablePool::getInstance().dimension(_i);
		if(dim >= mCoordinates.rows()) {
			vector_t<Number> old = mCoordinates;
			mCoordinates.resize(dim+1);
			mCoordinates.topLeftCorner(old.rows(),1) = old;
		}
		return mCoordinates(dim);
	}
	
	template<typename Number>
	Number& Point<Number>::operator[] (unsigned _i)
	{
		if(_i >= mCoordinates.rows()) {
			vector_t<Number> old = mCoordinates;
			mCoordinates.resize(_i+1);
			mCoordinates.topLeftCorner(old.rows(),1) = old;
		}
		return mCoordinates(_i);
	}

	template<typename Number>
	Number Point<Number>::at(const carl::Variable& _i) const
	{
		assert(hypro::VariablePool::getInstance().dimension(_i) < mCoordinates.rows());
		return mCoordinates(hypro::VariablePool::getInstance().dimension(_i));
	}
	
	template<typename Number>
	Number Point<Number>::at(unsigned _index) const {
		assert(_index < mCoordinates.rows());
		return mCoordinates(_index);
	}
} // namespace
