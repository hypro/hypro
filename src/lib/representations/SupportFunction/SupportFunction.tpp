/** 
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.tpp
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-11-23
 */

#include "SupportFunction.h"

namespace hypro{
    
    //CONSTRUCTORS
    
    template <typename Number>
    SupportFunction<Number>::SupportFunction(const std::shared_ptr<SupportFunctionContent<Number>> _source){
        content = _source;
    }
    
    template <typename Number>
    SupportFunction<Number>::SupportFunction(){
        content = std::shared_ptr<SupportFunctionContent<Number>>();
    }
    
    
    //Problem in this function
    template <typename Number>
    SupportFunction<Number>::SupportFunction( const SupportFunction<Number> &_orig ){
        content = hypro::SupportFunctionContent<Number>(_orig.content);
    }
    
    template <typename Number>
    SupportFunction<Number>::SupportFunction(SF_TYPE _type, Number _radius ){
       content = hypro::SupportFunctionContent<Number>::create( _type, _radius ); 
    }
    
    template <typename Number>
    SupportFunction<Number>::SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances){
        content = hypro::SupportFunctionContent<Number>::create( _type, _directions, _distances);
    }
    
    template <typename Number>
    SupportFunction<Number>::SupportFunction(SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes){
        content = hypro::SupportFunctionContent<Number>::create( _type, _planes);
    } 
    
    template <typename Number>
    SupportFunction<Number>::~SupportFunction() {
    }
    
    template <typename Number>
    SupportFunction<Number> SupportFunction<Number>::operator=( SupportFunction<Number> _orig) const {
        content = _orig.content;
        return *this;
    }
    
    
    // FUNCTIONS
    
    template <typename Number>
    evaluationResult<Number> SupportFunction<Number>::evaluate( const vector_t<Number> &_direction ) const {
        return content.evaluate(_direction);
    }
    
    template <typename Number>
    vector_t<Number> SupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_directions ) const {
        return content.multiEvaluate(_directions);
    }
    
    template <typename Number>
    std::size_t SupportFunction<Number>::dimension() const {
        return content.dimension();
    }
    
    template <typename Number>
    SF_TYPE SupportFunction<Number>::type() const {
        return content.type();
    }
    
    template <typename Number>
    sumContent<Number> *SupportFunction<Number>::summands() const {
       return content.summands(); 
    }
    
    template <typename Number>
    trafoContent<Number> *SupportFunction<Number>::linearTrafoParameters() const {
        return content.linearTrafoParameters();
    }
    
    template <typename Number>
    scaleContent<Number> *SupportFunction<Number>::scaleParameters() const {
        return content.scaleParameters();
    }
    
    template <typename Number>
    unionContent<Number> *SupportFunction<Number>::unionParameters() const {
        return content.unionParameters();
    }
    
    template <typename Number>
    intersectionContent<Number> *SupportFunction<Number>::intersectionParameters() const {
        return content.intersectionParameters();
    }
    
    template <typename Number>
    PolytopeSupportFunction<Number> *SupportFunction<Number>::polytope() const {
        return content.polytope();
    }
    
    template <typename Number>
    BallSupportFunction<Number> *SupportFunction<Number>::ball() const {
        return content.ball();
    }
    
    template <typename Number>
    SupportFunction<Number> SupportFunction<Number>::linearTransformation(const matrix_t<Number> &_A, const vector_t<Number> &_b ) const {
        SupportFunction<Number> res = SupportFunction<Number>(content.linearTransformation(_A, _b));
        return res;
    }
    
    template <typename Number> 
    SupportFunction<Number>  SupportFunction<Number>::minkowskiSum( SupportFunction<Number> &_rhs ) const {
        SupportFunction<Number> res = SupportFunction<Number>(content.minkowskiSum(_rhs.content));
        return res;
    }
    
    template <typename Number>
    SupportFunction<Number>  SupportFunction<Number>::intersect(SupportFunction<Number> &_rhs) const {
        SupportFunction<Number> res = SupportFunction<Number>(content.intersect(_rhs.content));
        return res;
    }
    
    template <typename Number>
    bool SupportFunction<Number>::contains( const Point<Number> &_point ) const {
        return content.contains(_point);
    }
    
    template <typename Number>
    bool SupportFunction<Number>::contains( const vector_t<Number> &_point ) const {
        return content.contains(_point);
    }
    
    template <typename Number>
    SupportFunction<Number>  SupportFunction<Number>::unite( SupportFunction<Number> &_rhs ) const {
        SupportFunction<Number> res = SupportFunction<Number>(content.unite(_rhs.content));
        return res;
    }
    
    template <typename Number>
    SupportFunction<Number> SupportFunction<Number>::scale( const Number &_factor ) const {
        SupportFunction<Number> res = SupportFunction<Number>(content.scale( _factor));
        return res;
    }
    
    template <typename Number>
    bool SupportFunction<Number>::empty() const {
        return content.empty();
    }
    
    template <typename Number>
    void SupportFunction<Number>::print() const {
        return content.print();
    }
    
    
    
    
    
} //namespace