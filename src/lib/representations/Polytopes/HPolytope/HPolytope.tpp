#include "HPolytope.h"
namespace hypro
{
	template<typename Number>
	HPolytope<Number>::HPolytope() :
	mHPlanes(),
	mFanSet(false),
	mFan(),
	mDimension(0),
	mInitialized(false)
	{}

	template<typename Number>
	HPolytope<Number>::HPolytope(const HPolytope& orig) :
	mHPlanes(),
	mFanSet(orig.mFanSet),
	mFan(orig.mFan),
	mDimension(orig.mDimension),
	mInitialized(false)
	{
		for(const auto& plane : orig.constraints()) {
			mHPlanes.push_back(plane);
		}
	}

	template<typename Number>
	HPolytope<Number>::HPolytope(const Hyperplane<Number>& plane) :
		mHPlanes({plane}),
		mFanSet(false),
		mFan(),
		mDimension(plane.dimension()),
		mInitialized(false)
	{}

	template<typename Number>
	HPolytope<Number>::HPolytope(const HyperplaneVector& planes) :
		mHPlanes(),
		mFanSet(false),
		mFan(),
		mDimension(0),
		mInitialized(false)
	{
		if(!planes.empty()) {
			mDimension = planes.begin()->dimension();
			for(const auto& plane : planes) {
				mHPlanes.push_back(plane);
			}
		}
	}

	template<typename Number>
	HPolytope<Number>::HPolytope(const matrix_t<Number>& A, const vector_t<Number>& b) :
		mHPlanes(),
		mFanSet(false),
		mFan(),
		mDimension(A.cols()),
		mInitialized(false)
	{
		assert(A.rows() == b.rows());
		for(unsigned i = 0; i < A.rows(); ++i) {
			mHPlanes.push_back(Hyperplane<Number>(A.row(i), b(i)));
		}
	}

	template<typename Number>
	HPolytope<Number>::HPolytope(const matrix_t<Number>& A) :
		mHPlanes(),
		mFanSet(false),
		mFan(),
		mDimension(A.cols()),
		mInitialized(false)
	{
		for(unsigned i = 0; i < A.rows(); ++i) {
			mHPlanes.push_back(Hyperplane<Number>(A.row(i), Number(0)));
		}
	}


	template<typename Number>
	HPolytope<Number>::HPolytope(const VPolytope<Number>& alien) :
		mHPlanes(),
		mFanSet(false),
		mFan(),
		mDimension(0),
		mInitialized(false)
	{
		if(!alien.empty()){
			// degenerate cases
			unsigned size = alien.size();
			mDimension = alien.dimension();
			if( size < mDimension ){
				// TODO
				assert(false);
			} else if (size == mDimension) {
				typename std::vector<Point<Number>> points = alien.vertices();
				std::vector<vector_t<Number>> rawPoints;
				for(const auto point : points)
					rawPoints.push_back(point.rawCoordinates());

				vector_t<Number> root = rawPoints.back();
				rawPoints.pop_back();
				mHPlanes.push_back(Hyperplane<Number>(root, rawPoints));

			} else {
				typename std::vector<Point<Number>> points = alien.vertices();
				std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull(points).first;
				for(auto& facet : facets) {
					mHPlanes.push_back(facet->hyperplane());
				}
				facets.clear();
			}
		}
	}


	template<typename Number>
	HPolytope<Number>::~HPolytope()
	{
		if(mInitialized)
			deleteArrays();
	}

	/*
	 * Getters and setters
	 */

	template<typename Number>
	bool HPolytope<Number>::empty() const
	{
		return mHPlanes.empty();
	}

	 template<typename Number>
	 unsigned HPolytope<Number>::dimension() const
	{
		assert(!mHPlanes.empty());
		return mDimension;
	}

	template<typename Number>
	unsigned HPolytope<Number>::size() const {
		return mHPlanes.size();
	}

	template<typename Number>
	const typename polytope::Fan<Number>& HPolytope<Number>::fan() const
	{
		if(!mFanSet)
		{
			calculateFan();
		}
		return mFan;
	}

