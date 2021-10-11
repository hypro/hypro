#pragma once
#include "Starset.h"

namespace hypro {


template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT() 
:mCenter(vector_t<Number>::Zero(1)) ,mGenerator(matrix_t<Number>::Zero(1,1)),constraints(){
    //std::cout<<"star1"<<std::endl;
    
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const vector_t<Number>& center,const matrix_t<Number>& shapematrix,const vector_t<Number>& limits,const matrix_t<Number>& generator)
:mCenter(center),mGenerator(generator), constraints(shapematrix,limits)
{
    //std::cout<<"star2"<<std::endl;
    //checking if the dimensions match
   /* assert(mLimits.rows() == mShapeMatrix.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
    assert(mGenerator.rows()==mCenter.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
    assert(mCenter.rows()==mShapeMatrix.cols());*/
}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const vector_t<Number>& center,const matrix_t<Number>& generator, const Representation Constraints)
:mCenter(center),mGenerator(generator), constraints(Constraints)
{
    //std::cout<<"starmeineee"<<std::endl;
}
//only with
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const matrix_t<Number>& shapematrix,const vector_t<Number>& limits)
:mCenter(vector_t<Number>::Zero(shapematrix.cols())),mGenerator(matrix_t<Number>::Identity(shapematrix.cols(),shapematrix.cols())),constraints(shapematrix,limits)
{

    //checking if the dimensions match
    //std::cout<<"star3"<<std::endl;

   // assert(mLimits.rows() == mShapeMatrix.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
   // assert(mGenerator.rows()==mCenter.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
   // assert(mCenter.rows()==mShapeMatrix.cols());
}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(Representation Constraints)
:mCenter(vector_t<Number>::Zero(Constraints.matrix().cols())),mGenerator(matrix_t<Number>::Identity(Constraints.matrix().cols(),Constraints.matrix().cols())),constraints(Constraints)
{

    //checking if the dimensions match
    //std::cout<<"star3"<<std::endl;

   // assert(mLimits.rows() == mShapeMatrix.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
   // assert(mGenerator.rows()==mCenter.rows() && "ShapeMatrix and mLimits have to have same dimensionality.");
   // assert(mCenter.rows()==mShapeMatrix.cols());
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT( const StarsetT<Number, Converter, Setting,Representation>& orig ) 
    :GeometricObjectBase(orig),
    mCenter(orig.center()),mGenerator(orig.generator()),constraints(orig.constraintss())
{
   //std::cout<<"copy"<<std::endl;
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT( StarsetT<Number, Converter, Setting,Representation>&& orig )
    :GeometricObjectBase(orig),
    mCenter(orig.center()),mGenerator(orig.generator()),constraints(orig.constraintss())
    {
    
     //std::cout<<"move"<<std::endl;


}

//new getters
template <typename Number, typename Converter, typename Setting, class Representation>
vector_t<Number> StarsetT<Number, Converter, Setting,Representation>::center() const {
    return mCenter;
}
template <typename Number, typename Converter, typename Setting, class Representation>
vector_t<Number> StarsetT<Number, Converter, Setting,Representation>::limits() const {
    return constraints.vector();
}
template <typename Number, typename Converter, typename Setting, class Representation>
matrix_t<Number> StarsetT<Number, Converter, Setting,Representation>::shape() const {
    return constraints.matrix();
}
template <typename Number, typename Converter, typename Setting, class Representation>
matrix_t<Number> StarsetT<Number, Converter, Setting,Representation>::generator() const {
    return mGenerator;
}

template <typename Number, typename Converter, typename Setting, class Representation>
Representation StarsetT<Number, Converter, Setting,Representation>::constraintss() const {
    return constraints;
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::empty() const {
    //to polytope without basis for more efficiency then check if empty
    if(mGenerator.isZero(0.0000001)){
        return 1;
    }
    //StarsetT<Number, Converter, Setting,Representation> star2=StarsetT<Number, Converter, Setting,Representation>(constraints) ;

    //auto intermediate=Converter::toHPolytope( star2 );

    //std::cout<<"EMPTY="<<intermediate.empty()<<std::endl;
    return constraints.empty();

}

template <typename Number, typename Converter, typename Setting, class Representation>
Number StarsetT<Number, Converter, Setting,Representation>::supremum() const {
    //std::cout<<"sup"<<std::endl;
    
}

template <typename Number, typename Converter, typename Setting, class Representation>
std::vector<Point<Number>> StarsetT<Number, Converter, Setting,Representation>::vertices() const {
    //std::cout<<"vertices"<<std::endl;
    auto placeholder= constraints.vertices();

	for ( auto point : placeholder ) {
        point=point.affineTransformation(mGenerator.transpose(),mCenter);
    }
    return placeholder;
}

template <typename Number, typename Converter, typename Setting, class Representation>
EvaluationResult<Number> StarsetT<Number, Converter, Setting,Representation>::evaluate( const vector_t<Number>& _direction, bool ) const {
    //std::cout<<"evaluate"<<std::endl;
}

template <typename Number, typename Converter, typename Setting, class Representation>
std::vector<EvaluationResult<Number>> StarsetT<Number, Converter, Setting,Representation>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
    //std::cout<<"evaluate2"<<std::endl;

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::size_t StarsetT<Number, Converter, Setting,Representation>::dimension() const {
    return mGenerator.rows();
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::removeRedundancy() {
    auto intermediate=Converter::toHPolytope(*this );
    intermediate=intermediate.removeRedundancy();
    auto tmp=Converter::toStarset(intermediate);
    return tmp;
}

template <typename Number, typename Converter, typename Setting, class Representation>
std::size_t StarsetT<Number, Converter, Setting,Representation>::size() const {
    //std::cout<<"size"<<std::endl;

    return 1;
}

template <typename Number, typename Converter, typename Setting, class Representation>
const StarsetT<Number, Converter, Setting,Representation>& StarsetT<Number, Converter, Setting,Representation>::reduceNumberRepresentation() {
    //std::cout<<"reduce"<<std::endl;

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting,Representation>> StarsetT<Number, Converter, Setting,Representation>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
    //std::cout<<"satisfies one"<<std::endl;
    //satisfiesda cevir halfspacei ayni koordinatta yaz hpolye ver
    StarsetT<Number, Converter, Setting,Representation> star=this->intersectHalfspace(rhs);
    StarsetT<Number, Converter, Setting,Representation> star2=StarsetT<Number, Converter, Setting,Representation>(constraints) ;

    auto intermediate  = Converter::toHPolytope(star2);
    //std::cout<<std::get<0>(intermediate.satisfiesHalfspace(calculateHalfspace(rhs)))<<std::endl;
    return std::make_pair(std::get<0>(intermediate.satisfiesHalfspace(star.calculateHalfspace(rhs))),std::move( star ));
}

template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting,Representation>> StarsetT<Number, Converter, Setting,Representation>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
    //std::cout<<"satisfies half"<<_mat<<std::endl;
    //std::cout<<"satisfies half"<<_vec<<std::endl;
    if(this->empty()){
        //std::cout<<"yirmak"<<std::endl;
        return std::make_pair( CONTAINMENT::NO, std::move(*this ) );
    }
    StarsetT<Number, Converter, Setting,Representation> star2=StarsetT<Number, Converter, Setting,Representation>(constraints) ;
    auto intermediate  = Converter::toHPolytope(star2 );
    auto zz=this->calculateHalfspaces(_mat ,_vec);
    auto res=std::get<0>(intermediate.satisfiesHalfspaces(std::get<0>(zz),std::get<1>(zz)));

    StarsetT<Number, Converter, Setting,Representation> star=this->intersectHalfspaces(_mat ,_vec);
    if(CONTAINMENT::NO==res){
        //std::cout<<"No1"<<std::endl;
        //std::cout<< "bu center    " << star.center()<<std::endl;
        //std::cout<< "bu generator " << star.generator()<<std::endl;
        //std::cout<< "bu generator " << star.shape()<<std::endl;
        return std::make_pair( CONTAINMENT::NO, std::move( star ) );
    }
    
    /*
    //std::cout<< "bu calculate " <<std::get<1>(zz)<<std::endl;
    //std::cout<< "bu intersect " << star.limits()<<std::endl;
    //std::cout<< "bu center    " << star.center()<<std::endl;
    //std::cout<< "bu generator " << star.generator()<<std::endl;
    */
    //std::cout<<res<<std::endl;
    if(CONTAINMENT::FULL==res){
        //std::cout<<"Full"<<std::endl;
        return  std::make_pair( res,star);
    }
    else{
        //std::cout<<"Partial"<<std::endl;
        return std::make_pair( res, std::move( star ));
    }
}
    
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::projectOn( const std::vector<std::size_t>& dimensions ) const {
    //std::cout<<"proj"<<std::endl;

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::linearTransformation( const matrix_t<Number>& A ) const {
    //std::cout<<"linear"<<std::endl;
    matrix_t<Number> newGenerator = matrix_t<Number>(mGenerator.rows(),mGenerator.cols());
    newGenerator=A*mGenerator;
    vector_t<Number> newCenter=A*mCenter;
    return StarsetT<Number, Converter, Setting,Representation>(newCenter,newGenerator,constraints);
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
    //std::cout<<"A= "<<A<<std::endl;
  //  //std::cout<<"Generator= "<<mGenerator<<std::endl;
    //std::cout<<"affine"<<std::endl;
    if(A.isZero(0.00001)){
        //std::cout<<"girdim"<<std::endl;

        auto intermediate  = Converter::toHPolytope(*this );
        intermediate=intermediate.affineTransformation(A,b);
        return Converter::toStarset(intermediate);
    }

    matrix_t<Number> newGenerator=(A.transpose()*mGenerator);

    if ( !this->empty()){
        StarsetT<Number, Converter, Setting,Representation> tmp=StarsetT<Number, Converter, Setting,Representation>(A*(mCenter)+b,newGenerator,constraints);

        return tmp;
    }
    return *this;
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::minkowskiSum( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
     //assuming same dimension
    //std::cout<<" minkows"<<std::endl;

    //std::cout<< "bu intersect " << this->limits()<<std::endl;
    //std::cout<< "bu center    " << this->center()<<std::endl;
    //std::cout<< "bu generator " << this->generator()<<std::endl;
    //std::cout<< "bu generator " << this->shape()<<std::endl;
    if(rhs.dimension()==0){
        return *this;
    }
    if(this->dimension()==0){
        return rhs;
    }
    auto intermediate=Converter::toHPolytope(*this );
    auto intermediate2=Converter::toHPolytope(rhs );
    return Converter::toStarset(intermediate.minkowskiSum(intermediate2));

    //ilk minkowski kontrol et aynisi varsa ekleme insert diye fonksiyon yazabilirsin belki intersect icin de
    /*matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(mGenerator.rows(),mGenerator.cols()+rhs.generator().cols()); 
    matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(mShapeMatrix.rows()+rhs.shape().rows(),mShapeMatrix.cols()+rhs.shape().cols());
    vector_t<Number> newmLimits=vector_t<Number>::Zero(mLimits.rows()+rhs.limits().rows());
    
    //setting new generator matrix
    newmGenerator.block(0,0,mGenerator.rows(),mGenerator.cols())=mGenerator;
    newmGenerator.block(0, mGenerator.cols(), rhs.generator().rows() , rhs.generator().cols())=rhs.generator();
  
    //setting new shape Matrix  
    newmShapeMatrix.topLeftCorner(mShapeMatrix.rows(),mShapeMatrix.cols())=mShapeMatrix;
    newmShapeMatrix.bottomRightCorner(rhs.shape().rows(),rhs.shape().cols())=rhs.shape();
    
    //setting new limits vector
    newmLimits.head(mLimits.rows())=mLimits;
    newmLimits.tail(rhs.limits().rows())=rhs.limits();
   
    //setting new center
    vector_t<Number> newmCenter=mCenter+rhs.center();
    
    auto intermediate=Converter::toHPolytope(*this );

    auto intermediate2=Converter::toHPolytope(rhs );

    return StarsetT<Number, Converter, Setting,Representation>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator).removeRedundancy();
  */  
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersect( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
    //std::cout<<"intersect stars"<<std::endl;

    auto intermediate  = Converter::toHPolytope(*this );
    auto intermediate2 = Converter::toHPolytope(  rhs );
    return Converter::toStarset(intermediate.intersect(intermediate2)).removeRedundancy();
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
    //std::cout<<"intersect  "<<std::endl;
    auto intermediate=this->calculateHalfspace(hspace);
	return StarsetT<Number, Converter, Setting,Representation>(mCenter,mGenerator, constraints.intersectHalfspace(intermediate));
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
    //std::cout<<"intersect halfspaces"<<std::endl;

    StarsetT<Number, Converter, Setting,Representation> star= StarsetT<Number, Converter, Setting,Representation>(this->center(),this->generator(),this->constraintss());
    for(int i=0;i<_mat.rows();i++){
        star=star.intersectHalfspace(Halfspace<Number>(_mat.row(i),_vec(i)));
    }
    StarsetT<Number, Converter, Setting,Representation> star2= StarsetT<Number, Converter, Setting,Representation>(star.shape(),star.limits());
    star2=star2.removeRedundancy();
    return StarsetT<Number, Converter, Setting,Representation>(star.center(),star.generator(),star2.constraintss());
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::contains( const Point<Number>& point ) const {
    //std::cout<<"point"<<point<<std::endl;
    //pointi benim koordinatta yaz matrixim carp sonra icinde mi diye ver 
    auto intermediate=Converter::toHPolytope(*this );
    return constraints.contains(point.affineTransformation(this->generator().transpose(),mCenter));
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::contains( const StarsetT<Number, Converter, Setting,Representation>& Starset ) const {
    //std::cout<<"containstar"<<std::endl;
    auto intermediate=Converter::toHPolytope(*this );
    auto rhs=Converter::toHPolytope(Starset);
    return intermediate.contains(rhs);
}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::unite( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
    /*The method implemented here is similar to the method proposed by
     * Prof. Girard for Zonotope.
     * Reachability of Uncertain Linear Systems Using
     *      Zonotopes, Antoin Girard, HSCC2005 
     * Output is an overapproximation of convex hull of two star sets
     * Explanation for this method is written in Bachelor thesis of Dogu Tamgac*/
    //std::cout<<"unite"<<std::endl;
    auto intermediate=Converter::toHPolytope(*this );
    auto intermediate2=Converter::toHPolytope(rhs );
    return Converter::toStarset(intermediate.unite(intermediate2));
/*
    //std::cout<< "bu intersect " << this->limits()<<std::endl;
    //std::cout<< "bu center    " << this->center()<<std::endl;
    //std::cout<< "bu generator " << this->generator()<<std::endl;
    //std::cout<< "bu generator " << this->shape()<<std::endl;
    return Converter::toStarset(intermediate.unite(intermediate2).removeRedundancy());
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
     return rhs.minkowskiSum( StarsetT<Number, Converter, Setting,Representation>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator)).removeRedundancy() ;
*/
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::unite( const std::vector<StarsetT<Number, Converter, Setting,Representation>>& Starsets ) {
    //std::cout<<"unite"<<std::endl;
    StarsetT<Number, Converter, Setting,Representation> star= StarsetT<Number, Converter, Setting,Representation>(Starsets[0].center(),Starsets[0].generator(),Starsets[0].constraintss());
    for(int i=1;i<Starsets.size();i++){
        star=star.unite(Starsets[i]);
    }
    return star;
}

template <typename Number, typename Converter, typename Setting, class Representation>
void StarsetT<Number, Converter, Setting,Representation>::reduceRepresentation() {
  
}
template <typename Number, typename Converter, typename Setting, class Representation>
 Halfspace<Number> StarsetT<Number, Converter, Setting,Representation>::calculateHalfspace( const Halfspace<Number>& hspace ) const{
    matrix_t<Number> temp=matrix_t<Number>(1,1);
    temp(0,0)=hspace.offset();
    Halfspace<Number> hp1(hspace.normal().transpose()*this->generator().transpose(),(temp-(hspace.normal().transpose())*(this->center()))(0,0) );
    return hp1;
 }
template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<matrix_t<Number>, vector_t<Number>> StarsetT<Number, Converter, Setting,Representation>::calculateHalfspaces(const matrix_t<Number>& _mat, const vector_t<Number>& _vec  ) const{
    matrix_t<Number> temp=matrix_t<Number>(_mat.rows(),_mat.cols());
    vector_t<Number> temp2=vector_t<Number>(_mat.rows());
    for(int i=0; i<_mat.rows(); i++){
        Halfspace<Number> hp1(_mat.row(i), Number(_vec(i)) );
        auto tmp=this->calculateHalfspace(hp1);
        temp.row(i)=tmp.normal();
        temp2(i)=Number(tmp.offset());
    }
    return std::make_pair(temp,temp2);
}

template <typename Number, typename Converter, typename Setting, class Representation>
void StarsetT<Number, Converter, Setting,Representation>::clear() {
   // //std::cout<<"clear"<<std::endl;

}

}  // namespace hypro
