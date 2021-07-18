#pragma once
#include "Starset.h"

namespace hypro {

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT() 
:mCenter(0), mLimits(0), mGenerator(0,0), mShapeMatrix(0,0){
}

//regular Starset constructor
template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT(const vector_t<Number>& center,const matrix_t<Number>& shapematrix,const vector_t<Number>& limits,const matrix_t<Number>& generator)
:mCenter(center),mShapeMatrix(shapematrix),mGenerator(generator),mLimits(limits)
{
    //checking if the dimensions match
    assert(limits.rows() == shapematrix.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
    assert(generator.rows()==center.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
    assert(center.rows()==shapematrix.cols());
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( const StarsetT<Number, Converter, Setting>& orig ) {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( StarsetT<Number, Converter, Setting>&& orig ) {
}

//new getters
template <typename Number, typename Converter, typename Setting>
vector_t<Number> StarsetT<Number, Converter, Setting>::center() const {
    return mCenter;
}
template <typename Number, typename Converter, typename Setting>
vector_t<Number> StarsetT<Number, Converter, Setting>::limits() const {
    return mLimits;
}
template <typename Number, typename Converter, typename Setting>
matrix_t<Number> StarsetT<Number, Converter, Setting>::shape() const {
    return mShapeMatrix;
}
template <typename Number, typename Converter, typename Setting>
matrix_t<Number> StarsetT<Number, Converter, Setting>::generator() const {
    return mGenerator;
}

template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::empty() const {
    //to polytope without basis for more efficiency then check if empty
    auto intermediate=Converter::toHPolytope(*this );
    return intermediate.empty();

}

template <typename Number, typename Converter, typename Setting>
Number StarsetT<Number, Converter, Setting>::supremum() const {
    
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> StarsetT<Number, Converter, Setting>::vertices( const matrix_t<Number>& m ) const {
    auto intermediate=Converter::toHPolytope(*this );
    return intermediate.vertices();
}

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> StarsetT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> StarsetT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
}

template <typename Number, typename Converter, typename Setting>
std::size_t StarsetT<Number, Converter, Setting>::dimension() const {
    return mGenerator.rows();
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::removeRedundancy() {
}

template <typename Number, typename Converter, typename Setting>
std::size_t StarsetT<Number, Converter, Setting>::size() const {
}

template <typename Number, typename Converter, typename Setting>
const StarsetT<Number, Converter, Setting>& StarsetT<Number, Converter, Setting>::reduceNumberRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting>> StarsetT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
    StarsetT<Number, Converter, Setting> tmp =this->intersectHalfspace(rhs);
    if(!tmp->empty()){
        if(tmp->contains(this)){
            return std::make_pair( CONTAINMENT::FULL, std::move( tmp ) );
        }
        return std::make_pair( CONTAINMENT::PARTIAL, std::move( tmp ) );
    }
    else{
        return std::make_pair( CONTAINMENT::NO, std::move( tmp ) );
    }
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting>> StarsetT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
    StarsetT<Number, Converter, Setting> star=this->intersectHalfspaces(_mat ,_vec);
    if(!star->empty()){
        if(star->contains(this)){
            return std::make_pair( CONTAINMENT::FULL, std::move( star ) );
        }
        return std::make_pair( CONTAINMENT::PARTIAL, std::move( star ) );
    }
    else{
        return std::make_pair( CONTAINMENT::NO, std::move( star ) );
    }
}
    
template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
    matrix_t<Number> newGenerator = matrix_t<Number>(mGenerator.rows(),mGenerator.cols());
    newGenerator=A*mGenerator;
    return StarsetT<Number, Converter, Setting>(mCenter,mShapeMatrix,mLimits,newGenerator);
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
    vector_t<Number> newCenter=A*mCenter + b;
    matrix_t<Number> newGenerator=A*mGenerator;
    return StarsetT<Number, Converter, Setting>(newCenter,mShapeMatrix,mLimits,newGenerator);
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::minkowskiSum( const StarsetT<Number, Converter, Setting>& rhs ) const {
     //assuming same dimension
    matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(mGenerator.rows(),mGenerator.cols()+rhs.generator().cols()); 
    matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(mShapeMatrix.rows()+rhs.shape().rows(),mShapeMatrix.cols()+rhs.shape().cols());
    vector_t<Number> newmLimits=vector_t<Number>::Zero(mLimits.rows()+rhs.limits().rows());
    //setting new generator matrix
    newmGenerator.block(0,0,mGenerator.rows(),mGenerator.cols())=mGenerator;
    newmGenerator.block(0, mGenerator.cols(), rhs.generator().rows() , rhs.generator().cols())=rhs.generator();
    //setting new shape Matrix matrix
    newmShapeMatrix.topLeftCorner(mShapeMatrix.rows(),mShapeMatrix.cols())=mShapeMatrix;
    newmShapeMatrix.bottomRightCorner(rhs.shape().rows(),rhs.shape().cols())=rhs.shape();
    //setting new limits vector
    newmLimits.head(mLimits.rows())=mLimits;
    newmLimits.tail(rhs.limits().rows())=rhs.limits();
    //setting new center 
    vector_t<Number> newmCenter=mCenter+rhs.center();
    return StarsetT<Number, Converter, Setting>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator);
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersect( const StarsetT<Number, Converter, Setting>& rhs ) const {
    auto intermediate  = Converter::toHPolytope(*this );
    auto intermediate2 = Converter::toHPolytope(rhs );
    return Converter::toStarset(intermediate.intersect(intermediate2));
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
    matrix_t<Number> newmShapeMatrix=matrix_t<Number>(mShapeMatrix.rows()+1,mShapeMatrix.cols()); //rows+1 to add the halfspace constraint
    vector_t<Number> newmLimits=vector_t<Number>(mLimits.rows()+1);
    newmShapeMatrix.block(0,0,mShapeMatrix.rows(),mShapeMatrix.cols())=mShapeMatrix;
    newmLimits.head(mLimits.rows())=mLimits;
    newmShapeMatrix.block(newmShapeMatrix.rows()-1,0, 1,mShapeMatrix.cols())=(hspace.normal().transpose()*mGenerator);
    //added the right side here
    matrix_t<Number> temp=matrix_t<Number>(1,1);
    temp(0,0)=hspace.offset();
    newmLimits(newmLimits.rows()-1)=(temp-(hspace.normal().transpose())*(mCenter))(0,0);
    
    return StarsetT<Number, Converter, Setting>(mCenter,newmShapeMatrix,newmLimits,mGenerator);
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
    StarsetT<Number, Converter, Setting> star= StarsetT<Number, Converter, Setting>(mCenter,mShapeMatrix,mLimits,mGenerator);
    for(int i=0;i<_mat.rows();i++){
        star=star.intersectHalfspace(Halfspace<Number>(_mat.row(i),_vec(i)));
    }
    return star;
}

template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
    auto intermediate=Converter::toHPolytope(*this );
    return intermediate.contains(point);
}

template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::contains( const StarsetT<Number, Converter, Setting>& Starset ) const {
    auto intermediate=Converter::toHPolytope(*this );
    auto rhs=Converter::toHPolytope(Starset);
    return intermediate.contains(rhs);
}
template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::unite( const StarsetT<Number, Converter, Setting>& rhs ) const {
    /*The method implemented here is similat to the method proposed by
     * Prof. Girard for Zonotope.
     * Reachability of Uncertain Linear Systems Using
     *      Zonotopes, Antoin Girard, HSCC2005 
     * Output is an overapproximation of convex hull of two star sets
     * Explanation for this method is written in Bachelor thesis of Dogu Tamgac*/
     
     //Assuming same dimension
     matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(mGenerator.rows(),mGenerator.cols()+rhs.generator().cols()); 
     matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(mShapeMatrix.rows()+rhs.shape().rows(),mShapeMatrix.cols()+rhs.shape().cols());
     vector_t<Number> newmLimits=vector_t<Number>::Zero(mLimits.rows()+rhs.limits().rows());
    
     vector_t<Number> newmCenter=mCenter-rhs.center();
     newmGenerator.block(0,0,mGenerator.rows(),mGenerator.cols())=mGenerator;
     newmGenerator.block(0, mGenerator.cols(), rhs.generator().rows() , rhs.generator().cols())=-rhs.generator();
     
     newmShapeMatrix.topLeftCorner(mShapeMatrix.rows(),mShapeMatrix.cols())=mShapeMatrix;
     newmShapeMatrix.bottomRightCorner(rhs.shape().rows(),rhs.shape().cols())=rhs.shape();
     
     newmLimits.head(mLimits.rows())=mLimits;
     newmLimits.tail(rhs.limits().rows())=rhs.limits();
     
     return this->minkowskiSum( StarsetT<Number, Converter, Setting>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator) );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::unite( const std::vector<StarsetT<Number, Converter, Setting>>& Starsets ) {
    StarsetT<Number, Converter, Setting> star= StarsetT<Number, Converter, Setting>(Starsets[0].center(),Starsets[0].shape(),Starsets[0].limits(),Starsets[0].generator());
    for(int i=1;i<Starsets.size();i++){
        star=star.unite(Starsets[i]);
    }
    return star;
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::reduceRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::clear() {
}

}  // namespace hypro