	template<typename Number>
	typename std::vector<Point<Number>> HPolytope<Number>::vertices() const {
		//std::cout << "Compute vertices of " << *this << std::endl;
		typename std::vector<Point<Number>> vertices;
		for(unsigned planeA = 0; planeA < mHPlanes.size()-1; ++planeA) {
			for(unsigned planeB = planeA+1; planeB < mHPlanes.size(); ++planeB) {
				matrix_t<Number> A(2, mHPlanes.at(planeA).dimension());
				vector_t<Number> b(2);

				std::cout << __func__ << ": combine: " << mHPlanes.at(planeA).normal().transpose() << " ("<< planeA <<") and " << mHPlanes.at(planeB).normal().transpose() << " (" << planeB << ")" << std::endl;

				// initialize
				A.row(0) = mHPlanes.at(planeA).normal().transpose();
				A.row(1) = mHPlanes.at(planeB).normal().transpose();

				// check if rank is full
				Eigen::FullPivLU<matrix_t<Number>> lu_decomp(A);
				if(lu_decomp.rank() < A.rows()) {
					continue;
				}

				b(0) = mHPlanes.at(planeA).offset();
				b(1) = mHPlanes.at(planeB).offset();

				vector_t<Number> res = A.fullPivHouseholderQr().solve(b);

				//	Number relative_error = (A*res - b).norm() / b.norm();

				// check for infinity
				bool infty = false;
				for(unsigned i = 0; i < res.rows(); ++i){
					if(std::numeric_limits<Number>::infinity() == (Number(res(i)))){
						std::cout << (Number(res(i))) << " is infty." << std::endl;
						infty = true;
						break;
					}
				}

				if(!infty) {
					vertices.push_back(Point<Number>(res));
					std::cout << "Computed vertex: " << Point<Number>(res) << std::endl;
				}
				else
					std::cout << "Intersection at infinity." << std::endl;

			}
		}
		for(auto vertexIt = vertices.begin(); vertexIt != vertices.end(); ) {
			std::cout << "Check contains." << std::endl;
			if(!this->contains(*vertexIt)) {
				std::cout << "Removed vertex: " << *vertexIt << std::endl;
				vertexIt = vertices.erase(vertexIt);
			} else {
				++vertexIt;
			}
		}
		return vertices;
	}

	template<typename Number>
	Number HPolytope<Number>::supremum() const {
		Number max = 0;
        for(auto& point : this->vertices())
        {
            Number inftyNorm = hypro::Point<Number>::inftyNorm(point);
            max = max > inftyNorm ? max : inftyNorm;
        }
        return max;
	}

