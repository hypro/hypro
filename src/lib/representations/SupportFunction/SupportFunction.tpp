/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.tpp
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-12-16
 */

#include "SupportFunction.h"

namespace hypro{

//CONSTRUCTORS


    //-------PRIVATE---------
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::shared_ptr<SupportFunctionContent<Number>> _source) : content(_source){
        //handled by initializer list
    }

    //-------PUBLIC---------
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT() : content(std::shared_ptr<SupportFunctionContent<Number>>()){
        //handled by initializer list
    }

    //copy constructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT( const SupportFunctionT<Number,Converter> &_orig ) : content(_orig.content){
        //handled by initializer list
    }

    //move constructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT( SupportFunctionT<Number,Converter>&& other) : SupportFunctionT<Number,Converter>(){
        swap(*this, other);
    }


    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(SF_TYPE _type, Number _radius ) : content(SupportFunctionContent<Number>::create(_type, _radius)){
        //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::vector<Point<Number>>& _vertices)
        : content(SupportFunctionContent<Number>::create(SF_TYPE::POLY, _vertices)) {
        //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const matrix_t<Number>& _directions, const vector_t<Number>& _distances) : content(SupportFunctionContent<Number>::create(SF_TYPE::POLY, _directions, _distances)){
         //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::vector<Halfspace<Number>>& _planes) : content(SupportFunctionContent<Number>::create(SF_TYPE::POLY, _planes)){
         //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const matrix_t<Number>& _shapeMatrix) : content(SupportFunctionContent<Number>::create(SF_TYPE::ELLIPSOID, _shapeMatrix)){
         //handled by initializer list
    }

    //destructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::~SupportFunctionT() {
    }

// OPERATOR OVERLOADING

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>& SupportFunctionT<Number,Converter>::operator=(SupportFunctionT<Number,Converter> _orig) {
        //std::cout << "SupportFunction Copy\n";
        if (this != &_orig){
            swap(*this, _orig);
        }
        return *this;
    }


