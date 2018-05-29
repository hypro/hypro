/*
 * This file contains the basic implementation of support functions of boxes.
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#include "BoxSupportFunction.h"

namespace hypro {

template <typename Number>
BoxSupportFunction<Number>::BoxSupportFunction( const std::vector<carl::Interval<Number>>& intervals )
	: mBox(intervals) {
		TRACE("hypro.representations.supportFunction", "");
}


template<typename Number>
BoxSupportFunction<Number>::BoxSupportFunction( const std::vector<Point<Number>>& _points )
	: mBox()
{
	TRACE("hypro.representations.supportFunction", "");
	auto pIt = _points.begin();
	for(int d = 0; d < _points.begin()->dimension(); ++d) {
		mBox.emplace_back(carl::Interval<Number>(_points.begin()->rawCoordinates()(d)));
	}
	++pIt;
	for(; pIt != _points.end(); ++pIt) {
		for(int d = 0; d < pIt->dimension(); ++d) {
			mBox[d] = mBox[d].convexHull(carl::Interval<Number>(pIt->rawCoordinates()(d)));
		}
	}
}

template <typename Number>
BoxSupportFunction<Number>::BoxSupportFunction( const BoxSupportFunction<Number> &_origin )
	: mBox(_origin.getBox())
{
		TRACE("hypro.representations.supportFunction", "");
}

template <typename Number>
BoxSupportFunction<Number>::~BoxSupportFunction() {
	TRACE("hypro.representations.supportFunction", "");
}

template <typename Number>
BoxSupportFunction<Number>& BoxSupportFunction<Number>::operator=(const BoxSupportFunction<Number>& _orig){
	TRACE("hypro.representations.supportFunction", "");
    this->mBox = _orig.mBox;
}

template <typename Number>
std::size_t BoxSupportFunction<Number>::dimension() const {
	return mBox.size();
}

template <typename Number>
SF_TYPE BoxSupportFunction<Number>::type() const {
	return SF_TYPE::BOX;
}

template <typename Number>
matrix_t<Number> BoxSupportFunction<Number>::constraints() const {
	std::vector<vector_t<Number>> constraints = computeTemplate(mBox.size(),4);
	matrix_t<Number> res = matrix_t<Number>(constraints.size(), mBox.size());
	Eigen::Index row = 0;
	for(const auto& r : constraints) {
		res.row(row) = constraints[row];
		++row;
	}
	return res;
}

template <typename Number>
vector_t<Number> BoxSupportFunction<Number>::constants() const {
	vector_t<Number> res = vector_t<Number>(mBox.size() * 2);
	Eigen::Index row = 0;
	for(const auto& i : mBox) {
		res(row*2) = i.upper();
		res(row*2+1) = Number(-1*i.lower());
		++row;
	}
	return res;
}

template<typename Number>
std::vector<Point<Number>> BoxSupportFunction<Number>::vertices() const {
	std::vector<Point<Number>> result;
	std::size_t limit = std::size_t(pow( 2, this->dimension() ));

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<Number> coord = vector_t<Number>( this->dimension() );
		for ( std::size_t dimension = 0; dimension < this->dimension(); ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos ) {
				coord( dimension ) = mBox[dimension].upper();
			} else {
				coord( dimension ) = mBox[dimension].lower();
			}
		}
		result.push_back( Point<Number>( coord ) );
	}
	return result;
}

template<typename Number>
Point<Number> BoxSupportFunction<Number>::supremumPoint() const {
	assert(!this->empty());
	vector_t<Number> res = vector_t<Number>(mBox.size());
	for(Eigen::Index i = 0; i < res.rows(); ++i) {
		res(i) = mBox[i].upper();
	}
	return Point<Number>(res);
}

template <typename Number>
EvaluationResult<Number> BoxSupportFunction<Number>::evaluate( const vector_t<Number> &l, bool ) const {
	TRACE("hypro.representations.supportFunction", "this dimension is " << this->dimension());
	COUNT("Box evaluate.");
	assert(std::size_t(l.rows()) == this->dimension());
	if(this->empty() || this->dimension() == 0){
		return EvaluationResult<Number>(); // defaults to infeasible, i.e. empty.
	}

	// find the point, which represents the maximum towards the direction - compare signs.
	vector_t<Number> furthestPoint = vector_t<Number>(this->dimension());
	for(Eigen::Index i = 0; i < furthestPoint.rows(); ++i) {
		furthestPoint(i) = l(i) >= 0 ? mBox[i].upper() : mBox[i].lower();
	}
	TRACE("hypro.representations.supportFunction","Have result, return.");
	return EvaluationResult<Number>(furthestPoint.dot(l),furthestPoint,SOLUTION::FEAS);
}

template <typename Number>
std::vector<EvaluationResult<Number>> BoxSupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_A, bool , bool ) const {
	assert( std::size_t(_A.cols()) == this->dimension() );
	TRACE("hypro.representations.supportFunction", "Evaluate in directions " << matrix_t<double>(convert<Number,double>(_A)) << std::endl << "BOX SF IS " << *this);
	std::vector<EvaluationResult<Number>> res;
	for(Eigen::Index i = 0; i < _A.rows(); ++i) {
		res.emplace_back(this->evaluate(vector_t<Number>(_A.row(i)), true));
	}
	TRACE("hypro.representations.supportFunction","Have result, return.");
	return res;
}

template <typename Number>
bool BoxSupportFunction<Number>::contains( const Point<Number> &_point ) const {
	assert(_point.dimension() == this->dimension());
	for(Eigen::Index i = 0; i < this->dimension(); ++i) {
		if(!mBox[i].contains(_point[i])){
			return false;
		}
	}
	return true;
}

template <typename Number>
bool BoxSupportFunction<Number>::contains( const vector_t<Number> &_point ) const {
	assert(std::size_t(_point.rows()) == this->dimension());
	for(Eigen::Index i = 0; i < Eigen::Index(this->dimension()); ++i) {
		if(!mBox[i].contains(_point(i))){
			return false;
		}
	}
	return true;
}

template <typename Number>
bool BoxSupportFunction<Number>::empty() const {
	TRACE("hypro.representations.supportFunction", "");
	for(Eigen::Index i = 0; i < Eigen::Index(this->dimension()); ++i) {
		if(mBox[i].isEmpty()){
			TRACE("hypro.representations.supportFunction", "is empty.");
			return true;
		}
	}
	TRACE("hypro.representations.supportFunction", "is not empty.");
	return false;
}

template <typename Number>
std::string BoxSupportFunction<Number>::getDotRepresentation() const {
	std::stringstream s;
	s << "<TR><TD>";
	for(const auto& i : mBox) {
		s << i << "<BR>";
	}
	s << "</TD></TR>";
	return s.str();
}

}  // namespace hypro