	template<typename Number>
    void HPolytope<Number>::calculateFan() const{

    	std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull(vertices()).first;
		std::set<Point<Number>> preresult;
		for(unsigned i = 0; i<facets.size(); i++) {
			for(unsigned j = 0; j<facets[i].vertices().size(); j++) {
				preresult.insert(facets[i]->vertices().at(j));
			}
		}
		polytope::Fan<Number> fan;
		for(auto& point : preresult) {
			polytope::Cone<Number>* cone = new polytope::Cone<Number>();
			for(unsigned i = 0; i<facets.size(); i++) {
				for(unsigned j = 0; j<facets[i]->vertices().size(); j++) {
					if(point == facets[i]->vertices().at(j))	{
					std::vector<Ridge<Number>> ridges = getRidges(*facets[i]);
						for(unsigned m = 0; m<ridges.size(); m++) {
							if(checkInsideRidge(ridges[m], point)) {
								std::vector<Facet<Number>> conefacets = shareRidge(facets, ridges[m]);

								matrix_t<Number> matrix = matrix_t<Number>(conefacets.size(),point.size());
								for(unsigned k = 1; k < conefacets.size(); k++) {
									for(unsigned l = 0; l < conefacets[k].getNormal().size(); l++) {
										matrix(k,l) = conefacets[k].getNormal()(l);
									}
								}

								for(unsigned j = 0; j < point.size(); j++) {
									matrix(0,j) = 1;

									if(matrix.fullPivLu().rank()==point.size()){
										break;
									} else {
										matrix(0,j) = 0;
									}
								}
								vector_t<Number> b = vector_t<Number>::Zero(conefacets.size());
								b(0) = 1;
								vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);

								cone->add(std::shared_ptr<Hyperplane<Number>>( new Hyperplane<Number>(result, result.dot(point.rawCoordinates()))));
								//cone->add(std::make_shared<Hyperplane<Number>>(Hyperplane<Number>(result, result.dot(point.rawCoordinates()))));
							}
						}
					}
				}
			}
			fan.add(cone);
		}
		mFanSet = true;
		mFan = fan;
    }

	template<typename Number>
	void HPolytope<Number>::insert(const Hyperplane<Number>& plane)
	{
		assert(mDimension == 0 || mDimension == plane.dimension());
		if(mDimension == 0)
		{
			mDimension = plane.dimension();
		}
		mHPlanes.push_back(plane);
		mInitialized = false;
	}

	template<typename Number>
	void HPolytope<Number>::insert(const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end)
	{
		assert(mDimension == 0 || mDimension == begin->dimension());
		if(mDimension == 0)
		{
			mDimension = begin->dimension();
		}
		auto it = begin;
		while(it != end) {
			mHPlanes.push_back(*it);
			++it;
		}
		mInitialized = false;
	}

	template<typename Number>
	const typename HPolytope<Number>::HyperplaneVector& HPolytope<Number>::constraints() const
	{
		return mHPlanes;
	}

	template<typename Number>
	bool HPolytope<Number>::hasConstraint(const Hyperplane<Number>& hplane) const
	{
		for(const auto& plane : mHPlanes) {
			if(hplane == plane)
				return true;
		}
		return false;
	}

	template<typename Number>
	void HPolytope<Number>::reduce() {
		std::cout << __func__ << ": " << *this << std::endl;
		for(auto planeIt = mHPlanes.begin(); planeIt != mHPlanes.end(); ) {
			//std::cout << "Current plane: " << *planeIt << std::endl;
			std::pair<Number, SOLUTION> evalRes = this->evaluate(planeIt->normal());
			if(evalRes.second == INFEAS) {
				// return empty polytope
				this->clear();
				break;
			} else if (evalRes.second == FEAS) {
				if(evalRes.first < planeIt->offset() && !carl::AlmostEqual2sComplement(evalRes.first,planeIt->offset())) {
					//std::cout << "erase " << *planeIt << " which is really redundant." << std::endl;
					planeIt = mHPlanes.erase(planeIt);
					mInitialized = false;
				}
				else{
					Hyperplane<Number> tmp = Hyperplane<Number>(*planeIt);
					auto pos = mHPlanes.erase(planeIt);
					mInitialized = false;
					std::pair<Number,SOLUTION> tmpRes = this->evaluate(tmp.normal());
					//std::cout << "Eval with: " << evalRes.first << ", without: " << tmpRes.first << ", solution type: " << tmpRes.second << std::endl;
					if( tmpRes.second == INFTY || (tmpRes.first > tmp.offset() && !carl::AlmostEqual2sComplement(tmpRes.first,tmp.offset())) ) {
						planeIt = mHPlanes.insert(pos, tmp);
						mInitialized = false;
						++planeIt;
						//std::cout << "keep "  << tmp << std::endl;
					}
					else {
						//std::cout << "erase " << tmp << " which is equal to something." << std::endl;
						planeIt = pos;
					}
				}
			} // FEAS
		} // loop
		//std::cout << __func__ << ": Result: " << *this << std::endl;
	}


	template<typename Number>
	matrix_t<Number> HPolytope<Number>::peter() const{
		matrix_t<Number> result = matrix_t<Number>(mHPlanes.size(), mHPlanes[0].normal().size());

		for(unsigned i = 0; i<mHPlanes.size(); i++){
			for(unsigned j = 0; j< mHPlanes[i].normal().size(); j++){
				result(i,j) = mHPlanes[i].normal()(j);
			}
		}

		return result;
	}

	template<typename Number>
	vector_t<Number> HPolytope<Number>::getConstraintsOffsetVector() const{
		vector_t<Number> result = vector_t<Number>(mHPlanes.size());

		for(unsigned i = 0; i < mHPlanes.size(); i++){
			result(i) = mHPlanes[i].offset();
		}

		return result;
	}

	template<typename Number>
	bool HPolytope<Number>::isExtremePoint(vector_t<Number> point) const {
		unsigned cnt = 0;
		for(const auto& plane : mHPlanes) {
			Number val = plane.evaluate(point);
			//std::cout << "Eval: " << plane.normal() << " in direction " << point << " = " << val << ", offset is " << plane.offset() << ", with tolerance: " << abs(plane.offset() - val) << std::endl;
			if( carl::AlmostEqual2sComplement(plane.offset(),val) ) {
				//std::cout << "Increase cnt " << std::endl;
				++cnt;
			}
			else if( plane.offset() - val < 0 ) {
				//std::cout << "######" << val << " != " << plane.offset() << std::endl;
				return false;
			}
		}
		//std::cout << "CNT: " << cnt << std::endl;
		return cnt >= mDimension;
	}

	template<typename Number>
	bool HPolytope<Number>::isExtremePoint(const Point<Number>& point) const {
		return isExtremePoint(point.rawCoordinates());
	}

	template<typename Number>
	std::pair<Number,SOLUTION> HPolytope<Number>::evaluate(const vector_t<Number>& _direction) const{
		if(!mInitialized) {
			initialize();
		}

		//std::cout << __func__ << ": " << _direction.transpose() << std::endl;

		assert(_direction.rows() == mDimension);

		//std::cout << "Set target: ";
		for (unsigned i = 0; i < mDimension; i++)
		{
			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0);
			glp_set_obj_coef(lp, i+1, double(_direction(i)));
			//std::cout << double(_direction(i)) << ", ";
		}
		//std::cout << std::endl;

		/* solve problem */
		glp_simplex(lp, NULL);

		Number result = glp_get_obj_val(lp);

		// display potential problems
		switch(glp_get_status(lp))
		{
			case GLP_OPT:
			case GLP_FEAS:{
				 break;}
			case GLP_UNBND:{
				 return std::make_pair(1, INFTY);
				 break;}
			default:
				//std::cout << __func__ << ": " << *this << " in direction " << _direction << std::endl;
				//std::cout << "Unable to find a suitable solution for the support function (linear program). ErrorCode: " << glp_get_status(lp) << std::endl;
				return std::make_pair(0,INFEAS);
		}
		//std::cout << "Result: " << result << std::endl;

		return std::make_pair(result,FEAS);
	}

	template<typename Number>
	typename HPolytope<Number>::HyperplaneVector::iterator HPolytope<Number>::begin()
	{
		return mHPlanes.begin();
	}

	template<typename Number>
	typename HPolytope<Number>::HyperplaneVector::const_iterator HPolytope<Number>::begin() const
	{
		return mHPlanes.begin();
	}

	template<typename Number>
	typename HPolytope<Number>::HyperplaneVector::iterator HPolytope<Number>::end()
	{
		return mHPlanes.end();
	}

	template<typename Number>
	typename HPolytope<Number>::HyperplaneVector::const_iterator HPolytope<Number>::end() const
	{
		return mHPlanes.end();
	}

	/*
	 * General interface
	 */

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const {
		std::cout << __func__ << " this: " << *this << std::endl;
		std::cout << __func__ << " vertices: " << std::endl;
		for(const auto& vertex : this->vertices())
			std::cout << vertex << std::endl;

		std::cout << "Create intermediate. " << std::endl;

		VPolytope<Number> intermediate(this->vertices());

		std::cout << "Intermediate : " << intermediate << std::endl;

		intermediate = intermediate.linearTransformation(A, b);

		std::cout << "Intermediate : " << intermediate << std::endl;

		HPolytope<Number> res(intermediate);
		return res;
	}

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::minkowskiSum(const HPolytope& rhs) const {
		HPolytope<Number> res;
		Number result;

		// evaluation of rhs in directions of lhs
		for(unsigned i = 0; i < mHPlanes.size(); ++i) {
			std::pair<Number,SOLUTION> evalRes = rhs.evaluate(mHPlanes.at(i).normal());
			if(evalRes.second == INFTY) {
				// Do nothing - omit inserting plane.
			} else if (evalRes.second == INFEAS) {
				// TODO: Return empty polytope.
			} else {
				result = mHPlanes.at(i).offset() + evalRes.first;
				res.insert(Hyperplane<Number>( mHPlanes.at(i).normal(), result ));
				//std::cout << __func__ << " Evaluated against " << mHPlanes.at(i).normal() << std::endl;
			}
		}

		// evaluation of lhs in directions of rhs
		for(unsigned i = 0; i < rhs.constraints().size(); ++i) {
			std::pair<Number,SOLUTION> evalRes = this->evaluate(rhs.constraints().at(i).normal());
			if(evalRes.second == INFTY) {
				// Do nothing - omit inserting plane.
			} else if (evalRes.second == INFEAS) {
				// TODO: Return empty polytope.
			} else {
				result = rhs.constraints().at(i).offset() + evalRes.first;
				res.insert(Hyperplane<Number>( rhs.constraints().at(i).normal(), result ));
				//std::cout << __func__ << " Evaluated against " << mHPlanes.at(i).normal() << std::endl;
			}
		}
		//res.reduce();
		return res;
	}

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::intersect(const HPolytope& rhs) const {
		std::cout << __func__ << std::endl;
		// Todo: Improve.
		if(rhs.empty()){
			return HPolytope<Number>();
		}
		else {
			HPolytope<Number> res;
			for(const auto& plane : mHPlanes) {
				res.insert(plane);
			}
			for(const auto& plane : rhs.constraints()) {
				res.insert(plane);
			}
			res.reduce();
			return res;
		}
	}

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::intersectHyperplane(const Hyperplane<Number>& rhs) const {
	}

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::intersectHyperplanes(const matrix_t<Number>& _mat, const vector_t<Number>& _vec) const {
		assert(_mat.rows() == _vec.rows());
		std::cout << __func__ << std::endl;

		HPolytope<Number> res(*this);
		for(unsigned i = 0; i < _mat.rows(); ++i) {
			res.insert(Hyperplane<Number>(_mat.row(i), _vec(i)));
		}
		//res.reduce();

		return res;
	}

	template<typename Number>
	bool HPolytope<Number>::contains(const Point<Number>& point) const {
		return this->contains(point.rawCoordinates());
	}

	template<typename Number>
	bool HPolytope<Number>::contains(const vector_t<Number>& vec) const {
		//std::cout << __func__ << "  " << vec << ": ";
		for(const auto& plane : mHPlanes) {
			//std::cout << plane << ": " << plane.normal().dot(vec) << ", -> " << (!carl::AlmostEqual2sComplement(plane.normal().dot(vec), plane.offset(),TOLLERANCE_ULPS) && plane.normal().dot(vec) > plane.offset()) << std::endl;
			//carl::AlmostEqual2sComplement(plane.normal().dot(vec), plane.offset());
			if(!carl::AlmostEqual2sComplement(plane.normal().dot(vec), plane.offset(),TOLLERANCE_ULPS) && plane.normal().dot(vec) > plane.offset()) {
				std::cout << "Not contained in " << plane.normal().transpose() << " <= " << plane.offset() << "(is: " << plane.normal().dot(vec) << ")" << std::endl;
				return false;
			}
		}
		return true;
	}

	template<typename Number>
	bool HPolytope<Number>::contains(const HPolytope<Number>& rhs) const {
		for(const auto& plane : rhs) {
			std::pair<Number,SOLUTION> evalRes = this->evaluate(plane.normal());
			if( evalRes.second == INFEAS ) {
				return false; // empty!
			} else if ( evalRes.second == INFTY ) {
				continue;
			} else if( evalRes.first < plane.offset() && !carl::AlmostEqual2sComplement(evalRes.first, plane.offset()) ) {
				return false;
			}
		}
		return true;
	}

	template<typename Number>
	HPolytope<Number> HPolytope<Number>::unite(const HPolytope& _rhs) const {
		if(_rhs.empty()){
			return HPolytope<Number>(*this);
		}
		else {
			VPolytope<Number> lhs(this->vertices());
			VPolytope<Number> tmpRes = lhs.unite(VPolytope<Number>(_rhs.vertices()));

			return HPolytope<Number>(tmpRes);
		}
	}

	template<typename Number>
	void HPolytope<Number>::clear() {
		mHPlanes.clear();
		mFanSet = false;
		mDimension = 0;
		deleteArrays();
		mInitialized = false;
	}

	template<typename Number>
	void HPolytope<Number>::print() const {
		std::cout << *this << std::endl;
	}

	/*
	 * Operators
	 */

	template<typename Number>
	Hyperplane<Number> HPolytope<Number>::operator[](unsigned i) const
	{
		return mHPlanes.at(i);
	}

	template<typename Number>
	HPolytope<Number>& HPolytope<Number>::operator= (const HPolytope<Number>& rhs)
	{
		if(this != &rhs)
		{
			HPolytope<Number> tmp(rhs);
			swap(*this, tmp);
		}
		return *this;
	}

	/*
	 * Auxiliary functions
	 */

	template<typename Number>
	void HPolytope<Number>::createArrays(unsigned size) const{
		ia = new int[size+1];
		ja = new int[size+1];
		ar = new double[size+1];
	}

	template<typename Number>
	void HPolytope<Number>::deleteArrays() {
		delete[] ia;
		delete[] ja;
		delete[] ar;
	}

	template<typename Number>
	void HPolytope<Number>::printArrays() {
		if (!mInitialized) {
			initialize();
		}
		unsigned size = mHPlanes.size()*mDimension;
		std::cout << "IA: ";
		for(unsigned pos = 0; pos < size; ++pos) {
			std::cout << ia[pos] << ", ";
		}
		std::cout << std::endl;
	}

	template<typename Number>
	void HPolytope<Number>::initialize() const{
		if(!mInitialized) {
			/* create glpk problem */
			lp = glp_create_prob();
			glp_set_prob_name(lp, "hpoly");
			glp_set_obj_dir(lp, GLP_MAX);
			glp_term_out(GLP_OFF);

			unsigned numberOfConstraints = mHPlanes.size();

			// convert constraint constants
			glp_add_rows(lp, numberOfConstraints);
			for (unsigned i = 0; i < numberOfConstraints; i++)
			{
				glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double(mHPlanes[i].offset()) );
			}

			// add cols here
			glp_add_cols(lp, mDimension);
			createArrays(numberOfConstraints*mDimension);

			// convert constraint matrix
			ia[0] = 0;
			ja[0] = 0;
			ar[0] = 0;
			for (unsigned i = 0; i < numberOfConstraints*mDimension; ++i)
			{
				ia[i+1] = ((int)(i / mDimension))+1;
				//std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
				ja[i+1] = ((int)(i%mDimension))+1;
				//std::cout << ", ja[" << i+1 << "]= " << ja[i+1];
				ar[i+1] = double(mHPlanes[ia[i+1]-1].normal()(ja[i+1]-1));
				//std::cout << ", ar[" << i+1 << "]=" << ar[i+1] << std::endl;
			}

			glp_load_matrix(lp, numberOfConstraints*mDimension, ia, ja, ar);
			mInitialized = true;
		}
	}

	/*
	template<typename Number>
	Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> HPolytope<Number>::getOptimalDictionary(
		const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A,
		unsigned dimension,
		std::vector<unsigned>& B,
		std::vector<unsigned>& N) const
	{
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> matrix_t;
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, 1> vector_t;
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, 1, Eigen::Dynamic> row_t;
		// create matrix from HPlanes
		const unsigned numRows = mHPlanes.size() - mHPlanes.begin()->dimension();
		const unsigned numCols = mHPlanes.begin()->dimension() + 1;
		matrix_t dictionary = matrix_t(numRows, numCols);

		// Assumption: The last d equations of A are linear independent
		auto bottom = A.bottomRows(dimension);
		auto top = A.topRows(A.rows()-dimension);
		auto varBlock = bottom.rightCols(dimension);
		auto constPart = bottom.leftCols(1);

		matrix_t tmp = matrix_t(varBlock);
		vector_t b = vector_t(constPart);

		matrix_t a(tmp.rows(), 2*dimension+1);
		a << tmp, -b, matrix_t::Identity(dimension,dimension);

		//normalize rows for each variable and forward insertion
		for(unsigned rowIndex = 0; rowIndex < a.rows()-1; ++rowIndex)
		{
			a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,rowIndex);
			a.row(rowIndex+1) = a.row(rowIndex+1) - (a.row(rowIndex)*a(rowIndex+1, rowIndex));
		}

		// backward insertion
		for(unsigned rowIndex = a.rows()-1; rowIndex > 0; --rowIndex)
		{
			if(a(rowIndex,rowIndex) != 1)
			{
				a.row(rowIndex) = a.row(rowIndex) / a(rowIndex,rowIndex);
			}
			a.row(rowIndex-1) = a.row(rowIndex-1) - (a.row(rowIndex)*a(rowIndex-1, rowIndex));
		}

		auto substitutionBlock = a.rightCols(dimension+1);

		for(unsigned rI = 0; rI < top.rows(); ++rI)
		{
			dictionary(rI,0) = top(rI,0);

			for(unsigned dI = 1; dI < top.cols(); ++dI)
			{
				dictionary.row(rI) = dictionary.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
			}
		}

		// Augment dictionary by a row of -1s
		dictionary.conservativeResize(numRows+1,Eigen::NoChange_t());

		row_t allOnes = matrix_t::Constant(1,numCols, carl::FLOAT_T<Number>(-1));
		allOnes(0) = carl::FLOAT_T<Number>(0);
		dictionary.row(numRows) = allOnes;

		//std::cout << "Optimal dictionary: " << dictionary << std::endl;
		for(unsigned index = 0; index < mHPlanes.size() - dimension; ++index)
			B.push_back(index);
		//B.push_back(mHPlanes.size()+1);

		for(unsigned index = 1 ; index < dictionary.cols() ; ++index)
			N.push_back(index);

		return dictionary;
	}

	template<typename Number>
	std::vector<Point<Number> > HPolytope<Number>::vertexEnumeration() const
	{
		std::vector<Point<Number> > solution;

		// create Matrix from hPlanes TODO: Recheck with page 299 of the paper
		const unsigned rows = mHPlanes.size();
		const unsigned colums = this->dimension()+1;
		Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic, Eigen::Dynamic> poly = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>(rows,colums);
		unsigned rowCount = 0;
		unsigned columCount = 0;

		for(auto& hplane : mHPlanes)
		{
			columCount = 0;
			poly(rowCount, columCount) = carl::FLOAT_T<double>(hplane.offset());
			vector_t<Number> normal = hplane.normal();
			for(unsigned index = 0; index < normal.rows(); ++index)
			{
				++columCount;
				poly(rowCount, columCount) = -normal(index);
			}
			++rowCount;
		}

		// get unique optimal first Dictionary
		std::vector<unsigned> basis;
		std::vector<unsigned> coBasis;
		Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> dictionary = getOptimalDictionary(poly,this->dimension(), basis, coBasis);

		//std::cout << "Optimal dictionary:" << std::endl << dictionary << std::endl;

		// Note: f and g mark the indices, not the enumeration as stored in B and N
		//unsigned f = dictionary.rows();
		//unsigned g = 0;

		//unsigned m = mHPlanes.size() - dimension() +1;
		//unsigned n = mHPlanes.size() +2;

		hpolytope::search(basis, coBasis, dictionary);

		return solution;
	}
	*/

} // namespace