// FUNCTIONS

    template<typename Number, typename Converter>
    EvaluationResult<Number> SupportFunctionT<Number,Converter>::evaluate( const vector_t<Number> &_direction ) const {
        //std::cout << __func__ << "(" << _direction << ") :" << tmp.supportValue << std::endl;
        return content->evaluate(_direction);
    }

    template<typename Number, typename Converter>
    std::vector<EvaluationResult<Number>> SupportFunctionT<Number,Converter>::multiEvaluate( const matrix_t<Number> &_directions ) const {
        //std::cout << __func__ << " " << convert<Number,double>(_directions) << std::endl;
        std::vector<EvaluationResult<Number>> res = content->multiEvaluate(_directions);
        assert(res.size() == std::size_t(_directions.rows()));
        //std::cout << __func__ << " Distances: " << std::endl;
        //for(const auto& item : res){
        //	std::cout << item.supportValue << std::endl;
        //}
        return res;
    }

    template<typename Number, typename Converter>
    std::size_t SupportFunctionT<Number,Converter>::dimension() const {
        return content->dimension();
    }

    template<typename Number, typename Converter>
    SF_TYPE SupportFunctionT<Number,Converter>::type() const {
        return content->type();
    }

    template<typename Number, typename Converter>
    unsigned SupportFunctionT<Number,Converter>::depth() const {
        return content->depth();
    }

    template<typename Number, typename Converter>
    unsigned SupportFunctionT<Number,Converter>::multiplicationsPerEvaluation() const {
        return content->multiplicationsPerEvaluation();
    }

    template<typename Number, typename Converter>
    unsigned SupportFunctionT<Number,Converter>::operationCount() const {
        return content->operationCount();
    }

    template<typename Number, typename Converter>
    sumContent<Number> *SupportFunctionT<Number,Converter>::summands() const {
       return content->summands();
    }

    template<typename Number, typename Converter>
    trafoContent<Number> *SupportFunctionT<Number,Converter>::linearTrafoParameters() const {
        return content->linearTrafoParameters();
    }

    template<typename Number, typename Converter>
    scaleContent<Number> *SupportFunctionT<Number,Converter>::scaleParameters() const {
        return content->scaleParameters();
    }

    template<typename Number, typename Converter>
    unionContent<Number> *SupportFunctionT<Number,Converter>::unionParameters() const {
        return content->unionParameters();
    }

    template<typename Number, typename Converter>
    intersectionContent<Number> *SupportFunctionT<Number,Converter>::intersectionParameters() const {
        return content->intersectionParameters();
    }

    template<typename Number, typename Converter>
    PolytopeSupportFunction<Number> *SupportFunctionT<Number,Converter>::polytope() const {
        return content->polytope();
    }

    template<typename Number, typename Converter>
    BallSupportFunction<Number> *SupportFunctionT<Number,Converter>::ball() const {
        return content->ball();
    }

    template<typename Number, typename Converter>
    EllipsoidSupportFunction<Number> *SupportFunctionT<Number,Converter>::ellipsoid() const {
        return content->ellipsoid();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::removeRedundancy() {
        // Support functions are already non-redundant (Polytope support functions are made non-redundant upon construction).
    }

    template<typename Number, typename Converter>
    std::vector<Point<Number>> SupportFunctionT<Number,Converter>::vertices(const Location<Number>* loc) const {
		std::vector<vector_t<Number>> additionalDirections;
		if(loc != nullptr) {
			for(unsigned rowIndex = 0; rowIndex < loc->invariant().mat.rows(); ++rowIndex){
				additionalDirections.push_back(vector_t<Number>(loc->invariant().mat.row(rowIndex)));
			}
		}

		//std::cout << "Added " << additionalDirections.size() << " additional directions for evaluation." << std::endl;
		/*
		std::list<unsigned> projections = collectProjections();
		if( projections.size() == this->dimension() ){
			//std::cout << "Full vertices" << std::endl;
			auto tmp = Converter::toHPolytope(*this, additionalDirections);
			return tmp.vertices();
		} else {
			//std::cout << "Projection" << std::endl;
			std::list<unsigned> zeroDimensions;
			for(unsigned i = 0; i < this->dimension(); ++i) {
				if(std::find(projections.begin(), projections.end(), i) == projections.end()){
					//std::cout << "Dimension " << i << " is zero." << std::endl;
					zeroDimensions.emplace_back(i);
				}
			}
			std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(projections, 8, this->dimension()); // TODO: ATTENTION, 8 is hardcoded here.
			for(auto& direction : additionalDirections) {
				// project direction
				for(const auto& dir : zeroDimensions) {
					direction(dir) = 0;
				}
				// add projected direction
				if(direction != vector_t<Number>::Zero(this->dimension()) && std::find(templateDirections.begin(), templateDirections.end(), direction) == templateDirections.end()) {
					templateDirections.insert(templateDirections.end(), std::move(direction));
				}
			}

			matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), this->dimension());

			//fills the matrix with the template directions
			for (unsigned i=0; i<templateDirections.size();++i){
				templateDirectionMatrix.row(i) = templateDirections[i];
			}
			//std::cout << "TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;

			std::vector<EvaluationResult<Number>> offsets = content->multiEvaluate(templateDirectionMatrix);
			assert(offsets.size() == unsigned(templateDirectionMatrix.rows()));

			//std::cout << "Multi-Eval done, add zero constraints" << std::endl;

			std::vector<unsigned> boundedConstraints;
			for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
				if(offsets[offsetIndex].errorCode != SOLUTION::INFTY){
					boundedConstraints.push_back(offsetIndex);
				}
			}
			matrix_t<Number> constraints = matrix_t<Number>::Zero(boundedConstraints.size()+2*zeroDimensions.size(), this->dimension());
			vector_t<Number> constants = vector_t<Number>::Zero(boundedConstraints.size()+2*zeroDimensions.size());
			unsigned pos = boundedConstraints.size()-1;
			unsigned zeroDimensionPos = boundedConstraints.size();
			while(!boundedConstraints.empty()){
				constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
				constants(pos) = offsets[boundedConstraints.back()].supportValue;
				boundedConstraints.pop_back();
				--pos;
			}

			//std::cout << "Projected polytope without zero constraints: " << std::endl << convert<Number,double>(constraints) << std::endl << convert<Number,double>(constants) << std::endl;

			// add zero dimension constraints
			while(!zeroDimensions.empty()) {
				//std::cout << "Add zero constraints for dimension " << zeroDimensions.front() << " at rows " << zeroDimensionPos << "f" << std::endl;
				vector_t<Number> zDimConstraint = vector_t<Number>::Zero(this->dimension());
				zDimConstraint(zeroDimensions.front()) = 1;
				constraints.row(zeroDimensionPos) = zDimConstraint;
				constants(zeroDimensionPos) = 0;
				//std::cout << "Positive zero constraint for dimension " << zeroDimensions.front() << ": " << zDimConstraint << std::endl;

				++zeroDimensionPos;

				zDimConstraint(zeroDimensions.front()) = -1;
				constraints.row(zeroDimensionPos) = zDimConstraint;
				constants(zeroDimensionPos) = 0;
				//std::cout << "Negative zero constraint for dimension " << zeroDimensions.front() << ": " << zDimConstraint << std::endl;

				zeroDimensions.pop_front();
				++zeroDimensionPos;
			}

			std::cout << "Projected Polytope: " << std::endl << constraints << std::endl << constants << std::endl;

			VertexEnumeration<Number> ve(constraints, constants);
			ve.enumerateVertices();
			return ve.getPoints();
		}
		*/
		auto tmp = Converter::toHPolytope(*this, additionalDirections);
		return tmp.vertices();
    }

    template<typename Number, typename Converter>
    Number SupportFunctionT<Number,Converter>::supremum() const {
		Point<Number> supPoint = content->supremumPoint();
        return Point<Number>::inftyNorm(supPoint);
    }

	template<typename Number, typename Converter>
	SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::project(const std::vector<unsigned>& dimensions) const {
		// check for full projection
		bool fullProjection = true;
		for(unsigned i = 0; i < this->dimension(); ++i) {
			if(std::find(dimensions.begin(), dimensions.end(), i) == dimensions.end()) {
				fullProjection = false;
				break;
			}
		}
		if(!fullProjection){
			SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->project(dimensions));
			return res;
		}
		return *this;
	}

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::linearTransformation( const std::shared_ptr<const lintrafoParameters<Number>>& parameters ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->linearTransformation(parameters));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>  SupportFunctionT<Number,Converter>::minkowskiSum( SupportFunctionT<Number,Converter> &_rhs ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->minkowskiSum(_rhs.content));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::intersect(SupportFunctionT<Number,Converter> &_rhs) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->intersect(_rhs.content));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const{
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->intersect(SupportFunctionT<Number,Converter>(_mat,_vec).content));
        return res;
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const Point<Number> &_point ) const {
        return content->contains(_point);
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const vector_t<Number> &_point ) const {
        return content->contains(_point);
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const SupportFunctionT<Number, Converter>& rhs, unsigned directions ) const {
    	std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(this->dimension(), directions);
    	for(const auto& direction : templateDirections) {
    		if(this->evaluate(direction).supportValue < rhs.evaluate(direction).supportValue){
				return false;
			}
    	}
    	return true;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>  SupportFunctionT<Number,Converter>::unite( SupportFunctionT<Number,Converter> &_rhs ) const {
        return SupportFunctionT<Number,Converter>(content->unite(_rhs.content));
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::scale( const Number &_factor ) const {
        return SupportFunctionT<Number,Converter>(content->scale( _factor));
    }

    template<typename Number, typename Converter>
    std::pair<bool, SupportFunctionT<Number,Converter>> SupportFunctionT<Number,Converter>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
        //std::cout << __func__ << ": " << _mat << std::endl << " <= " << _vec <<  std::endl;
		if(_mat.rows() == 0) {
			return std::make_pair(true, *this);
		}
		assert(_mat.rows() == _vec.rows());
        std::vector<unsigned> limitingPlanes;
        for(unsigned rowI = 0; rowI < _mat.rows(); ++rowI) {
        	//std::cout << "Evaluate against plane " << rowI << std::endl;
        	EvaluationResult<Number> planeEvalRes = content->evaluate(_mat.row(rowI));
        	if(planeEvalRes.errorCode == SOLUTION::INFEAS){
				//std::cout << "Is infeasible (should not happen)." << std::endl;
				//std::cout << "Set is (Hpoly): " << std::endl << Converter::toHPolytope(*this) << std::endl;
				assert(Converter::toHPolytope(*this).empty());
        		return std::make_pair(false, *this);
        	} else if(planeEvalRes.supportValue > _vec(rowI)){
				//std::cout << "Object will be limited. " << std::endl;
        		// the actual object will be limited by the new plane
        		limitingPlanes.push_back(rowI);
				// std::cout << "evaluate(" << convert<Number,double>(-(_mat.row(rowI))) << ") <=  " << -(_vec(rowI)) << ": " << content->evaluate(-(_mat.row(rowI))).supportValue << " <= " << -(_vec(rowI)) << std::endl;
        		// std::cout << __func__ <<  ": Limiting plane " << convert<Number,double>(_mat.row(rowI)).transpose() << " <= " << carl::toDouble(_vec(rowI)) << std::endl;
	            if(content->evaluate(-(_mat.row(rowI))).supportValue < -(_vec(rowI))){
					//std::cout << "fullyOutside" << std::endl;
	                // the object lies fully outside one of the planes -> return false
	                return std::make_pair(false, this->intersectHalfspaces(_mat,_vec) );
	            }
        	}
        }
    	if(limitingPlanes.size() < unsigned(_mat.rows())){
    		if(limitingPlanes.size() == 0 ){
    			//std::cout << __func__ << " Object will stay the same" << std::endl;
    			return std::make_pair(true, *this);
    		}
    		//std::cout << __func__ << " Object will be limited but not empty (" << limitingPlanes.size() << " planes)" << std::endl;
    		// if the result is not fullyOutside, only add planes, which affect the object
        	matrix_t<Number> planes = matrix_t<Number>(limitingPlanes.size(), _mat.cols());
        	vector_t<Number> distances = vector_t<Number>(limitingPlanes.size());
        	for(unsigned i = 0; i < distances.rows(); ++i){
        		// std::cout << "Set row " << i << " to plane " << limitingPlanes.back() << std::endl;
        		planes.row(i) = _mat.row(limitingPlanes.back());
        		distances(i) = _vec(limitingPlanes.back());
        		limitingPlanes.pop_back();
        	}
			assert(limitingPlanes.empty());
        	//std::cout << "Intersect with " << planes << ", " << distances << std::endl;
        	return std::make_pair(true, this->intersectHalfspaces(planes,distances));
    	} else {
    		//std::cout << __func__ << " Object will be fully limited but not empty" << std::endl;
    		assert(limitingPlanes.size() == unsigned(_mat.rows()));
    		//std::cout << "Intersect with " << _mat << ", " << _vec << std::endl;
    		return std::make_pair(true, this->intersectHalfspaces(_mat,_vec));
    	}
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::empty() const {
        return content->empty();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::print() const {
        return content->print();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::swap(SupportFunctionT<Number,Converter>& first, SupportFunctionT<Number,Converter>& second){
         first.content.swap(second.content);
     }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::forceLinTransReduction(){
        content->forceLinTransReduction();
    }

	template<typename Number, typename Converter>
	std::list<unsigned> SupportFunctionT<Number,Converter>::collectProjections() const {
		return content->collectProjections();
	}

} // namespace hypro
